#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int cgi(char * file, char * args[]){
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
        // close stdin, stdout and stderr
        int in = dup(0);
        int out = dup(1);
        int err = dup(2);

        close(0);
        close(1);
        close(2);

        // redirect stdin to descriptor input
        dup2(descriptor[0], 0);

        // wait for child process to end
        wait(&status);

        // reopen stdin, stdout and stderr
        dup2(in, 0);
        dup2(out, 1);
        dup2(err, 2);

        // close write descriptor
        close(descriptor[1]);

        if (status){
            close(descriptor[0]);
            return status;
        } else {
            return descriptor[0];
        }

        return descriptor[0];

    // child process
    } else {
        close(0);
        close(2);
        dup2(descriptor[1], 1);

        // replace the child fork with a new process
        if(execv(file, args) == -1){
            exit(1);
        }

        exit(0);
    }

}
