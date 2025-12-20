#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#include "structs_adv.h"
#include "dbauxfuncs.h"

#define BACKUPDB_PATH "files/backupdb.txt"
#define LOGS_PATH "files/logs/logs.txt"

#define SELECT "SELECT a.id, s.id, s.name, s.class, s.lvl, s.exp, s.max_hp, s.max_mana, s.pd, s.md, m.id, m.move1, m.move2, m.move3, m.move4, e.id, h.id, h.h_name, h.h_lvl, h.h_exp, h.h_defense, c.id, c.c_name, c.c_lvl, c.c_exp, c.c_defense, a2.id, a2.a_name, a2.a_lvl, a2.a_exp, a2.a_defense, b.id, b.b_name, b.b_lvl, b.b_exp, b.b_defense, w.id, w.w_name, w.w_lvl, w.w_exp, w.w_pd, w.w_md FROM adv a INNER JOIN adv_stats s ON a.id_stats = s.id INNER JOIN adv_moves m ON a.id_moves = m.id INNER JOIN adv_equipment e ON a.id_equipment = e.id INNER JOIN helmets h ON e.helmet_id = h.id INNER JOIN chestplates c ON e.chestplate_id  = c.id INNER JOIN armlets a2 ON e.armlet_id = a2.id INNER JOIN boots b ON e.boots_id = b.id INNER JOIN weapons w ON e.weapon_id = w.id;"

int new_log(char* log) {
    if(!log) return 0;

    FILE* f = fopen(LOGS_PATH, "a"); 
    if(!f) { free(log); return 0;}

    fprintf(f, log);

    fclose(f);
    return 1;
}


// Backup a cada 6h, enquanto o jogo estiver ativo
void* create_filebackup(void* arg) {
    MYSQL* conn = (MYSQL*)arg;
    if(!conn) return NULL;

    FILE* f = fopen(BACKUPDB_PATH, "w");

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, SELECT, strlen(SELECT))) {
        mysql_stmt_close(stmt);
        return NULL;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        return NULL;
    }
    if(mysql_stmt_store_result(stmt)) {
        mysql_stmt_close(stmt);
        return NULL;
    }

    while(mysql_stmt_fetch(stmt) == 0) {
        char* newline = sprintf();
        
        fprintf(f, newline);
    }

    fclose(f);
    mysql_stmt_free_result(stmt);

    return NULL;
}