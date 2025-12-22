#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 6767

int cli_conn() {
    int cli_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(cli_socket < 0) return 0;

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if(connect(cli_socket, (struct server_addr*)&server_addr, sizeof(server_addr))) {
        return 0;
    }

    char server_response[256];
    recv(cli_socket, &server_response, sizeof(server_response), 0);

    close(cli_socket);

    return 1;
}

