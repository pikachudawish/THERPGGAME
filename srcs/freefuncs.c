#include <stdio.h>
#include <stdlib.h>

#include "structs_hash.h"

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



