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

typedef struct _infoAtributo {
	double entropia;
	double gainInfo;
	double gainRatio;
} infoAtributo;

/* Define la estructura de una nodo del arbol de decisiones */
typedef struct _nodo {
	unsigned int atributo;			/* Indica que atributo usar para dividir */
	unsigned int clase;				/* Si es una hoja, indica la clase a la pertenece */
	bool hoja;						/* Indica si el nodo es una hoja */
	int *arrHijos[];				/* Contiene el valor de los atributos de sus hijos */
	struct _nodo *izq;				/* Direccion de memoria del hijo izquierdo */
	struct _nodo *der;				/* Direccion de memoria del hijo derecho */
} nodo;


/* Contiene el numero de filas que contiene la tabla filtrada asi como la tabla filtrada */
typedef struct _filtroInfo {
	int numFil;
	float **tabla;
}


infoAtributo calculoEntropiaCat(int numFilas, int numAtributos, float **tabla, int indexAtributo);

int elegirAtributo(int numFilas, int numAtributos, float **tabla);

float **readData(unsigned int numFil, unsigned int numAtributos);

nodo* construirArbolDecision(int numFil, int numAtributos, float **tabla, nodo* ptrNodo);

float **filtrarTabla(int numFilas, int numAtributos, float **tabla, int indexAtributo, float valorAtributo);

bool esTablaVacia(float **tabla);

bool esHomojenea(int numFil, int numAtributos, float **tabla);