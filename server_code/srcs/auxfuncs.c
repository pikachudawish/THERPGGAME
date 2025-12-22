#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* wait_input(void* arg) {
    int end = 0, opt = 0;

    char buffer[100];
    while(!end) {
        printf("\n->> ");
        fgets(buffer, 100, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if(strcmp(buffer, "quit") == 0) opt = 1;

        switch(opt) {
            case 1:
                printf("Ending Programm...");
                end = 1;
                break;
            default:
                printf("Invalid Input!");
                break;
        }
    }
    printf("\n");

    return NULL;
} 