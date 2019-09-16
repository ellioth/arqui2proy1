#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/tablaDirecciones.h"
#include "../include/memoria.h"
#include "../include/instGen.h"
#include "../include/clock.h"
#include "../include/printer.h"

//constantes para la generacion de instrucciones
#define MAX_INST 100
#define ROT 0.005
#define PROC 0
#define WRITE 1
#define READ 2
#define INITPOS -1

//constantes para el clk
#define HIGH 1
#define LOW -1

//constantes para la coherencia de cache
#define I 0
#define M 1
#define S 2
#define MEM 4

//constantes para cpu0
#define CPU0 0
#define P0 0.6 
#define W0 0.3
#define R0 0.1
#define CPU0_PRINT_COLOR "\x1b[31m"

//constantes para cpu1
#define CPU1 1
#define P1 0.0
#define W1 0.7 
#define R1 0.0
#define CPU1_PRINT_COLOR "\x1b[32m"

//constantes para cpu2
#define CPU2 2
#define P2 0.5 
#define W2 0.27 
#define R2 0.23
#define CPU2_PRINT_COLOR "\x1b[35m"

//constantes para cpu3
#define CPU3 3
#define P3 0.1 
#define W3 0.0 
#define R3 0.9
#define CPU3_PRINT_COLOR "\x1b[36m"

#define COLOR_RESET "\x1b[0m"

//colores para la impresion de los datos de memoria
#define MEMN "\x1b[33m MEM\x1b[0m"
#define CPU0N "\x1b[31mCPU0\x1b[0m"
#define CPU1N "\x1b[32mCPU1\x1b[0m"
#define CPU2N "\x1b[35mCPU2\x1b[0m"
#define CPU3N "\x1b[36mCPU3\x1b[0m"

#define clear() printf("\033[6;0H")
#define reSizeS() printf("\e[8;41;120t")

typedef struct {
	int state;
	int tag;
	int data;
}cache;

typedef struct{
	int cpuID;
	int * inst;
	cache kashe[8];
}pu;


static pthread_mutex_t MTks =PTHREAD_MUTEX_INITIALIZER;
static pu *PUs=NULL;

/**
	method to init the values of the cpu.
*/
void initCPUs(){
	srand(time(NULL));
	PUs=calloc(sizeof(pu),4);								//creating the needed space for all the cpu
	
	PUs[0].cpuID=0;										//setting the id of my cpu0
	PUs[0].inst=armarInst(P0,W0,R0,MAX_INST,ROT);		//setting the instruction set of the cpu
	for(int j=0; j<8; j++){
		PUs[0].kashe[j].state=I;
		PUs[0].kashe[j].tag=0;
		PUs[0].kashe[j].data=-1;
	}
	
	PUs[1].cpuID=1;										//setting the id of my cpu0
	PUs[1].inst=armarInst(P1,W1,R1,MAX_INST,ROT);		//setting the instruction set of the cpu
	for(int j=0; j<8; j++){
		PUs[1].kashe[j].state=I;
		PUs[1].kashe[j].tag=0;
		PUs[1].kashe[j].data=-1;
	}

	PUs[2].cpuID=2;										//setting the id of my cpu0
	PUs[2].inst=armarInst(P2,W2,R2,MAX_INST,ROT);		//setting the instruction set of the cpu
	for(int j=0; j<8; j++){
		PUs[2].kashe[j].state=I;
		PUs[2].kashe[j].tag=0;
		PUs[2].kashe[j].data=-1;
	}
	
	PUs[3].cpuID=3;										//setting the id of my cpu0
	PUs[3].inst=armarInst(P3,W3,R3,MAX_INST,ROT);		//setting the instruction set of the cpu
	for(int j=0; j<8; j++){
		PUs[3].kashe[j].state=I;
		PUs[3].kashe[j].tag=0;
		PUs[3].kashe[j].data=-1;
	}
	
}

