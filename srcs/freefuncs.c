#include <stdio.h>
#include <stdlib.h>

#include "structs_hash.h"

#define TABLE_SIZE 167

void freeht(hashtable* ht) {
    for(int s = 0; s < TABLE_SIZE; s++) {
        entry* aux = ht->buckets[s];
        while(aux) {
            entry* tmp = aux;
            aux = aux->next;
            free(tmp->adventurer.stats.class);
            free(tmp->adventurer.stats.name);
            free(tmp);
        }
    }
    free(ht);

    return;
}

