#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#include "../../hdrs/structs_adv.h"

#define INS_H "INSERT INTO helmets (h_name, h_lvl, h_exp, h_defense) VALUES (?, ?, ?, ?);"
#define INS_C "INSERT INTO chestplates (c_name, c_lvl, c_exp, c_defense) VALUES (?, ?, ?, ?);"
#define INS_A "INSERT INTO armlets (a_name, a_lvl, a_exp, a_defense) VALUES (?, ?, ?, ?);"
#define INS_B "INSERT INTO boots (b_name, b_lvl, b_exp, b_defense) VALUES (?, ?, ?, ?);"
#define INS_W "INSERT INTO weapons (w_name, w_lvl, w_exp, w_pd, w_md) VALUES (?, ?, ?, ?, ?);"
#define INS_E "INSERT INTO adv_equipment (helmet_id, chestplate_id, armlet_id, boots_id, weapon_id) VALUES (?, ?, ?, ?, ?);"
#define INS_M "INSERT INTO adv_moves (move1, move2, move3, move4) VALUES (?, ?, ?, ?);"
#define INS_S "INSERT INTO adv_stats (name, class, lvl, exp, max_hp, max_mana, pd, md) VALUES (?, ?, ?, ?, ?, ?, ?, ?);"
#define INS_ADV "INSERT INTO adv (id_stats, id_moves, id_equipment) VALUES (?, ?, ?);"
#define UPD_H "UPDATE helmets SET h_id = ?, h_name = ?, h_lvl = ?, h_exp = ?, h_defense = ? WHERE id = ?"
#define UPD_C "UPDATE chestplate SET c_name = ?, c_lvl = ?, c_exp = ?, c_defense = ? WHERE id = ?"
#define UPD_A "UPDATE armlets SET a_name = ?, a_lvl = ?, a_exp = ?, a_defense = ? WHERE id = ?"
#define UPD_B "UPDATE boots SET b_name = ?, b_lvl = ?, b_exp = ?, b_defense = ? WHERE id = ?"
#define UPD_W "UPDATE weapons SET w_name = ?, w_lvl = ?, w_exp = ?, w_pd = ?, w_md = ? WHERE id = ?"
#define UPD_E "UPDATE adv_equipment SET helmet_id = ?, chestplate_id = ?, armlet_id = ?, boots_id = ?, weapond_id = ? WHERE id = ?"
#define UPD_M "UPDATE adv_moves SET move1 = ?, move2 = ?, move3 = ?, move4 = ? WHERE id = ?"
#define UPD_S "UPDATE adv_stats SET name = ?, class = ?, lvl = ?, exp = ?, max_hp = ?, max_mana = ?, pd = ?, md = ? WHERE id = ?"
#define UPD_ADV "UPDATE adv SET id_stats = ?, id_moves = ?, id_equipment = ? WHERE id = ?"

long ins_helmet_db(MYSQL* conn, helmet_stats* h) {
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, INS_H, strlen(INS_H))) {
        mysql_stmt_close(stmt);
        return 0;
    }   

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
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        return 0;
    }

    long id_helmet = mysql_stmt_insert_id(stmt);
    mysql_stmt_close(stmt);

    h->h_id = id_helmet;
    return id_helmet;
}

long ins_chestplate_db(MYSQL* conn, chestplate_stats* c) {
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, INS_C, strlen(INS_C))) {
        mysql_stmt_close(stmt);
        return 0;
    }   

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
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        return 0;
    }

    long id_chestplate = mysql_stmt_insert_id(stmt);
    mysql_stmt_close(stmt);

    c->c_id = id_chestplate;
    return id_chestplate;
}

long ins_armlet_db(MYSQL* conn, armlet_stats* a) {
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, INS_A, strlen(INS_A))) {
        mysql_stmt_close(stmt);
        return 0;
    }   

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
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        return 0;
    }

    long id_armlet = mysql_stmt_insert_id(stmt);
    mysql_stmt_close(stmt);

    a->a_id = id_armlet;
    return id_armlet;
}

long ins_boots_db(MYSQL* conn, boots_stats* b) {
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, INS_B, strlen(INS_B))) {
        mysql_stmt_close(stmt);
        return 0;
    }   

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
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        return 0;
    }

    long id_boots = mysql_stmt_insert_id(stmt);
    mysql_stmt_close(stmt);

    b->b_id = id_boots;
    return id_boots;
}