/**
	method to check the coherence in the struct cache
	*****paralelizable*****
*/
void* checkingCacheCohe(void * pData){
	int id=*((int*)pData);
	cache * kashe=PUs[id].kashe;
	int realPos=-1, tag=-1, data=-1, state=I;
	while(1<2){
		for(int i=0; i<8; i++){
			pthread_mutex_lock(&MTks);
			tag=kashe[i].tag;
			data=kashe[i].data;
			state=kashe[i].state;
			pthread_mutex_unlock(&MTks);
			realPos=tag<<3;										//tag=0001 -> realPos=1000
			realPos+=i;											//realPos=1XXX [MEM]
			int temp=TDread(realPos);
			if(data!=temp && state!=I){
				pthread_mutex_lock(&MTks);
				kashe[i].state=I;
				printInvaBus(id, i);
				pthread_mutex_unlock(&MTks);
			}
		}
	}
}

/*
	method to show the values of the 
	memory in the terminal
*/
void* showMem(){
	reSizeS();
	pthread_mutex_t tt=getMT();
	while(1<2){
		cache * kashe0=PUs[CPU0].kashe;
		cache * kashe1=PUs[CPU1].kashe;
		cache * kashe2=PUs[CPU2].kashe;
		cache * kashe3=PUs[CPU3].kashe;
		pthread_mutex_lock( &tt);
		printf("+----------MEM-----------+ +----------%s----------+ +----------%s----------+\n",CPU0N,CPU1N);
		printf("+  Espacio  |    Dato    + + S |  T  |      Dato    + + S |  T  |      Dato    +\n");
		printf("+-----------+------------+ +---+-----+--------------+ +---+-----+--------------+\n");
		printf("+    0x0    |    %s    + + %s |  %d  |     %s     + + %s |  %d  |     %s     +\n",getName(0),getState(kashe0[0].state),kashe0[0].tag, getName(kashe0[0].data), getState(kashe1[0].state),kashe1[0].tag, getName(kashe1[0].data));
		printf("+-----------+------------+ +---+-----+--------------+ +---+-----+--------------+\n");
		printf("+    0x1    |    %s    + + %s |  %d  |     %s     + + %s |  %d  |     %s     +\n",getName(1),getState(kashe0[1].state),kashe0[1].tag, getName(kashe0[1].data), getState(kashe1[1].state),kashe1[1].tag, getName(kashe1[1].data));
		printf("+-----------+------------+ +---+-----+--------------+ +---+-----+--------------+\n");
		printf("+    0x2    |    %s    + + %s |  %d  |     %s     + + %s |  %d  |     %s     +\n",getName(2),getState(kashe0[2].state),kashe0[2].tag, getName(kashe0[2].data), getState(kashe1[2].state),kashe1[2].tag, getName(kashe1[2].data));
		printf("+-----------+------------+ +---+-----+--------------+ +---+-----+--------------+\n");
		printf("+    0x3    |    %s    + + %s |  %d  |     %s     + + %s |  %d  |     %s     +\n",getName(3),getState(kashe0[3].state),kashe0[3].tag, getName(kashe0[3].data), getState(kashe1[3].state),kashe1[3].tag, getName(kashe1[3].data));
		printf("+-----------+------------+ +---+-----+--------------+ +---+-----+--------------+\n");
		printf("+    0x4    |    %s    + + %s |  %d  |     %s     + + %s |  %d  |     %s     +\n",getName(4),getState(kashe0[4].state),kashe0[4].tag, getName(kashe0[4].data), getState(kashe1[4].state),kashe1[4].tag, getName(kashe1[4].data));
		printf("+-----------+------------+ +---+-----+--------------+ +---+-----+--------------+\n");
		printf("+    0x5    |    %s    + + %s |  %d  |     %s     + + %s |  %d  |     %s     +\n",getName(5),getState(kashe0[5].state),kashe0[5].tag, getName(kashe0[5].data), getState(kashe1[5].state),kashe1[5].tag, getName(kashe1[5].data));
		printf("+-----------+------------+ +---+-----+--------------+ +---+-----+--------------+\n");
		printf("+    0x6    |    %s    + + %s |  %d  |     %s     + + %s |  %d  |     %s     +\n",getName(6),getState(kashe0[6].state),kashe0[6].tag, getName(kashe0[6].data), getState(kashe1[6].state),kashe1[6].tag, getName(kashe1[6].data));
		printf("+-----------+------------+ +---+-----+--------------+ +---+-----+--------------+\n");
		printf("+    0x7    |    %s    + + %s |  %d  |     %s     + + %s |  %d  |     %s     +\n",getName(7),getState(kashe0[7].state),kashe0[7].tag, getName(kashe0[7].data), getState(kashe1[7].state),kashe1[7].tag, getName(kashe1[7].data));
		printf("+-----------+------------+ +---+-----+--------------+ +---+-----+--------------+\n");
		printf("+    0x8    |    %s    +\n",getName(8));
		printf("+-----------+------------+ +----------%s----------+ +----------%s----------+\n",CPU2N,CPU3N);
		printf("+    0x9    |    %s    + + S |  T  |      Dato    + + S |  T  |      Dato    +\n",getName(9));
		printf("+-----------+------------+ +---+-----+--------------+ +---+-----+--------------+\n");
		printf("+    0xA    |    %s    + + %s |  %d  |     %s     + + %s |  %d  |     %s     +\n",getName(10),getState(kashe2[0].state),kashe2[0].tag, getName(kashe2[0].data), getState(kashe3[0].state),kashe3[0].tag, getName(kashe3[0].data));
		printf("+-----------+------------+ +---+-----+--------------+ +---+-----+--------------+\n");
		printf("+    0xB    |    %s    + + %s |  %d  |     %s     + + %s |  %d  |     %s     +\n",getName(11),getState(kashe2[1].state),kashe2[1].tag, getName(kashe2[1].data), getState(kashe3[1].state),kashe3[1].tag, getName(kashe3[1].data));
		printf("+-----------+------------+ +---+-----+--------------+ +---+-----+--------------+\n");
		printf("+    0xC    |    %s    + + %s |  %d  |     %s     + + %s |  %d  |     %s     +\n",getName(12),getState(kashe2[2].state),kashe2[2].tag, getName(kashe2[2].data), getState(kashe3[2].state),kashe3[2].tag, getName(kashe3[2].data));
		printf("+-----------+------------+ +---+-----+--------------+ +---+-----+--------------+\n");
		printf("+    0xD    |    %s    + + %s |  %d  |     %s     + + %s |  %d  |     %s     +\n",getName(13),getState(kashe2[3].state),kashe2[3].tag, getName(kashe2[3].data), getState(kashe3[3].state),kashe3[3].tag, getName(kashe3[3].data));
		printf("+-----------+------------+ +---+-----+--------------+ +---+-----+--------------+\n");
		printf("+    0xE    |    %s    + + %s |  %d  |     %s     + + %s |  %d  |     %s     +\n",getName(14),getState(kashe2[4].state),kashe2[4].tag, getName(kashe2[4].data), getState(kashe3[4].state),kashe3[4].tag, getName(kashe3[4].data));
		printf("+-----------+------------+ +---+-----+--------------+ +---+-----+--------------+\n");
		printf("+    0xF    |    %s    + + %s |  %d  |     %s     + + %s |  %d  |     %s     +\n",getName(15),getState(kashe2[5].state),kashe2[5].tag, getName(kashe2[5].data), getState(kashe3[5].state),kashe3[5].tag, getName(kashe3[5].data));
		printf("+-----------+------------+ +---+-----+--------------+ +---+-----+--------------+\n");
		printf("                           + %s |  %d  |     %s     + + %s |  %d  |     %s     +\n",getState(kashe2[6].state),kashe2[6].tag, getName(kashe2[6].data), getState(kashe3[6].state),kashe3[6].tag, getName(kashe3[6].data));
		printf("                           +---+-----+--------------+ +---+-----+--------------+\n");
		printf("                           + %s |  %d  |     %s     + + %s |  %d  |     %s     +\n",getState(kashe2[7].state),kashe2[7].tag, getName(kashe2[7].data), getState(kashe3[7].state),kashe3[7].tag, getName(kashe3[7].data));
		printf("                           +---+-----+--------------+ +---+-----+--------------+\n");
		pthread_mutex_unlock( &tt);
		checkingSClk(LOW,1);
		clear();
	}
}

