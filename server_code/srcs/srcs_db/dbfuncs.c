#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#include "../../hdrs/hdrs_db/dbauxfuncs.h"
#include "../../hdrs/hdrs_db/dbfuncs.h"

int ins_user_db(MYSQL* conn, char username[30], char pass[30]) {
    mysql_autocommit(conn, 0);

    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, INS_U, strlen(INS_U)) != 0) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }

    MYSQL_BIND b[2];
    memset(b, 0, sizeof(b));
    b[0].buffer_type = MYSQL_TYPE_STRING;
    b[0].buffer = username;
    b[0].buffer_length = strlen(username); 
    b[1].buffer_type = MYSQL_TYPE_STRING;
    b[1].buffer = pass;
    b[1].buffer_length = strlen(pass);
    if(mysql_stmt_bind_param(stmt, b)) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }
    mysql_stmt_close(stmt);

    mysql_commit(conn);
    mysql_autocommit(conn, 1);

    return 1;
}

int add_adv_to_user(MYSQL* conn, int user_id, int adv_id) {
    mysql_autocommit(conn, 0);
    
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, ADD_ADV_TO_USER, strlen(ADD_ADV_TO_USER)) != 0) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }

    MYSQL_BIND b[2];
    memset(b, 0, sizeof(b));
    b[0].buffer_type = MYSQL_TYPE_LONG;
    b[0].buffer = &adv_id;
    b[1].buffer_type = MYSQL_TYPE_LONG;
    b[1].buffer = &user_id;
    if(mysql_stmt_bind_param(stmt, b)) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }
    mysql_stmt_close(stmt);

    mysql_commit(conn);
    mysql_autocommit(conn, 1);

    return 1;
}

int rmv_adv_db(MYSQL* conn, int adv_id) {
    mysql_autocommit(conn, 0);
    
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if(mysql_stmt_prepare(stmt, DELETE, strlen(DELETE)) != 0) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }

    MYSQL_BIND b[1]; 
    memset(b, 0, sizeof(b));
    b[0].buffer_type = MYSQL_TYPE_LONG;
    b[0].buffer = &adv_id;
    if(mysql_stmt_bind_param(stmt, b)) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }
    if(mysql_stmt_execute(stmt)) {
        mysql_rollback(conn); mysql_autocommit(conn, 1); mysql_stmt_close(stmt);
        return 0;
    }
    mysql_stmt_close(stmt);

    mysql_commit(conn);
    mysql_autocommit(conn, 1);

    return 1;
}
