#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#include "../../hdrs/structs_adv.h"
#include "../../hdrs/dbauxfuncs.h"

#define BACKUPDB_PATH "files/backupdb.txt"
#define LOGS_PATH "files/logs/logs_all.txt"

#define SELECT "SELECT a.id, s.id, s.name, s.class, s.lvl, s.exp, s.max_hp, s.max_mana, s.pd, s.md, m.id, m.move1, m.move2, m.move3, m.move4, e.id, h.id, h.h_name, h.h_lvl, h.h_exp, h.h_defense, c.id, c.c_name, c.c_lvl, c.c_exp, c.c_defense, a2.id, a2.a_name, a2.a_lvl, a2.a_exp, a2.a_defense, b.id, b.b_name, b.b_lvl, b.b_exp, b.b_defense, w.id, w.w_name, w.w_lvl, w.w_exp, w.w_pd, w.w_md FROM adv a INNER JOIN adv_stats s ON a.id_stats = s.id INNER JOIN adv_moves m ON a.id_moves = m.id INNER JOIN adv_equipment e ON a.id_equipment = e.id INNER JOIN helmets h ON e.helmet_id = h.id INNER JOIN chestplates c ON e.chestplate_id  = c.id INNER JOIN armlets a2 ON e.armlet_id = a2.id INNER JOIN boots b ON e.boots_id = b.id INNER JOIN weapons w ON e.weapon_id = w.id;"

