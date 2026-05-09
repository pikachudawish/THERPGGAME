#ifndef STRUCTS_SERVER_H
#define STRUCTS_SERVER_H

#include "../../hdrs/hdrs_structs/structs_adv.h"

typedef struct _package {
    int type;
    union {
        user_info ui;
        adv adventurer;
        stats s;
        equipment e;
        helmet_stats h;
        chestplate_stats c;
        armlet_stats a;
        boots_stats b;
    } data;
    struct _package* next; 
} package;

#endif