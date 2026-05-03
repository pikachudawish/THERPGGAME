#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#include "../../hdrs/hdrs_db/dbfuncs.h"

long vrf_ui_db(MYSQL* conn, user_info* ui) {


    return 1;
}

adv get_adv_db(MYSQL* conn, char* username) {
    if(!username) return NULL;

    adv* aux = (adv*) malloc(sizeof(adv));
    if(!aux) return NULL;

    aux->stats = (stats*)malloc(sizeof(stats));
    if(!aux->stats) {
        free(aux);
        return NULL;
    }
    aux->moves = (moves*)malloc(sizeof(moves));
    if(!aux->moves) {
        free(aux->stats); free(aux);
        return NULL;
    }
    aux->equipment = (equipment*)malloc(sizeof(equipment));
    if(!aux->equipment) {
        free(aux->moves); free(aux->stats); free(aux->equipment->b_s); free(aux->equipment->a_s); free(aux->equipment->c_s); 
        free(aux->equipment->h_s); free(aux->equipment); free(aux->moves); free(aux->stats); free(aux);
        return NULL;
    }
    aux->equipment->h_s = (helmet_stats*)malloc(sizeof(helmet_stats));
    if(!aux->equipment->h_s) {
        free(aux->equipment); free(aux->moves); free(aux->stats); free(aux);
        return NULL;
    }
    aux->equipment->c_s = (chestplate_stats*)malloc(sizeof(chestplate_stats));
    if(!aux->equipment->c_s) {
        free(aux->equipment->h_s); free(aux->equipment); free(aux->moves); free(aux->stats); free(aux);
        return NULL;
    }
    aux->equipment->a_s = (armlet_stats*)malloc(sizeof(armlet_stats));
    if(!aux->equipment->a_s) {
        free(aux->equipment->c_s); free(aux->equipment->h_s); free(aux->equipment); 
        free(aux->moves); free(aux->stats); free(aux);
        return NULL;
    }
    aux->equipment->b_s = (boots_stats*)malloc(sizeof(boots_stats));
    if(!aux->equipment->b_s) {
        free(aux->equipment->a_s); free(aux->equipment->c_s); free(aux->equipment->h_s); 
        free(aux->equipment); free(aux->moves); free(aux->stats); free(aux);
        return NULL;
    }
    aux->equipment->w_s = (weapon_stats*)malloc(sizeof(weapon_stats));
    if(!aux->equipment->w_s) {
        free(aux->equipment->b_s); free(aux->equipment->a_s); free(aux->equipment->c_s); free(aux->equipment->h_s); 
        free(aux->equipment); free(aux->moves); free(aux->stats); free(aux); 
        return NULL;
    }

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, GET_ADV, strlen(GET_ADV))) {
        free(aux->equipment->b_s); free(aux->equipment->a_s); free(aux->equipment->c_s); free(aux->equipment->h_s); 
        free(aux->equipment); free(aux->moves); free(aux->stats); free(aux);
        mysql_stmt_close(stmt);
        return NULL;
    }   

    MYSQL_BIND bind_param[1];
    memset(bind_param, 0, sizeof(bind_param));
    bind_param[0].buffer_type = MYSQL_TYPE_STRING;
    bind_param[0].buffer = username;
    bind_param[0].buffer_length = strlen(username);
    if(mysql_stmt_bind_param(stmt, bind_param)){
        free(aux->equipment->b_s); free(aux->equipment->a_s); free(aux->equipment->c_s); free(aux->equipment->h_s); 
        free(aux->equipment); free(aux->moves); free(aux->stats); free(aux);
        mysql_stmt_close(stmt);
        return NULL;
    }

    MYSQL_BIND bind_res[42];
    memset(bind_res, 0, sizeof(bind_res));
    bind_res[0].buffer_type = MYSQL_TYPE_LONG;
    bind_res[0].buffer = &aux->adv_id;
    bind_res[1].buffer_type = MYSQL_TYPE_LONG;
    bind_res[1].buffer = &aux->stats->s_id;
    bind_res[2].buffer_type = MYSQL_TYPE_STRING;
    bind_res[2].buffer = aux->stats->name;
    bind_res[2].buffer_length = sizeof(aux->stats->name);
    bind_res[3].buffer_type = MYSQL_TYPE_STRING;
    bind_res[3].buffer = aux->stats->class;
    bind_res[3].buffer_length = sizeof(aux->stats->class);
    bind_res[4].buffer_type = MYSQL_TYPE_LONG;
    bind_res[4].buffer = &aux->stats->lvl;
    bind_res[5].buffer_type = MYSQL_TYPE_DOUBLE;
    bind_res[5].buffer = &aux->stats->exp;
    bind_res[6].buffer_type = MYSQL_TYPE_LONG;
    bind_res[6].buffer = &aux->stats->max_hp;
    bind_res[7].buffer_type = MYSQL_TYPE_LONG;
    bind_res[7].buffer = &aux->stats->max_mana;
    bind_res[8].buffer_type = MYSQL_TYPE_LONG;
    bind_res[8].buffer = &aux->stats->physical_dmg;
    bind_res[9].buffer_type = MYSQL_TYPE_LONG;
    bind_res[9].buffer = &aux->stats->magic_dmg;
    bind_res[10].buffer_type = MYSQL_TYPE_LONG;
    bind_res[10].buffer = &aux->moves->m_id;
    bind_res[11].buffer_type = MYSQL_TYPE_LONG;
    bind_res[11].buffer = &aux->moves->move1_id;
    bind_res[12].buffer_type = MYSQL_TYPE_LONG;
    bind_res[12].buffer = &aux->moves->move2_id;
    bind_res[13].buffer_type = MYSQL_TYPE_LONG;
    bind_res[13].buffer = &aux->moves->move3_id;
    bind_res[14].buffer_type = MYSQL_TYPE_LONG;
    bind_res[14].buffer = &aux->moves->move4_id;
    bind_res[15].buffer_type = MYSQL_TYPE_LONG;
    bind_res[15].buffer = &aux->equipment->e_id;
    bind_res[16].buffer_type = MYSQL_TYPE_LONG;
    bind_res[16].buffer = &aux->equipment->h_s->h_id;
    bind_res[17].buffer_type = MYSQL_TYPE_STRING;
    bind_res[17].buffer = aux->equipment->h_s->name;
    bind_res[17].buffer_length = sizeof(aux->equipment->h_s->name);
    bind_res[18].buffer_type = MYSQL_TYPE_LONG;
    bind_res[18].buffer = &aux->equipment->h_s->lvl;
    bind_res[19].buffer_type = MYSQL_TYPE_DOUBLE;
    bind_res[19].buffer = &aux->equipment->h_s->exp;
    bind_res[20].buffer_type = MYSQL_TYPE_LONG;
    bind_res[20].buffer = &aux->equipment->h_s->defense;
    bind_res[21].buffer_type = MYSQL_TYPE_LONG;
    bind_res[21].buffer = &aux->equipment->c_s->c_id;
    bind_res[22].buffer_type = MYSQL_TYPE_STRING;
    bind_res[22].buffer = aux->equipment->c_s->name;
    bind_res[22].buffer_length = sizeof(aux->equipment->c_s->name);
    bind_res[23].buffer_type = MYSQL_TYPE_LONG;
    bind_res[23].buffer = &aux->equipment->c_s->lvl;
    bind_res[24].buffer_type = MYSQL_TYPE_DOUBLE;
    bind_res[24].buffer = &aux->equipment->c_s->exp;
    bind_res[25].buffer_type = MYSQL_TYPE_LONG;
    bind_res[25].buffer = &aux->equipment->c_s->defense;
    bind_res[26].buffer_type = MYSQL_TYPE_LONG;
    bind_res[26].buffer = &aux->equipment->a_s->a_id;
    bind_res[27].buffer_type = MYSQL_TYPE_STRING;
    bind_res[27].buffer = aux->equipment->a_s->name;
    bind_res[27].buffer_length = sizeof(aux->equipment->a_s->name);
    bind_res[28].buffer_type = MYSQL_TYPE_LONG;
    bind_res[28].buffer = &aux->equipment->a_s->lvl;
    bind_res[29].buffer_type = MYSQL_TYPE_DOUBLE;
    bind_res[29].buffer = &aux->equipment->a_s->exp;
    bind_res[30].buffer_type = MYSQL_TYPE_LONG;
    bind_res[30].buffer = &aux->equipment->a_s->defense;
    bind_res[31].buffer_type = MYSQL_TYPE_LONG;
    bind_res[31].buffer = &aux->equipment->b_s->b_id;
    bind_res[32].buffer_type = MYSQL_TYPE_STRING;
    bind_res[32].buffer = aux->equipment->b_s->name;
    bind_res[32].buffer_length = sizeof(aux->equipment->b_s->name);
    bind_res[33].buffer_type = MYSQL_TYPE_LONG;
    bind_res[33].buffer = &aux->equipment->b_s->lvl;
    bind_res[34].buffer_type = MYSQL_TYPE_DOUBLE;
    bind_res[34].buffer = &aux->equipment->b_s->exp;
    bind_res[35].buffer_type = MYSQL_TYPE_LONG;
    bind_res[35].buffer = &aux->equipment->b_s->defense;
    bind_res[36].buffer_type = MYSQL_TYPE_LONG;
    bind_res[36].buffer = &aux->equipment->w_s->w_id;
    bind_res[37].buffer_type = MYSQL_TYPE_STRING;
    bind_res[37].buffer = aux->equipment->w_s->name;
    bind_res[37].buffer_length = sizeof(aux->equipment->w_s->name);
    bind_res[38].buffer_type = MYSQL_TYPE_LONG;
    bind_res[38].buffer = &aux->equipment->w_s->lvl;
    bind_res[39].buffer_type = MYSQL_TYPE_DOUBLE;
    bind_res[39].buffer = &aux->equipment->w_s->exp;
    bind_res[40].buffer_type = MYSQL_TYPE_LONG;
    bind_res[40].buffer = &aux->equipment->w_s->physical_dmg;
    bind_res[41].buffer_type = MYSQL_TYPE_LONG;
    bind_res[41].buffer = &aux->equipment->w_s->magic_dmg;
    
    if(mysql_stmt_bind_result(stmt, bind_res)) {
        free(aux->equipment->b_s); free(aux->equipment->a_s); free(aux->equipment->c_s); free(aux->equipment->h_s); 
        free(aux->equipment); free(aux->moves); free(aux->stats); free(aux);
        mysql_stmt_close(stmt);
        return NULL;
    }
    if(mysql_stmt_execute(stmt)) {
        free(aux->equipment->b_s); free(aux->equipment->a_s); free(aux->equipment->c_s); free(aux->equipment->h_s); 
        free(aux->equipment); free(aux->moves); free(aux->stats); free(aux);
        mysql_stmt_close(stmt);
        return NULL;
    }
    if(mysql_stmt_store_result(stmt)) {
        free(aux->equipment->b_s); free(aux->equipment->a_s); free(aux->equipment->c_s); free(aux->equipment->h_s); 
        free(aux->equipment); free(aux->moves); free(aux->stats); free(aux);
        mysql_stmt_close(stmt);
        return NULL;
    }
    if(mysql_stmt_fetch(stmt)) {
        free(aux->equipment->b_s); free(aux->equipment->a_s); free(aux->equipment->c_s); free(aux->equipment->h_s); 
        free(aux->equipment); free(aux->moves); free(aux->stats); free(aux);
        mysql_stmt_free_result(stmt);
        mysql_stmt_close(stmt);
        return NULL;
    }

    adv* cpy = (adv*)malloc(sizeof(adv));
    if(!cpy) {
        return NULL;
    }
    cpy->adv_id = aux->adv_id;

    cpy->stats = (stats*)malloc(sizeof(stats));
    if(!cpy->stats) {
        free(cpy); 
        return NULL;
    }
    *(cpy->stats) = *(aux->stats);

    cpy->moves = (moves*)malloc(sizeof(moves));
    if(!cpy->moves) {
        free(cpy->stats); free(cpy); 
        return NULL;
    }
    *(cpy->moves) = *(aux->moves);

    cpy->equipment = (equipment*)malloc(sizeof(equipment));
    if(!cpy->equipment) {
        free(cpy->moves); free(cpy->stats); free(cpy); 
        return NULL;
    }

    cpy->equipment->h_s = (helmet_stats*) malloc(sizeof(helmet_stats));
    if(!cpy->equipment->h_s) {
        free(cpy->equipment); free(cpy->moves); free(cpy->stats); free(cpy); 
        return NULL;
    }
    *(cpy->equipment->h_s) = *(aux->equipment->h_s);

    cpy->equipment->c_s = (chestplate_stats*) malloc(sizeof(chestplate_stats));
    if(!cpy->equipment->c_s) {
        free(cpy->equipment->h_s); free(cpy->equipment); free(cpy->moves);
        free(cpy->stats); free(cpy); 
        return NULL;
    }
    *(cpy->equipment->c_s) = *(aux->equipment->c_s);

    cpy->equipment->a_s = (armlet_stats*) malloc(sizeof(armlet_stats));
    if(!cpy->equipment->a_s) {
        free(cpy->equipment->c_s); free(cpy->equipment->h_s); free(cpy->equipment);
        free(cpy->moves); free(cpy->stats); free(cpy); 
        return NULL;
    }
    *(cpy->equipment->a_s) = *(aux->equipment->a_s);

    cpy->equipment->b_s = (boots_stats*) malloc(sizeof(boots_stats));
    if(!cpy->equipment->b_s) {
        free(cpy->equipment->a_s); free(cpy->equipment->c_s); free(cpy->equipment->h_s); free(cpy->equipment);
        free(cpy->moves); free(cpy->stats); free(cpy); 
        return NULL;
    }
    *(cpy->equipment->b_s) = *(aux->equipment->b_s);

    cpy->equipment->w_s = (weapon_stats*) malloc(sizeof(weapon_stats));
    if(!cpy->equipment->w_s) {
        free(cpy->equipment->b_s); free(cpy->equipment->a_s); free(cpy->equipment->c_s); free(cpy->equipment->h_s);
        free(cpy->equipment); free(cpy->moves); free(cpy->stats); free(cpy); 
        return NULL;
    }
    *(cpy->equipment->w_s) = *(aux->equipment->w_s);

    mysql_stmt_free_result(stmt);
    mysql_stmt_close(stmt);

    return cpy;
}

