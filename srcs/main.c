#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <mysql/mysql.h>

#include "structs_hash.h"
#include "freefuncs.h"
#include "hashfuncs.h"
#include "sdlfuncs.h"
#include "dbfuncs.h"
#include "filefuncs.h"

int main() {
    hashtable* ht = create_ht();

    /*
    MYSQL* conn = mysql_init(NULL);
    if(!db_to_ht_init_conn(conn, ht)) {
        mysql_close(conn); freeht(ht);
        return 1;
    }
    */

    pthread_t* t_backupdb = (pthread_t*)malloc(sizeof(pthread_t));
    if(!t_backupdb) {
        freeht(ht);
        //mysql_close(conn); 
    }
    pthread_create(t_backupdb, NULL, create_filebackup, NULL);

    if(!gameloop()) {
        freeht(ht); free(t_backupdb); 
        //mysql_close(conn);
        return 1;
    } 
    
    free(t_backupdb);
    freeht(ht);
    //mysql_close(conn);

    return 0;
}