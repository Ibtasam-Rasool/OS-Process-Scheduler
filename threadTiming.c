#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MICRO_SEC_IN_SEC 1000000

void *thread_function(void *arg);

char message[] = "Hello World";

int main() {
    
    int res;
    pthread_t a_thread;
    void *thread_result;
    pid_t pid;
    struct timeval start, end;
    
    for(int i = 0; i < 10; i++){
    	gettimeofday(&start, NULL);
    	pid = fork();
	switch(pid){
		case -1:
			perror("fork failed");
			exit(1);
			
		case 0: 
			gettimeofday(&end, NULL);	//shows how long system call fork() takes 
			printf("\n Eplapsed Time Time took to call fork and create process: %ld micro sec \n", ((end.tv_sec * MICRO_SEC_IN_SEC + end.tv_usec) - (start.tv_sec * MICRO_SEC_IN_SEC + start.tv_usec)));
			exit(0);
			
		default:
			break;
		}
    	

    
    }
    
        for(int i = 0; i < 10; i++){
        	gettimeofday(&start, NULL);
        	res = pthread_create(&a_thread, NULL, thread_function, NULL);
        	  if (res != 0) {
        	    perror("Thread creation failed");
    		    exit(EXIT_FAILURE);
    		}
    		gettimeofday(&end, NULL);	//shows how long system call pthread create() takes 
    		printf("\n Eplapsed Time Time took to call pthread_create: %ld micro sec \n", ((end.tv_sec * MICRO_SEC_IN_SEC + end.tv_usec) - (start.tv_sec * MICRO_SEC_IN_SEC + start.tv_usec)));
    		res = pthread_join(a_thread, &thread_result);
    		    if (res != 0) {
			perror("Thread join failed");
			exit(EXIT_FAILURE);
		    }
    
    }
    
    
}

void *thread_function(void *arg) {
    pthread_exit(NULL);
}
