#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#include "structs_hash.h"
#include "freefuncs.h"
#include "hashfuncs.h"
#include "sdlfuncs.h"
#include "dbfuncs.h"

int main() {
    hashtable* ht = create_ht();

    MYSQL* conn = mysql_init(NULL);
    if(!db_to_ht_init_conn(conn, ht)) {
        mysql_close(conn); freeht(ht);
        return 1;
    }
    
    printf("\n#-#-#-#-# THE RPG GAME #-#-#-#-#\n\n");
    printf("Greetings Adventure, welcome to the amazing world of *insert name*! ");

    if(!gameloop()) {
        freeht(ht); mysql_close(conn);
        return 1;
    } 

    freeht(ht);

    mysql_close(conn);

    return 0;
}