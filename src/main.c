#include "../include/instGen.h"
#include "../include/memoria.h"
#include "../include/tablaDirecciones.h"
#include "../include/cpu.h"
#include "../include/clock.h"
#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
	function to start the clock
*/
void startClk(){
	pthread_t tClk;
	/* init first thread */
	int iret1 = pthread_create( &tClk, NULL, initClk,NULL);
	/* cheking if the first thread is created right */
	if(iret1){
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
		exit(EXIT_FAILURE);
	}
	printf("\n************  iniciando reloj del procesador  *************\n");
}

/*
	function starting the cpus.
*/
void startCPUS(){
	initCPUs();													//init the values of the cpus
	pthread_t tC0, tC1, tC2, tC3;
	int pC0=0, pC1=1, pC2=2, pC3=3;
	int iret0 = pthread_create( &tC0, NULL, startCPU, &pC0);	// init first thread
	//cheking if the first thread is created right
	if(iret0){
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret0);
		exit(EXIT_FAILURE);
	}

	int iret1 = pthread_create( &tC1, NULL, startCPU, &pC1);
	// cheking if the first thread is created right 
	if(iret1){
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
		exit(EXIT_FAILURE);
	}

	int iret2 = pthread_create( &tC2, NULL, startCPU, &pC2);
	// cheking if the first thread is created right 
	if(iret2){
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
		exit(EXIT_FAILURE);
	}
	
	int iret3 = pthread_create( &tC3, NULL, startCPU, &pC3);
	// cheking if the first thread is created right
	if(iret3){
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret3);
		exit(EXIT_FAILURE);
	}
	
	pthread_join( tC0, NULL);
	pthread_join( tC1, NULL);
	pthread_join( tC2, NULL);
	pthread_join( tC3, NULL);
}

void printShow(){
	pthread_t tSw;
	int iret4 = pthread_create( &tSw, NULL, showMem, NULL);	// init first thread
	//cheking if the first thread is created right
	if(iret4){
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret4);
		exit(EXIT_FAILURE);
	}
}

int main(){
	printf("\n************  iniciando programa  *************\n");
	startClk();
	initMem();
	initTable();
	printShow();
	startCPUS();
	
	return 0;
}