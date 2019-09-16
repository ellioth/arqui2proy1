#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "../include/memoria.h"

//constantes para ubicaciones
#define CPU0 0
#define CPU1 1
#define CPU2 2
#define CPU3 3
#define MEM 4

//estados de la cache
#define I 0
#define M 1
#define S 2

//constantes para los colores
#define MEMN "\x1b[33m MEM\x1b[0m"
#define CPU0N "\x1b[31mCPU0\x1b[0m"
#define CPU1N "\x1b[32mCPU1\x1b[0m"
#define CPU2N "\x1b[35mCPU2\x1b[0m"
#define CPU3N "\x1b[36mCPU3\x1b[0m"
#define VOID "\x1b[34mVOID\x1b[0m"

#define CPU0_PRINTA "\x1b[31m"
#define CPU0_PRINTB "\x1b[31m"
#define CPU0_PRINTC "\x1b[31m"
#define CPU1_PRINTA "\x1b[32m"
#define CPU1_PRINTB "\x1b[32m"
#define CPU1_PRINTC "\x1b[32m"
#define CPU2_PRINTA "\x1b[35m"
#define CPU2_PRINTB "\x1b[35m"
#define CPU2_PRINTC "\x1b[35m"
#define CPU3_PRINTA "\x1b[36m"
#define CPU3_PRINTB "\x1b[36m"
#define CPU3_PRINTC "\x1b[36m"
#define COLOR_RESET "\x1b[0m"

static pthread_mutex_t MTpf =PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t getMT(){
	return MTpf;	
}


void printClean(int id){
	/*if(id==CPU0){
		pthread_mutex_lock( &MTpf);
		printf(CPU0_PRINTA"                                                             ");
		printf(CPU0_PRINTB"                                                             ");
		printf(CPU0_PRINTB"                                                             ");
		pthread_mutex_unlock( &MTpf);
	}
	else if(id==CPU1){
		pthread_mutex_lock( &MTpf);
		printf(CPU1_PRINTA"                                                             ");
		printf(CPU1_PRINTB"                                                             ");
		printf(CPU1_PRINTB"                                                             ");
		pthread_mutex_unlock( &MTpf);
	}
	else if(id==CPU2){
		pthread_mutex_lock( &MTpf);
		printf(CPU2_PRINTA"                                                             ");
		printf(CPU2_PRINTB"                                                             ");
		printf(CPU2_PRINTB"                                                             ");
		pthread_mutex_unlock( &MTpf);
	}
	else{
		pthread_mutex_lock( &MTpf);
		printf(CPU3_PRINTA"                                                             ");
		printf(CPU3_PRINTB"                                                             ");
		printf(CPU3_PRINTB"                                                             ");
		pthread_mutex_unlock( &MTpf);
	}*/
}

void printProcess(int id){
	/*if(id==CPU0){
		pthread_mutex_lock( &MTpf);
		printf(CPU0_PRINTA"[CPU%d]: inst de procesamiento\n",id);
		pthread_mutex_unlock( &MTpf);
	}
	else if(id==CPU1){
		pthread_mutex_lock( &MTpf);
		printf(CPU1_PRINTA"[CPU%d]: inst de procesamiento\n",id);
		pthread_mutex_unlock( &MTpf);
	}
	else if(id==CPU2){
		pthread_mutex_lock( &MTpf);
		printf(CPU2_PRINTA"[CPU%d]: inst de procesamiento\n",id);
		pthread_mutex_unlock( &MTpf);
	}
	else{
		pthread_mutex_lock( &MTpf);
		printf(CPU3_PRINTA"[CPU%d]: inst de procesamiento\n",id);
		pthread_mutex_unlock( &MTpf);
	}*/
	
}

void printWriteMiss(int id, int addr){
	/*if(id==CPU0){
		pthread_mutex_lock( &MTpf);
		printf(CPU0_PRINTA"[CPU%d]: write miss cache[%d], tag=%d""\n",id, addr%8,addr>>3);
		printf(CPU0_PRINTB"[CPU%d]: memory miss penalty""\n",id);
		pthread_mutex_unlock( &MTpf);
	}
	else if(id==CPU1){
		pthread_mutex_lock( &MTpf);
		printf(CPU1_PRINTA"[CPU%d]: write miss cache[%d], tag=%d""\n",id, addr%8,addr>>3);
		printf(CPU1_PRINTB"[CPU%d]: memory miss penalty""\n",id);
		pthread_mutex_unlock( &MTpf);
	}
	else if(id==CPU2){
		pthread_mutex_lock( &MTpf);
		printf(CPU2_PRINTA"[CPU%d]: write miss cache[%d], tag=%d""\n",id, addr%8,addr>>3);
		printf(CPU2_PRINTB"[CPU%d]: memory miss penalty""\n",id);
		pthread_mutex_unlock( &MTpf);
	}
	else{
		pthread_mutex_lock( &MTpf);
		printf(CPU3_PRINTA"[CPU%d]: write miss cache[%d], tag=%d""\n",id, addr%8,addr>>3);
		printf(CPU3_PRINTB"[CPU%d]: memory miss penalty""\n",id);
		pthread_mutex_unlock( &MTpf);
	}*/
}

