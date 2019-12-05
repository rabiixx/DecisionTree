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


/*** LIBRERIA QUE CONTIENE LAS FUNCIONES DE LA FASE DE TESTEO ***/

/* Liberias estandares de C */
#include <stdio.h>
#include <stdlib.h>

#define NUM_FILAS_TEST 1000		/* Numero de filas del dataset de testeo */

/**
  * Funcion testDatosDT
  * Predice la clase a la que pertenece una fila (dato)
  * @param linea contiene los atributos del dato
  * @param ptrNodo raiz del arlbol binario de decisiones
  * @return prediccion clase predicha
  */
int testDatosDT(float *linea, nodo *ptrNodo);

/* Analiza los resultados obtenidos y calcula la tasa de aciertos */
int analizarResultados(float claseReales[], float clasesPredichas[]);
