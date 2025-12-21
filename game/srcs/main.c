#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#include "../../hdrs/structs_hash.h"
#include "../../hdrs/freefuncs.h"
#include "../../hdrs/hashfuncs.h"
#include "../../hdrs/sdlfuncs.h"
#include "../../hdrs/dbfuncs.h"
#include "../../hdrs/filefuncs.h"

int main(int argc, char* argv[]) {
    hashtable* ht = create_ht();

    MYSQL* conn = mysql_init(NULL);
    if(!db_to_ht_init_conn(conn, ht)) {
        mysql_close(conn); freeht(ht);
        return 1;
    }
    
    if(!gameloop()) {
        freeht(ht); mysql_close(conn);
        return 1;
    } 

    freeht(ht);
    mysql_close(conn);

    return 0;
}