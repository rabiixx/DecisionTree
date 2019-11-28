
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

#define NUM_FILAS_TRAIN 15    	/* Numero de filas del dataset de entrenamiento */
#define NUM_FILAS_TEST 20		/* Numero de filas de los datos de entrenamiento */

#define NUM_ATRIBUTOS 10		/* Numero de atributos del problema */
#define NUM_CLASES 2			/* Numero de clases */

char *arrAtributos[] = {"Masculino", "Libro1", "Libro2", "Libro3", "Libro4", "Libro5", "Matrimonio", "Nobleza", "MuertesR", "Popularidad"};
char *arrClases[2] = {"Vivo", "Muerto"};


string testDataOnDecisionTree(vs &singleLine, node* nodePtr, vvs &tableInfo, string defaultClass)
{
	string prediction;
	while (!nodePtr->isLeaf && !nodePtr->children.empty()) {
		int index = returnColumnIndex(nodePtr->splitOn, tableInfo);	/*dev atributo */
		string value = singleLine[index];
		int childIndex = returnIndexOfVector(nodePtr->childrenValues, value);
		nodePtr = nodePtr->children[childIndex];
		if (nodePtr == NULL) {
			prediction = defaultClass;
			break;
		}
		prediction = nodePtr->label;
	}
	return prediction;
}

/* Fase de testeo */
int testDatosDT(float **tabla, nodo *ptrNodo, int clasePorDefecto) {

	int prediccion;

	while ( !ptrNodo->esHoja ) {
		int valor = linea[atributo];
		if (valor = NO) {
			ptrNodo = ptrNodo->izq;
		} else if (valor = SI) {
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

int main(int argc, char const *argv[]) {

	system("clear");

	/* Declaracion de una matriz mediante punteros */
	float **tabla = (float**)malloc( (NUM_FILAS + 1) * sizeof(float*));

	for (int i = 0; i < NUM_FILAS + 1; ++i) {
		tabla[i] = (float*)malloc( (NUM_ATRIBUTOS + 1) * sizeof(float));
	}

	FILE *trainData, *testData;
	FILE *output = fopen("output.txt", "w");

	if ( (trainData = fopen("problem_book1.csv", "r")) == NULL ) {
		printf("Error al abrir fichero: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	/* Se leen los datos de entrenamieto */
	tabla = readData(trainData, NUM_FILAS_TRAIN, output);
	fclose(inputData);

	/* Nodo raiz del arbol de deciciones */
	nodo *raiz = (nodo*)malloc(sizeof(nodo));

	/* Fase de entrenamiento: construccion del arbol de decisiones */
	raiz = construirArbolDecision(NUM_FILAS, NUM_ATRIBUTOS, tabla, raiz, output);

	/* FASE DE TESTO */

	tabla = readData(testData, NUM_FILAS_TEST, output);
	fclose(testData);

	float clasesReales;			/* Guarda las clase de los datos de testeo*/
	float clasesPredichas;		/* Guarda las clases predecidas de los datos de testeo */

	for (int i = 0; i < N; ++i) {
		clasesReales = tablaDatos[i + 1][NUM_ATRIBUTOS];
	}

	for (int i = 0; i < ; ++i) {
		clasesPredichas[i] = testDatosDT(tablaDatos, raiz, clasePorDefecto);
	}

	free(tabla);

	return EXIT_SUCCESS;
}

nodo nuevoNodo() {
	return (nodo*)malloc(sizeof(nodo));
}

void analizarResultados(int claseReales[], int clasesPredichas){

	FILE *reporte;
	unsigned int numAciertos = 0;
	double tasaAciertºos;

	if ( (reporte = fopen("reporte.txt", "w")) == NULL ) {
		printf("Error al abrir fichero: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	fprintf(reporte, "| Clase Real -------------------- Clase Predicha |\n", );
	fprintf(reporte, "| ---------------------------------------------- |\n", );
	for (int i = 0; i < NUM_FILAS_TEST; ++i) {
		
		if (claseReales[i] == 0) {
			fprintf(reporte, "Muerto");
		} else {
			fprintf(reporte, "Vivo");
		}

		if (claseReales[i] == clasesPredichas[i]) {
			++numAciertos;
			fprintf(reporte, "-------------");
		} else {
			fprintf(reporte, "xxxxxxxxxxxxx");
		}

		if (clasesPredichas[i] == 0) {
			fprintf(reporte, "Muerto");
		} else {
			fprintf(reporte, "Vivo");
		}	
	}

	tasaAciertos = (double)numAciertos / (double)NUM_FILAS_TEST;

	fprintf(reporte, "Numero de filas: %d\n", NUM_FILAS_TEST);
	fprintf(reporte, "Numero de Aciertos: %d\n", numAciertos);
	fprintf(reporte, "Tasa De Acierto: %f", tasaAciertos);

	fclose(reporte);


}
