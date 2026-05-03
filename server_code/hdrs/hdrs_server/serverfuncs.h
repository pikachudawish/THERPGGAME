#ifndef SERVERFUNCS_H
#define SERVERFUNCS_H

#include <poll.h>

#define PORT 6767

#define POLLSIZE 512
#define TIMEOUT_POLL 10000

int server_init();
int server_loop();
void free_server(_cliinfo* fdinfo, package* pkg, int pollsize);

#endif