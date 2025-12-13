#ifndef HASHFUNCS_H
#define HASHFUNCS_H

#include "structs_hash.h"

hashtable* create_ht();
unsigned int hash_int(int key);
adv* ht_get(hashtable *ht, int key);
int ht_insert(hashtable *ht, adv* new_adv);

#endif