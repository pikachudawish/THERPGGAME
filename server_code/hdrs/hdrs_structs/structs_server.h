#ifndef STRUCTS_SERVER_H
#define STRUCTS_SERVER_H

#include <time.h>

#include "../../hdrs/hdrs_structs/structs_adv.h"

typedef struct {
    struct pollfd* poll;
    time_t* last_seen;
} _cliinfo;



typedef struct _package {
    int type;
    int cli_fd;
    union {
        int ids;
        user_info ui;
        adv adventurer;
        stats s;
        moves m;
        equipment e;
        helmet_stats h;
        chestplate_stats c;
        armlet_stats a;
        boots_stats b;
        weapon_stats w;
    } data;
    struct _package* next; 
} package;

typedef struct _packagelist {
    package pkg;
    struct _packagelist* next;
} packagelist;

typedef struct _dbtask {
    int type;
    int client_fd;       
    void* data;          
    struct _dbtask* next; 
} dbtask;

#endif
