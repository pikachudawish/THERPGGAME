#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#include "hashfuncs.h"
#include "dbauxfuncs.h"

#define TABLE_SIZE 167
#define SELECT "SELECT a.id, s.name, s.class, s.lvl, s.exp, s.max_hp, s.max_mana, s.pd, s.md, m.move1, m.move2, m.move3, m.move4, h.h_name, h.h_lvl, h.h_exp, h.h_defense, c.c_name, c.c_lvl, c.c_exp, c.c_defense, a2.a_name, a2.a_lvl, a2.a_exp, a2.a_defense, b.b_name, b.b_lvl, b.b_exp, b.b_defense, w.w_name, w.w_lvl, w.w_exp, w.w_pd, w.w_md FROM adv a INNER JOIN adv_stats s ON a.id_stats = s.id INNER JOIN adv_moves m ON a.id_moves = m.id INNER JOIN adv_equipment e ON a.id_equipment = e.id INNER JOIN helmets h ON e.helmet_id = h.id INNER JOIN chestplates c ON e.chestplate_id  = c.id INNER JOIN armlets a2 ON e.armlet_id = a2.id INNER JOIN boots b ON e.boots_id = b.id INNER JOIN weapons w ON e.weapon_id = w.id;"
#define HOST "100.82.64.91"
#define USER "rpggameadm"
#define PASS "Ru@25092006"
#define DBNAME "rpggame"

