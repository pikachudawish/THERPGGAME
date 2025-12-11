#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#include "hashfuncs.h"

#define TABLE_SIZE 167

int db_to_ht_init_conn(hashtable* ht) {
    MYSQL* conn = mysql_init(NULL);
    if(!conn) return 0;

    if(mysql_real_connect(conn, "100.82.64.91", "rpggameadm", "Ru@25092006", "rpggame", 3306, NULL, 0) == NULL) {
        mysql_close(conn);
        return 0;
    }

    adv* aux = (adv*)malloc(sizeof(adv));
    aux->stats = (stats*)malloc(sizeof(stats));
    aux->moves = (moves*)malloc(sizeof(moves));
    aux->equipment = (equipment*)malloc(sizeof(equipment));

    MYSQL_STMT* stmt_adv = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt_adv, "SELECT * FROM adv", strlen("SELECT * FROM adv")) != 0) {
        mysql_close(conn);
        return 0;
    } 

    MYSQL_BIND res_adv[4];
    memset(res_adv, 0, sizeof(res_adv));
    res_adv[0].buffer_type = MYSQL_TYPE_LONG;
    res_adv[0].buffer = &aux->adv_id;
    res_adv[1].buffer_type = MYSQL_TYPE_LONG;
    res_adv[1].buffer = &aux->stats_id;
    res_adv[2].buffer_type = MYSQL_TYPE_LONG;
    res_adv[2].buffer = &aux->moves_id;
    res_adv[3].buffer_type = MYSQL_TYPE_LONG;
    res_adv[3].buffer = &aux->equipment_id;
    mysql_stmt_bind_result(stmt_adv, res_adv);
    mysql_stmt_execute(stmt_adv);

    MYSQL_STMT* stmt_stats = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt_stats, "SELECT * FROM adv_stats", strlen("SELECT * FROM adv_stats")) != 0) {
        mysql_stmt_close(stmt_adv); mysql_close(conn);
        return 0;
    }
    MYSQL_BIND res_stats[9];
    memset(res_stats, 0, sizeof(res_stats));
    res_stats[1].buffer_type = MYSQL_TYPE_STRING;
    res_stats[1].buffer = aux->stats->name;
    res_stats[1].buffer_length = sizeof(aux->stats->name);
    res_stats[2].buffer_type = MYSQL_TYPE_STRING;
    res_stats[2].buffer = aux->stats->class;
    res_stats[2].buffer_length = sizeof(aux->stats->class);
    res_stats[3].buffer_type = MYSQL_TYPE_LONG;
    res_stats[3].buffer = &aux->stats->lvl;
    res_stats[4].buffer_type = MYSQL_TYPE_DOUBLE;
    res_stats[4].buffer = &aux->stats->exp;
    res_stats[5].buffer_type = MYSQL_TYPE_LONG;
    res_stats[5].buffer = &aux->stats->max_hp;
    res_stats[6].buffer_type = MYSQL_TYPE_LONG;
    res_stats[6].buffer = &aux->stats->max_mana;
    res_stats[7].buffer_type = MYSQL_TYPE_LONG;
    res_stats[7].buffer = &aux->stats->physical_dmg;
    res_stats[8].buffer_type = MYSQL_TYPE_LONG;
    res_stats[8].buffer = &aux->stats->magic_dmg;
    mysql_stmt_bind_result(stmt_stats, res_stats);
    mysql_stmt_execute(stmt_stats);

    MYSQL_STMT* stmt_moves = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt_moves, "SELECT * FROM adv_moves", strlen("SELECT * FROM adv_moves")) != 0) {
        mysql_stmt_close(stmt_stats); mysql_stmt_close(stmt_adv); mysql_close(conn);
        return 0;
    }
    MYSQL_BIND res_moves[5];
    res_moves[1].buffer_type = MYSQL_TYPE_LONG;
    res_moves[1].buffer = &aux->moves->move1_id;
    res_moves[2].buffer_type = MYSQL_TYPE_LONG;
    res_moves[2].buffer = &aux->moves->move2_id;
    res_moves[3].buffer_type = MYSQL_TYPE_LONG;
    res_moves[3].buffer = &aux->moves->move3_id;
    res_moves[4].buffer_type = MYSQL_TYPE_LONG;
    res_moves[4].buffer = &aux->moves->move4_id;
    mysql_stmt_bind_result(stmt_moves, res_moves);
    mysql_stmt_execute(stmt_moves);

    MYSQL_STMT* stmt_equipment = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt_equipment, "SELECT * FROM adv_equipment", strlen("SELECT * FROM adv_equipment")) != 0) {
        mysql_stmt_close(stmt_moves); mysql_stmt_close(stmt_stats); mysql_stmt_close(stmt_adv); mysql_close(conn);
        return 0;
    }
    MYSQL_BIND res_equipment[6];
    res_equipment[1].buffer_type = MYSQL_TYPE_LONG;
    res_equipment[1].buffer = &aux->equipment->helmet_id;
    res_equipment[2].buffer_type = MYSQL_TYPE_LONG;
    res_equipment[2].buffer = &aux->equipment->chestplate_id;
    res_equipment[3].buffer_type = MYSQL_TYPE_LONG;
    res_equipment[3].buffer = &aux->equipment->armlet_id;
    res_equipment[4].buffer_type = MYSQL_TYPE_LONG;
    res_equipment[4].buffer = &aux->equipment->boots_id;
    res_equipment[5].buffer_type = MYSQL_TYPE_LONG;
    res_equipment[5].buffer = &aux->equipment->weapon_id;
    mysql_stmt_bind_result(stmt_equipment, res_equipment);
    mysql_stmt_execute(stmt_equipment);

    for(int s = 0; s < TABLE_SIZE; s++) {
        entry* aux = ht->buckets[s];

        
        
    }

    free(aux->equipment);
    free(aux->moves);
    free(aux->stats);
    free(aux);

    return 1;
}