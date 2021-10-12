#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void pid1func(int fd[]){
    
    char sendmsg[] = "I have a sample file, which consist of sample of sample";
    //char sendmsg[] = "I have a  file, which consist of  of ";
    
    write(fd[1], sendmsg, strlen(sendmsg)+1); // write message to the output pipe buffer?
    close(fd[1]); // parent closes the write end of the pipe 
    wait(NULL); // wait for the child process to finish its business
    
    // extraneous comments
    //printf("Child Recieved Message\n");
    //write sendmsg to the pipe
    //ensure pipe ends are close properly

}

void pid2func(int fd[]){

    // extraneous comments
    // close fds as necessary
    // redirect read end to STDIN_FILENO
    // read(fd[0], recvStr, 100);
    //printf("Received msg from parent : %s \n", recvStr);
    // run grep for "sample" on the text in STDIN_FILENO using execvp

    close(fd[1]); // child closes the write end of pipe

    dup2(fd[0], STDIN_FILENO); // in making a copy of fd[0] place the standard input file number
                               // this will redirect the read buffer to the standard input marker

    char recvStr[100]; // arbitrary length string of characters

    close(fd[0]); // child closes read buffer of pipe
    
    char *args[] = {"grep", "-a", "sample", NULL}; // search standard input for "sample"
    execvp("grep", args); // execute aforementioned command

}

int main(int argc, char *argv[]){
    
    // extraneous comments
    //printf("r: %d, w: %d\n", fd1[0], fd1[1]);
    //printf("hello\n");
    // How many copies of pipe is created when the following processes are created? If you do not understand this, your program may run forever.
    //if (PID > 0) { printf("COMPLETE\n"); }
    // wait for both process to complete
    
    int fd1[2]; // create array of 2 int elements to hold file descriptors

    if (pipe(fd1) == -1) { // add error checking DONE

        printf("ERROR: Failed to generate pipeline...\n");
        exit(1);

    }

    pid_t PID = fork(); 
    
    if (PID < 0) {

        printf("ERROR: Failed to fork...\n");

    }
    
    else if (PID > 0) { // fork first process

        pid1func(fd1);
        // run pid1func()

    }

    else {  //fork second process

        pid2func(fd1); 
        // run pid2func()

    }

    wait(NULL);

    return 0;

}
