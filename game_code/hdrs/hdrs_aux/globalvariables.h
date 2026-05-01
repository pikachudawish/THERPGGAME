#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#include "../../hdrs/hdrs_structs/structs_adv.h"

extern int* game;

extern user_info* currAcc;

extern package* pkg_queue_head;
extern package* pkg_queue_tail;

extern pthread_mutex_t send_mutex;
extern pthread_cond_t send_cond;

#endif