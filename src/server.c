// watki odlaczone - detached state
// joiny na watkach

#include <netinet/in.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <client.h>

int server(int port) {

    struct sockaddr_in address;
    socklen_t address_length;

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // make sure that we can reuse the socket port
    int byte = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &byte, sizeof(byte)) == -1) {
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Binding the socket on address and port
    if (bind(sock, (struct sockaddr *) &address, sizeof(address)) == 0){
        printf("Socket: listening on port %d\n", port);
    } else {
        printf("Socket: unable to bind on port %d\n", port);
        return 1;
    }

    while (1) {

        if (listen(sock, 10) < 0) {
            return 1;
        }

        long connection = accept(sock, (struct sockaddr *) &address, &address_length);

        pthread_t new_thread;

        pthread_create(&new_thread, NULL, client, (void *) connection);

    }

    close(sock);

    return 0;
}
