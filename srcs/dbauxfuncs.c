#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#include "structs_adv.h"

#define INS_H "INSERT INTO helmets (h_name, h_lvl, h_exp, h_defense) VALUES (?, ?, ?, ?);"
#define INS_C "INSERT INTO chestplates (c_name, c_lvl, c_exp, c_defense) VALUES (?, ?, ?, ?);"
#define INS_A "INSERT INTO armlets (a_name, a_lvl, a_exp, a_defense) VALUES (?, ?, ?, ?);"
#define INS_B "INSERT INTO boots (b_name, b_lvl, b_exp, b_defense) VALUES (?, ?, ?, ?);"
#define INS_W "INSERT INTO weapons (w_name, w_lvl, w_exp, w_pd, w_md) VALUES (?, ?, ?, ?, ?);"
#define INS_E "INSERT INTO adv_equipment (helmet_id, chestplate_id, armlet_id, boots_id, weapon_id) VALUES (?, ?, ?, ?, ?);"
#define INS_M "INSERT INTO adv_moves (move1, move2, move3, move4) VALUES (?, ?, ?, ?);"
#define INS_S "INSERT INTO adv_stats (name, class, lvl, exp, max_hp, max_mana, pd, md) VALUES (?, ?, ?, ?, ?, ?, ?, ?);"
#define INS_ADV "INSERT INTO adv (id_stats, id_moves, id_equipment) VALUES (?, ?, ?);"
#define UPD_H
#define UPD_C
#define UPD_A
#define UPD_B
#define UPD_W
#define UPD_E
#define UPD_M
#define UPD_S
#define UPD_ADV

long insupd_helmet_db(MYSQL* conn, helmet_stats* h, int upd) {
    if(upd) {
        

        return 0;
    }

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    mysql_stmt_prepare(stmt, INS_H, strlen(INS_H));

    MYSQL_BIND bind[4];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = h->name;
    bind[0].buffer_length = strlen(h->name);
    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &h->lvl;
    bind[2].buffer_type = MYSQL_TYPE_DOUBLE;
    bind[2].buffer = &h->exp;
    bind[3].buffer_type = MYSQL_TYPE_LONG;
    bind[3].buffer = &h->defense;
    mysql_stmt_bind_param(stmt, bind);
    mysql_stmt_execute(stmt);

    long id_helmet = mysql_stmt_insert_id(stmt);
    mysql_stmt_close(stmt);

    return id_helmet;
}

long insupd_chestplate_db(MYSQL* conn, chestplate_stats* c, int upd) {
    if(upd) {


        return 0;
    }

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    mysql_stmt_prepare(stmt, INS_C, strlen(INS_C));

    MYSQL_BIND bind[4];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = c->name;
    bind[0].buffer_length = strlen(c->name);
    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &c->lvl;
    bind[2].buffer_type = MYSQL_TYPE_DOUBLE;
    bind[2].buffer = &c->exp;
    bind[3].buffer_type = MYSQL_TYPE_LONG;
    bind[3].buffer = &c->defense;
    mysql_stmt_bind_param(stmt, bind);
    mysql_stmt_execute(stmt);

    long id_chestplate = mysql_stmt_insert_id(stmt);
    mysql_stmt_close(stmt);

    return id_chestplate;
}


long insupd_armlet_db(MYSQL* conn, armlet_stats* a, int upd) {
    if(upd) {


        return 0;
    }

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    mysql_stmt_prepare(stmt, INS_A, strlen(INS_A));

    MYSQL_BIND bind[4];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = a->name;
    bind[0].buffer_length = strlen(a->name);
    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &a->lvl;
    bind[2].buffer_type = MYSQL_TYPE_DOUBLE;
    bind[2].buffer = &a->exp;
    bind[3].buffer_type = MYSQL_TYPE_LONG;
    bind[3].buffer = &a->defense;
    mysql_stmt_bind_param(stmt, bind);
    mysql_stmt_execute(stmt);

    long id_armlet = mysql_stmt_insert_id(stmt);
    mysql_stmt_close(stmt);

    return id_armlet;
}

long insupd_boots_db(MYSQL* conn, boots_stats* b, int upd) {
    if(upd) {


        return 0;
    }

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    mysql_stmt_prepare(stmt, INS_B, strlen(INS_B));

    MYSQL_BIND bind[4];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = b->name;
    bind[0].buffer_length = strlen(b->name);
    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &b->lvl;
    bind[2].buffer_type = MYSQL_TYPE_DOUBLE;
    bind[2].buffer = &b->exp;
    bind[3].buffer_type = MYSQL_TYPE_LONG;
    bind[3].buffer = &b->defense;
    mysql_stmt_bind_param(stmt, bind);
    mysql_stmt_execute(stmt);

    long id_boots = mysql_stmt_insert_id(stmt);
    mysql_stmt_close(stmt);

    return id_boots;
}

