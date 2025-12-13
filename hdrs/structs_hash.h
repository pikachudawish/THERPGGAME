#ifndef STRUCTS_HASH_H
#define STRUCTS_HASH_H

#include "structs_adv.h"

typedef struct _entry {
    int key;
    adv* adventurer;
    struct entry *next;
} entry;

typedef struct _hashtable {
    entry** buckets;
} hashtable;

#endif