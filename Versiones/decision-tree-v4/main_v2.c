
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "funciones_v2.h"


//char *arrAtributos[] = {"Masculino", "Libro1", "Libro2", "Libro3", "Libro4", "Libro5", "Matrimonio", "Nobleza", "MuertesR", "Popularidad"};
//char *arrClases[2] = {"Vivo", "Muerto"};


/*string testDataOnDecisionTree(vs &singleLine, node* nodePtr, vvs &tableInfo, string defaultClass)
{
	string prediction;
	while (!nodePtr->isLeaf && !nodePtr->children.empty()) {
		/*int index = returnColumnIndex(nodePtr->splitOn, tableInfo);*/	/*dev atributo */
		/*string value = singleLine[index];
		int childIndex = returnIndexOfVector(nodePtr->childrenValues, value);
		nodePtr = nodePtr->children[childIndex];
		if (nodePtr == NULL) {
			prediction = defaultClass;
			break;
		}
		prediction = nodePtr->label;
	}
	return prediction;
}*/

/* Fase de testeo */
int testDatosDT(float *linea, nodo *ptrNodo) {

	int prediccion;

	while ( ptrNodo && ptrNodo->izq && ptrNodo->der) {

		float valor = linea[ptrNodo->atributo];
		printf("ptrNodo->atributo: %d\n", ptrNodo->atributo);
		//printf("Valor: %f\n", valor);
		//printf("ptrNodo->atributo: %d\n", ptrNodo->atributo);
		if (ptrNodo->atributo == 8 || ptrNodo->atributo == 9) {	
		//	printf("ptrNodo->umbral: %f\n\n", ptrNodo->umbralA);
			if (valor <= ptrNodo->umbralA) {
				ptrNodo = ptrNodo->izq;	
				//printf("hola1\n");
			} else if (valor > ptrNodo->umbralA) {
				ptrNodo = ptrNodo->der;
				//printf("hola2\n");
			}
		} else {	
			if (valor == 0)
				ptrNodo = ptrNodo->izq;
			else if (valor == 1)
				ptrNodo = ptrNodo->der;
		}

		if (ptrNodo == NULL) {
			prediccion = clasePorDefecto;
			break;
		}

		prediccion = ptrNodo->clase;

	}

	return prediccion;

}


/* Analiza los resultados obtenidos y calcula la tasa de aciertos */
int analizarResultados(float claseReales[], float clasesPredichas[]){

	FILE *reporte;						/* Fichero de reporte */
	unsigned int numAciertos = 0;		/* Numero de aciertos */
	double tasaAciertos;				/* Tasa de aciertos */

	if ( (reporte = fopen("reporte.txt", "w")) == NULL ) {
		printf("Error al abrir fichero: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	fprintf(reporte, "| Clase Real -------------------- Clase Predicha |\n");
	fprintf(reporte, "| ---------------------------------------------- |\n");
	for (int i = 0; i < NUM_FILAS_TEST; ++i) {
		
		if (claseReales[i] == 0) {
			fprintf(reporte, "\tMuerto");
		} else {
			fprintf(reporte, "\tVivo");
		}

		if (claseReales[i] == clasesPredichas[i]) {
			++numAciertos;
			fprintf(reporte, "\t-------------\t");
		} else {
			fprintf(reporte, "\txxxxxxxxxxxxx\t");
		}

		if (clasesPredichas[i] == 0) {
			fprintf(reporte, "Muerto\n");
		} else {
			fprintf(reporte, "Vivo\n");
		}	
	}

	fprintf(reporte, "| ---------------------------------------------- |\n");
	fprintf(reporte, "RESULTADOS FINALES: \n");
	tasaAciertos = (double) numAciertos / (double) NUM_FILAS_TEST;


	fprintf(reporte, "\t[+] Numero de filas: %d\n", NUM_FILAS_TEST);
	fprintf(reporte, "\t[+] Numero de Aciertos: %d\n", numAciertos);
	fprintf(reporte, "\t[+] Tasa De Acierto: %f", tasaAciertos);

	fclose(reporte);

	return EXIT_SUCCESS;

}


int main(int argc, char const *argv[]) {

	system("clear");

	/* Declaracion de una matriz mediante punteros */
	float **tablaTrain = (float**)malloc( (NUM_FILAS_TRAIN + 1) * sizeof(float*));

	for (int i = 0; i < NUM_FILAS_TRAIN + 1; ++i) {
		tablaTrain[i] = (float*)malloc( (NUM_ATRIBUTOS + 1) * sizeof(float));
	}

	FILE *trainData, *testData;
	FILE *output = fopen("output.txt", "w");

	if ( (trainData = fopen("trainData2.dat", "r")) == NULL ) {
		printf("Error al abrir fichero: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	if ( (testData = fopen("testData2.dat", "r")) == NULL ) {
		printf("Error al abrir fichero: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}


	/* Se leen los datos de entrenamieto */
	tablaTrain = readData(trainData, NUM_FILAS_TRAIN, output);
	fclose(trainData);

	/* Nodo raiz del arbol de deciciones */
	nodo *raiz = (nodo*)malloc(sizeof(nodo));

	printf("[+] Comienzo la fase de entrenamiento\n");

	/* Fase de entrenamiento: construccion del arbol de decisiones */
	raiz = construirArbolDecision(NUM_FILAS_TRAIN, NUM_ATRIBUTOS, tablaTrain, raiz, output);

	printf("[+] Finalizada la fase de entrenamiento\n");

	mostrarPreorden(raiz, output);


	/* FASE DE TESTO */

	/* Declaracion de una matriz mediante punteros */
	float **tablaTest = (float**)malloc( (NUM_FILAS_TEST + 1) * sizeof(float*));

	for (int i = 0; i < NUM_FILAS_TEST + 1; ++i) {
		tablaTest[i] = (float*)malloc( (NUM_ATRIBUTOS + 1) * sizeof(float));
	}

	tablaTest = readData(testData, NUM_FILAS_TEST, output);
	fclose(testData);

	float clasesReales[NUM_FILAS_TEST];			/* Guarda las clase de los datos de testeo */
	float clasesPredichas[NUM_FILAS_TEST];		/* Guarda las clases predecidas de los datos de testeo */


	printf("[+] Comienzo la fase de testeo\n");

	for (int i = 0; i < NUM_FILAS_TEST; ++i) {
		clasesReales[i] = tablaTest[i + 1][NUM_ATRIBUTOS];
	}

	for (int i = 0; i < NUM_FILAS_TEST; ++i) {
		clasesPredichas[i] = testDatosDT(tablaTest[i + 1], raiz);
	}

	free(tablaTrain);
	free(tablaTest);

	printf("[+] Finaliza la fase de testeo\n");

	
	/* Analizamos los resultados obtenidos */
	analizarResultados(clasesReales, clasesPredichas);


	return EXIT_SUCCESS;
}
