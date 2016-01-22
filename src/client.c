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
#include <fcntl.h>

#include <const.h>
#include <error.h>
#include <cgi.h>
#include <reader.h>

int is_file_executable(char * file){
    struct stat sb;
    return stat(file, &sb) == 0 && sb.st_mode & S_IXUSR ? 1 : 0;
}

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

    char root[256] = ROOT;
    char url[256] = "";
    strcat(url, root);
    strcat(url, path);

    int fd;

    if (is_file_executable(url)){
        fd = cgi(url, NULL);
    } else {
        fd = open(url, O_RDONLY);
    }

    if (fd != -1){
        FileReader(fd, &socket);
    } else {
        Http404Error(path, &socket);
    }

    // close the connection
    close(socket);

}