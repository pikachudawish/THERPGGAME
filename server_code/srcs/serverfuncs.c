#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../../hdrs/structs_hash.h"
#include "../../hdrs/freefuncs.h"
#include "../../hdrs/hashfuncs.h"
#include "../../hdrs/dbfuncs.h"

#define PORT 6767

int server_conn() {
    MYSQL* conn = mysql_init(NULL);

    int opt;
    switch(opt) {
        case 1:
            hashtable* ht = create_ht();
            if(!db_to_ht_init_conn) {
                free(ht); mysql_close(conn);
            }

            freeht(ht);
            break;
        
        case 2:
            break;
    }

    
    mysql_close(conn);
    return 1;
}