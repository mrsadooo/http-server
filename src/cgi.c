#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int cgi(char * exec, char * command){
    pid_t pid;

    int status;
    int descriptor[2];

    // setup pipe
    if(pipe(descriptor)){
        return -1;
    }

    // create a process fork
    pid = fork();

    if(pid == -1){
        return -1;
    }

    // parent process
    if(pid){
        int in = dup(0);

        // close unused descriptors
        close(descriptor[1]);
        close(0);

        // redirect stdin to descriptor input
        dup2(descriptor[0], 0);

        // wait for child process to end
        wait(&status);

        // reopen stdin
        dup2(in, 0);

    // child process
    } else {
        close(1);
        dup2(descriptor[1], 1);

        // replace the child fork with a new process
        if(execl(exec, command, NULL) == -1){
            exit(1);
        }

        exit(0);
    }

    return descriptor[0];

}