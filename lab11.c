#define _BSD_SOURCE
#define NUM_ARGS 0

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

long condTotal = 0;

struct buffer {

	int vals[100];
	int index; //indicates the next available spot
};

struct condBuffer {

	struct buffer* q;
	pthread_cond_t* cond;
	pthread_mutex_t* mutex;
};


void insert(struct buffer* q, int val) {

	q->vals[q->index] = val;
	++q->index;
}

int extract(struct buffer* q) {

	--q->index;
	int val = q->vals[q->index];
	return val;
}

// TODO: Insert code to use a condition variable.
// hint: what should be done when an item is added so that it may later be removed?
void *condProducer(void* arg) {
	
	// Random delay. DO NOT REMOVE!
	usleep(rand() % 1000);

	struct condBuffer* cq = (struct condBuffer*) arg;

	pthread_mutex_lock(cq->mutex);

	// Counter.
	static int in = 0;
	++in;

	// Add an element to the buffer.
	insert(cq->q, in);

	pthread_cond_signal(cq->cond);

	pthread_mutex_unlock(cq->mutex);
	
	return NULL;
}

// TODO: Insert code to use a condition variable.
// hint: what condition must hold before an item can be removed from the queue?
void *condConsumer(void* arg) {

	// Random delay. DO NOT REMOVE!
	usleep(rand() % 1000);

	struct condBuffer* cq = (struct condBuffer*) arg;

	pthread_mutex_lock(cq->mutex);

	while(cq->q->index==0){

		pthread_cond_wait(cq->cond, cq->mutex);

	}

	// Remove an element from the buffer.
	condTotal += extract(cq->q);

	pthread_mutex_unlock(cq->mutex);

	return NULL;
}

int main(int argc, char** argv) {

	if (argc != NUM_ARGS + 1) {

		printf("Wrong number of args, expected %d, given %d\n", NUM_ARGS, argc - 1);
		exit(1);
	}

	// Seed the random generator.
	srand(time(NULL));

	// Create threads.
	pthread_t condPool[100];

	struct timeval start;
	gettimeofday(&start, NULL);

	// Create the cond variable controlled task buffer.
	struct condBuffer* cq = (struct condBuffer*) malloc(sizeof(struct condBuffer));
	cq->q = (struct buffer*) malloc(sizeof(struct buffer));
	cq->q->index=0;
	cq->cond = (pthread_cond_t*) malloc(sizeof(pthread_cond_t));
	cq->mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
	pthread_cond_init(cq->cond, NULL);
	pthread_mutex_init(cq->mutex, NULL);

	// Launch them.
	for (int i=0; i < 50; ++i) {

		pthread_create(&condPool[i], NULL, condProducer, (void*) cq); //start 50 producer threads
		pthread_create(&condPool[50 + i], NULL, condConsumer, (void*) cq); //start 50 consumer threads
	}

	for (int i=0; i < 100; ++i) pthread_join(condPool[i], NULL); //wait for all the threads to be finished

	struct timeval end;
	gettimeofday(&end, NULL);

	printf("Cond Test: \nTotal of buffer = %ld\n", condTotal);
	printf("Time (in us) to run = %ld\n\n", ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec));

	}
