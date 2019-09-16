#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//#define MAX_INST 100
#define PROC 0
#define WRITE 1
#define READ 2

//agregar esto al main del programa srand(time(NULL));

/**
	method to get the address of the memory using a pseudorandom;
*/
int addrGen(){
	return (int)(rand()%16);      // Returns a pseudo-random integer between 0 and 15
}

int* instShuffle(int * inst, int maxInst){
	for(int i=maxInst-1; i>1; i--){
		int ttRPos=(int)(rand()%i);
		int ttInst=inst[ttRPos];
		inst[ttRPos]=inst[i];
		inst[i]=ttInst;
	}
	return inst;
}

/**
	function to obtein the factorial of a number.
*/
double fact(double a){
	double tt=1;
	for(; a!=0; a--){
		tt*=a;
	}
	return tt;
}

/**
	function to obtein the power of a number.
*/
double powE(double a, double b){
	double resp=1;
	if(b==0){
		return 1;
	}
	for(int i=0; i<b; i++){
		resp*=a;
	}
	return resp;
}

/**
	function to obtein the bionomical probability, 
	given the next number, p(know probablity), x 
	( better known as the K), and the n, to know
	how much data is in the propsition.
*/
double genProb(double p, double x, double n){
	if(p>1 || p<0){
		return -1;//error
	}
	if(n<1){
		return -1;//error
	}
	if(x<0 || x>n){
		return -1; //error	
	}
	double comb=fact(n)/(fact(x)*fact(n-x)); //(n k)
	double expPX=powE(p,x);//p^k
	double expPNX=powE(1-p,n-x);//(1-p)^(n-k)
	return (comb*expPX*expPNX); //(i=0)(k)E [ (n k)(p^k)((1-p)^(n-k)) ]
}

/**
	method to build all the instruction set that is
	going to be read and process by the cpu.
*/
int* armarInst(double p, double w, double r, int max_inst, double rot){
	int * inst=(int*)calloc(sizeof(int),max_inst);
	double ttP=0, ttW=0, ttR=0, tSize=max_inst;
	double x=(double)(max_inst*rot);
	if(x<1){
		x=1;	
	}
	for(int i=0;x<max_inst;i++,max_inst--){
		//prob for process
		ttP=genProb(p,x,max_inst);
		ttW=genProb(w,x,max_inst);
		ttR=genProb(r,x,max_inst);
		if(ttP>ttW && ttP>ttR){
			inst[i]=PROC;
		}
		else if(ttW>ttP && ttW>ttR){
			inst[i]=((addrGen()*10)+WRITE);
		}
		else if(ttR>ttP && ttR>ttW){
			inst[i]=((addrGen()*10)+READ);
		}
	}
	return instShuffle(inst, tSize);
}
