libTrain: funcionesTrain.c
	gcc -c funcionesTrain.c -lm

libTest: funcionesTesteo.c
	gcc -c funcionesTesteo.c -lm

libUtil: DT_utilities.c
	gcc -c DT_utilities.c -lm

main: mainDT.c funcionesTrain.o funcionesTesteo.o DT_utilities.o
	gcc mainDT.c -o mainDT funcionesTrain.o funcionesTesteo.o DT_utilities.o -Wall -pedantic -lm

all: libTrain libTest libUtil main

dbg_libTrain: funcionesTrain.c
	gcc -g -c funcionesTrain.c -lm

dbg_libTets: funcionesTesteo.c
	gcc -g -c funcionesTesteo.c

dbg_libUtil: DT_utilities.c
	gcc -g -c DT_utilities.c

dbg_main: mainDT.c funcionesTrain.o funcionesTesteo.o DT_utilities.o
	gcc -g mainDT.c -o mainDT_dbg funcionesTrain.o funcionesTesteo.o DT_utilities.o -Wall -pedantic -lm

degub: dbg_libTrain dbg_libTrain dbg_libUtil mainDT_dbg

clean:
	@- rm -f -v mainDT 
	@- rm -f -v funcionesTrain.o
	@- rm -f -v funcionesTesteo.o
	@- rm -f -v  DT_utilities.o

dbg_clean:
	@- rm -f -v mainDT_dbg 
	@- rm -f -v funcionesTrain.o
	@- rm -f -v funcionesTesteo.o
	@- rm -f -v DT_utilities.o
