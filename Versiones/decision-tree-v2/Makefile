lib: funciones_v2.c
	gcc -c funciones_v2.c -lm

main: main_v2.c funciones_v2.o
	gcc main_v2.c -o main_v2 funciones_v2.o -Wall -pedantic -lm

all: main

dbg_lib: funciones_v2.c
	gcc -g -c funciones_v2.c -lm

dbg_main: main_v2.c funciones_v2.o
	gcc -g main_v2.c -o main_v2 funciones_v2.o -Wall -pedantic -lm

degub: dbg_main dbg_lib

clean:
	rm main_v2 
	rm funciones_v2.o