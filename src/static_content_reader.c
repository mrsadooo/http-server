#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

int StaticContentReader(char * file, int * socket){

    FILE * fd = fopen(file, "r");

    if (fd != NULL){

        const int size = 256;
        char line[size];

        while (fgets(line, size, fd) != NULL) {

            // write response
            write(*socket, line, strlen(line));

        };

        fclose(fd);

        return 0;
    } else {
        return 1;
    }

};