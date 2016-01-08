#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <cgi.h>

int CGIContentReader(char * file, int * socket){

    int fd = cgi_bash(file);

    if (fd){

        const int size = 256;
        char line[size];

        while (read(fd, &line, size)) {

            // write response
            write(*socket, line, strlen(line));

        };

        close(fd);

        return 0;
    } else {
        return 1;
    }

}