long insupd_weapon_db(MYSQL* conn, weapon_stats* w, int upd) {
    if(upd) {


        return 0;
    }

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    mysql_stmt_prepare(stmt, INS_W, strlen(INS_W));

    MYSQL_BIND bind[5];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = w->name;
    bind[0].buffer_length = strlen(w->name);
    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &w->lvl;
    bind[2].buffer_type = MYSQL_TYPE_DOUBLE;
    bind[2].buffer = &w->exp;
    bind[3].buffer_type = MYSQL_TYPE_LONG;
    bind[3].buffer = &w->physical_dmg;
    bind[4].buffer_type = MYSQL_TYPE_LONG;
    bind[4].buffer = &w->magic_dmg;
    mysql_stmt_bind_param(stmt, bind);
    mysql_stmt_execute(stmt);

    long id_weapon = mysql_stmt_insert_id(stmt);
    mysql_stmt_close(stmt);

    return id_weapon;
}


long insupd_equipment_db(MYSQL* conn, equipment* e, int upd) {
    if(upd) {


        return 0;
    }

    int helmet_id = insupd_helmet_db(conn, e->h_s, upd);
    int chestplate_id = insupd_chestplate_db(conn, e->c_s, upd);
    int armlet_id = insupd_armlet_db(conn, e->a_s, upd);
    int boots_id = insupd_boots_db(conn, e->b_s, upd);
    int weapon_id = insupd_weapon_db(conn, e->w_s, upd);

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    mysql_stmt_prepare(stmt, INS_E, strlen(INS_E));

    MYSQL_BIND bind[5];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &helmet_id;
    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &chestplate_id;
    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = &armlet_id;
    bind[3].buffer_type = MYSQL_TYPE_LONG;
    bind[3].buffer = &boots_id;
    bind[4].buffer_type = MYSQL_TYPE_LONG;
    bind[4].buffer = &weapon_id;
    mysql_stmt_bind_param(stmt, bind);
    mysql_stmt_execute(stmt);

    long id_equipment = mysql_stmt_insert_id(stmt);
    mysql_stmt_close(stmt);

    return id_equipment;
}

long insupd_moves_db(MYSQL* conn, moves* m, int upd) {
    if(upd) {


        return 0;
    }

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    mysql_stmt_prepare(stmt, INS_M, strlen(INS_M));

    MYSQL_BIND bind[4];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &m->move1_id;
    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &m->move2_id;
    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = &m->move3_id;
    bind[3].buffer_type = MYSQL_TYPE_LONG;
    bind[3].buffer = &m->move4_id;
    mysql_stmt_bind_param(stmt, bind);
    mysql_stmt_execute(stmt);

    long id_moves = mysql_stmt_insert_id(stmt);
    mysql_stmt_close(stmt);

    return id_moves;
}

long insupd_stats_db(MYSQL* conn, stats* s, int upd) {
    if(upd) {


        return 0;
    }

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    mysql_stmt_prepare(stmt, INS_S, strlen(INS_S));

    MYSQL_BIND bind[8];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = s->name;
    bind[0].buffer_length = strlen(s->name);
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = s->class;
    bind[1].buffer_length = strlen(s->class);    
    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = &s->lvl;
    bind[3].buffer_type = MYSQL_TYPE_DOUBLE;
    bind[3].buffer = &s->exp;
    bind[4].buffer_type = MYSQL_TYPE_LONG;
    bind[4].buffer = &s->max_hp;
    bind[5].buffer_type = MYSQL_TYPE_LONG;
    bind[5].buffer = &s->max_mana;
    bind[6].buffer_type = MYSQL_TYPE_LONG;
    bind[6].buffer = &s->physical_dmg;
    bind[7].buffer_type = MYSQL_TYPE_LONG;
    bind[7].buffer = &s->magic_dmg;
    mysql_stmt_bind_param(stmt, bind);
    mysql_stmt_execute(stmt);

    long id_stats = mysql_stmt_insert_id(stmt);
    mysql_stmt_close(stmt);

    return id_stats;
}

long insupd_adv_db(MYSQL* conn, adv* adventurer, int upd) {
    if(upd) {

        return 0;
    }

    int id_stats = insupd_stats_db(conn, adventurer->stats, upd);
    int id_moves = insupd_moves_db(conn, adventurer->moves, upd);
    int id_equipment = insupd_equipment_db(conn, adventurer->equipment, upd);

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    mysql_stmt_prepare(stmt, INS_ADV, strlen(INS_ADV));

    MYSQL_BIND bind[3];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &id_stats;
    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &id_moves;
    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = &id_equipment;
    mysql_stmt_bind_param(stmt, bind);
    mysql_stmt_execute(stmt);

    mysql_stmt_close(stmt);

    return 1;
} 