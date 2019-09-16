PHONY: clean install

OPO=src/instGen.o src/tablaDirecciones.o src/memoria.o src/cpu.o src/main.o src/clock.o src/printer.o
OPB=bin/output

install:
		cd src/ && make
		
clean:
		rm $(OPB) $(OPO)