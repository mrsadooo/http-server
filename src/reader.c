#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <const.h>

void FileReader(int fd, int * socket){
    int bytes;
    char line[BUFFER_SIZE];

    while ((bytes = read(fd, line, BUFFER_SIZE)) != 0) {
        write(*socket, line, bytes);
    };

    close(fd);
};