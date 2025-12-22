#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <mysql/mysql.h>

#include "../../hdrs/filefuncs.h"
#include "../../hdrs/auxfuncs.h"
#include "../../hdrs/serverfuncs.h"

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

    pthread_t* thread_backup = (pthread_t*)malloc(sizeof(pthread_t));
    if(!thread_backup) {
        mysql_close(conn);
        return 0;
    }
    pthread_create(thread_backup, NULL, wait_input, NULL);

    if(!server_conn(conn)) {
        free(thread_backup); mysql_close(conn);
        return 0;
    }

    pthread_join(*thread_backup, NULL);

    free(thread_backup);
    mysql_close(conn);

    return 0;
}