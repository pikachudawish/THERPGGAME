#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mysql/mysql.h>

#include "../../hdrs/hdrs_structs/structs_hash.h"

#include "../../hdrs/hdrs_server/serverfuncs.h"
#include "../../hdrs/hdrs_game/gamefuncs.h"
#include "../../hdrs/hdrs_aux/freefuncs.h"
#include "../../hdrs/hdrs_hashtable/hashfuncs.h"

int main() {
    int cli_socket = cli_conn();
    if(!cli_socket) return 1;

    if(!gameintro(cli_socket)) {
        close(cli_socket);
        return 1;
    }

    if(!gameloop(cli_socket)) {
        close(cli_socket);
        return 1;
    } 

    close(cli_socket);

    return 0;
}