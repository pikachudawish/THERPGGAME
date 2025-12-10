#include <stdio.h>
#include <stdlib.h>

#include "structs_hash.h"

#define TABLE_SIZE 167

hashtable* create_ht() {
    hashtable* ht = (hashtable*)malloc(sizeof(hashtable));
    if(!ht) return NULL;

    ht->buckets = (entry**)malloc(TABLE_SIZE * sizeof(entry*));
    for(int s = 0; s < TABLE_SIZE; s++) ht->buckets[s] = NULL;

    return ht;
}