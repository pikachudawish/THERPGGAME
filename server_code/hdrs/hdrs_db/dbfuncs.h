#ifndef DBFUNCS_H
#define DBFUNCS_H

#include "../../hdrs/hdrs_structs/structs_adv.h"

#define SELECT "SELECT a.id, s.id, s.name, s.class, s.lvl, s.exp, s.max_hp, s.max_mana, s.pd, s.md, m.id, m.move1, m.move2, m.move3, m.move4, e.id, h.id, h.h_name, h.h_lvl, h.h_exp, h.h_defense, c.id, c.c_name, c.c_lvl, c.c_exp, c.c_defense, a2.id, a2.a_name, a2.a_lvl, a2.a_exp, a2.a_defense, b.id, b.b_name, b.b_lvl, b.b_exp, b.b_defense, w.id, w.w_name, w.w_lvl, w.w_exp, w.w_pd, w.w_md FROM adv a INNER JOIN adv_stats s ON a.id_stats = s.id INNER JOIN adv_moves m ON a.id_moves = m.id INNER JOIN adv_equipment e ON a.id_equipment = e.id INNER JOIN helmets h ON e.helmet_id = h.id INNER JOIN chestplates c ON e.chestplate_id  = c.id INNER JOIN armlets a2 ON e.armlet_id = a2.id INNER JOIN boots b ON e.boots_id = b.id INNER JOIN weapons w ON e.weapon_id = w.id;"
#define DELETE "DELETE FROM adv WHERE id = ?;"
#define INS_U "" //FALTAAA

#define ADD_ADV_TO_USER "UPDATE userinfo SET adv = ? WHERE id = ?;"

#define GET_ADV "SELECT a.id, s.id, s.name, s.class, s.lvl, s.exp, s.max_hp, s.max_mana, s.pd, s.md, m.id, m.move1, m.move2, m.move3, m.move4, e.id, h.id, h.h_name, h.h_lvl, h.h_exp, h.h_defense, c.id, c.c_name, c.c_lvl, c.c_exp, c.c_defense, a2.id, a2.a_name, a2.a_lvl, a2.a_exp, a2.a_defense, b.id, b.b_name, b.b_lvl, b.b_exp, b.b_defense, w.id, w.w_name, w.w_lvl, w.w_exp, w.w_pd, w.w_md FROM userinfo u INNER JOIN adv a ON u.adv = a.id INNER JOIN adv_stats s ON a.id_stats = s.id INNER JOIN adv_moves m ON a.id_moves = m.id INNER JOIN adv_equipment e ON a.id_equipment = e.id INNER JOIN helmets h ON e.helmet_id = h.id INNER JOIN chestplates c ON e.chestplate_id  = c.id INNER JOIN armlets a2 ON e.armlet_id = a2.id INNER JOIN boots b ON e.boots_id = b.id INNER JOIN weapons w ON e.weapon_id = w.id WHERE u.username = ?;"

#define INS_H "INSERT INTO helmets (h_name, h_lvl, h_exp, h_defense) VALUES (?, ?, ?, ?);"
#define INS_C "INSERT INTO chestplates (c_name, c_lvl, c_exp, c_defense) VALUES (?, ?, ?, ?);"
#define INS_A "INSERT INTO armlets (a_name, a_lvl, a_exp, a_defense) VALUES (?, ?, ?, ?);"
#define INS_B "INSERT INTO boots (b_name, b_lvl, b_exp, b_defense) VALUES (?, ?, ?, ?);"
#define INS_W "INSERT INTO weapons (w_name, w_lvl, w_exp, w_pd, w_md) VALUES (?, ?, ?, ?, ?);"
#define INS_E "INSERT INTO adv_equipment (helmet_id, chestplate_id, armlet_id, boots_id, weapon_id) VALUES (?, ?, ?, ?, ?);"
#define INS_M "INSERT INTO adv_moves (move1, move2, move3, move4) VALUES (?, ?, ?, ?);"
#define INS_S "INSERT INTO adv_stats (name, class, lvl, exp, max_hp, max_mana, pd, md) VALUES (?, ?, ?, ?, ?, ?, ?, ?);"
#define INS_ADV "INSERT INTO adv (id_stats, id_moves, id_equipment) VALUES (?, ?, ?) WHERE;"

#define UPD_H "UPDATE helmets SET h_id = ?, h_name = ?, h_lvl = ?, h_exp = ?, h_defense = ? WHERE id = ?;"
#define UPD_C "UPDATE chestplate SET c_name = ?, c_lvl = ?, c_exp = ?, c_defense = ? WHERE id = ?;"
#define UPD_A "UPDATE armlets SET a_name = ?, a_lvl = ?, a_exp = ?, a_defense = ? WHERE id = ?;"
#define UPD_B "UPDATE boots SET b_name = ?, b_lvl = ?, b_exp = ?, b_defense = ? WHERE id = ?;"
#define UPD_W "UPDATE weapons SET w_name = ?, w_lvl = ?, w_exp = ?, w_pd = ?, w_md = ? WHERE id = ?;"
#define UPD_E "UPDATE adv_equipment SET helmet_id = ?, chestplate_id = ?, armlet_id = ?, boots_id = ?, weapond_id = ? WHERE id = ?;"
#define UPD_M "UPDATE adv_moves SET move1 = ?, move2 = ?, move3 = ?, move4 = ? WHERE id = ?;"
#define UPD_S "UPDATE adv_stats SET name = ?, class = ?, lvl = ?, exp = ?, max_hp = ?, max_mana = ?, pd = ?, md = ? WHERE id = ?;"
#define UPD_ADV "UPDATE adv SET id_stats = ?, id_moves = ?, id_equipment = ? WHERE id = ?;"
#define UPD_U "UPDATE userinfo SET username = ?, pass = ?, adv = ?; WHERE id = ?;"

adv get_adv_db(MYSQL* conn, char* username);

long vrf_ui_db(MYSQL* conn, user_info* ui);

long ins_helmet_db(MYSQL* conn, helmet_stats* h);
long ins_chestplate_db(MYSQL* conn, chestplate_stats* c);
long ins_armlet_db(MYSQL* conn, armlet_stats* a);
long ins_boots_db(MYSQL* conn, boots_stats* b);
long ins_weapon_db(MYSQL* conn, weapon_stats* w);
long ins_equipment_db(MYSQL* conn, equipment* e);
long ins_moves_db(MYSQL* conn, moves* m);
long ins_stats_db(MYSQL* conn, stats* s);
long ins_adv_db(MYSQL* conn, adv* adventurer);
int ins_user_db(MYSQL* conn, char name[30], char pass[30]);

int upd_helmet_db(MYSQL* conn, helmet_stats* h);
int upd_chestplate_db(MYSQL* conn, chestplate_stats* c);
int upd_armlet_db(MYSQL* conn, armlet_stats* a);
int upd_boots_db(MYSQL* conn, boots_stats* b);
int upd_weapon_db(MYSQL* conn, weapon_stats* w);
int upd_equipment_db(MYSQL* conn, equipment* e);
int upd_moves_db(MYSQL* conn, moves* m);
int upd_stats_db(MYSQL* conn, stats* s);
int upd_adv_db(MYSQL* conn, adv* adventurer);
int upd_user_db(MYSQL* conn, user_info* u);

int add_adv_to_user(MYSQL* conn, int user_id, int adv_id);

int rmv_adv_db(MYSQL* conn, int adv_id);

#endif