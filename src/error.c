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

void Http404Error(char * url, int * socket){
    char response[BUFFER_SIZE];
    char * content = "404 Page Not Found";

    snprintf(response, BUFFER_SIZE, "HTTP/1.1 404 OK\nContent-Length: %lu\n%s", sizeof(content), content);

    write(*socket, response, sizeof(response));
}