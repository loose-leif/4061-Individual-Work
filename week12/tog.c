#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int toggler = 0;

void foo() {

	static int count = 0;
	
	if(toggler == 0)
	{
		printf("%d: Count = %d\n", time(NULL), ++count);
	}

	sleep(1);
}

void SIGINT_handler(int sig)
{
	signal(sig,SIG_IGN);
	
	if(toggler == 0){
		toggler = 1;
	}
	else if(toggler == 1){
		toggler = 0;
	}

	signal(sig, SIGINT_handler);
	
}


int main() {
	// TODO: use sigprocmask to block; or use sigaction to toggle. 
	struct sigaction interr;
	
	interr.sa_handler = SIGINT_handler;
	sigemptyset(&interr.sa_mask);
	sigaction(SIGINT, &act, NULL);
	
	
	/* Print infinitely. */
	while (1) foo();
}
