#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/socket.h>

#include "../../hdrs/hdrs_structs/structs_adv.h"
#include "../../hdrs/hdrs_structs/structs_server.h"

int createAcc() {


    return 1;
}

user_info* logIn() {
    user_info* userAcc = NULL;

    return 1;
} 

adv* getAdv(int cli_socket) {
    adv* currAdv = (adv*)malloc(sizeof(adv));

    if(send(cli_socket, &(package){.type = PKG_GET_ADV, .data = NULL}, sizeof(package), 0) == -1) {
        return NULL;
    } 

    package pkg_adv = {.type = 0, .data = NULL, .size = 0};
    if(recv(cli_socket, &pkg_adv, sizeof(package), 0) == -1) {
        return NULL;
    }
    

    return currAdv;
}