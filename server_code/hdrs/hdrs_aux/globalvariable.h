#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#include <pthread.h>

#include "../../hdrs/hdrs_structs/structs_server.h"

extern int* server;

extern dbtask* db_queue_head;
extern dbtask* db_queue_tail;

extern packagelist* pkglist_queue_head;
extern packagelist* pkglist_queue_tail;

extern pthread_mutex_t db_mutex;
extern pthread_cond_t db_cond;
extern pthread_mutex_t send_mutex;
extern pthread_cond_t send_cond;

#endif