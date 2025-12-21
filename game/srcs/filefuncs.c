#include <stdio.h>
#include <stdlib.h>

#define LOGS_PATH "files/logs/logs_player.txt"

int new_log(char* log) {
    if(!log) return 0;

    FILE* f = fopen(LOGS_PATH, "a"); 
    if(!f) { free(log); return 0;}

    fprintf(f, log);

    fclose(f);
    return 1;
}

