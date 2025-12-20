#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#include "structs_adv.h"
#include "dbauxfuncs.h"

#define BACKUPDB_PATH "files/backupdb.txt"
#define LOGS_PATH "files/logs/logs.txt"

#define SEL_ADV
#define SEL_S
#define SEL_M
#define SEL_E
#define SEL_H
#define SEL_C
#define SEL_A
#define SEL_B
#define SEL_W

int new_log(char* log) {
    if(!log) return 0;

    FILE* f = fopen(LOGS_PATH, "a"); 
    if(!f) { free(log); return 0;}

    fprintf(f, log);

    fclose(f);
    return 1;
}


// Backup a cada 6h, enquanto o jogo estiver ativo
void* create_filebackup(void* arg) {
    arg = NULL;

    return NULL;
}