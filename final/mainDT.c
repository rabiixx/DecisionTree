// The MIT License (MIT)

// Copyright (c) 2019 Ruben Cherif Narvaez

//  Permission is hereby granted, free of charge, to any person obtaining a 
//  copy of this software and associated documentation files (the "Software"), 
//  to deal in the Software without restriction, including without limitation 
//  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
//  and/or sell copies of the Software, and to permit persons to whom the 
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in 
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
//  DEALINGS IN THE SOFTWARE.


/**
  * Compilador: GCC 
  * Version compilador: 7.4.0
  * Entorno: Ubuntu 18.04.3 LTS
  * Kernel Version: 4.15.0-64-generic
  * Autor: Ruben Cherif Narvaez
  * Email: 99rubenche@gmail.com
  * github: https://github.com/rabiixx
  * Fecha: 
  */



/* Librerias estandares de C */
#include <errno.h>
#include "funciones.h"


/* Main Program */
int main(int argc, char const *argv[]) {

	system("clear");		/* Clear Linux STDOUT */

	/* Declaracion de una matriz mediante punteros */
	float **tablaTrain = (float**)malloc( (NUM_FILAS_TRAIN + 1) * sizeof(float*));

	for (int i = 0; i < NUM_FILAS_TRAIN + 1; ++i) {
		tablaTrain[i] = (float*)malloc( (NUM_ATRIBUTOS + 1) * sizeof(float));
	}

	FILE *trainData, *testData;						/* Dataset de entrenamiento y de testeo */
	FILE *output = fopen("traza.txt", "w");			/* Fichero traza */

	if ( (trainData = fopen("Datasets/train1500.dat", "r")) == NULL ) {
		printf("Error al abrir fichero: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	if ( (testData = fopen("Datasets/test448.dat", "r")) == NULL ) {
		printf("Error al abrir fichero: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}


	/* Se leen los datos de entrenamieto */
	tablaTrain = readData(trainData, NUM_FILAS_TRAIN, output);
	fclose(trainData);

	/* Nodo raiz del arbol de deciciones */
	nodo *raiz = (nodo*)malloc(sizeof(nodo));

	printf("[+] Comienzo la fase de entrenamiento\n");

	/*** FASE DE ENTRENAMIENTO ***/

	/* Se construye del arbol de decisiones */
	raiz = construirArbolDecision(NUM_FILAS_TRAIN, NUM_ATRIBUTOS, tablaTrain, raiz, output);

	printf("[+] Finalizada la fase de entrenamiento\n");

	//mostrarPreorden(raiz, output);


	/*** FASE DE TESTO ***/


	float clasesReales[NUM_FILAS_TEST];			/* Guarda las clase de los datos de testeo */
	float clasesPredichas[NUM_FILAS_TEST];		/* Guarda las clases predecidas de los datos de testeo */

	/* Declaracion de una matriz mediante punteros */
	float **tablaTest = (float**)malloc( (NUM_FILAS_TEST + 1) * sizeof(float*));

	for (int i = 0; i < NUM_FILAS_TEST + 1; ++i) {
		tablaTest[i] = (float*)malloc( (NUM_ATRIBUTOS + 1) * sizeof(float));
	}

	/* Se leen los datos de testeo */
	tablaTest = readData(testData, NUM_FILAS_TEST, output);
	
	fclose(testData);

	printf("[+] Comienzo la fase de testeo\n");

	/* Se guardan las clases reales de los datos de testeo */
	for (int i = 0; i < NUM_FILAS_TEST; ++i) {
		clasesReales[i] = tablaTest[i + 1][NUM_ATRIBUTOS];
	}

	/* Se guardan las clase predichas de los datos de testeo */
	for (int i = 0; i < NUM_FILAS_TEST; ++i) {
		clasesPredichas[i] = testDatosDT(tablaTest[i + 1], raiz);
	}

	/* Liberacion de memoria final */
	free(tablaTrain);
	free(tablaTest);

	printf("[+] Finaliza la fase de testeo\n");
	
	/* Se analizan los resultados obtenidos */
	analizarResultados(clasesReales, clasesPredichas);

	return EXIT_SUCCESS;
}
