#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {

	if (argc < 2) {

		printf("Incorrect number of args: given %d, expected 1.\n", argc - 1);
		exit(1);
	}

	// first child [echo hello]

	pid_t pid;

	pid = fork();

	if (pid < 0) {

		printf("error in birthing");

	}

	if (pid == 0) {

		//printf("birthedddd with PID number %d\n", getpid());

		execl("/bin/echo", "echo", "hello world", NULL);

	}
	else {

		//printf("waiting\n");

		wait(NULL);

	}

	// second child [lab4.o]

	pid = fork();

	if (pid < 0) {

		printf("error in birthing");

	}

	if (pid == 0) {

		//printf("birthed with PID number %d\n", getpid());

		char* array[] = { "./lab4.o", argv[1], NULL };

		execv("./lab4.o", array);

	}
	else {

		wait(NULL);

		//printf("(im parent) your number is this %s and my PID is %d\n", argv[2], getpid());
	}
	
	
}
