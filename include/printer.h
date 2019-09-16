#ifndef _PRINTER_H
#define _PRINTER_H

pthread_mutex_t getMT();
void printClean(int id);
void printProcess(int id);
void printWriteMiss(int id, int addr);
void printWriteHit(int id, int addr);
void printReadMiss(int id, int addr);
void printReadHit(int id, int addr);
void printInvaBus(int id, int addr);
void printMissPenal(int id);
const char* getState(int state);
const char* getName(int addr);

#endif