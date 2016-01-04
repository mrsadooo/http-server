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
#include <client.h>

const int PORT = 8080;

struct sockaddr_in address;

int main(int argc, char *argv[]) {

   socklen_t address_length;

   int sock = socket(AF_INET, SOCK_STREAM, 0);

   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(PORT);

   // Binding the socket on address and port
   if (bind(sock, (struct sockaddr *) &address, sizeof(address)) == 0){
      printf("Socket: listening on port %d\n", PORT);
   }

   while (1) {

        if (listen(sock, 10) < 0) {
            exit(1);
        }

        long connection = accept(sock, (struct sockaddr *) &address, &address_length);

        pthread_t thread;

        pthread_create(&thread, NULL, client, (void *) connection);

   }

   close(sock);

   return 0;
}
