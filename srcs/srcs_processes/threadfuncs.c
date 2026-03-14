#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../../hdrs/hdrs_aux/globalvariables.h"
#include "../../hdrs/hdrs_structs/structs_server.h"

void* sendpkg_worker(void* arg) {
    int cli_socket = (int)&arg;
    
    while(*game || (pkg_queue_head != NULL)) {
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

        switch(task->type) {
            case PKG_GET_ADV:
                if(send(cli_socket, task, sizeof(*task), 0) < 0) {
                    //ERROR
                }
                break;
            
        }
        
        free(task); 
    }

    return NULL;
}