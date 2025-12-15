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

int ht_insert(hashtable *ht, adv* new_adv) {
    unsigned int hash = hash_int(new_adv->adv_id);

    entry* new_entry = (entry*)malloc(sizeof(entry));
    if(!new_entry) return 0;

    adv* cpy = (adv*)malloc(sizeof(adv));
    if(!cpy) {
        free(new_entry);
        return 0;
    }
    cpy->adv_id = new_adv->adv_id;

    cpy->stats = (stats*)malloc(sizeof(stats));
    if(!cpy->stats) {
        free(cpy); free(new_entry);
        return 0;
    }
    *(cpy->stats) = *(new_adv->stats);

    cpy->moves = (moves*)malloc(sizeof(moves));
    if(!cpy->moves) {
        free(cpy->stats); free(cpy); free(new_entry);
        return 0;
    }
    *(cpy->moves) = *(new_adv->moves);

    cpy->equipment = (equipment*)malloc(sizeof(equipment));
    if(!cpy->equipment) {
        free(cpy->moves); free(cpy->stats); free(cpy); free(new_entry);
        return 0;
    }

    cpy->equipment->h_s = (helmet_stats*) malloc(sizeof(helmet_stats));
    if(!cpy->equipment->h_s) {
        free(cpy->equipment); free(cpy->moves); free(cpy->stats); free(cpy); free(new_entry);
        return 0;
    }
    *(cpy->equipment->h_s) = *(new_adv->equipment->h_s);

    cpy->equipment->c_s = (chestplate_stats*) malloc(sizeof(chestplate_stats));
    if(!cpy->equipment->c_s) {
        free(cpy->equipment->h_s); free(cpy->equipment); free(cpy->moves);
        free(cpy->stats); free(cpy); free(new_entry);
        return 0;
    }
    *(cpy->equipment->c_s) = *(new_adv->equipment->c_s);

    cpy->equipment->a_s = (armlet_stats*) malloc(sizeof(armlet_stats));
    if(!cpy->equipment->a_s) {
        free(cpy->equipment->c_s); free(cpy->equipment->h_s); free(cpy->equipment);
        free(cpy->moves); free(cpy->stats); free(cpy); free(new_entry);
        return 0;
    }
    *(cpy->equipment->a_s) = *(new_adv->equipment->a_s);

    cpy->equipment->b_s = (boots_stats*) malloc(sizeof(boots_stats));
    if(!cpy->equipment->b_s) {
        free(cpy->equipment->a_s); free(cpy->equipment->c_s); free(cpy->equipment->h_s); free(cpy->equipment);
        free(cpy->moves); free(cpy->stats); free(cpy); free(new_entry);
        return 0;
    }
    *(cpy->equipment->b_s) = *(new_adv->equipment->b_s);

    cpy->equipment->w_s = (weapon_stats*) malloc(sizeof(weapon_stats));
    if(!cpy->equipment->w_s) {
        free(cpy->equipment->b_s); free(cpy->equipment->a_s); free(cpy->equipment->c_s); free(cpy->equipment->h_s);
        free(cpy->equipment); free(cpy->moves); free(cpy->stats); free(cpy); free(new_entry);
        return 0;
    }
    *(cpy->equipment->w_s) = *(new_adv->equipment->w_s);

    new_entry->key = new_adv->adv_id;
    new_entry->adventurer = cpy;
    new_entry->next = ht->buckets[hash];
    ht->buckets[hash] = new_entry;

    return 1;
}

adv* ht_get(hashtable *ht, int key) {
    unsigned int hash = hash_int(key);
    entry *curr = ht->buckets[hash];

    while (curr) {
        if (curr->key == key) {
            return curr->adventurer;
        }
        curr = curr->next;
    }

    return NULL;
}

