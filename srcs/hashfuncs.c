#include <stdio.h>
#include <stdlib.h>

#include "structs_hash.h"
#include "auxfuncs.h"

#define TABLE_SIZE 167

hashtable* create_ht() {
    hashtable* ht = (hashtable*)malloc(sizeof(hashtable));
    if(!ht) return NULL;

    ht->buckets = (entry**)malloc(TABLE_SIZE * sizeof(entry*));
    if(!ht->buckets) {
        free(ht);
        return NULL;
    }

    for(int s = 0; s < TABLE_SIZE; s++) ht->buckets[s] = NULL;

    return ht;
}

unsigned int hash_int(int key) {
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = (key >> 16) ^ key;
    return key % TABLE_SIZE;
}

void ht_insert(hashtable *ht, adv new_adv) {
    unsigned int hash = hash_int(new_adv.adv_id);

    entry *new_entry = (entry*)malloc(sizeof(entry));
    new_entry->key = new_adv.adv_id;
    new_entry->adventurer = new_adv;

    new_entry->next = ht->buckets[hash];
    ht->buckets[hash] = new_entry;
}

adv ht_get(hashtable *ht, int key) {
    unsigned int hash = hash_int(key);
    entry *curr = ht->buckets[hash];

    while (curr) {
        if (curr->key == key) {
            return curr->adventurer;
        }
        curr = curr->next;
    }

    return (adv){0};
}

