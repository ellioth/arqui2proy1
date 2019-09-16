#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define MEM 4

static int * table=NULL;
static pthread_mutex_t MTtable =PTHREAD_MUTEX_INITIALIZER;

void initTable(){
	table=(int*)calloc(sizeof(int),16);
	for(int i=0; i<16; i++){
		table[i]=MEM;	
	}
}

/**
	Method to read from the memory, recives 
	the addr [0-15] thats is need to bee read.
**/
int TDread(int addr){
	int respond=-1;
	pthread_mutex_lock( &MTtable );
	respond=table[addr];
	pthread_mutex_unlock( &MTtable );
	return respond;
}

/**
	Method to write to the memory, recives 
	the addr [0-15] thats is going to be 
	written and the data(#idCpu)
**/
void TDwrite(int addr, int data){
	pthread_mutex_lock( &MTtable );
	table[addr]=data;
	pthread_mutex_unlock( &MTtable );
}
