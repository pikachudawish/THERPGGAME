#ifndef STRUCTS_HASH_H
#define STRUCTS_HASH_H

#define TABLE_SIZE 167

#include "structs_adv.h"

typedef struct _entry {
    int adv_id;
    adv adventure;
} entry;

typedef struct _hashtable {
    entry** buckets;
} hashtable;

#endif