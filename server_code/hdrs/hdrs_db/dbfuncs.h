#ifndef DBFUNCS_H
#define DBFUNCS_H

#define SELECT "SELECT a.id, s.id, s.name, s.class, s.lvl, s.exp, s.max_hp, s.max_mana, s.pd, s.md, m.id, m.move1, m.move2, m.move3, m.move4, e.id, h.id, h.h_name, h.h_lvl, h.h_exp, h.h_defense, c.id, c.c_name, c.c_lvl, c.c_exp, c.c_defense, a2.id, a2.a_name, a2.a_lvl, a2.a_exp, a2.a_defense, b.id, b.b_name, b.b_lvl, b.b_exp, b.b_defense, w.id, w.w_name, w.w_lvl, w.w_exp, w.w_pd, w.w_md FROM adv a INNER JOIN adv_stats s ON a.id_stats = s.id INNER JOIN adv_moves m ON a.id_moves = m.id INNER JOIN adv_equipment e ON a.id_equipment = e.id INNER JOIN helmets h ON e.helmet_id = h.id INNER JOIN chestplates c ON e.chestplate_id  = c.id INNER JOIN armlets a2 ON e.armlet_id = a2.id INNER JOIN boots b ON e.boots_id = b.id INNER JOIN weapons w ON e.weapon_id = w.id;"
#define DELETE "DELETE FROM adv WHERE id = ?;"
#define INS_U ""
#define ADD_ADV_TO_USER "UPDATE userinfo SET adv = ? WHERE id = ?;"

int ins_user_db(MYSQL* conn, char name[30], char pass[30]);
int add_adv_to_user(MYSQL* conn, int user_id, int adv_id);
int rmv_adv_db(MYSQL* conn, int adv_id);

#endif