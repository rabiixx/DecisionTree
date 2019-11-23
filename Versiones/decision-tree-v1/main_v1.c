#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/* code */

#define NUM_ENTRENAMIENTO 100    /* Numero de filas del dataset de entrenamiento */
#define NUM_TEST                  /* Numero de filas del dataset de testeo */ 


#define NUM_ATRIBUTOS 10          /* Numero de atributos del problema */
#define NUM_CLASES 2              /* Numero de clases */

int main(int argc, char const *argv[]) {

	char *str_atributos[] = {"Masculino", "Libro1", "Libro2", "Libro3", "Libro4", "Libro5", "Matrimonio", "Nobleza", "MuertesR", "Popularidad"};

	char *arrClases[2] = {"Vivo", "Muerto"};


	float **tabla = (float**)malloc(NUM_FILAS * sizeof(float*));

	for (int i = 0; i < NUM_FILAS; ++i) {
		tabla[i] = (float*)malloc(NUM_ATRIBUTOS * sizeof(float));
	}

	tabla = readData(NUM_FILAS, NUM_ATRIBUTOS);

	nodo *raiz = NULL;
	raiz = construirArbol(tabla, raiz, arrAtributos);


	return 0;
}
