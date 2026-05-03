#include <stdio.h>
#include <stdlib.h>

#include "../../hdrs/hdrs_structs/structs_hash.h"
#include "../../hdrs/hdrs_structs/structs_server.h"

#define TABLE_SIZE 167

void free_adv(adv* a) {
    free(a->equipment->h_s);
    free(a->equipment->c_s);
    free(a->equipment->a_s);
    free(a->equipment->b_s);
    free(a->equipment->w_s);

    free(a->equipment);
    free(a->stats);
    free(a->moves);
    free(a);

    return;
}

void free_dbtask(dbtask* db_queue_head) {
    dbtask* tmp = db_queue_head;

    while(tmp != NULL) {
        dbtask* next_node = tmp->next; 
        free(tmp); 
        tmp = next_node;
    }
    
    return;
}

void free_sendtask(packagelist* pkglist_queue_head) {
    packagelist* tmp = pkglist_queue_head;

    while(tmp != NULL) {
        packagelist* next_node = tmp->next; 
        free(tmp); 
        tmp = next_node;
    }
    
    return;
}


