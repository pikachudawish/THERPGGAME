#ifndef DBAUXFUNCS_H
#define DBAUXFUNCS_H

long ins_helmet_db(MYSQL* conn, helmet_stats* h);
long ins_chestplate_db(MYSQL* conn, chestplate_stats* c);
long ins_armlet_db(MYSQL* conn, armlet_stats* a);
long ins_boots_db(MYSQL* conn, boots_stats* b);
long ins_weapon_db(MYSQL* conn, weapon_stats* w);
long ins_equipment_db(MYSQL* conn, equipment* e);
long ins_moves_db(MYSQL* conn, moves* m);
long ins_stats_db(MYSQL* conn, stats* s);
long ins_adv_db(MYSQL* conn, adv* adventurer);

int upd_helmet_db(MYSQL* conn, helmet_stats* h);
int upd_chestplate_db(MYSQL* conn, chestplate_stats* h);
int upd_armlet_db(MYSQL* conn, armlet_stats* h);
int upd_boots_db(MYSQL* conn, boots_stats* h);
int upd_weapon_db(MYSQL* conn, weapon_stats* h);
int upd_equipment_db(MYSQL* conn, equipment* h);
int upd_moves_db(MYSQL* conn, moves* h);
int upd_stats_db(MYSQL* conn, stats* h);
int upd_adv_db(MYSQL* conn, adv* h);


#endif