/**
	method to get data from a specific 
	cache of a cpu.
*/
int getFromOutCache(int addr, int cpuID){
	int Caddr=addr%8;
	int ttD=-1;
	pthread_mutex_lock( &MTks);
	ttD=PUs[cpuID].kashe[Caddr].data;
	pthread_mutex_unlock( &MTks);
	return ttD;
}

/**
	method to check if the data is on the cache
*/
int lookIntoCache(int addr, int cpuID){
	int Caddr=addr%8, tag=addr>>3, sta, ktag;
	cache *ttKS;
	pthread_mutex_lock( &MTks);
	ttKS=PUs[cpuID].kashe;
	sta=ttKS[Caddr].state;
	ktag=ttKS[Caddr].tag;
	pthread_mutex_unlock( &MTks);
	if(sta!=I && ktag==tag){
		return 1;
	}
	return I;
}

/**
	method to write in my cache, cheks if the data was
	on modif state, send it to the mem, make the alert to
	the address table.
*/
void writeIntoCache(int addr, int data, int id){
	int Caddr=addr%8;
	int tag=addr>>3;
	//writing a block of the cache 
	pthread_mutex_lock( &MTks);
	PUs[id].kashe[Caddr].state=M;
	PUs[id].kashe[Caddr].tag=tag;
	PUs[id].kashe[Caddr].data=data;
	pthread_mutex_unlock( &MTks);
	/**if(state==M){
		write(addr, MEM);//atrasar ************************
	}*/
	TDwrite(addr,data); //tabla de direcciones alterada
	write(addr,data); //memoria alterada
}

