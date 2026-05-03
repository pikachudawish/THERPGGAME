#include <stdio.h>
#include <pthread.h>

#include "../../hdrs/hdrs_aux/globalvariable.h"

int* server = NULL;

pthread_mutex_t db_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t db_cond = PTHREAD_COND_INITIALIZER;

pthread_mutex_t send_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t send_cond = PTHREAD_COND_INITIALIZER;

packagelist* pkglist_queue_head = NULL;
packagelist* pkglist_queue_tail = NULL;

dbtask* db_queue_head = NULL;
dbtask* db_queue_tail = NULL;