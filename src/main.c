#include <stdio.h>
#include <server.h>

int main(int argc, char * argv[]){
    int status = server(8080);
    printf("Server: Exiting with status %d\n", status);
    return status;
}