long ins_weapon_db(MYSQL* conn, weapon_stats* w) {
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, INS_W, strlen(INS_W))) {
        mysql_stmt_close(stmt);
        return 0;
    }   

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
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        return 0;
    }

    long id_weapon = mysql_stmt_insert_id(stmt);
    mysql_stmt_close(stmt);

    w->w_id = id_weapon;
    return id_weapon;
}

long ins_equipment_db(MYSQL* conn, equipment* e) {
    int helmet_id = ins_helmet_db(conn, e->h_s);
    int chestplate_id = ins_chestplate_db(conn, e->c_s);
    int armlet_id = ins_armlet_db(conn, e->a_s);
    int boots_id = ins_boots_db(conn, e->b_s);
    int weapon_id = ins_weapon_db(conn, e->w_s);
    if(!helmet_id || !chestplate_id || !armlet_id || !boots_id || !weapon_id) return 0;

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, INS_E, strlen(INS_E))) {
        mysql_stmt_close(stmt);
        return 0;
    }   

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
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        return 0;
    }

    long id_equipment = mysql_stmt_insert_id(stmt);
    mysql_stmt_close(stmt);

    e->e_id = id_equipment;
    return id_equipment;
}

long ins_moves_db(MYSQL* conn, moves* m) {
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, INS_M, strlen(INS_M))) {
        mysql_stmt_close(stmt);
        return 0;
    }   

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
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        return 0;
    }

    long id_moves = mysql_stmt_insert_id(stmt);
    mysql_stmt_close(stmt);

    m->m_id = id_moves;
    return id_moves;
}

long ins_stats_db(MYSQL* conn, stats* s) {
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, INS_S, strlen(INS_S))) {
        mysql_stmt_close(stmt);
        return 0;
    }   

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
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        return 0;
    }

    long id_stats = mysql_stmt_insert_id(stmt);
    mysql_stmt_close(stmt);

    s->s_id = id_stats;
    return id_stats;
}

long ins_adv_db(MYSQL* conn, adv* adventurer) {
    mysql_autocommit(conn, 0);

    int id_stats = ins_stats_db(conn, adventurer->stats);
    int id_moves = ins_moves_db(conn, adventurer->moves);
    int id_equipment = ins_equipment_db(conn, adventurer->equipment);
    if(!id_stats || !id_equipment || !id_moves) {
        mysql_rollback(conn);   
        return 0;
    }

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, INS_ADV, strlen(INS_ADV))) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }   

    MYSQL_BIND bind[3];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &id_stats;
    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &id_moves;
    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = &id_equipment;
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    adventurer->adv_id = mysql_stmt_insert_id(stmt);
    
    mysql_stmt_close(stmt);
    
    mysql_commit(conn);
    mysql_autocommit(conn, 1);

    return 1;
}

int upd_helmet_db(MYSQL* conn, helmet_stats* h) {
    if(!h) return 0;
    
    mysql_autocommit(conn, 0);

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, UPD_H, strlen(UPD_H))) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }

    MYSQL_BIND bind[5];
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
    bind[4].buffer_type = MYSQL_TYPE_LONG;
    bind[4].buffer = &h->h_id;
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    mysql_stmt_close(stmt);

    mysql_commit(conn);
    mysql_autocommit(conn, 1);

    return 1;
}

int upd_chestplate_db(MYSQL* conn, chestplate_stats* c) {
    if(!c) return 0;
    
    mysql_autocommit(conn, 0);

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, UPD_C, strlen(UPD_C))) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }

    MYSQL_BIND bind[5];
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
    bind[4].buffer_type = MYSQL_TYPE_LONG;
    bind[4].buffer = &c->c_id;
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }   
    mysql_stmt_close(stmt);

    mysql_commit(conn);
    mysql_autocommit(conn, 1);

    return 1;
}

