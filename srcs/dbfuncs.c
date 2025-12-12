#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#include "hashfuncs.h"

#define TABLE_SIZE 167
#define SQL_QUERY "SELECT a.id, s.name, s.class, s.lvl, s.exp, s.max_hp, s.max_mana, s.pd, s.md, m.move1, m.move2, m.move3, m.move4, e.helmet, e.chestplate, e.armlet, e.boots, e.weapon FROM adv a INNER JOIN adv_stats s ON a.id_stats = s.id INNER JOIN adv_moves m ON a.id_moves = m.id INNER JOIN adv_equipment e ON a.id_equipment = e.id;"

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
    int helmet_id=0, chestplate_id=0, armlet_id=0, boots_id=0, weapon_id=0;

    MYSQL_STMT* stmt_adv = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt_adv, SQL_QUERY, strlen(SQL_QUERY)) != 0) {
        mysql_close(conn);
        return 0;
    } 

    MYSQL_BIND res_adv[18];
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
    res_adv[13].buffer_type = MYSQL_TYPE_LONG;
    res_adv[13].buffer = &helmet_id;
    res_adv[14].buffer_type = MYSQL_TYPE_LONG;
    res_adv[14].buffer = &chestplate_id;
    res_adv[15].buffer_type = MYSQL_TYPE_LONG;
    res_adv[15].buffer = &armlet_id;
    res_adv[15].buffer_type = MYSQL_TYPE_LONG;
    res_adv[16].buffer = &boots_id;
    res_adv[17].buffer_type = MYSQL_TYPE_LONG;
    res_adv[17].buffer = &weapon_id;

    mysql_stmt_bind_result(stmt_adv, res_adv);
    mysql_stmt_execute(stmt_adv); 
    mysql_stmt_store_result(stmt_adv);
    while(mysql_stmt_fetch(stmt_adv) == 0) {
        //treat equipment id here
        ht_insert(ht, (*aux));
    }

    mysql_stmt_free_result(stmt_adv);
    mysql_stmt_close(stmt_adv);

    free(aux->equipment);
    free(aux->moves);
    free(aux->stats);
    free(aux);

    return 1;
}