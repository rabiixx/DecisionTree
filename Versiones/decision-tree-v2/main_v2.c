
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "funciones_v2.h"

#define NUM_FILAS 15    /* Numero de filas del dataset de entrenamiento */

#define NUM_ATRIBUTOS 10          /* Numero de atributos del problema */
#define NUM_CLASesrfES 2              /* Numero de clases */


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

	FILE *inputData, *outputData;
	//FILE *output = fopen("output.txt", "w");

	if ( (inputData = fopen("problem_book1.csv", "r")) == NULL ) {
		printf("Error al abrir fichero: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	float **tabla = (float**)malloc( (NUM_FILAS + 1) * sizeof(float*));

	for (int i = 0; i < NUM_FILAS + 1; ++i) {
		tabla[i] = (float*)malloc( (NUM_ATRIBUTOS + 1) * sizeof(float));
	}

	tabla = readData(NUM_FILAS, NUM_ATRIBUTOS, output);

	nodo *raiz = NULL;

 	nodo *temp =  (nodo*)malloc(sizeof(nodo)); 

 	raiz = temp;

	raiz = construirArbolDecision(NUM_FILAS, NUM_ATRIBUTOS, tabla, raiz, output);

	//mostrarPreorden(raiz, output);

    printLevelOrder(raiz);  

	fclose(output);

	return 0;
}



