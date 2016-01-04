// watki odlaczone - detached state
// joiny na watkach

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

const int PORT = 8080;
const int BUFFER_SIZE = 1024;
struct sockaddr_in address;
char * root = "example";

void * newClient(void* newSock) {

    int new_socket = (long) newSock;
    // create a buffer to keep data from request
    char *buffer = (char*) malloc(BUFFER_SIZE);

    if (new_socket < 0) {
        exit(1);
    }

    // Receive data from client
    recv(new_socket, buffer, BUFFER_SIZE, 0);

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
        write(new_socket, line, strlen(line));

    };

    fclose(file);

    }

   // close the connection
   close(new_socket);

}


int main(int argc, char *argv[]) {

   socklen_t address_length;

   int create_socket = socket(AF_INET, SOCK_STREAM, 0);

   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(PORT);

   // Binding the socket on address and port
   if (bind(create_socket, (struct sockaddr *) &address, sizeof(address)) == 0){
      printf("Socket: listening on port %d\n", PORT);
   }

   printf("Socket: folder \"%s\"\n", root);

   while (1) {

        if (listen(create_socket, 10) < 0) {
            exit(1);
        }

        long new_socket = accept(create_socket, (struct sockaddr *) &address, &address_length);

    pthread_t newThread;

    pthread_create(&newThread, NULL, newClient, (void*) new_socket);

   }

   close(create_socket);

   return 0;
}