/**
	method to read from the cache, checks if you have to go to 
	mem or other caches and if the last data on that 
	cache place needs to be lower to mem, and the data, cpuID thats 
	is going to be written on the location.
*/
int readData(int addr, int place, int id){
	int Caddr=addr%8;
	int tag=addr>>3;
	/**if(state==M){
		write(addr, (*tmp).data);//atrasar ************************
	}*/
	int data=-1, stall=0;
	if(place==MEM){
		data=read(addr);	//asking for the data in the memory	
		stall=MEM;			//emitir un atraso
		printMissPenal(id);
	}
	else{
		//asking for the data store in a another cache
		data=getFromOutCache(addr, place);
	}
	//making the changes in the local block of the cache
	pthread_mutex_lock( &MTks);
	PUs[id].kashe[Caddr].state=S;
	PUs[id].kashe[Caddr].tag=tag;
	PUs[id].kashe[Caddr].data=data;
	pthread_mutex_unlock( &MTks);
	return stall;	
}

/**
	metodo que hace que se ejecuten las instrucciones 
	del procesador
	*****paralelizable*****
*/
void* startCPU(void * data){
	int id=*((int*)data);
	pu * myPU=&PUs[id];
	pthread_t tCache;
	int iret1 = pthread_create( &tCache, NULL, checkingCacheCohe,data);
	/* cheking if the first thread is created right */
	if(iret1){
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
		exit(EXIT_FAILURE);
	}
	int * inst=myPU->inst;
	for(int i=0; i<MAX_INST; i++){
		//esperando a que el clock sea HIGH
		checkingSClk(HIGH, 1);
		printClean(id);
		//extraemos el tipo de instruccion que es
		int type=inst[i]%10; 
		if(type==PROC){
			printProcess(id);
			//esperar a que termine el ciclo.
			checkingSClk(LOW, 1);
			continue;
		}
		/**
			ya se sabe que no es de procesamiento 
			por lo que se pasa a calcular la direccion
			y se verifica que existe en la cache y cual
			es su estado
		*/
		int stall=1;
		int addr=inst[i]/10;
		int state=lookIntoCache(addr,id);
		//preguntamos si es una escritura
		if(type==WRITE){
			if(state==I){ 
				printWriteMiss(id, addr);
			}
			else{
				printWriteHit(id, addr);
			}
			writeIntoCache(addr,id, id);
			stall=MEM;
		}
		//preguntamos si es una lectura
		else if(type==READ){
			if(state==I){
				printReadMiss(id, addr);
				/** buscarlo en la tabla de direcciones*/
				int place=TDread(addr);
				//extraer el dato de donde se encuentre
				stall=readData(addr, place, id);
			}
			else{
				printReadHit(id, addr);
			}
			//suponer que el dato fue leido y almacenado en cache, 
			//no hace nada con el, se puede continuar
		}
		checkingSClk(LOW, stall);
	}
	return NULL;
}