int ins_user_db(MYSQL* conn, char username[30], char pass[30]) {
    mysql_autocommit(conn, 0);

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, INS_U, strlen(INS_U)) != 0) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }

    MYSQL_BIND b[2];
    memset(b, 0, sizeof(b));
    b[0].buffer_type = MYSQL_TYPE_STRING;
    b[0].buffer = username;
    b[0].buffer_length = strlen(username); 
    b[1].buffer_type = MYSQL_TYPE_STRING;
    b[1].buffer = pass;
    b[1].buffer_length = strlen(pass);
    if(mysql_stmt_bind_param(stmt, b)) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }
    mysql_stmt_close(stmt);

    mysql_commit(conn);
    mysql_autocommit(conn, 1);

    return 1;
}

long ins_helmet_db(MYSQL* conn, helmet_stats* h) {
    if(!h) return 0;

    mysql_autocommit(conn, 0);

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, INS_H, strlen(INS_H))) {
        mysql_stmt_close(stmt); mysql_autocommit(conn, 1);
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
        mysql_stmt_close(stmt); mysql_autocommit(conn, 0);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt); mysql_autocommit(conn, 0);
        return 0;
    }

    long id_helmet = mysql_stmt_insert_id(stmt);
    mysql_stmt_close(stmt);

    h->h_id = id_helmet;
    return id_helmet;
}

