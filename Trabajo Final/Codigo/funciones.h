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

/* Librerias estandares de C */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <math.h>
#include <string.h>

/* Define la estructura de un nodo del arbol de decisiones */
typedef struct _nodo {
  unsigned int atributo;          	/* Indica que atributo utilizado para dividir */
  float umbralA;                  	/* Si el atributo es continuo almacena su umbral */
  unsigned int clase;             	/* Indica la clase a la que pertenece */
  bool hoja;                      	/* Indica si el nodo es una hoja */
  float arrHijos[2];              	/* DEBUG: Contiene el valor de los atributos de sus hijos */
  struct _nodo *izq;              	/* Direccion de memoria del hijo izquierdo */
  struct _nodo *der;              	/* Direccion de memoria del hijo derecho */
} nodo;


/** Estructura de datos para alamacenar la heuristica de cada atributo */
typedef struct _infoAtributo {
	double entropia;                /* Entropia del atributo */
	double gainInfo;                /* Ganancia de informacion del atributo */
	double gainRatio;            	/* DEBUG: ratio de ganancia del atributo */
} infoAtributo;


/* Estructura utilada en para dev en funcion filtrar tabla */
typedef struct _filtroInfo {
	int numFil;                  	/* Numero de filas de la nueva matriz */
	float **tabla;               	/* Tabla filtrada */
} filtroInfo;


/* Definicion de constantes */
#define NUM_FILAS_TRAIN 998       	/* Numero de filas del dataset de entrenamiento */
#define NUM_ATRIBUTOS 10          	/* Numero de atributos del problema */
#define NUM_CLASES 2              	/* Numero de clases del problema */
#define UMBRAL_GAIN 0.001         	/* Umbral de ganancia para evitar ramas infinitas */


#define clasePorDefecto 1           /* Clase por defecto */
#define NUM_FILAS_TEST 948          /* Numero de filas del dataset de testeo */



/*** FUNCIONES FASE ENTRENAMIENTO ***/

/* Calcula y devuelve la entropia, ganancia de informacion y ratio de ganancia */
infoAtributo calcularHeuristica(int numFilas, int numAtributos, float **tabla, int indexAtributo, float umbral, FILE *);

/* Elige el mejor atributo en base a la ganancia de informacion normalizada */
int elegirAtributo(int numFilas, int numAtributos, float **tabla, float umbral1, float umbral2, FILE *);

/* Contruye el arbol con los datos de entrenamiento */
nodo* construirArbolDecision(int numFil, int numAtributos, float **tabla, nodo* ptrNodo, FILE *output);

/** Devulve un nueva tabla en la cual se han eliminado 
  * las filas con valor valorAtributo y la columna del atributo. 
  * Devuelve una matriz de M x numAtributos */
filtroInfo filtrarTabla(int numFilas, int numAtributos, float **tabla, int indexAtributo, float valorAtributo, FILE *output);

/* Filtro de tabla para atributos continuos */
filtroInfo filtrarTablaCont(int numFil, int numAtributos, float **tabla, int atributo, float valorAtributo, float umbral, FILE *output);

/* Comprueba si todas las filas de una tabla pertenecen a la misma clase */
bool esHomojenea(int numFil, int numAtributos, float **tabla);

/* Si nos quedamos sin atributos pero con datos(filas), calcula el atributo mas frecuente de los datos */
int claseMasFrecuente(int numFil, int numAtributos, float **tabla);

/** Recorre la tabla almacenando y ordenando los valores del atritubo continuo.
  * Llama a la funcion discretizacion y devuelve el umbral del atributo */
float elegirUmbral(int numFil, int numAtributos, float **tabla, float atributo, FILE *);

/* Calcula el umbral de un atributo continuo mediante discretizacion  */
float discretizacion(int numCol, float arr[][numCol], FILE *output);

/* Busca el indice del atributo en arrAtributos */
int buscarAtributo(int numAtributos, float arrAtributos[], float atributo);



/*** FUNCIONES FASE TESTEO ***/

/**
  * Funcion testDatosDT
  * Predice la clase a la que pertenece una fila (dato)
  * @param linea contiene los atributos del dato
  * @param ptrNodo raiz del arlbol binario de decisiones
  * @return prediccion clase predicha
  */
int testDatosDT(float *linea, nodo *ptrNodo);

/** 
  * Funcion analizarResultados
  * Analiza los resultados obtenidos y calcula la tasa de aciertos 
  * @param claseReales array que contiene las clase reales a las que pertenece cada dato
  * @param clasePredichass array que contiene las clase predichas a las que pertenece cada dato
  * @return EXIT_SUCCESS
  */
int analizarResultados(float claseReales[], float clasesPredichas[]);



/*** FUNCIONES UTILITARIAS  ***/

/* Lee y almacena los datos en una matriz de [numFil + 1] x [numAtributos + 1] */
float **readData(FILE *, unsigned int numFil, FILE *output);

/* Quicksort: utilizado para ordenar los valores de los atributos continuos */
void quickSort(int numCol, float arr[][numCol], int ini, int fin);

int particion(int numCol, float arr[][numCol], int ini, int fin);

void swap(float *a, float *b);


/*** FUNCIONES DEGUG ***/

/* Muestra el arbol en preorden */
void mostrarPreorden(nodo *raiz, FILE *output);

/* Imprime el arbol en anchura */
void printGivenLevel(nodo* root, int level); 

int height(nodo* node); 

void printLevelOrder(nodo* root);

/* Muestra el arbol en preorden */
void mostrarPreorden(nodo *raiz, FILE *output);