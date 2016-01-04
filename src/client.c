#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

const int BUFFER_SIZE = 1024;
const char root[] = "example";

void * client(void * sock) {

    int socket = (long) sock;

    // create a buffer to keep data from request
    char * buffer = (char *) malloc(BUFFER_SIZE);

    if (socket < 0) {
        exit(1);
    }

    // Receive data from client
    recv(socket, buffer, BUFFER_SIZE, 0);

    // extracting a method and a path from the first line
    char * method = strtok(buffer, " ");
    char * path = strtok(NULL, " ");

    printf("Socket: [%s] %s\n", method, path);

    char url[256] = "";
    strcat(url, root);
    strcat(url, path);

    FILE * file = fopen(url, "r");

    if (file != NULL){

    const int size = 256;
    char line[size];

    while (fgets(line, size, file) != NULL) {

        // write response
        write(socket, line, strlen(line));

    };

    fclose(file);

    }

   // close the connection
   close(socket);

}