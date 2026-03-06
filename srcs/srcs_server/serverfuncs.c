#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "../../hdrs/hdrs_server/serverfuncs.h"

int cli_conn() {
    printf("\nConnecting to the server...");

    int cli_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(cli_socket < 0) {
        fprintf(stderr, "ERROR: Socket()\n");
        return 0;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP_TEST);

    if(connect(cli_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        fprintf(stderr, "ERROR: connect()\n");
        close(cli_socket);
        return 0;
    }
    printf("\n✅Connection successfully established!\n");

    return cli_socket;
}