int db_to_ht_init_conn(MYSQL* conn, hashtable* ht) {
    if(mysql_real_connect(conn, HOST, USER, PASS, DBNAME, 3306, NULL, 0) == NULL) return 0;
    
    adv* aux = (adv*) malloc(sizeof(adv));
    if(!aux) return 0;

    aux->stats = (stats*)malloc(sizeof(stats));
    if(!aux->stats) {
        free(aux);
        return 0;
    }
    aux->moves = (moves*)malloc(sizeof(moves));
    if(!aux->moves) {
        free(aux->stats); free(aux);
        return 0;
    }
    aux->equipment = (equipment*)malloc(sizeof(equipment));
    if(!aux->equipment) {
        free(aux->moves); free(aux->stats); free(aux);
        return 0;
    }
    aux->equipment->h_s = (helmet_stats*)malloc(sizeof(helmet_stats));
    if(!aux->equipment->h_s) {
        free(aux->equipment); free(aux->moves); free(aux->stats); free(aux);
        return 0;
    }
    aux->equipment->c_s = (chestplate_stats*)malloc(sizeof(chestplate_stats));
    if(!aux->equipment->c_s) {
        free(aux->equipment->h_s); free(aux->equipment); free(aux->moves); free(aux->stats); free(aux);
        return 0;
    }
    aux->equipment->a_s = (armlet_stats*)malloc(sizeof(armlet_stats));
    if(!aux->equipment->a_s) {
        free(aux->equipment->c_s); free(aux->equipment->h_s); free(aux->equipment); 
        free(aux->moves); free(aux->stats); free(aux);
        return 0;
    }
    aux->equipment->b_s = (boots_stats*)malloc(sizeof(boots_stats));
    if(!aux->equipment->b_s) {
        free(aux->equipment->a_s); free(aux->equipment->c_s); free(aux->equipment->h_s); 
        free(aux->equipment); free(aux->moves); free(aux->stats); free(aux);
        return 0;
    }
    aux->equipment->w_s = (weapon_stats*)malloc(sizeof(weapon_stats));
    if(!aux->equipment->w_s) {
        free(aux->equipment->b_s); free(aux->equipment->a_s); free(aux->equipment->c_s); free(aux->equipment->h_s); 
        free(aux->equipment); free(aux->moves); free(aux->stats); free(aux); 
        return 0;
    }


    MYSQL_STMT* stmt_adv = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt_adv, SELECT, strlen(SELECT)) != 0) {
        free(aux->equipment->b_s); free(aux->equipment->a_s); free(aux->equipment->c_s); free(aux->equipment->h_s); 
        free(aux->equipment); free(aux->moves); free(aux->stats); free(aux);
        mysql_stmt_close(stmt_adv);
        return 0;
    }

    MYSQL_BIND res_adv[34];
    memset(res_adv, 0, sizeof(res_adv));
    res_adv[0].buffer_type = MYSQL_TYPE_LONG;
    res_adv[0].buffer = &aux->adv_id;
    res_adv[1].buffer_type = MYSQL_TYPE_STRING;
    res_adv[1].buffer = aux->stats->name;
    res_adv[1].buffer_length = sizeof(aux->stats->name);
    res_adv[2].buffer_type = MYSQL_TYPE_STRING;
    res_adv[2].buffer = aux->stats->class;
    res_adv[2].buffer_length = sizeof(aux->stats->class);
    res_adv[3].buffer_type = MYSQL_TYPE_LONG;
    res_adv[3].buffer = &aux->stats->lvl;
    res_adv[4].buffer_type = MYSQL_TYPE_DOUBLE;
    res_adv[4].buffer = &aux->stats->exp;
    res_adv[5].buffer_type = MYSQL_TYPE_LONG;
    res_adv[5].buffer = &aux->stats->max_hp;
    res_adv[6].buffer_type = MYSQL_TYPE_LONG;
    res_adv[6].buffer = &aux->stats->max_mana;
    res_adv[7].buffer_type = MYSQL_TYPE_LONG;
    res_adv[7].buffer = &aux->stats->physical_dmg;
    res_adv[8].buffer_type = MYSQL_TYPE_LONG;
    res_adv[8].buffer = &aux->stats->magic_dmg;
    res_adv[9].buffer_type = MYSQL_TYPE_LONG;
    res_adv[9].buffer = &aux->moves->move1_id;
    res_adv[10].buffer_type = MYSQL_TYPE_LONG;
    res_adv[10].buffer = &aux->moves->move2_id;
    res_adv[11].buffer_type = MYSQL_TYPE_LONG;
    res_adv[11].buffer = &aux->moves->move3_id;
    res_adv[12].buffer_type = MYSQL_TYPE_LONG;
    res_adv[12].buffer = &aux->moves->move4_id;
    res_adv[13].buffer_type = MYSQL_TYPE_STRING;
    res_adv[13].buffer = aux->equipment->h_s->name;
    res_adv[13].buffer_length = sizeof(aux->equipment->h_s->name);
    res_adv[14].buffer_type = MYSQL_TYPE_LONG;
    res_adv[14].buffer = &aux->equipment->h_s->lvl;
    res_adv[15].buffer_type = MYSQL_TYPE_DOUBLE;
    res_adv[15].buffer = &aux->equipment->h_s->exp;
    res_adv[16].buffer_type = MYSQL_TYPE_LONG;
    res_adv[16].buffer = &aux->equipment->h_s->defense;
    res_adv[17].buffer_type = MYSQL_TYPE_STRING;
    res_adv[17].buffer = aux->equipment->c_s->name;
    res_adv[17].buffer_length = sizeof(aux->equipment->c_s->name);
    res_adv[18].buffer_type = MYSQL_TYPE_LONG;
    res_adv[18].buffer = &aux->equipment->c_s->lvl;
    res_adv[19].buffer_type = MYSQL_TYPE_DOUBLE;
    res_adv[19].buffer = &aux->equipment->c_s->exp;
    res_adv[20].buffer_type = MYSQL_TYPE_LONG;
    res_adv[20].buffer = &aux->equipment->c_s->defense;
    res_adv[21].buffer_type = MYSQL_TYPE_STRING;
    res_adv[21].buffer = aux->equipment->a_s->name;
    res_adv[21].buffer_length = sizeof(aux->equipment->a_s->name);
    res_adv[22].buffer_type = MYSQL_TYPE_LONG;
    res_adv[22].buffer = &aux->equipment->a_s->lvl;
    res_adv[23].buffer_type = MYSQL_TYPE_DOUBLE;
    res_adv[23].buffer = &aux->equipment->a_s->exp;
    res_adv[24].buffer_type = MYSQL_TYPE_LONG;
    res_adv[24].buffer = &aux->equipment->a_s->defense;
    res_adv[25].buffer_type = MYSQL_TYPE_STRING;
    res_adv[25].buffer = aux->equipment->b_s->name;
    res_adv[25].buffer_length = sizeof(aux->equipment->b_s->name);
    res_adv[26].buffer_type = MYSQL_TYPE_LONG;
    res_adv[26].buffer = &aux->equipment->b_s->lvl;
    res_adv[27].buffer_type = MYSQL_TYPE_DOUBLE;
    res_adv[27].buffer = &aux->equipment->b_s->exp;
    res_adv[28].buffer_type = MYSQL_TYPE_LONG;
    res_adv[28].buffer = &aux->equipment->b_s->defense;
    res_adv[29].buffer_type = MYSQL_TYPE_STRING;
    res_adv[29].buffer = aux->equipment->w_s->name;
    res_adv[29].buffer_length = sizeof(aux->equipment->w_s->name);
    res_adv[30].buffer_type = MYSQL_TYPE_LONG;
    res_adv[30].buffer = &aux->equipment->w_s->lvl;
    res_adv[31].buffer_type = MYSQL_TYPE_DOUBLE;
    res_adv[31].buffer = &aux->equipment->w_s->exp;
    res_adv[32].buffer_type = MYSQL_TYPE_LONG;
    res_adv[32].buffer = &aux->equipment->w_s->physical_dmg;
    res_adv[33].buffer_type = MYSQL_TYPE_LONG;
    res_adv[33].buffer = &aux->equipment->w_s->magic_dmg;
    
    mysql_stmt_bind_result(stmt_adv, res_adv);
    mysql_stmt_execute(stmt_adv); 
    mysql_stmt_store_result(stmt_adv);

    while(mysql_stmt_fetch(stmt_adv) == 0) {
        if(!ht_insert(ht, aux)) {
            free(aux->equipment->b_s); free(aux->equipment->a_s); free(aux->equipment->c_s); free(aux->equipment->h_s); 
            free(aux->equipment); free(aux->moves); free(aux->stats); free(aux);
            mysql_stmt_free_result(stmt_adv); mysql_stmt_close(stmt_adv);
            return 0;
        }
    }

    mysql_stmt_free_result(stmt_adv);
    mysql_stmt_close(stmt_adv);
    
    free(aux->equipment->h_s);
    free(aux->equipment->c_s);
    free(aux->equipment->a_s);
    free(aux->equipment->b_s);
    free(aux->equipment->w_s);
    free(aux->equipment);
    free(aux->moves);
    free(aux->stats);
    free(aux);

    return 1;
}

