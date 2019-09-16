#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define HIGH 1
#define LOW -1
#define AMP 2.5

static int _clock=-1;
static pthread_mutex_t MTClk=PTHREAD_MUTEX_INITIALIZER;

/**
	method to initialized the clock in order 
	for the cpus to operate
*/
void* initClk(){
	pthread_mutex_lock(&MTClk);
	_clock=HIGH;
	pthread_mutex_unlock(&MTClk);
	struct timespec start, finish;
	double elapsed;
	while(1<2){
		clock_gettime(CLOCK_MONOTONIC, &finish);
		elapsed = (finish.tv_sec - start.tv_sec);
		elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
		if(elapsed>AMP){
			//cambiando el valor del clock
			pthread_mutex_lock(&MTClk);
			_clock*=LOW;
			pthread_mutex_unlock(&MTClk);
			//reiniciando el contador
			clock_gettime(CLOCK_MONOTONIC, &start);
		}
	}
}

/**
	method to read the value of the actual clock
*/
int getClock(){
	int ttClk=0;
	//obteniendo el valor del clock actual
	pthread_mutex_lock(&MTClk);
	ttClk=_clock;
	pthread_mutex_unlock(&MTClk);
	return ttClk;
}

/**
	method to make the operations in function
	of the clock.
*/
void checkingSClk(int state, int stall){
	int i=getClock();
	while(stall!=0){
		if(i==state){
			stall--;
			state*=-1;
		}
		i=getClock();
	}
}