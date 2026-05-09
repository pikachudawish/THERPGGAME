#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

#include <mysql/mysql.h>

#include "../../hdrs/hdrs_structs/structs_server.h"
#include "../../hdrs/hdrs_aux/globalvariable.h"
#include "../../hdrs/hdrs_thread/threadfuncs.h"
#include "../../hdrs/hdrs_server/serverfuncs.h"

#define HOST "100.82.64.91"
#define USER "rpggameadm"
#define PASS "Ru@25092006"
#define DBNAME "rpggame"

#define N_THREADS 4

int main() {
    unsigned int timeout = 5;
    MYSQL* conn = mysql_init(NULL);
    if(mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout)) {
        mysql_close(conn);
        return 1;
    }
    if(!mysql_real_connect(conn, HOST, USER, PASS, DBNAME, 3306, NULL, 0)) {
        mysql_close(conn);
        fprintf(stderr, "[ERROR] Couldn't establish a connection with the DataBase");
        return 1;
    }

    server = (int*)malloc(sizeof(int));
    if(!server) {
        mysql_close(conn); 
        return 1;
    }
    *server = 1;

    pthread_t* threads = (pthread_t*)malloc(N_THREADS * sizeof(pthread_t));
    if(!threads) {
        free(server); mysql_close(conn);
        return 1;
    } 
    pthread_create(&threads[0], NULL, commandline, NULL);
    pthread_create(&threads[1], NULL, db_backup, conn);
    pthread_create(&threads[2], NULL, db_worker, conn);
    pthread_create(&threads[3], NULL, sendpkg_worker, NULL);

    if(!server_loop()) {
        fprintf(stdout,"[ERROR] Critical Server Failure\n");
        free(server); mysql_close(conn);

        for(int s = 0; s < N_THREADS; s++) pthread_join(threads[s], NULL);
        free(threads);
        return 1;
    }

    for(int s = 0; s < N_THREADS; s++) pthread_join(threads[s], NULL);  
    free(threads);
    
    free(server);
    mysql_close(conn);

    return 0;
}
