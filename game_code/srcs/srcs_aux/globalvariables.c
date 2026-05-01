#include <stdio.h>
#include <pthread.h>

#include "../../hdrs/hdrs_structs/structs_adv.h"
#include "../../hdrs/hdrs_structs/structs_server.h"

int* game = NULL;

user_info* currAcc = NULL;

package* pkg_queue_head = NULL;
package* pkg_queue_tail = NULL;

pthread_mutex_t send_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t send_cond = PTHREAD_COND_INITIALIZER;