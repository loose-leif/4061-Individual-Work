#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void pid1func(int fd[]){
    char sendmsg[] = "I have a sample file, which consist of sample of sample";
    //write sendmsg to the pipe
    //ensure pipe ends are close properly

}

void pid2func(int fd[]){
    // close fds as necessary
    // redirect read end to STDIN_FILENO

    // run grep for "sample" on the text in STDIN_FILENO using execvp
    char *args[] = {"grep", "-a", "sample", NULL};
    execvp("grep", args); 
}

int main(int argc, char *argv[]){
    int fd1[2];
    pipe(fd1); // add error checking

    // How many copies of pipe is created when the following processes are created? If you do not understand this, your program may run forever.

    // fork first process
        // run pid1func()

    //fork second process
        // run pid2func()


    // wait for both process to complete

    return 0;
}