void printWriteHit(int id, int addr){
	/*if(id==CPU0){
		pthread_mutex_lock( &MTpf);
		printf(CPU0_PRINTA"[CPU%d]: write hit cache[%d], tag=%d""\n",id, addr%8,addr>>3);
		pthread_mutex_unlock( &MTpf);	
	}
	else if(id==CPU1){
		pthread_mutex_lock( &MTpf);
		printf(CPU1_PRINTA"[CPU%d]: write hit cache[%d], tag=%d""\n",id, addr%8,addr>>3);
		pthread_mutex_unlock( &MTpf);	
	}
	else if(id==CPU2){
		pthread_mutex_lock( &MTpf);
		printf(CPU2_PRINTA"[CPU%d]: write hit cache[%d], tag=%d""\n",id, addr%8,addr>>3);
		pthread_mutex_unlock( &MTpf);	
	}
	else{
		pthread_mutex_lock( &MTpf);
		printf(CPU3_PRINTA"[CPU%d]: write hit cache[%d], tag=%d""\n",id, addr%8,addr>>3);
		pthread_mutex_unlock( &MTpf);	
	}*/
}

void printReadMiss(int id, int addr){
	/*if(id==CPU0){
		pthread_mutex_lock( &MTpf);
		printf(CPU0_PRINTA"[CPU%d]: read miss, cache[%d], tag=%d""\n",id, addr%8,addr>>3);
		pthread_mutex_unlock( &MTpf);
	}
	else if(id==CPU1){
		pthread_mutex_lock( &MTpf);
		printf(CPU1_PRINTA"[CPU%d]: read miss, cache[%d], tag=%d""\n",id, addr%8,addr>>3);
		pthread_mutex_unlock( &MTpf);
	}
	else if(id==CPU2){
		pthread_mutex_lock( &MTpf);
		printf(CPU2_PRINTA"[CPU%d]: read miss, cache[%d], tag=%d""\n",id, addr%8,addr>>3);
		pthread_mutex_unlock( &MTpf);
	}
	else{
		pthread_mutex_lock( &MTpf);
		printf(CPU3_PRINTA"[CPU%d]: read miss, cache[%d], tag=%d""\n",id, addr%8,addr>>3);
		pthread_mutex_unlock( &MTpf);
	}*/
}

void printMissPenal(int id){
	/*if(id==CPU0){
		pthread_mutex_lock( &MTpf);
		printf(CPU0_PRINTB"[CPU%d]: memory miss penalty""\n",id);
		pthread_mutex_unlock( &MTpf);
	}
	else if(id==CPU1){
		pthread_mutex_lock( &MTpf);
		printf(CPU1_PRINTB"[CPU%d]: memory miss penalty""\n",id);
		pthread_mutex_unlock( &MTpf);
	}
	else if(id==CPU2){
		pthread_mutex_lock( &MTpf);
		printf(CPU2_PRINTB"[CPU%d]: memory miss penalty""\n",id);
		pthread_mutex_unlock( &MTpf);
	}
	else{
		pthread_mutex_lock( &MTpf);
		printf(CPU3_PRINTB"[CPU%d]: memory miss penalty""\n",id);
		pthread_mutex_unlock( &MTpf);
	}**/
}

void printReadHit(int id, int addr){
	/*if(id==CPU0){
		pthread_mutex_lock( &MTpf);
		printf(CPU0_PRINTA"[CPU%d]: read hit cache[%d], tag=%d""\n",id, addr%8,addr>>3);
		pthread_mutex_unlock( &MTpf);	
	}
	else if(id==CPU1){
		pthread_mutex_lock( &MTpf);
		printf(CPU1_PRINTA"[CPU%d]: read hit cache[%d], tag=%d""\n",id, addr%8,addr>>3);
		pthread_mutex_unlock( &MTpf);	
	}
	else if(id==CPU2){
		pthread_mutex_lock( &MTpf);
		printf(CPU2_PRINTA"[CPU%d]: read hit cache[%d], tag=%d""\n",id, addr%8,addr>>3);
		pthread_mutex_unlock( &MTpf);	
	}
	else{
		pthread_mutex_lock( &MTpf);
		printf(CPU3_PRINTA"[CPU%d]: read hit cache[%d], tag=%d""\n",id, addr%8,addr>>3);
		pthread_mutex_unlock( &MTpf);	
	}*/
}

void printInvaBus(int id, int addr){
	/*if(id==CPU0){
		pthread_mutex_lock( &MTpf);
		printf(CPU0_PRINTC"[cohCPU%d]: invalidacion de cache[%d]""\n",id,addr);
		pthread_mutex_unlock( &MTpf);	
	}
	else if(id==CPU1){
		pthread_mutex_lock( &MTpf);
		printf(CPU1_PRINTC"[cohCPU%d]: invalidacion de cache[%d]""\n",id,addr);
		pthread_mutex_unlock( &MTpf);	
	}
	else if(id==CPU2){
		pthread_mutex_lock( &MTpf);
		printf(CPU2_PRINTC"[cohCPU%d]: invalidacion de cache[%d]""\n",id,addr);
		pthread_mutex_unlock( &MTpf);	
	}
	else{
		pthread_mutex_lock( &MTpf);
		printf(CPU0_PRINTC"[cohCPU%d]: invalidacion de cache[%d]""\n",id,addr);
		pthread_mutex_unlock( &MTpf);	
	}*/
}

/*
	method to get, in  char the state of
	a cache block
*/
const char* getState(int state){
	if(state==I){
		return "I";	
	}
	else if(state==M){
		return "M";	
	}
	return "S";	
}

/*
	method to get the name of the 
	actual owner of the memory block
*/
const char* getName(int addr){
	if(addr==-1){
		return VOID;	
	}
	int tt=read(addr);
	if(tt==MEM){
		return MEMN;
	}
	else if(tt==CPU0){
		return CPU0N;
	}
	else if(tt==CPU1){
		return CPU1N;
	}
	else if(tt==CPU2){
		return CPU2N;
	}
	return CPU3N;
}
