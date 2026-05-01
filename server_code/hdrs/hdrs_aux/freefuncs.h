#ifndef FREEFUNCS_H
#define FREEFUNCS_H

#include "../../hdrs/hdrs_structs/structs_hash.h"

void free_adv(adv* a);
void free_dbtask(dbtask* db_queue_head);
void free_sendtask(package* pkg_queue_head);

#endif