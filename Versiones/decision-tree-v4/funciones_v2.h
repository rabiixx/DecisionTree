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



/** Indices Atributos
  * 0 --> Masculino
  * 1 --> Libro1
  * 2 --> Libro2
  * 3 --> Libro3
  * 4 --> Libro4
  * 5 --> Libro5
  * 6 --> Matrimonio
  * 7 --> Nobleza
  * 8 --> Muertes Realcionadas
  * 9 --> Popularidad 
  */

/** Indices tipos atributo
  * 1 --> Si
  * 0 --> No
  */

/** Indices clases
  * 1 -- > Vivo
  * 0 --> Muerto
  */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define VIVO -5
#define MUERTO -10

#define SI 213
#define NO 564

#define NUM_FILAS_TRAIN 1000      /* Numero de filas del dataset de entrenamiento */
#define NUM_FILAS_TEST 1000       /* Numero de filas de los datos de entrenamiento */

#define NUM_ATRIBUTOS 10        /* Numero de atributos del problema */
#define NUM_CLASES 2            /* Numero de clases */

#define clasePorDefecto 1

#define UMBRAL_GAIN 0.01


/** Estructura de datos para alamacenar la heuristica de cada atributo */
typedef struct _infoAtributo {
	double entropia;
	double gainInfo;
	double gainRatio;
} infoAtributo;

/* Define la estructura de una nodo del arbol de decisiones */
typedef struct _nodo {
	unsigned int atributo;       /* Indica que atributo usar para dividir */
	float umbralA;               /* Si el atributo es continuo almacena su umbral */
  unsigned int clase;          /* Si es una hoja, indica la clase a la pertenece */
	bool hoja;						       /* Indica si el nodo es una hoja */
	float arrHijos[2];             /* Contiene el valor de los atributos de sus hijos */
	struct _nodo *izq;           /* Direccion de memoria del hijo izquierdo */
	struct _nodo *der;           /* Direccion de memoria del hijo derecho */
} nodo;


/* Contiene el numero de filas que contiene la tabla filtrada asi como la tabla filtrada */
typedef struct _filtroInfo {
	int numFil;
	float **tabla;
} filtroInfo;

/* Calcula y devuelve la entropia, ganancia de informacion y ratio de ganancia */
infoAtributo calcularHeuristica(int numFilas, int numAtributos, float **tabla, int indexAtributo, float umbral, FILE *);

/* Elige el mejor atributo en base a la ganancia de informacion normalizada */
int elegirAtributo(int numFilas, int numAtributos, float **tabla, float umbral1, float umbral2, FILE *);

/* Lee y almacena los datos en una matriz de [numFil+1] x [numAtributos + 1] */
float **readData(FILE *, unsigned int numFil, FILE *output);

/* Contruye el arbol con los datos de entrenamiento */
nodo* construirArbolDecision(int numFil, int numAtributos, float **tabla, nodo* ptrNodo, FILE *output);

/** Devulve un nueva tabla en la cual se han eliminado 
  * las filas con valor valorAtributo y la columna del atributo. 
  * Devuelve una matriz de M x numAtributos */
filtroInfo filtrarTabla(int numFilas, int numAtributos, float **tabla, int indexAtributo, float valorAtributo, FILE *output);

/* Filtro de tabla para atributos continuos */
filtroInfo filtrarTablaCont(int numFil, int numAtributos, float **tabla, int atributo, float valorAtributo, float umbral, FILE *output);

/* Elimina una columna completa de un atributo continuo cuando el umbral = 0 */
filtroInfo eliminarCol(int numFil, int numAtributos, float **tabla, int atributo, FILE *output);

/* Comprueba si todas las filas de una tabla pertenecen a la misma clase */
bool esHomojenea(int numFil, int numAtributos, float **tabla);

/* Muestra el arbol en preorden */
void mostrarPreorden(nodo *raiz, FILE *output);

/* Si nos quedamos sin atributos pero con datos(filas), calcula el atributo mas frecuente de los datos */
int claseMasFrecuente(int numFil, int numAtributos, float **tabla);

/* Imprime el arbol en anchura */
void printGivenLevel(nodo* root, int level); 

int height(nodo* node); 

void printLevelOrder(nodo* root);

/** Recorre la tabla almacenando y ordenando los valores del atritubo continuo.
  * Llama a la funcion discretizacion y devuelve el umbral del atributo */
float elegirUmbral(int numFil, int numAtributos, float **tabla, float atributo, FILE *);

/* Quicksort: utilizado para ordenar los valores de los atributos continuos */
void swap(float *a, float *b);

int partition (int numCol, float arr[][numCol], int low, int high);

void quickSort(int numCol, float arr[][numCol], int low, int high);

/* Funcion de discretizacion que devulve un umbral del atributo coninuo */
float discretizacion(int numCol, float arr[][numCol], FILE *output);