int create_filebackup(MYSQL* conn) {
    if(!conn) return 0;

    FILE* f = fopen(BACKUPDB_PATH, "w");

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

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, SELECT, strlen(SELECT))) {
        free(aux->equipment->b_s); free(aux->equipment->a_s); free(aux->equipment->c_s); free(aux->equipment->h_s); 
        free(aux->equipment); free(aux->moves); free(aux->stats); free(aux); mysql_stmt_close(stmt);
        return 0;
    }

    MYSQL_BIND bind[42];
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &aux->adv_id;
    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &aux->stats->s_id;
    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = aux->stats->name;
    bind[2].buffer_length = sizeof(aux->stats->name);
    bind[3].buffer_type = MYSQL_TYPE_STRING;
    bind[3].buffer = aux->stats->class;
    bind[3].buffer_length = sizeof(aux->stats->class);
    bind[4].buffer_type = MYSQL_TYPE_LONG;
    bind[4].buffer = &aux->stats->lvl;
    bind[5].buffer_type = MYSQL_TYPE_DOUBLE;
    bind[5].buffer = &aux->stats->exp;
    bind[6].buffer_type = MYSQL_TYPE_LONG;
    bind[6].buffer = &aux->stats->max_hp;
    bind[7].buffer_type = MYSQL_TYPE_LONG;
    bind[7].buffer = &aux->stats->max_mana;
    bind[8].buffer_type = MYSQL_TYPE_LONG;
    bind[8].buffer = &aux->stats->physical_dmg;
    bind[9].buffer_type = MYSQL_TYPE_LONG;
    bind[9].buffer = &aux->stats->magic_dmg;
    bind[10].buffer_type = MYSQL_TYPE_LONG;
    bind[10].buffer = &aux->moves->m_id;
    bind[11].buffer_type = MYSQL_TYPE_LONG;
    bind[11].buffer = &aux->moves->move1_id;
    bind[12].buffer_type = MYSQL_TYPE_LONG;
    bind[12].buffer = &aux->moves->move2_id;
    bind[13].buffer_type = MYSQL_TYPE_LONG;
    bind[13].buffer = &aux->moves->move3_id;
    bind[14].buffer_type = MYSQL_TYPE_LONG;
    bind[14].buffer = &aux->moves->move4_id;
    bind[15].buffer_type = MYSQL_TYPE_LONG;
    bind[15].buffer = &aux->equipment->e_id;
    bind[16].buffer_type = MYSQL_TYPE_LONG;
    bind[16].buffer = &aux->equipment->h_s->h_id;
    bind[17].buffer_type = MYSQL_TYPE_STRING;
    bind[17].buffer = aux->equipment->h_s->name;
    bind[17].buffer_length = sizeof(aux->equipment->h_s->name);
    bind[18].buffer_type = MYSQL_TYPE_LONG;
    bind[18].buffer = &aux->equipment->h_s->lvl;
    bind[19].buffer_type = MYSQL_TYPE_DOUBLE;
    bind[19].buffer = &aux->equipment->h_s->exp;
    bind[20].buffer_type = MYSQL_TYPE_LONG;
    bind[20].buffer = &aux->equipment->h_s->defense;
    bind[21].buffer_type = MYSQL_TYPE_LONG;
    bind[21].buffer = &aux->equipment->c_s->c_id;
    bind[22].buffer_type = MYSQL_TYPE_STRING;
    bind[22].buffer = aux->equipment->c_s->name;
    bind[22].buffer_length = sizeof(aux->equipment->c_s->name);
    bind[23].buffer_type = MYSQL_TYPE_LONG;
    bind[23].buffer = &aux->equipment->c_s->lvl;
    bind[24].buffer_type = MYSQL_TYPE_DOUBLE;
    bind[24].buffer = &aux->equipment->c_s->exp;
    bind[25].buffer_type = MYSQL_TYPE_LONG;
    bind[25].buffer = &aux->equipment->c_s->defense;
    bind[26].buffer_type = MYSQL_TYPE_LONG;
    bind[26].buffer = &aux->equipment->a_s->a_id;
    bind[27].buffer_type = MYSQL_TYPE_STRING;
    bind[27].buffer = aux->equipment->a_s->name;
    bind[27].buffer_length = sizeof(aux->equipment->a_s->name);
    bind[28].buffer_type = MYSQL_TYPE_LONG;
    bind[28].buffer = &aux->equipment->a_s->lvl;
    bind[29].buffer_type = MYSQL_TYPE_DOUBLE;
    bind[29].buffer = &aux->equipment->a_s->exp;
    bind[30].buffer_type = MYSQL_TYPE_LONG;
    bind[30].buffer = &aux->equipment->a_s->defense;
    bind[31].buffer_type = MYSQL_TYPE_LONG;
    bind[31].buffer = &aux->equipment->b_s->b_id;
    bind[32].buffer_type = MYSQL_TYPE_STRING;
    bind[32].buffer = aux->equipment->b_s->name;
    bind[32].buffer_length = sizeof(aux->equipment->b_s->name);
    bind[33].buffer_type = MYSQL_TYPE_LONG;
    bind[33].buffer = &aux->equipment->b_s->lvl;
    bind[34].buffer_type = MYSQL_TYPE_DOUBLE;
    bind[34].buffer = &aux->equipment->b_s->exp;
    bind[35].buffer_type = MYSQL_TYPE_LONG;
    bind[35].buffer = &aux->equipment->b_s->defense;
    bind[36].buffer_type = MYSQL_TYPE_LONG;
    bind[36].buffer = &aux->equipment->w_s->w_id;
    bind[37].buffer_type = MYSQL_TYPE_STRING;
    bind[37].buffer = aux->equipment->w_s->name;
    bind[37].buffer_length = sizeof(aux->equipment->w_s->name);
    bind[38].buffer_type = MYSQL_TYPE_LONG;
    bind[38].buffer = &aux->equipment->w_s->lvl;
    bind[39].buffer_type = MYSQL_TYPE_DOUBLE;
    bind[39].buffer = &aux->equipment->w_s->exp;
    bind[40].buffer_type = MYSQL_TYPE_LONG;
    bind[40].buffer = &aux->equipment->w_s->physical_dmg;
    bind[41].buffer_type = MYSQL_TYPE_LONG;
    bind[41].buffer = &aux->equipment->w_s->magic_dmg;
    if(mysql_stmt_bind_result(stmt, bind)) {
        free(aux->equipment->b_s); free(aux->equipment->a_s); free(aux->equipment->c_s); free(aux->equipment->h_s); 
        free(aux->equipment); free(aux->moves); free(aux->stats); free(aux); mysql_stmt_close(stmt);
        return 0;
    }

    if(mysql_stmt_execute(stmt)) {
        free(aux->equipment->b_s); free(aux->equipment->a_s); free(aux->equipment->c_s); free(aux->equipment->h_s); 
        free(aux->equipment); free(aux->moves); free(aux->stats); free(aux); mysql_stmt_close(stmt);
        return 0;
    }
    if(mysql_stmt_store_result(stmt)) {
        free(aux->equipment->b_s); free(aux->equipment->a_s); free(aux->equipment->c_s); free(aux->equipment->h_s); 
        free(aux->equipment); free(aux->moves); free(aux->stats); free(aux); mysql_stmt_close(stmt);
        return 0;
    }

    fprintf(f, "adv_id;stats_id;name;class;lvl;exp;hp;mana;pd;md;moves_id;move1;move2;move3;move4;equipment_id;helmet_id;h_name;h_lvl;h_exp;h_defense;chestplate_id;c_name;c_lvl;c_exp;c_defense;armlet_id;a_name;a_lvl;a_exp;a_defense;boots_id;b_name;b_lvl;b_exp;b_defense;weapon_id;w_name;w_lvl;w_exp;w_pd;w_md\n");
    while(mysql_stmt_fetch(stmt) == 0) { 
        fprintf(f,
            "%d;%d;%s;%s;%d;%lf;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%s;%d;%lf;%d;%d;%s;%d;%lf;%d;%d;%s;%d;%lf;%d;%d;%s;%d;%lf;%d;%d;%s;%d;%lf;%d;%d\n", 
            aux->adv_id, aux->stats->s_id, aux->stats->name, aux->stats->class, aux->stats->lvl, 
            aux->stats->exp, aux->stats->max_hp, aux->stats->max_mana, aux->stats->physical_dmg, 
            aux->stats->magic_dmg, aux->moves->m_id, aux->moves->move1_id, aux->moves->move2_id,
            aux->moves->move3_id, aux->moves->move4_id, aux->equipment->e_id, aux->equipment->h_s->h_id,
            aux->equipment->h_s->name, aux->equipment->h_s->lvl, aux->equipment->h_s->exp, aux->equipment->h_s->defense,
            aux->equipment->c_s->c_id, aux->equipment->c_s->name, aux->equipment->c_s->lvl, aux->equipment->c_s->exp, 
            aux->equipment->c_s->defense, aux->equipment->a_s->a_id, aux->equipment->a_s->name, aux->equipment->a_s->lvl, 
            aux->equipment->a_s->exp, aux->equipment->a_s->defense, aux->equipment->b_s->b_id, aux->equipment->b_s->name, 
            aux->equipment->b_s->lvl, aux->equipment->b_s->exp, aux->equipment->b_s->defense, aux->equipment->w_s->w_id, 
            aux->equipment->w_s->name, aux->equipment->w_s->lvl, aux->equipment->w_s->exp, aux->equipment->w_s->physical_dmg, 
            aux->equipment->w_s->magic_dmg); 
    }

    fclose(f);
    mysql_stmt_free_result(stmt);
    free(aux->equipment->b_s); free(aux->equipment->a_s); free(aux->equipment->c_s); free(aux->equipment->h_s); 
    free(aux->equipment); free(aux->moves); free(aux->stats); free(aux);
    mysql_stmt_close(stmt); 

    return 1;
}