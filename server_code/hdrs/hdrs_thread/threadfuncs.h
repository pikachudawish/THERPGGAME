#ifndef THREADFUNCS_H
#define THREADFUNCS_H

#define SELECT_BACKUP "SELECT u.username, u.pass, a.id, s.id, s.name, s.class, s.lvl, s.exp, s.max_hp, s.max_mana, s.pd, s.md, m.id, m.move1, m.move2, m.move3, m.move4, e.id, h.id, h.h_name, h.h_lvl, h.h_exp, h.h_defense, c.id, c.c_name, c.c_lvl, c.c_exp, c.c_defense, a2.id, a2.a_name, a2.a_lvl, a2.a_exp, a2.a_defense, b.id, b.b_name, b.b_lvl, b.b_exp, b.b_defense, w.id, w.w_name, w.w_lvl, w.w_exp, w.w_pd, w.w_md FROM userinfo u INNER JOIN adv a ON u.adv = a.id INNER JOIN adv_stats s ON a.id_stats = s.id INNER JOIN adv_moves m ON a.id_moves = m.id INNER JOIN adv_equipment e ON a.id_equipment = e.id INNER JOIN helmets h ON e.helmet_id = h.id INNER JOIN chestplates c ON e.chestplate_id  = c.id INNER JOIN armlets a2 ON e.armlet_id = a2.id INNER JOIN boots b ON e.boots_id = b.id INNER JOIN weapons w ON e.weapon_id = w.id;"

#define USERINFO_CSV "files/backupdb/userinfo.csv"
#define ADVENTURER_CSV "files/backupdb/adventurer.csv"
#define STATS_CSV "files/backupdb/stats.csv"
#define MOVES_CSV "files/backupdb/moves.csv"
#define EQUIPMENT_CSV "files/backupdb/equipment.csv"
#define HELMET_CSV "files/backupdb/helmet.csv"
#define CHESTPLATE_CSV "files/backupdb/chestplate.csv"
#define ARMLET_CSV "files/backupdb/armlet.csv"
#define BOOTS_CSV "files/backupdb/boots.csv"
#define WEAPON_CSV "files/backupdb/weapon.csv"

#define LOG_DB "files/logs/log_db.txt"
#define LOG_SEND "files/logs/log_sent.txt"

void* commandline(void* arg);
void* db_backup(void* arg);
void* db_worker(void* arg);
void* sendpkg_worker(void* arg);

#endif