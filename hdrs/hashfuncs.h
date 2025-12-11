#ifndef HASHFUNCS_H
#define HASHFUNCS_H

#include "structs_hash.h"

hashtable* create_ht();
unsigned int hash_int(int key);
void ht_insert(hashtable *ht, int key, adv new_adv);
adv ht_get(hashtable *ht, int key);

#endif