lib: funciones_v1.c
	gcc -c funciones_v1.c -lm

main: main_v1.c funciones_v1.o
	gcc main_v1.c -o main_v1 funciones_v1.o -Wall -pedantic -lm

all: main

dbg_lib: funciones_v1.c
	gcc -g -c funciones_v1.c -lm

dbg_main: main_v1.c funciones_v1.o
	gcc -g main_v1.c -o main_v1 funciones_v1.o -Wall -pedantic -lm

degub: dbg_main dbg_lib

clean:
	rm main_v1 
	rm funciones_v1.o