long ins_chestplate_db(MYSQL* conn, chestplate_stats* c) {
    if(!c) return 0;
    
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
    if(!a) return 0;

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
    if(!b) return 0;
    
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
    if(!w) return 0;
    
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
    if(!e) return 0;

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
    if(!m) return 0;

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
    if(!s) return 0;
    
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
    if(!adventurer) return 0;
    
    mysql_autocommit(conn, 0);

    int id_equipment = ins_equipment_db(conn, adventurer->equipment);
    int id_stats = ins_stats_db(conn, adventurer->stats);
    int id_moves = ins_moves_db(conn, adventurer->moves);
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

int upd_user_db(MYSQL* conn, user_info* u) {
    if(!u || !u->adventurer) return 0;

    mysql_autocommit(conn, 0);
    
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, UPD_U, strlen(UPD_U))) {
        mysql_stmt_close(stmt); mysql_rollback(conn); mysql_autocommit(conn, 1);
        return 0;
    }

    MYSQL_BIND bind[4];
    memset(bind, 0, sizeof(bind)); 
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = u->user_name;
    bind[0].buffer_length = strlen(u->user_name);
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = u->pass;
    bind[1].buffer_length = strlen(u->pass);
    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = &u->adventurer->adv_id;
    bind[3].buffer_type = MYSQL_TYPE_LONG;
    bind[3].buffer = &u->id;
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

