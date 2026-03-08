#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sys/socket.h>

#include "../../hdrs/hdrs_structs/structs_adv.h"
#include "../../hdrs/hdrs_structs/structs_server.h"

#include "../../hdrs/hdrs_game/gameauxfuncs.h"

#define GAMENAME "idk"

int gameintro(int cli_socket) {
    printf("\n\nWELCOME TO THE VIBRANT WORLD OF %s!", GAMENAME);
    printf("\nDo you already have an account or do you want to create one?");
    printf("\nOptions: \n1. Log in\n2. Create Account");

    int playeropt = 0;
    while(!playeropt) {
        printf("\n->> ");
        if(scanf("%d", playeropt) != 1 || (playeropt != 1 && playeropt != 2)) {
            printf("\nDear Adventure, please choose between Log In (1) and Create Account (2)!");
        }
    }

    switch(playeropt) {
        case 1:
            if(!logIn(cli_socket)) {
                
            }

            break;
            
        case 2:
            createAcc(cli_socket);
            
            break;
    }

    return 1;
}

int gameloop(int cli_socket) {
    time_t last_hb = time(NULL);

    int gl = 1;
    while(gl) {
        time_t now = time(NULL);
        if(difftime(now, last_hb) >= 10) {
            if(send(cli_socket, &(package){.type = PKG_HB}, sizeof(package), 0) == -1) {
                return 0;
            }
            
            last_hb = time(NULL);
        }

      
        
        
        
    }


    return 1;
}
