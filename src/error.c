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
#include <const.h>

void HttpResponse(int * socket, int status, char * content){
    char response[BUFFER_SIZE];
    char * template = "HTTP/1.1 %d OK\nContent-Length: %lu\nConnection: close\n\n%s";

    snprintf(response, BUFFER_SIZE, template, status, strlen(content), content);

    write(*socket, response, sizeof(response));
}

void Http404Error(char * url, int * socket){
    HttpResponse(socket, 404, "404 Page Not Found");
}