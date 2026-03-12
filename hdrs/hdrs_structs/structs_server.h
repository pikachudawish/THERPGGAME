#ifndef STRUCTS_SERVER_H
#define STRUCTS_SERVER_H

#include "../../hdrs/hdrs_structs/structs_adv.h"

enum pkgtype {
    PKG_HB,
    PKG_LOGIN_USERINFO,
    PKG_CREATE_USERINFO,
    PKG_GET_ADV,
    PKG_INS_UI,
    PKG_ADD_ADV_TO_USER,
    PKG_INS,
    PKG_UPD_UI,
    PKG_UPD_ADV,
    PKG_UPD_S,
    PKG_UPD_M,
    PKG_UPD_E,
    PKG_UPD_H,
    PKG_UPD_C,
    PKG_UPD_A,
    PKG_UPD_B,
    PKG_UPD_W,
    PKG_RMV,
    PKG_PING_SUCESS,
    PKG_PING_FAILURE,
};

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
} package;

#endif