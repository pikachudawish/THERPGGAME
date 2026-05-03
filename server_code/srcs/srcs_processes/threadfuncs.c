#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <mysql/mysql.h>

#include <sys/types.h>
#include <sys/socket.h>

#include "../../hdrs/hdrs_structs/structs_server.h"
#include "../../hdrs/hdrs_structs/structs_adv.h"
#include "../../hdrs/hdrs_aux/globalvariable.h"

#include "../../hdrs/hdrs_aux/freefuncs.h"
#include "../../hdrs/hdrs_db/dbfuncs.h"
#include "../../hdrs/hdrs_thread/threadfuncs.h"

void* commandline(void* arg) {    
    int end = 0, opt = 0;

    char buffer[100];
    while(!end) {
        printf("->> ");
        fgets(buffer, 100, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if(!(*server)) return NULL;

        if(strcasecmp(buffer, "h") == 0 || strcasecmp(buffer, "help") == 0) opt = 1;
        if(strcasecmp(buffer, "quit") == 0) opt = 2;

        switch(opt) {
            case 1:
                printf("\nAll Commands:\n \"quit\" --> Shutsdown Server\n");
                break;
            case 2:
                printf("\nEnding Programm...");
                *server = 0;
                end = 1;
                break;
            default:
                printf("\nInvalid Input!");
                break;
        }
    }
    printf("\n");

    return NULL;
} 

void* db_backup(void* arg) {
    MYSQL* conn = (MYSQL*)arg;

    user_info* aux = (user_info*)malloc(sizeof(user_info));
    if(!aux) return 0;

    aux->adventurer = (adv*)malloc(sizeof(adv));
    if(!aux->adventurer) {
        free(aux);
        return 0;
    }
    aux->adventurer->stats = (stats*)malloc(sizeof(stats));
    if(!aux->adventurer->stats) {
        free(aux->adventurer); free(aux);
        return 0;
    }
    aux->adventurer->moves = (moves*)malloc(sizeof(moves));
    if(!aux->adventurer->moves) {
        free(aux->adventurer->stats); free(aux->adventurer); free(aux);
        return 0;
    }
    aux->adventurer->equipment = (equipment*)malloc(sizeof(equipment));
    if(!aux->adventurer->equipment) {
        free(aux->adventurer->moves); free(aux->adventurer->stats); free(aux->adventurer); free(aux);
        return 0;
    }
    aux->adventurer->equipment->h_s = (helmet_stats*)malloc(sizeof(helmet_stats));
    if(!aux->adventurer->equipment->h_s) {
        free(aux->adventurer->equipment); free(aux->adventurer->moves); free(aux->adventurer->stats); 
        free(aux->adventurer); free(aux);
        return 0;
    }
    aux->adventurer->equipment->c_s = (chestplate_stats*)malloc(sizeof(chestplate_stats));
    if(!aux->adventurer->equipment->c_s) {
        free(aux->adventurer->equipment->h_s); free(aux->adventurer->equipment); free(aux->adventurer->moves); 
        free(aux->adventurer->stats); free(aux->adventurer); free(aux);
        return 0;
    }
    aux->adventurer->equipment->a_s = (armlet_stats*)malloc(sizeof(armlet_stats));
    if(!aux->adventurer->equipment->a_s) {
        free(aux->adventurer->equipment->c_s); free(aux->adventurer->equipment->h_s); free(aux->adventurer->equipment); 
        free(aux->adventurer->moves); free(aux->adventurer->stats); free(aux->adventurer); free(aux);
        return 0;
    }
    aux->adventurer->equipment->b_s = (boots_stats*)malloc(sizeof(boots_stats));
    if(!aux->adventurer->equipment->b_s) {
        free(aux->adventurer->equipment->a_s); free(aux->adventurer->equipment->c_s); 
        free(aux->adventurer->equipment->h_s); free(aux->adventurer->equipment); free(aux->adventurer->moves); 
        free(aux->adventurer->stats); free(aux->adventurer); free(aux);
        return 0;
    }
    aux->adventurer->equipment->w_s = (weapon_stats*)malloc(sizeof(weapon_stats));
    if(!aux->adventurer->equipment->w_s) {
        free(aux->adventurer->equipment->b_s); free(aux->adventurer->equipment->a_s); free(aux->adventurer->equipment->c_s); 
        free(aux->adventurer->equipment->h_s); free(aux->adventurer->equipment); free(aux->adventurer->moves); 
        free(aux->adventurer->stats); free(aux->adventurer); free(aux);
        return 0;
    }

    while(*server) {
        MYSQL_STMT* stmt_adv = mysql_stmt_init(conn);
        if(mysql_stmt_prepare(stmt_adv, SELECT_BACKUP, strlen(SELECT_BACKUP)) != 0) {
            free(aux->adventurer->equipment->b_s); free(aux->adventurer->equipment->a_s); free(aux->adventurer->equipment->c_s); 
            free(aux->adventurer->equipment->h_s); free(aux->adventurer->equipment); free(aux->adventurer->moves); 
            free(aux->adventurer->stats); free(aux->adventurer); free(aux);
            mysql_stmt_close(stmt_adv);
            return 0;
        }

        MYSQL_BIND bind[44];
        memset(bind, 0, sizeof(bind));
        bind[0].buffer_type = MYSQL_TYPE_STRING;
        bind[0].buffer = aux->user_name;
        bind[0].buffer_length = sizeof(aux->user_name);
        bind[1].buffer_type = MYSQL_TYPE_STRING;
        bind[1].buffer = aux->pass;
        bind[1].buffer_length = sizeof(aux->pass);
        bind[2].buffer_type = MYSQL_TYPE_LONG;
        bind[2].buffer = &aux->adventurer->adv_id;
        bind[3].buffer_type = MYSQL_TYPE_LONG;
        bind[3].buffer = &aux->adventurer->stats->s_id;
        bind[4].buffer_type = MYSQL_TYPE_STRING;
        bind[4].buffer = aux->adventurer->stats->name;
        bind[4].buffer_length = sizeof(aux->adventurer->stats->name);
        bind[5].buffer_type = MYSQL_TYPE_STRING;
        bind[5].buffer = aux->adventurer->stats->class;
        bind[5].buffer_length = sizeof(aux->adventurer->stats->class);
        bind[6].buffer_type = MYSQL_TYPE_LONG;
        bind[6].buffer = &aux->adventurer->stats->lvl;
        bind[7].buffer_type = MYSQL_TYPE_DOUBLE;
        bind[7].buffer = &aux->adventurer->stats->exp;
        bind[8].buffer_type = MYSQL_TYPE_LONG;
        bind[8].buffer = &aux->adventurer->stats->max_hp;
        bind[9].buffer_type = MYSQL_TYPE_LONG;
        bind[9].buffer = &aux->adventurer->stats->max_mana;
        bind[10].buffer_type = MYSQL_TYPE_LONG;
        bind[10].buffer = &aux->adventurer->stats->physical_dmg;
        bind[11].buffer_type = MYSQL_TYPE_LONG;
        bind[11].buffer = &aux->adventurer->stats->magic_dmg;
        bind[12].buffer_type = MYSQL_TYPE_LONG;
        bind[12].buffer = &aux->adventurer->moves->m_id;
        bind[13].buffer_type = MYSQL_TYPE_LONG;
        bind[13].buffer = &aux->adventurer->moves->move1_id;
        bind[14].buffer_type = MYSQL_TYPE_LONG;
        bind[14].buffer = &aux->adventurer->moves->move2_id;
        bind[15].buffer_type = MYSQL_TYPE_LONG;
        bind[15].buffer = &aux->adventurer->moves->move3_id;
        bind[16].buffer_type = MYSQL_TYPE_LONG;
        bind[16].buffer = &aux->adventurer->moves->move4_id;
        bind[17].buffer_type = MYSQL_TYPE_LONG;
        bind[17].buffer = &aux->adventurer->equipment->e_id;
        bind[18].buffer_type = MYSQL_TYPE_LONG;
        bind[18].buffer = &aux->adventurer->equipment->h_s->h_id;
        bind[19].buffer_type = MYSQL_TYPE_STRING;
        bind[19].buffer = aux->adventurer->equipment->h_s->name;
        bind[19].buffer_length = sizeof(aux->adventurer->equipment->h_s->name);
        bind[20].buffer_type = MYSQL_TYPE_LONG;
        bind[20].buffer = &aux->adventurer->equipment->h_s->lvl;
        bind[21].buffer_type = MYSQL_TYPE_DOUBLE;
        bind[21].buffer = &aux->adventurer->equipment->h_s->exp;
        bind[22].buffer_type = MYSQL_TYPE_LONG;
        bind[22].buffer = &aux->adventurer->equipment->h_s->defense;
        bind[23].buffer_type = MYSQL_TYPE_LONG;
        bind[23].buffer = &aux->adventurer->equipment->c_s->c_id;
        bind[24].buffer_type = MYSQL_TYPE_STRING;
        bind[24].buffer = aux->adventurer->equipment->c_s->name;
        bind[24].buffer_length = sizeof(aux->adventurer->equipment->c_s->name);
        bind[25].buffer_type = MYSQL_TYPE_LONG;
        bind[25].buffer = &aux->adventurer->equipment->c_s->lvl;
        bind[26].buffer_type = MYSQL_TYPE_DOUBLE;
        bind[26].buffer = &aux->adventurer->equipment->c_s->exp;
        bind[27].buffer_type = MYSQL_TYPE_LONG;
        bind[27].buffer = &aux->adventurer->equipment->c_s->defense;
        bind[28].buffer_type = MYSQL_TYPE_LONG;
        bind[28].buffer = &aux->adventurer->equipment->a_s->a_id;
        bind[29].buffer_type = MYSQL_TYPE_STRING;
        bind[29].buffer = aux->adventurer->equipment->a_s->name;
        bind[29].buffer_length = sizeof(aux->adventurer->equipment->a_s->name);
        bind[30].buffer_type = MYSQL_TYPE_LONG;
        bind[30].buffer = &aux->adventurer->equipment->a_s->lvl;
        bind[31].buffer_type = MYSQL_TYPE_DOUBLE;
        bind[31].buffer = &aux->adventurer->equipment->a_s->exp;
        bind[32].buffer_type = MYSQL_TYPE_LONG;
        bind[32].buffer = &aux->adventurer->equipment->a_s->defense;
        bind[33].buffer_type = MYSQL_TYPE_LONG;
        bind[33].buffer = &aux->adventurer->equipment->b_s->b_id;
        bind[34].buffer_type = MYSQL_TYPE_STRING;
        bind[34].buffer = aux->adventurer->equipment->b_s->name;
        bind[34].buffer_length = sizeof(aux->adventurer->equipment->b_s->name);
        bind[35].buffer_type = MYSQL_TYPE_LONG;
        bind[35].buffer = &aux->adventurer->equipment->b_s->lvl;
        bind[36].buffer_type = MYSQL_TYPE_DOUBLE;
        bind[36].buffer = &aux->adventurer->equipment->b_s->exp;
        bind[37].buffer_type = MYSQL_TYPE_LONG;
        bind[37].buffer = &aux->adventurer->equipment->b_s->defense;
        bind[38].buffer_type = MYSQL_TYPE_LONG;
        bind[38].buffer = &aux->adventurer->equipment->w_s->w_id;
        bind[39].buffer_type = MYSQL_TYPE_STRING;
        bind[39].buffer = aux->adventurer->equipment->w_s->name;
        bind[39].buffer_length = sizeof(aux->adventurer->equipment->w_s->name);
        bind[40].buffer_type = MYSQL_TYPE_LONG;
        bind[40].buffer = &aux->adventurer->equipment->w_s->lvl;
        bind[41].buffer_type = MYSQL_TYPE_DOUBLE;
        bind[41].buffer = &aux->adventurer->equipment->w_s->exp;
        bind[42].buffer_type = MYSQL_TYPE_LONG;
        bind[42].buffer = &aux->adventurer->equipment->w_s->physical_dmg;
        bind[43].buffer_type = MYSQL_TYPE_LONG;
        bind[43].buffer = &aux->adventurer->equipment->w_s->magic_dmg;
        
        mysql_stmt_bind_result(stmt_adv, bind);
        mysql_stmt_execute(stmt_adv); 
        mysql_stmt_store_result(stmt_adv);

        FILE* userinfo_csv = fopen(USERINFO_CSV, "w");
        FILE* adventurer_csv = fopen(ADVENTURER_CSV, "w");
        FILE* stats_csv = fopen(STATS_CSV, "w");
        FILE* moves_csv = fopen(MOVES_CSV, "w");
        FILE* equipment_csv = fopen(EQUIPMENT_CSV, "w");
        FILE* helmet_csv = fopen(HELMET_CSV, "w");
        FILE* chesplate_csv = fopen(CHESTPLATE_CSV, "w");
        FILE* armlet_csv = fopen(ARMLET_CSV, "w");
        FILE* boots_csv = fopen(BOOTS_CSV, "w");
        FILE* weapon_csv = fopen(WEAPON_CSV, "w");

        fprintf(userinfo_csv, "user;pass;adv_id\n");
        fprintf(adventurer_csv, "adv_id;stats_id;moves_id;equipment_id\n");
        fprintf(stats_csv, "stats_id;name;class;lvl;exp;maxhp;maxmana;physical_dmg;magical_dmg\n");
        fprintf(moves_csv, "moves_id;move1;move2;move3;move4\n");
        fprintf(equipment_csv, "equipment_id;helmet_id;chestplate_id;armlet_id;boots_id;weapon_id\n");
        fprintf(helmet_csv, "helmet_id;helmet_name;helmet_lvl;helmet_exp;helmet_def\n");
        fprintf(chesplate_csv, "chestplate_id;chestplate_name;chestplate_lvl;chestplate_exp;chestplate_def\n");
        fprintf(armlet_csv, "armlet_id;armlet_name;armlet_lvl;armlet_exp;armlet_def\n");
        fprintf(boots_csv, "boots_id;boots_name;boots_lvl;boots_exp;boots_def\n");
        fprintf(weapon_csv, "weapon_id;weapon_name;weapon_lvl;weapon_exp;weapon_physical_dmg;weapon_magical_dmg\n");
        while(mysql_stmt_fetch(stmt_adv) == 0) {
            fprintf(userinfo_csv, "%s;%s;%d\n", 
                aux->user_name, aux->pass, aux->adventurer->adv_id);
            fprintf(adventurer_csv, "%d;%d;%d;%d\n", 
                aux->adventurer->adv_id, aux->adventurer->stats->s_id, aux->adventurer->moves->m_id, aux->adventurer->equipment->e_id);
            fprintf(stats_csv, "%d;%s;%s;%d;%lf;%d;%d;%d;%d\n",
                aux->adventurer->stats->s_id, aux->adventurer->stats->name, aux->adventurer->stats->class, aux->adventurer->stats->lvl,
                aux->adventurer->stats->exp, aux->adventurer->stats->max_hp, aux->adventurer->stats->max_mana, 
                aux->adventurer->stats->physical_dmg, aux->adventurer->stats->magic_dmg);
            fprintf(moves_csv, "%d;%d;%d;%d;%d\n", 
                aux->adventurer->moves->m_id, aux->adventurer->moves->move1_id, aux->adventurer->moves->move2_id, 
                aux->adventurer->moves->move3_id, aux->adventurer->moves->move4_id);
            fprintf(equipment_csv, "%d;%d;%d;%d;%d;%d\n", 
                aux->adventurer->equipment->e_id, aux->adventurer->equipment->h_s->h_id, aux->adventurer->equipment->c_s->c_id, 
                aux->adventurer->equipment->a_s->a_id, aux->adventurer->equipment->b_s->b_id, aux->adventurer->equipment->w_s->w_id);
            fprintf(helmet_csv, "%d;%s;%d;%lf;%d\n",
                aux->adventurer->equipment->h_s->h_id, aux->adventurer->equipment->h_s->name, aux->adventurer->equipment->h_s->lvl,
                aux->adventurer->equipment->h_s->exp, aux->adventurer->equipment->h_s->defense);
            fprintf(chesplate_csv, "%d;%s;%d;%lf;%d\n",
                aux->adventurer->equipment->c_s->c_id, aux->adventurer->equipment->c_s->name, aux->adventurer->equipment->c_s->lvl,
                aux->adventurer->equipment->c_s->exp, aux->adventurer->equipment->c_s->defense);
            fprintf(armlet_csv, "%d;%s;%d;%lf;%d\n",
                aux->adventurer->equipment->a_s->a_id, aux->adventurer->equipment->a_s->name, aux->adventurer->equipment->a_s->lvl,
                aux->adventurer->equipment->a_s->exp, aux->adventurer->equipment->a_s->defense);
            fprintf(boots_csv, "%d;%s;%d;%lf;%d\n",
                aux->adventurer->equipment->b_s->b_id, aux->adventurer->equipment->b_s->name, aux->adventurer->equipment->b_s->lvl,
                aux->adventurer->equipment->b_s->exp, aux->adventurer->equipment->b_s->defense);
            fprintf(weapon_csv, "%d;%s;%d;%lf;%d;%d\n",
                aux->adventurer->equipment->w_s->w_id, aux->adventurer->equipment->w_s->name, aux->adventurer->equipment->w_s->lvl,
                aux->adventurer->equipment->w_s->exp, aux->adventurer->equipment->w_s->physical_dmg, aux->adventurer->equipment->w_s->magic_dmg);
        }
        fclose(userinfo_csv); fclose(adventurer_csv); fclose(stats_csv); fclose(moves_csv); fclose(equipment_csv); 
        fclose(helmet_csv); fclose(chesplate_csv); fclose(armlet_csv); fclose(boots_csv); fclose(weapon_csv);

        mysql_stmt_free_result(stmt_adv);
        mysql_stmt_close(stmt_adv);

        sleep(90); if(!(*server)) break;
        sleep(90); if(!(*server)) break;
        sleep(90); if(!(*server)) break;
        sleep(90); if(!(*server)) break;
        sleep(90); if(!(*server)) break;
        sleep(90); if(!(*server)) break;
        sleep(90); if(!(*server)) break;
        sleep(90); if(!(*server)) break;
        sleep(90); if(!(*server)) break;
        sleep(90); if(!(*server)) break;
    }
    
    free(aux->adventurer->equipment->h_s);
    free(aux->adventurer->equipment->c_s);
    free(aux->adventurer->equipment->a_s);
    free(aux->adventurer->equipment->b_s);
    free(aux->adventurer->equipment->w_s);
    free(aux->adventurer->equipment);
    free(aux->adventurer->moves);
    free(aux->adventurer->stats);
    free(aux->adventurer);
    free(aux);

    return NULL;
} 

void* db_worker(void* arg) {
    MYSQL* conn = (MYSQL*)arg;

    FILE* logdb_file = fopen(LOG_DB, "a");

    while(*server || (db_queue_head != NULL)) {
        pthread_mutex_lock(&db_mutex);

        while (!db_queue_head) {
            pthread_cond_wait(&db_cond, &db_mutex);
            if(!(*server)) {
                free_dbtask(db_queue_head);
                fclose(logdb_file);
                return NULL;
            }
        }

        dbtask* task = db_queue_head;
        db_queue_head = task->next;
        if (db_queue_head == NULL) db_queue_tail = NULL;

        pthread_mutex_unlock(&db_mutex); 
        
        switch(task->type) {
            case DBTASK_GET_ADV:
                char* username = (char*)task->data;

                adv data = get_adv_db(conn, username);
                if(data.adv_id == -1) {
                    fprintf(logdb_file, "[ERROR] Aborted rallying adv information about client: %d\n", task->client_fd);
                    fprintf(stderr, "[ERROR] Aborted rallying adv information about client: %d\n", task->client_fd);
                    break;
                }
                fprintf(logdb_file, "[DB] Successfully got adv info for cli: %d\n", task->client_fd);

                packagelist* new_task = (package*)malloc(sizeof(package));
                if(!new_task) return 0;

                new_task->pkg.type = PKG_GET_ADV;
                new_task->pkg.cli_fd = task->client_fd;
                new_task->pkg.data.adventurer = data;
                new_task->next = NULL;

                pthread_mutex_lock(&send_mutex);

                if(!pkglist_queue_tail) { 
                    pkglist_queue_head = new_task;
                    pkglist_queue_tail = new_task;
                } else {
                    pkglist_queue_tail->next = new_task;
                    pkglist_queue_tail = new_task;
                }

                pthread_cond_signal(&send_cond);
                pthread_mutex_unlock(&send_mutex);        
                break;
            case DBTASK_INS_UI:
                char** userinfo = (char**)task->data;
                if(!ins_user_db(conn, userinfo[0], userinfo[1])) {
                    fprintf(logdb_file, "[ERROR] Aborted Insertion of the user: %s\n", userinfo[0]);
                    fprintf(stderr, "[ERROR] Aborted Insertion of the user: %s\n", userinfo[0]);
                    break;
                }
                fprintf(logdb_file, "[DB] Successfully Inserted the user: %s\n", userinfo[0]);
                break;
            case DBTASK_ADD_ADV_TO_USER:
                int* ids = (int*)task->data;
                if(!add_adv_to_user(conn, ids[0], ids[1])) {
                    fprintf(logdb_file, "[ERROR] Aborted Adding adventurer nº%d to the user nº%d\n", ids[0], ids[1]);
                    fprintf(stderr, "[ERROR] Aborted Adding adventurer nº%d to the user nº%d\n", ids[0], ids[1]); break;
                }
                fprintf(logdb_file, "[DB] Successfully Added adventurer nº%d to the user nº%d\n", ids[0], ids[1]);
                break;
            case DBTASK_INS:
                adv* adventurer_ins = (adv*)task->data;
                if(!ins_adv_db(conn, adventurer_ins)) {
                    fprintf(logdb_file, "[ERROR] Aborted Insertion of the adventurer nº%d\n", adventurer_ins->adv_id);
                    fprintf(stderr, "[ERROR] Aborted Insertion of the adventurer nº%d\n", adventurer_ins->adv_id); break;
                } 
                fprintf(logdb_file, "[DB] Successfully Inserted the adventurer nº%d\n", adventurer_ins->adv_id);
                break;
            case DBTASK_UPD_UI:
                user_info* u = (user_info*)task->data;
                if(!upd_user_db(conn, u)) {
                    fprintf(logdb_file, "[ERROR] Aborted Update of the user nº%d\n", u->id);
                    fprintf(stderr, "[ERROR] Aborted Update of the user nº%d\n", u->id); break;
                } 
                fprintf(logdb_file, "[DB] Successfully Updated the user nº%d\n", u->id);
                break;
            case DBTASK_UPD_ADV:
                adv* adventurer_upd = (adv*)task->data;
                if(!upd_adv_db(conn, adventurer_upd)) {
                    fprintf(logdb_file, "[ERROR] Aborted Update of the adventurer nº%d\n", adventurer_upd->adv_id);
                    fprintf(stderr, "[ERROR] Aborted Update of the adventurer nº%d\n", adventurer_upd->adv_id); break;
                }
                fprintf(logdb_file, "[DB] Successfully Updated the adventurer nº%d\n", adventurer_upd->adv_id);
                break;
            case DBTASK_UPD_S:
                stats* s = (stats*)task->data;
                if(!upd_stats_db(conn, s)) {
                    fprintf(logdb_file, "[ERROR] Aborted Update of the stats nº%d\n", s->s_id);
                    fprintf(stderr, "[ERROR] Aborted Update of the stats nº%d\n", s->s_id); break;
                }
                fprintf(logdb_file, "[DB] Successfully Updated the stats nº%d\n", s->s_id);
                break;
            case DBTASK_UPD_M:
                moves* m = (moves*)task->data;
                if(!upd_moves_db(conn, m)) {
                    fprintf(logdb_file, "[ERROR] Aborted Update of the moves nº%d\n", m->m_id);
                    fprintf(stderr, "[ERROR] Aborted Update of the moves nº%d\n", m->m_id); break;
                }
                fprintf(logdb_file, "[DB] Successfully Updated the moves nº%d\n", m->m_id);
                break;
            case DBTASK_UPD_E:
                equipment* e = (equipment*)task->data;
                if(!upd_equipment_db(conn, e)) {
                    fprintf(logdb_file, "[ERROR] Aborted Update of the equipment nº%d\n", e->e_id);
                    fprintf(stderr, "[ERROR] Aborted Update of the equipment nº%d\n", e->e_id); break;
                }
                fprintf(logdb_file, "[DB] Successfully Updated the equipment nº%d\n", e->e_id);
                break;
            case DBTASK_UPD_H:
                helmet_stats* h = (helmet_stats*)task->data;
                if(!upd_helmet_db(conn, h)) {
                    fprintf(logdb_file, "[ERROR] Aborted Update of the helmet nº%d\n", h->h_id);
                    fprintf(stderr, "[ERROR] Aborted Update of the helmet nº%d\n", h->h_id); break;
                }
                fprintf(logdb_file, "[DB] Successfully Updated the helmet nº%d\n", h->h_id);
                break;
            case DBTASK_UPD_C:
                chestplate_stats* c = (chestplate_stats*)task->data;
                if(!upd_chestplate_db(conn, c)) {
                    fprintf(logdb_file, "[ERROR] Aborted Update of the chestplate nº%d\n", c->c_id);
                    fprintf(stderr, "[ERROR] Aborted Update of the chestplate nº%d\n", c->c_id); break;
                }
                fprintf(logdb_file, "[DB] Successfully Updated the chestplate nº%d\n", c->c_id);
                break;
            case DBTASK_UPD_A:
                armlet_stats* a = (armlet_stats*)task->data;
                if(!upd_armlet_db(conn, a)) {
                    fprintf(logdb_file, "[ERROR] Aborted Update of the armlet nº%d\n", a->a_id);
                    fprintf(stderr, "[ERROR] Aborted Update of the armlet nº%d\n", a->a_id); break;
                }
                fprintf(logdb_file, "[DB] Successfully Updated the armlet nº%d\n", a->a_id);
                break;
            case DBTASK_UPD_B:
                boots_stats* b = (boots_stats*)task->data;
                if(!upd_boots_db(conn, b)) {
                    fprintf(logdb_file, "[ERROR] Aborted Update of the boots nº%d\n", b->b_id);
                    fprintf(stderr, "[ERROR] Aborted Update of the boots nº%d\n", b->b_id); break;
                }
                fprintf(logdb_file, "[DB] Successfully Updated the boots nº%d\n", b->b_id);
                break;
            case DBTASK_UPD_W:
                weapon_stats* w = (weapon_stats*)task->data;
                if(!upd_weapon_db(conn, w)) {
                    fprintf(logdb_file, "[ERROR] Aborted Update of the weapon nº%d\n", w->w_id);
                    fprintf(stderr, "[ERROR] Aborted Update of the weapon nº%d\n", w->w_id); break;
                }
                fprintf(logdb_file, "[DB] Successfully Updated the weapon nº%d\n", w->w_id);
                break;
            case DBTASK_RMV:
                adv* adventurer_rmv = (adv*)task->data;
                if(!rmv_adv_db(conn, adventurer_rmv->adv_id)) {
                    fprintf(logdb_file, "[ERROR] Aborted Remove of the adventurer nº%d\n", adventurer_rmv->adv_id);
                    fprintf(stderr, "[ERROR] Aborted Remove of the adventurer nº%d\n", adventurer_rmv->adv_id); break;
                }
                fprintf(logdb_file, "[DB] Successfully Removed the adventurer nº%d\n", adventurer_rmv->adv_id);
                break;

            case DBTASK_VRF_UI:
                user_info* ui = (user_info*)task->data;
                if(!vrf_ui_db(conn, ui)) {
                    fprintf(logdb_file, "[ERROR] Aborted the verification of userinfo nº%d\n", adventurer_rmv->adv_id);
                    fprintf(stderr, "[ERROR] Aborted the verification of userinfo  nº%d\n", adventurer_rmv->adv_id); break;
                }
                fprintf(logdb_file, "[DB] Successfully verificated userinfo nº%d\n", adventurer_rmv->adv_id);

                break;
        }

        free(task);
    }
    fclose(logdb_file);

    return NULL;
}

void* sendpkg_worker(void* arg) {
    FILE* logsend_file = fopen(LOG_SEND, "a");
    if(!logsend_file) return NULL;

    while(*server || (pkglist_queue_head != NULL)) {
        pthread_mutex_lock(&send_mutex);

        while(!pkglist_queue_head) {
            pthread_cond_wait(&send_cond, &send_mutex);
            if(!(*server)) {
                free_sendtask(pkglist_queue_head);
                fclose(logsend_file); 
                return NULL;
            }
        }

        packagelist* task = pkglist_queue_head;
        pkglist_queue_head = task->next;
        if(!pkglist_queue_head) pkglist_queue_tail = NULL;

        pthread_mutex_unlock(&send_mutex); 

        switch(task->pkg.type) {
            case PKG_GET_ADV:
                if(send(task->pkg.cli_fd, &task->pkg, sizeof(task->pkg), 0) < 0) {
                    fprintf(logsend_file, "[ERROR] Failed to send the pkg to cli: %d\n", task->pkg.cli_fd);
                    break;
                }
                fprintf(logsend_file, "[SUCESS] Pkg sent to cli: %d\n", task->pkg.cli_fd);
                break;
            
        }
        
        free(task); 
    }
    fclose(logsend_file);
    
    return NULL;
}



