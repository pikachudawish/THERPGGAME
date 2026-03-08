#ifndef GAMEAUXFUNCS_H
#define GAMEAUXFUNCS_H

#include "../../hdrs/hdrs_structs/structs_adv.h"

int createAcc(int cli_socket);
int logIn(int cli_socket);
adv* getAdv(int cli_socket);

#endif