OPO=instGen.o tablaDirecciones.o memoria.o clock.o cpu.o printer.o main.o 
LIB=../lib
INCLUDE=../include
FLAG1=-Wall -c 
FLAG2=-Wall -o 
CC=gcc

output.o: $(OPO)
		$(CC) $(OPO) $(FLAG2) ../bin/output -lpthread

cpu.o: $(LIB)/cpu.c $(INCLUDE)/cpu.h
		$(CC) $(FLAG1) ../lib/cpu.c

memoria.o: $(LIB)/memoria.c $(INCLUDE)/memoria.h
		$(CC) $(FLAG1) ../lib/memoria.c

tablaDirecciones.o: $(LIB)/tablaDirecciones.c $(INCLUDE)/tablaDirecciones.h
		$(CC) $(FLAG1) ../lib/tablaDirecciones.c

instGen.o: $(LIB)/instGen.c $(INCLUDE)/instGen.h
		$(CC) $(FLAG1) ../lib/instGen.c
		
clock.o: $(LIB)/clock.c $(INCLUDE)/clock.h
		$(CC) $(FLAG1) ../lib/clock.c
		
printer.o: $(LIB)/printer.c $(INCLUDE)/printer.h
		$(CC) $(FLAG1) ../lib/printer.c
		
main.o: main.c
		$(CC) $(FLAG1) main.c 