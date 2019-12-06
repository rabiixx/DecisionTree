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

#include "funcionesTesteo.h"

/**
  * Funcion testDatosDT
  * Predice la clase a la que pertenece una fila (dato)
  * @param linea contiene los atributos del dato
  * @param ptrNodo raiz del arlbol binario de decisiones
  * @return prediccion clase predicha
  */
int testDatosDT(float *linea, nodo *ptrNodo) {

	int prediccion;

	while ( ptrNodo && ptrNodo->izq && ptrNodo->der) {

		/* Guardamos el valor del atributo de la fila */
		float valor = linea[ptrNodo->atributo];

		/* Atributo continuo */
		if (ptrNodo->atributo == 8 || ptrNodo->atributo == 9) {	
			if (valor <= ptrNodo->umbralA)				/* Si es menor que el umbral buscamos por rama izquierda */
				ptrNodo = ptrNodo->izq;	
			else if (valor > ptrNodo->umbralA)			/* Si es mayor que el umbral buscamos por rama derecha */
				ptrNodo = ptrNodo->der;

		/* Atributo discreto */
		} else {	
			if (valor == 0)								/* Si es cero buscamos por rama izquierda */
				ptrNodo = ptrNodo->izq;
			else if (valor == 1)
				ptrNodo = ptrNodo->der;					/* Si es cero buscamos por rama derecha */
		}

		if (ptrNodo == NULL) {
			prediccion = clasePorDefecto;
			break;
		}

		prediccion = ptrNodo->clase;
	}

	return prediccion;
}


/** 
  * Funcion analizarResultados
  * Analiza los resultados obtenidos y calcula la tasa de aciertos 
  * @param claseReales array que contiene las clase reales a las que pertenece cada dato
  * @param clasePredichass array que contiene las clase predichas a las que pertenece cada dato
  * @return EXIT_SUCCESS
*/
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
	fprintf(reporte, "\tRESULTADOS FINALES: \n");
	tasaAciertos = (double) numAciertos / (double) NUM_FILAS_TEST;


	fprintf(reporte, "\t[+] Numero de filas: %d\n", NUM_FILAS_TEST);
	fprintf(reporte, "\t[+] Numero de Aciertos: %d\n", numAciertos);
	fprintf(reporte, "\t[+] Tasa De Acierto: %f %", tasaAciertos);

	fclose(reporte);

	return EXIT_SUCCESS;

}