#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

int main() {

   socklen_t address_length;

   // create a buffer to keep data from request
   char *buffer = (char*) malloc(BUFFER_SIZE);
   struct sockaddr_in address;

   int create_socket = socket(AF_INET, SOCK_STREAM, 0);

   if (create_socket > 0){
      printf("Socket: created (%d)\n", create_socket);
   }

   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(PORT);

   if (bind(create_socket, (struct sockaddr *) &address, sizeof(address)) == 0){
      printf("Socket: listening on port %d\n", PORT);
   }

   while (1) {

      if (listen(create_socket, 10) < 0) {
         perror("Socket: listen");
         exit(1);
      }

      int new_socket = accept(create_socket, (struct sockaddr *) &address, &address_length);

      if (new_socket < 0) {
         perror("Socket: accept");
         exit(1);
      }

      if (new_socket > 0){
         printf("Socket: client connected\n");
      }

      recv(new_socket, buffer, BUFFER_SIZE, 0);

      // Print request headers
      printf("%s\n", buffer);

      // write response
      write(new_socket, "hello world\n", 12);

      // close the connection
      close(new_socket);

   }

   close(create_socket);

   return 0;
}