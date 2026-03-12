#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/socket.h>

#include "../../hdrs/hdrs_aux/globalvariables.h"
#include "../../hdrs/hdrs_structs/structs_adv.h"
#include "../../hdrs/hdrs_structs/structs_server.h"

int createAcc(int cli_socket) {
    printf("\n[CREATE] Please Insert the credentials for your new account:");

    int successfulCreate = 0;
    while(!successfulCreate) {
        package pkg_send;
        pkg_send.type = PKG_CREATE_USERINFO;

        printf("\nUsername->> ");
        fgets(pkg_send.data.ui.username, 100, stdin);
        pkg_send.data.ui.username[strcspn(pkg_send.data.ui.username, "\n")] = '\0';

        printf("\nPASSWORD REQUIREMENTS:\n1. Atleast one number\n2. Your Password must contain between 6-12 characters\nPassword->> ");
        
        int acceptedPass = 0; char buffer[100];
        while(!acceptedPass) {
            fgets(buffer, 100, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';

            int hasNum = 0; int lenbuffer = strlen(buffer);
            for(int m = 0; m < lenbuffer; m++) {
                if(buffer[m] >= '0' && buffer[m] <= '9') {
                    hasNum = 1;
                    break;
                }
            }

            if(!hasNum && (lenbuffer < 6 || lenbuffer > 12)) {
                printf("\n\nYour Password doesn't have an number and doesnt meet the lenght requirements. Try again");
                continue;
            } else if(!hasNum) {
                printf("\n\nYour Password must have an number. Try again");
                continue;
            } else if(lenbuffer < 6 || lenbuffer > 12) {
                printf("\n\nYour Password doesn't meet the lenght requirements. Try again");
                continue;
            } else {
                acceptedPass = 1;
            }
        }
        strcpy(pkg_send.data.ui.pass, buffer);

        pkg_send.data.ui.adventurer = NULL;

        if(send(cli_socket, &pkg_send, sizeof(package), 0) == -1) {
            printf("\n[ERROR] Couldn't send pkg from server. Try restarting the game and Contact an Admin to report the issue.");
            printf("\n[ERROR] Critical Game Failure. Shutting down :(\n\n");
            return 0;
        }

        package pkg_recv = {.type = 0, .data = NULL};
        if(recv(cli_socket, &pkg_recv, sizeof(package), 0) == -1) {
            printf("\n[ERROR] Couldn't receive pkg from server. Try restarting the game and Contact an Admin to report the issue.");
            printf("\n[ERROR] Critical Game Failure. Shutting down :(\n\n");
            return 0;
        }

        switch(pkg_recv.type) {
            case PKG_PING_SUCESS:
                currAcc = (user_info*)malloc(sizeof(user_info*));
                if(!currAcc) {
                    printf("\n[ERROR] Insufficient RAM memory available.");
                    printf("\n[ERROR] Critical Game Failure. Shutting down :(\n\n");
                    return NULL;
                }

                *currAcc = pkg_send.data.ui;

                printf("\nThe account was created successfully! Welcome, %d ;)", currAcc->username);

                successfulCreate = 1;
                break;
            case PKG_PING_FAILURE:
                printf("\nThe Username is already taken. Choose Another one");
                break;
            default:
                printf("\n[ERROR] The input from the server is corrupted. Try restarting the game and Contact an Admin to report the issue.");
                printf("\n[ERROR] Critical Game Failure. Shutting down :(\n\n");
                return 0;
        }
    }

    return 1;
}

int logIn(int cli_socket) {
    printf("\n[LOG IN] Please Insert your account credentials:");

    int successfulLogin = 0;
    while(!successfulLogin) {
        package pkg_send;
        pkg_send.type = PKG_LOGIN_USERINFO;

        printf("\nUsername->> ");
        fgets(pkg_send.data.ui.username, 100, stdin);
        pkg_send.data.ui.username[strcspn(pkg_send.data.ui.username, "\n")] = '\0';

        printf("\nPassword->> ");
        fgets(pkg_send.data.ui.pass, 100, stdin);
        pkg_send.data.ui.pass[strcspn(pkg_send.data.ui.pass, "\n")] = '\0';

        pkg_send.data.ui.adventurer = NULL;

        if(send(cli_socket, &pkg_send, sizeof(package), 0) == -1) {
            printf("\n[ERROR] Couldn't send pkg from server. Try restarting the game and Contact an Admin to report the issue.");
            printf("\n[ERROR] Critical Game Failure. Shutting down :(\n\n");
            return 0;
        }

        package pkg_recv = {.type = 0, .data = NULL};
        if(recv(cli_socket, &pkg_recv, sizeof(package), 0) == -1) {
            printf("\n[ERROR] Couldn't receive pkg from server. Try restarting the game and Contact an Admin to report the issue.");
            printf("\n[ERROR] Critical Game Failure. Shutting down :(\n\n");
            return 0;
        }

        switch(pkg_recv.type) {
            case PKG_PING_SUCESS:
                currAcc = (user_info*)malloc(sizeof(user_info*));
                if(!currAcc) {
                    printf("\n[ERROR] Insufficient RAM memory available.");
                    printf("\n[ERROR] Critical Game Failure. Shutting down :(\n\n");
                    return NULL;
                }

                *currAcc = pkg_send.data.ui;

                printf("\nThe Log in was successful! Welcome back, %d ;)", currAcc->username);

                successfulLogin = 1;
                break;

            case PKG_PING_FAILURE:
                printf("\nIncorrect Credentials. Try Again.\n");
                break;

            default:
                printf("\n[ERROR] The input from the server is corrupted. Try restarting the game and Contact an Admin to report the issue.");
                printf("\n[ERROR] Critical Game Failure. Shutting down :(\n\n");
                return 0;
        }
         
    }   
        
    return 1;
} 

adv* getAdv(int cli_socket) {
    adv* currAdv = (adv*)malloc(sizeof(adv));

    if(send(cli_socket, &(package){.type = PKG_GET_ADV, .data = NULL}, sizeof(package), 0) == -1) {
        return NULL;
    } 

    package pkg_adv = {.type = 0, .data = NULL};
    if(recv(cli_socket, &pkg_adv, sizeof(package), 0) == -1) {
        return NULL;
    }
    

    return currAdv;
}