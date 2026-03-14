#ifndef FREEFUNCS_H
#define FREEFUNCS_H

#include "../../hdrs/hdrs_structs/structs_hash.h"
#include "../../hdrs/hdrs_structs/structs_server.h"

void free_sendtask(package* pkg_queue_head);
void freeht(hashtable* ht);
void free_adv(adv* a);

#endif