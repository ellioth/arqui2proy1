#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "../include/clock.h"

#define MEM 4

static int* mem=NULL;
static pthread_mutex_t MTmem =PTHREAD_MUTEX_INITIALIZER;

/**
	Method to read from the memory, recives 
	the addr [0-15] thats is need to bee read.
**/
int read(int addr){
	int respond=-1;
	pthread_mutex_lock( &MTmem );
	respond=mem[addr];
	pthread_mutex_unlock( &MTmem );
	return respond;
}

/**
	Method to write to the memory, recives 
	the addr [0-15] thats is going to be 
	written and the data(#idCpu)
**/
void write(int addr, int data){
	pthread_mutex_lock( &MTmem );
	mem[addr]=data;
	pthread_mutex_unlock( &MTmem );
}

/*
	method to initialized the memory of the cpu
*/
void initMem(){
	mem=(int*)calloc(sizeof(int),16);
	for(int i=0; i<16; i++){
		mem[i]=MEM;	
	}
	/*
	pthread_t tMem;
	int iret1 = pthread_create( &tMem, NULL, showMem,NULL);
	 cheking if the first thread is created right 
	if(iret1){
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
		exit(EXIT_FAILURE);
	}*/
}