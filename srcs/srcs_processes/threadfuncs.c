#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <sys/socket.h>

#include "../../hdrs/hdrs_aux/globalvariables.h"
#include "../../hdrs/hdrs_structs/structs_server.h"

void* sendpkg_worker(void* arg) {
    int cli_socket = (int)&arg;
    
    while(*game) {
        pthread_mutex_lock(&send_mutex);

        while(!pkg_queue_head) {
            pthread_cond_wait(&send_cond, &send_mutex);
            if(!(*game)) {
                free_sendtask(pkg_queue_head);
                return NULL;
            }
        }

        package* task = pkg_queue_head;
        pkg_queue_head = task->next;
        if(!pkg_queue_head) pkg_queue_tail = NULL;

        pthread_mutex_unlock(&send_mutex); 

        if(send(cli_socket, task, sizeof(*task), 0) < 0) {
            fprintf(stderr, "[ERROR] Failed to send Package (Type: %d)\n", task->type);
        }
        
        free(task); 
    }

    return NULL;
}

void* recvpkg_worker(void* arg) {
    int cli_socket = (int)&arg;

    package* pkg_recv = (package*)malloc(sizeof(package));
    while(*game) {
        if(recv(cli_socket, pkg_recv, sizeof(*pkg_recv), 0) < 0) {
            //ERROR
        }

        switch(pkg_recv->type) {
            case PKG_HB:
                package* pkg_hb_send = (package*)malloc(sizeof(package));

                pkg_hb_send->data.ui.adventurer = NULL;
                pkg_hb_send->type = PKG_HB;

                pthread_mutex_lock(&send_mutex);

                if(!pkg_queue_tail) { 
                    pkg_queue_head = pkg_hb_send;
                    pkg_queue_tail = pkg_hb_send;
                } else {
                    pkg_queue_tail->next = pkg_hb_send;
                    pkg_queue_tail = pkg_hb_send;
                }

                pthread_cond_signal(&send_cond);
                pthread_mutex_unlock(&send_mutex);

                break;
        }


    }
    free(pkg_recv);

    return NULL;
}