#ifndef DBFUNCS_H
#define DBFUNCS_H

int db_to_ht_init_conn(MYSQL* conn, hashtable* ht);
int ins_upd_db(MYSQL* conn, adv* adventurer, int insorupd);
int rmv_db(MYSQL* conn, int adv_id);

#endif