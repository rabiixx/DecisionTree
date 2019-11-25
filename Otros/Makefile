func: funciones.c
	gcc -g -c funciones.c

main: decisionTreeMain.c funciones.o
	gcc -g -o  decisionTreeMain decisionTreeMain.c funciones.o -Wall -pedantic

all: lib main

clean:
	@- rm -f -v decisionTreeMain
	@- rm -f -v funciones.o