int ins_upd_db(MYSQL* conn, adv* adventurer) {
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, "SELECT 1 FROM adv WHERE id = ?", strlen("SELECT 1 FROM adv WHERE id = ?")) != 0) {
        mysql_stmt_close(stmt);
        return 0;
    }

    int id = adventurer->adv_id;
    MYSQL_BIND b[1]; 
    memset(b, 0, sizeof(b));
    b[0].buffer_type = MYSQL_TYPE_LONG;
    b[0].buffer = &id;

    mysql_stmt_bind_param(stmt, b);
    mysql_stmt_execute(stmt);
    mysql_stmt_store_result(stmt);

    int insorupd = mysql_stmt_fetch(stmt);
    mysql_autocommit(conn, 0);

    int upd;
    switch(insorupd) {
        case 0:
            upd = 1;
            
            break;

        case MYSQL_NO_DATA:
            upd = 0;
            if(!insupd_adv_db(conn, adventurer, upd)) mysql_rollback(conn);
            break;

        default:
            mysql_autocommit(conn, 1);
            return 0;
    }

    mysql_commit(conn);
    mysql_autocommit(conn, 1);

    mysql_stmt_free_result(stmt);
    mysql_stmt_close(stmt);
    
    return 1;
}


int rmv_db(MYSQL* conn, int adv_id) {
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, "SELECT id_stats, id_moves, id_equipment FROM adv WHERE id = ?", strlen("SELECT id_stats, id_moves, id_equipment FROM adv WHERE id = ?")) != 0) {
        mysql_stmt_close(stmt);
        return 0;
    }

    long stats_id = 0, moves_id = 0, equipment_id = 0; 
    MYSQL_BIND bP[1]; 
    memset(bP, 0, sizeof(bP));
    bP[0].buffer_type = MYSQL_TYPE_LONG;
    bP[0].buffer = &adv_id;
    if(mysql_stmt_bind_param(stmt, bP)) {
        mysql_stmt_close(stmt);
        return 0;
    }

    MYSQL_BIND bR[1]; 
    memset(bR, 0, sizeof(bR));
    bR[0].buffer_type = MYSQL_TYPE_LONG;
    bR[0].buffer = &stats_id;
    bR[1].buffer_type = MYSQL_TYPE_LONG;
    bR[1].buffer = &moves_id;
    bR[2].buffer_type = MYSQL_TYPE_LONG;
    bR[2].buffer = &equipment_id;
    if(mysql_stmt_bind_result(stmt, bR)) {
        mysql_stmt_close(stmt);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        return 0;
    }

    mysql_autocommit(conn, 0);



    mysql_commit(conn);
    mysql_autocommit(conn, 1);
    mysql_stmt_close(stmt);

    return 1;
}
