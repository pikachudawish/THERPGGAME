#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <mysql/mysql.h>

#include "../../hdrs/filefuncs.h"
#include "../../hdrs/auxfuncs.h"

#define HOST "100.82.64.91"
#define USER "rpggameadm"
#define PASS "Ru@25092006"
#define DBNAME "rpggame"

int main(int argc, char* argv[]) {
    unsigned int timeout = 5;
    
    MYSQL* conn = mysql_init(NULL);
    if(mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout)) {
        mysql_close(conn);
        return 1;
    }
    if(mysql_real_connect(conn, HOST, USER, PASS, DBNAME, 3306, NULL, 0) == NULL) {
        mysql_close(conn);
        return 1;
    }

    pthread_t* thread = (pthread_t*)malloc(sizeof(pthread_t));
    if(!thread) {
        mysql_close(conn);
        return 0;
    }
    pthread_create(thread, NULL, wait_input, NULL);

    pthread_join(*thread, NULL);

    free(thread);
    mysql_close(conn);

    return 0;
}