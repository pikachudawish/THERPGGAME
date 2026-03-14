#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <mysql/mysql.h>

#include "../../hdrs/hdrs_structs/structs_hash.h"
#include "../../hdrs/hdrs_aux/globalvariables.h"

#include "../../hdrs/hdrs_server/serverfuncs.h"
#include "../../hdrs/hdrs_game/gamefuncs.h"
#include "../../hdrs/hdrs_aux/freefuncs.h"
#include "../../hdrs/hdrs_hashtable/hashfuncs.h"
#include "../../hdrs/hdrs_processes/threadfuncs.h"

int main() {
    int cli_socket = cli_conn();
    if(!cli_socket) return 1;

    game = (int*)malloc(sizeof(int));
    (*game) = 1;

    pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t));
    if(!threads) {
        free(game);
        close(cli_socket);
        return 1;
    }

    pthread_create(&threads[0], NULL, sendpkg_worker, &cli_socket);

    if(!gameintro(cli_socket)) {
        free(game); free(threads);
        close(cli_socket);
        return 1;
    }

    if(!gameloop(cli_socket)) {
        free(game); free(threads);
        close(cli_socket);
        return 1;
    } 

    close(cli_socket);

    free(game); free(threads);

    return 0;
}