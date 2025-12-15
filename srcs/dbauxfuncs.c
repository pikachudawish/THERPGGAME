#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#include "structs_adv.h"

#define INS_H
#define INS_C
#define INS_A
#define INS_B
#define INS_W
#define INS_E
#define INS_M
#define INS_S


long ins_helmet_db(MYSQL* conn, helmet_stats* h) {

    return 1;
}

long ins_chestplate_db(MYSQL* conn, chestplate_stats* c) {

    return 1;
}

long ins_armlet_db(MYSQL* conn, armlet_stats* a) {

    return 1;
}

long ins_boots_db(MYSQL* conn, boots_stats* b) {

    return 1;
}

long ins_weapon_db(MYSQL* conn, weapon_stats* w) {

    return 1;
}

long ins_equipment_db(MYSQL* conn, equipment* e) {

    return 1;
}

long ins_moves_db(MYSQL* conn, moves* m) {

    return 1;
}

long ins_stats_db(MYSQL* conn, stats* s) {

    return 1;
}