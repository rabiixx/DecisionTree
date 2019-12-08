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


#include "funciones.h"


/** 
  * funcion readData
  * Lee los datos del dataset y los almacena en una 
  * matriz de NUM_FILAS x NUM_ATRUBITOS + 1 y devuelve dicha matriz 
  * @param dataset ficheor del cual leeera los datos
  * @param numFil numero de filas que leera del fichero
  * @return los datos almacenados en una matriz de [numFil + 1] x [numAtributos + 1]
  */ 
float **readData(FILE *dataset, unsigned int numFil, FILE *output) {

	/** Declaracion de la matriz donde se guardaran los datos */
	float **arrMatrix = (float**)malloc( (numFil + 1) * sizeof(float*));

	for (int i = 0; i < numFil + 1; ++i) {
		arrMatrix[i] = (float*)malloc( (NUM_ATRIBUTOS + 1) * sizeof(float));
	}

	/* En la primera fila almacenamos los atrubutos como numeros 1,..,NumAtributos */
	for (int i = 0; i < NUM_ATRIBUTOS; ++i) {
		arrMatrix[0][i] = i;
	}

	/* Para diferencias que no es una atributo */
	arrMatrix[0][NUM_ATRIBUTOS] = 99;

	char *str = (char*)malloc(500 * sizeof(char));

	/* Leer primera linea */
	fgets(str, 500, dataset);

	for (int i = 1; i < numFil + 1; ++i) {
		fgets(str, 500, dataset);
		sscanf(str, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", &arrMatrix[i][0], &arrMatrix[i][1], &arrMatrix[i][2], &arrMatrix[i][3], &arrMatrix[i][4], &arrMatrix[i][5], &arrMatrix[i][6], &arrMatrix[i][7], &arrMatrix[i][8], &arrMatrix[i][9], &arrMatrix[i][10]);
	}


	int numVivos = 0;
	int numMuertos = 0;
	for (int i = 1; i < numFil + 1; ++i)
	{
		if (arrMatrix[i][NUM_ATRIBUTOS] == 1)
			++numVivos;
		else
			++numMuertos;
	}

	return arrMatrix;
}


/** Funcion QuickSort 
  * Ordena los valores de un array de [2, N] 
  * por columnas en base a los valores de la primera fila
  * @param numCol numero de elementos del array
  * @param arr array a ordenar  
  * @param indice inicial del array
  * @param indice final del array
  */
void quickSort(int numCol, float arr[][numCol], int ini, int fin) {  
    
    if (ini < fin) {  
        
        int part = particion(numCol, arr, ini, fin);  
  
        quickSort(numCol, arr, ini, part - 1);  
        quickSort(numCol, arr, part + 1, fin);  
    }  
}
  
int particion(int numCol, float arr[][numCol], int ini, int fin)  
{  
    float pivote = arr[0][fin]; 
    int i = (ini - 1);
  
    for (int j = ini; j <= fin - 1; j++)  
    {  
        // If current element is smaller than the pivot  
        if (arr[0][j] < pivote)  
        {  
            i++; // increment index of smaller element  
            swap(&arr[0][i], &arr[0][j]);
            swap(&arr[1][i], &arr[1][j]);  
  
        }  
    }  
    swap(&arr[0][i + 1], &arr[0][fin]);
    swap(&arr[1][i + 1], &arr[1][fin]);  
    return (i + 1);  
}  

/** Funcion utilitaria para intercambiar el valor de dos variables */ 
void swap(float *a, float *b)  
{  
    float t = *a;  
    *a = *b;  
    *b = t;  
} 


/** 
  *	Las funciones que se muestran a continuacion no son utilizadas en el algortimo
  * se han incluido por motivos de debug, si no es asi, carecen de sentido. 
  */


/**
  * Funcion mostrarPreorden
  * Muestra el arbol en preorden, esta funcion esta incluida
  * por motivos de degugeo
  * @param raiz direccion de memoria del nodo actual del arbol
  */
void mostrarPreorden(nodo *raiz, FILE *output) {
	if (raiz) {
        printf(/*output, */"Atributo: %d\n", raiz->atributo);
        printf(/*output, */"Clase: %d\n", raiz->clase);
        printf(/*output, */"Es Hoja: %d\n", raiz->hoja);
        printf(/*output, */"\n");
        mostrarPreorden(raiz->izq, output);
        mostrarPreorden(raiz->der, output);
    } else {
        return;
    }
}


/**
  * @author Geeksforgeeks.com 
  *	Imprime el arbol en anchur, esta funcion esta incluida
  * por motivos de debugeo 
  */
void printLevelOrder(nodo* root) 
{ 
	int h = height(root); 
	int i; 
	for (i = 1; i <= h; i++) 
		printGivenLevel(root, i); 
} 

/* Print nodes at a given level */
void printGivenLevel(nodo* root, int level) 
{ 
	if (root == NULL) 
		return; 
	if (level == 1) {
		printf("Atributo: %d\n", root->atributo);
        printf("Clase: %d\n", root->clase);
        printf("Es Hoja: %d\n", root->hoja);
        printf("\n");
	} else if (level > 1) { 
		printGivenLevel(root->izq, level-1); 
		printGivenLevel(root->der, level-1); 
	} 
} 

/* Compute the "height" of a tree -- the number of 
	nodes along the longest path from the root node 
	down to the farthest leaf node.*/
int height(nodo* node) 
{ 
	if (node == NULL) 
		return 0; 
	else
	{ 
		/* compute the height of each subtree */
		int lheight = height(node->izq); 
		int rheight = height(node->der); 

		/* use the larger one */
		if (lheight > rheight) 
			return(lheight + 1); 
		else return(rheight + 1); 
	} 
} 



  