int add_adv_to_user(MYSQL* conn, int user_id, int adv_id) {
    mysql_autocommit(conn, 0);
    
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, ADD_ADV_TO_USER, strlen(ADD_ADV_TO_USER)) != 0) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }

    MYSQL_BIND b[2];
    memset(b, 0, sizeof(b));
    b[0].buffer_type = MYSQL_TYPE_LONG;
    b[0].buffer = &adv_id;
    b[1].buffer_type = MYSQL_TYPE_LONG;
    b[1].buffer = &user_id;
    if(mysql_stmt_bind_param(stmt, b)) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }
    mysql_stmt_close(stmt);

    mysql_commit(conn);
    mysql_autocommit(conn, 1);

    return 1;
}

int rmv_adv_db(MYSQL* conn, int adv_id) {
    mysql_autocommit(conn, 0);
    
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, DELETE, strlen(DELETE)) != 0) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }

    MYSQL_BIND b[1]; 
    memset(b, 0, sizeof(b));
    b[0].buffer_type = MYSQL_TYPE_LONG;
    b[0].buffer = &adv_id;
    if(mysql_stmt_bind_param(stmt, b)) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }
    mysql_stmt_close(stmt);

    mysql_commit(conn);
    mysql_autocommit(conn, 1);

    return 1;
}
