#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <regex.h>

// file readers
#include <static_content_reader.h>
#include <cgi_content_reader.h>

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

    regex_t bash;
    regcomp(&bash, "\\.sh$", 0);

    if (!regexec(&bash, url, 0, NULL, 0)){
        CGIContentReader(url, &socket);
    } else {
        StaticContentReader(url, &socket);
    }

    // close the connection
    close(socket);

}