int upd_armlet_db(MYSQL* conn, armlet_stats* a) {
    if(!a) return 0;
    
    mysql_autocommit(conn, 0);

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, UPD_A, strlen(UPD_A))) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }

    MYSQL_BIND bind[5];
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
    bind[4].buffer_type = MYSQL_TYPE_LONG;
    bind[4].buffer = &a->a_id;
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    mysql_stmt_close(stmt);

    mysql_commit(conn);
    mysql_autocommit(conn, 1);

    return 1;
}

int upd_boots_db(MYSQL* conn, boots_stats* b) {
    if(!b) return 0;
    
    mysql_autocommit(conn, 0);
   
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, UPD_B, strlen(UPD_B))) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }

    MYSQL_BIND bind[5];
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
    bind[4].buffer_type = MYSQL_TYPE_LONG;
    bind[4].buffer = &b->b_id;
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    mysql_stmt_close(stmt);

    mysql_commit(conn);
    mysql_autocommit(conn, 1);

    return 1;
}

int upd_weapon_db(MYSQL* conn, weapon_stats* w) {
    if(!w) return 0;
    
    mysql_autocommit(conn, 0);

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, UPD_W, strlen(UPD_W))) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }

    MYSQL_BIND bind[6];
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
    bind[5].buffer_type = MYSQL_TYPE_LONG;
    bind[5].buffer = &w->w_id;
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    mysql_stmt_close(stmt);

    mysql_commit(conn);
    mysql_autocommit(conn, 1);

    return 1;
}

int upd_equipment_db(MYSQL* conn, equipment* e) {
    if(!e || !e->a_s || !e->b_s || !e->c_s || !e->h_s || !e->w_s) return 0;
    
    mysql_autocommit(conn, 0);
    
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, UPD_E, strlen(UPD_E))) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }

    MYSQL_BIND bind[6];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &e->h_s->h_id;
    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &e->c_s->c_id;
    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = &e->a_s->a_id;
    bind[3].buffer_type = MYSQL_TYPE_LONG;
    bind[3].buffer = &e->b_s->b_id;
    bind[4].buffer_type = MYSQL_TYPE_LONG;
    bind[4].buffer = &e->w_s->w_id;
    bind[5].buffer_type = MYSQL_TYPE_LONG;
    bind[5].buffer = &e->e_id;
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    mysql_stmt_close(stmt);

    mysql_commit(conn);
    mysql_autocommit(conn, 1);

    return 1;
}

int upd_moves_db(MYSQL* conn, moves* m) {
    if(!m) return 0;

    mysql_autocommit(conn, 0);
    
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, UPD_M, strlen(UPD_M))) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }

    MYSQL_BIND bind[5];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &m->move1_id;
    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &m->move2_id;
    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = &m->move3_id;
    bind[3].buffer_type = MYSQL_TYPE_LONG;
    bind[3].buffer = &m->move4_id;
    bind[4].buffer_type = MYSQL_TYPE_LONG;
    bind[4].buffer = &m->m_id;
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    mysql_stmt_close(stmt);

    mysql_commit(conn);
    mysql_autocommit(conn, 1);

    return 1;
}

int upd_stats_db(MYSQL* conn, stats* s) {
    if(!s) return 0;

    mysql_autocommit(conn, 0);
    
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, UPD_S, strlen(UPD_S))) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }

    MYSQL_BIND bind[9];
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
    bind[8].buffer_type = MYSQL_TYPE_LONG;
    bind[8].buffer = &s->s_id;
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    mysql_stmt_close(stmt);

    mysql_commit(conn);
    mysql_autocommit(conn, 1);

    return 1;
}

int upd_adv_db(MYSQL* conn, adv* adventurer) {
    if(!adventurer || !adventurer->equipment || !adventurer->moves || !adventurer->stats) return 0;

    mysql_autocommit(conn, 0);
    
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, UPD_ADV, strlen(UPD_ADV))) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }

    MYSQL_BIND bind[4];
    memset(bind, 0, sizeof(bind)); 
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &adventurer->stats->s_id;
    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &adventurer->moves->m_id;
    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = &adventurer->equipment->e_id;
    bind[3].buffer_type = MYSQL_TYPE_LONG;
    bind[3].buffer = &adventurer->adv_id;
    if(mysql_stmt_bind_param(stmt, bind)){
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }
    mysql_stmt_close(stmt);

    mysql_commit(conn);
    mysql_autocommit(conn, 1);

    return 1;
}