#ifndef DBAUXFUNCS_H
#define DBAUXFUNCS_H

long insupd_helmet_db(MYSQL* conn, helmet_stats* h, int upd);
long insupd_chestplate_db(MYSQL* conn, chestplate_stats* c, int upd);
long insupd_armlet_db(MYSQL* conn, armlet_stats* a, int upd);
long insupd_boots_db(MYSQL* conn, boots_stats* b, int upd);
long insupd_weapon_db(MYSQL* conn, weapon_stats* w, int upd);
long insupd_equipment_db(MYSQL* conn, equipment* e, int upd);
long insupd_moves_db(MYSQL* conn, moves* m, int upd);
long insupd_stats_db(MYSQL* conn, stats* s, int upd);
long insupd_adv_db(MYSQL* conn, adv* adventurer, int upd);

#endif