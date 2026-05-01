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

void free_sendtask(package* pkg_queue_head) {
    package* tmp = pkg_queue_head;

    while(tmp != NULL) {
        package* next_node = tmp->next; 
        free(tmp); 
        tmp = next_node;
    }
    
    return;
}

void freeht(hashtable* ht) {
    for(int s = 0; s < TABLE_SIZE; s++) {
        entry* aux = ht->buckets[s];
        while(aux) {
            entry* tmp = aux;
            aux = aux->next;
            free_adv(tmp->adventurer);
            free(tmp);
        }
    }
    
    free(ht->buckets);
    free(ht);

    return;
}



