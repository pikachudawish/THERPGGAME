#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <mysql/mysql.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include <netinet/in.h>

#include "../../hdrs/hdrs_structs/structs_server.h"
#include "../../hdrs/hdrs_structs/structs_hash.h"
#include "../../hdrs/hdrs_aux/globalvariable.h"

#include "../../hdrs/hdrs_server/serverfuncs.h"
#include "../../hdrs/hdrs_server/serverauxfuncs.h"
#include "../../hdrs/hdrs_aux/freefuncs.h"
#include "../../hdrs/hdrs_db/dbfuncs.h"

#define TIMEOUT_CLI 30.0

#define LOG_PATH "files/logs_all.txt"
#define LOG_TIMEOUT "files/logs/log_timeout"

int server_init() {
    int serv_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(serv_socket == -1) {
        fprintf(stderr, "[ERROR] Failed to create server socket\n");
        return 0;
    }

    int opt = 1;
    if(setsockopt(serv_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        fprintf(stderr, "[ERROR] Failed to set socket options\n");
        close(serv_socket);
        return 0;
    }
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(serv_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        fprintf(stderr, "[ERROR] Failed to bind IP address of the server\n");
        close(serv_socket);
        return 0;
    }
    if (listen(serv_socket, SOMAXCONN) == -1) {
        fprintf(stderr, "[ERROR] Failed to listen in the defined Port\n");
        close(serv_socket);
        return 0;
    }   

    return serv_socket;
}

int server_loop() {
    int pollsize = POLLSIZE;

    _cliinfo* clinfo = (_cliinfo*)malloc(pollsize * sizeof(_cliinfo));
    if(!clinfo) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (clinfo)\n");
        return 0;
    }

    clinfo->poll = (struct pollfd*)malloc(pollsize * sizeof(struct pollfd));
    if(!clinfo->poll) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (clinfo->poll)");
        free(clinfo);
        return 0;
    }
    for(int s = 0; s < POLLSIZE; s++) clinfo->poll[s].fd = -1;

    int serv_socket = server_init();
    if(!serv_socket) {
        fprintf(stderr, "[ERROR] Failed to get the server's socket\n");
        free(clinfo->poll); free(clinfo);
        return 0;
    }
    clinfo->poll[0].fd = serv_socket;
    clinfo->poll[0].events = POLLIN;

    FILE* log_file = fopen(LOG_PATH, "a");
    if(!log_file) {
        fprintf(stderr, "[ERROR] Failed to open a file (log_file)\n");
        free(clinfo->poll); free(clinfo);
        return 1;
    }
    FILE* timeout_file = fopen(LOG_TIMEOUT, "a");
    if(!timeout_file) {
        fprintf(stderr, "[ERROR] Failed to open a file (timeout_file)\n");
        free(clinfo->poll); free(clinfo);
        return 1;
    }

    clinfo->last_seen = (time_t*)malloc(pollsize * sizeof(time_t));
    if(!clinfo->last_seen) {
        fprintf(stderr, "[ERROR] Failed Memory Allocation (clinfo->last_seen)\n");
        free(clinfo->poll); free(clinfo);
        return 1;
    }
    memset(clinfo->last_seen, 0, pollsize * sizeof(time_t));
    clinfo->last_seen[0] = time(NULL);

    while(*server) {
        int poll_res = 0;
        if((poll_res = poll(clinfo->poll, pollsize, TIMEOUT_POLL)) == -1) {
            fprintf(stderr, "[ERROR] Failed to execute poll()\n");
            server_failure(clinfo, NULL, pollsize); fclose(log_file); fclose(timeout_file);
            return 0;
        }

        time_t now = time(NULL);
        for(int s = 1; s < pollsize; s++) {
            if(clinfo->poll[s].fd == -1) continue;

            double last_interaction  = difftime(now, clinfo->last_seen[s]);
            if(last_interaction <= TIMEOUT_CLI) continue;

            fprintf(timeout_file, "[TIMEOUT] Client %d was disconnected because of inactivity\n", clinfo->poll[s].fd);

            close(clinfo->poll[s].fd);
            clinfo->poll[s].fd = -1;
        }

        for(int s = 0; s < pollsize; s++) {
            if(clinfo->poll[s].fd == -1 || !(clinfo->poll[s].revents & POLLIN)) continue;

            if(clinfo->poll[s].fd == serv_socket) {
                struct sockaddr_in cli_addr;

                socklen_t addr_len = sizeof(cli_addr);
                int new_cli = accept(serv_socket, (struct sockaddr *)&cli_addr, &addr_len);
                if(new_cli < 0) {
                    fprintf(stderr, "[ERROR] Failed to accept new client connection\n");
                    continue;
                }

                for(int r = 0; r < pollsize; r++) {
                    if(clinfo->poll[r].fd != -1) continue;
                    clinfo->poll[r].fd = new_cli;
                    clinfo->poll[r].events = POLLIN;   
                    clinfo->last_seen[r] = time(NULL);
                    break;
                }      
                fprintf(log_file, "[LOG] New Connection on socket %d\n", new_cli);

                if(clinfo->poll[pollsize - 1].fd != -1) {
                    pollsize *= 2;
                    clinfo = (_cliinfo*)realloc(clinfo, pollsize * sizeof(clinfo));
                    if(!clinfo) { 
                        fprintf(stderr, "[ERROR] Failed Memory Reallocation (clinfo)\n");
                        server_failure(clinfo, NULL, pollsize/2);
                        return 0;
                    }
                    clinfo->poll = (struct pollfd*)realloc(clinfo->poll, pollsize * sizeof(struct pollfd));
                    if(!clinfo->poll) {
                        fprintf(stderr, "[ERROR] Failed Memory Reallocation (clinfo->poll)\n");
                        server_failure(clinfo, NULL, pollsize/2);
                        return 0;
                    }
                    clinfo->last_seen = (time_t*)realloc(clinfo->last_seen, pollsize * sizeof(time_t));
                    if(!clinfo->last_seen) {
                        fprintf(stderr, "[ERROR] Failed Memory Reallocation (clinfo->last_seen)\n");
                        server_failure(clinfo, NULL, pollsize);
                        return 0;
                    }
                }
            } else {
                package* pkg = (package*)malloc(sizeof(package));

                int nbytes = recv(clinfo->poll[s].fd, pkg, sizeof(package), 0);
                if(nbytes <= 0) {
                    fprintf(log_file, "[CONNECTION TERMINATED] Client %d disconnected\n", clinfo->poll[s].fd);
                    close(clinfo->poll[s].fd);
                    clinfo->poll[s].fd = -1;
                    continue;
                }

                clinfo->last_seen[s] = time(NULL);

                switch(pkg->type) {
                    case PKG_HB:
                        fprintf(log_file, "[HEARTBEAT] Client %d is still in line\n", clinfo->poll[s].fd);
                        break;
                    case PKG_GET_ADV:
                        if(!pkg_get_adv(clinfo->poll[s].fd, pkg)) {
                            server_failure(clinfo, pkg, pollsize);
                            fclose(timeout_file); fclose(log_file);
                            return 0;
                        }
                        break;                    
                    case PKG_INS_UI:
                        if(!pkg_ins_ui(clinfo->poll[s].fd, pkg)) {
                            server_failure(clinfo, pkg, pollsize);
                            fclose(timeout_file); fclose(log_file);
                            return 0;
                        }
                        break;
                    case PKG_ADD_ADV_TO_USER:
                        if(!pkg_add_adv_to_user(clinfo->poll[s].fd, pkg)) {
                            server_failure(clinfo, pkg, pollsize);
                            fclose(timeout_file); fclose(log_file);
                            return 0;
                        }
                        break;
                    case PKG_INS:
                        if(!pkg_ins(clinfo->poll[s].fd, pkg)) {
                            server_failure(clinfo, pkg, pollsize);
                            fclose(timeout_file); fclose(log_file);
                            return 0;
                        }
                        break;
                    case PKG_UPD_ADV:
                        if(!pkg_upd_adv(clinfo->poll[s].fd, pkg)) {
                            server_failure(clinfo, pkg, pollsize);
                            fclose(timeout_file); fclose(log_file);
                        }
                        break;
                    case PKG_UPD_S:
                        if(!pkg_upd_s(clinfo->poll[s].fd, pkg)) {
                            server_failure(clinfo, pkg, pollsize);
                            fclose(timeout_file); fclose(log_file);
                        }
                        break;
                    case PKG_UPD_M:
                        if(!pkg_upd_m(clinfo->poll[s].fd, pkg)) {
                            server_failure(clinfo, pkg, pollsize);
                            fclose(timeout_file); fclose(log_file);
                        }
                        break;
                    case PKG_UPD_E:
                        if(!pkg_upd_e(clinfo->poll[s].fd, pkg)) {
                            server_failure(clinfo, pkg, pollsize);
                            fclose(timeout_file); fclose(log_file);
                        }
                        break;
                    case PKG_UPD_H:
                        if(!pkg_upd_h(clinfo->poll[s].fd, pkg)) {
                            server_failure(clinfo, pkg, pollsize);
                            fclose(timeout_file); fclose(log_file);
                        }
                        break;
                    case PKG_UPD_C:
                        if(!pkg_upd_c(clinfo->poll[s].fd, pkg)) {
                            server_failure(clinfo, pkg, pollsize);
                            fclose(timeout_file); fclose(log_file);
                        }
                        break;
                    case PKG_UPD_A:
                        if(!pkg_upd_a(clinfo->poll[s].fd, pkg)) {
                            server_failure(clinfo, pkg, pollsize);
                            fclose(timeout_file); fclose(log_file);
                        }
                        break;
                    case PKG_UPD_B:
                        if(!pkg_upd_b(clinfo->poll[s].fd, pkg)) {
                            server_failure(clinfo, pkg, pollsize);
                            fclose(timeout_file); fclose(log_file);
                        }
                        break;
                    case PKG_UPD_W:
                        if(!pkg_upd_w(clinfo->poll[s].fd, pkg)) {
                            server_failure(clinfo, pkg, pollsize);
                            fclose(timeout_file); fclose(log_file);
                        }
                        break;
                    case PKG_RMV:
                        if(!pkg_rmv(clinfo->poll[s].fd, pkg)) {
                            server_failure(clinfo, pkg, pollsize);
                            fclose(timeout_file); fclose(log_file);
                        }
                        break;

                    case PKG_LOGIN_USERINFO:
                        if(!pkg_vrf_ui(clinfo->poll[s].fd, pkg)) {
                            server_failure(clinfo, pkg, pollsize);
                            fclose(timeout_file); fclose(log_file);
                        }
                        break;
                }

                free(pkg);
            }
        }
    }

    for(int s = 0; s < pollsize; s++) if(clinfo->poll[s].fd != -1) close(clinfo->poll[s].fd);
    fclose(log_file);
    fclose(timeout_file);
    
    free(clinfo->poll);
    free(clinfo->last_seen);
    free(clinfo);

    return 1;
}

void server_failure(_cliinfo* clinfo, package* pkg, int pollsize) {
    if(clinfo->last_seen) free(clinfo->last_seen); 
    if(pkg) free(pkg);

    if(clinfo->poll) {
        for(int s = 0; s < pollsize; s++) {
            if(clinfo->poll[s].fd != -1) close(clinfo->poll[s].fd);
        }
        free(clinfo->poll);
    }

    if(clinfo) free(clinfo);

    (*server) = 0;
    pthread_cond_signal(&db_cond);

    fprintf(stderr, "[ERROR] Critical Server Failure! Ending all procedures.\n");
    
    return;
}

