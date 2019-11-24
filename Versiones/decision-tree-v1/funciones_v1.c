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
#include <stdbool.h>
#include <math.h>
#include "funciones_v1.h"

/**
  * Calcula la entropia y la ganancia de informacion y la de un atributo categorico 
  * con una clase binaria
  */ 
infoAtributo calculoEntropiaCat(int numFilas, int numAtributos, float **tabla, int indexAtributo, FILE *output)
{

	/* DECLARACION DE VARIABLES */

	infoAtributo heuristica;					/* Estructura para almacenar los parametros de la heuristica */

	unsigned int numAtributoSi = 0;				/* Numero de filas que tiene un SI en el atributo */
	unsigned int numAtributoNo = 0;				/* Numero de filas que tiene un NO en el atributo */
	unsigned int numAtributoSiVivos = 0;		/* Numero de personajes que tiene un si en el atributo y estan vivos */
	unsigned int numAtributoSiMuertos = 0;		/* Numero de personajes que tiene un si en el atributo y estan muertos */
	unsigned int numAtributoNoVivos = 0;		/* Numero de personajes que tiene un no en el atributo y estan vivos */
	unsigned int numAtributoNoMuertos = 0;		/* Numero de personajes que tiene un no en el atributo y estan muertos */	
	unsigned int numVivos;						/* Numero de peresonajes vivos */
	unsigned int numMuertos;					/* Numero de peresonajes muertos */

	double entropiaSi; 
	double entropiaSiVivos;
	double entropiaSiMuertos;

	/* OBTENCION DATOS */

	/* Se recorre la tabla con el fin de obtener los datos que nos interesan para el calculo de la heuristica */
	for (int i = 1; i < numFilas + 1; ++i) {
		if (tabla[i][indexAtributo] == 1) {
			++numAtributoSi;
			if (tabla[i][numAtributos - 1] == 1)
				++numAtributoSiVivos;
			else
				++numAtributoSiMuertos;
		} else {
			++numAtributoNo;
			if (tabla[i][numAtributos - 1] == 0)
				++numAtributoNoVivos;
			else 
				++numAtributoNoMuertos;
		}
	}

	numVivos = numAtributoSiVivos + numAtributoNoVivos;
	numMuertos = numAtributoSiMuertos + numAtributoNoMuertos;

	/* CALCULO HEURISTICA */

	/* Se calcula la entropia de SI  -  E_Atributo(SI) */
	if ( numAtributoSiVivos != 0 ) {
		entropiaSiVivos = ( (double)numAtributoSiVivos / (double)numAtributoSi ) * ( log( ( (double)numAtributoSi / (double)numAtributoSiVivos) ) / log(2));
	} else {
		entropiaSiVivos = (double) 0;
	}

	if ( numAtributoSiMuertos != 0 ){
		entropiaSiMuertos = ( (double)numAtributoSiMuertos / (double)numAtributoSi ) * ( log( ( (double)numAtributoSi / (double)numAtributoSiMuertos) ) / log(2));
	} else {
		entropiaSiMuertos = (double) 0;
	}

	entropiaSi = (double) (entropiaSiVivos + entropiaSiMuertos);

	double entropiaNo; 
	double entropiaNoVivos;
	double entropiaNoMuertos;

	/* Se calcula la entropia de NO  -  E_Atributo(NO) */

	if ( numAtributoNoVivos != 0 ) {
		entropiaNoVivos = ( (double)numAtributoNoVivos / (double)numAtributoNo) * ( log( ( (double)numAtributoNo / (double) numAtributoNoVivos) ) / log(2));
	} else {
		entropiaNoVivos = (double) 0;
	}

	if ( numAtributoNoMuertos != 0 ) {
		entropiaNoMuertos = ( (double)numAtributoNoMuertos / (double)numAtributoNo) * ( log( ( (double) numAtributoNo / (double)numAtributoNoMuertos) ) / log(2));
	} else {
		entropiaNoMuertos = (double) 0;
	}

	entropiaNo = (double) (entropiaNoVivos + entropiaNoMuertos);

	/* Calcula la entropia del atributo  -  E(Atributo) */
	double entropiaAtributo = ( ( (double)numAtributoSi / (double)numFilas) * entropiaSi ) + ( ( (double)numAtributoNo / (double)numFilas) * entropiaNo );

	/* Calcula E(C) */
	double entropiaVivos;
	double entropiaMuertos;
	double entropiaC;

	if ( ( (double)numVivos / (double)numFilas ) != 0){
		entropiaVivos = ( (double)numVivos / (double)numFilas ) * ( log( ( (double)numFilas / (double)numVivos) ) / log(2));
	} else {
		entropiaVivos = (double) 0;
	}	

	if ( ( (double)numMuertos / (double)numFilas) != 0) {
		entropiaMuertos = ( (double)numMuertos / (double)numFilas) * ( log( ( (double)numFilas / (double)numMuertos)) / log(2));
	} else {
		entropiaMuertos = (double) 0;
	}

	entropiaC = (double) (entropiaVivos + entropiaMuertos);


	/* Calcula la Ganancia de Informacion - Gain(Atributo) */
	double gain = (double) (entropiaC - entropiaAtributo);


	/* Ratio de Ganancia  -  GainRatio(A) = Gain(A) / SplitInfo(A) */
	double splitInfoTotal;
	double splitInfo1;
	double splitInfo2;

	if (( (double)numAtributoSi / (double)numFilas) != 0) {
		splitInfo1 = ( (double)numAtributoSi / (double)numFilas) * ( log( ( (double)numFilas / (double)numAtributoSi ) ) / log(2) );	
	} else {
		splitInfo1 = (double) 0;
	}

	if ( ( (double)numAtributoNo / (double)numFilas) != 0) {
		splitInfo2 = ( (double)numAtributoNo / (double)numFilas) * ( log( ( (double)numFilas / (double)numAtributoNo ) ) / log(2) );	
	} else {

		splitInfo2 = (double) 0;
	}

	
	splitInfoTotal = (double) (splitInfo1 + splitInfo2); 

	double gainRatioA = (double) (gain / splitInfoTotal);

	fprintf(output, "Informacion Atributo %d: \n", indexAtributo);
	fprintf(output, "Numero AtributosSI: %d\n", numAtributoSi);
	fprintf(output, "Numero AtributosNO: %d\n", numAtributoNo);
	fprintf(output, "Numero AtributosSIVivos: %d\n", numAtributoSiVivos);
	fprintf(output, "Numero AtributosSIMuertos: %d\n", numAtributoSiMuertos);
	fprintf(output, "Numero AtributosNOVivos: %d\n", numAtributoNoVivos);
	fprintf(output, "Numero AtributosNOMuertos: %d\n", numAtributoNoMuertos);
	fprintf(output, "Numero VIvos; %d\n", numVivos);
	fprintf(output, "Numero Muertos; %d\n", numMuertos);
	fprintf(output, "EntropiaSI: %f\n", entropiaSi);
	fprintf(output, "EntropiaSIVivos: %f\n", entropiaSiVivos);
	fprintf(output, "EntropiaSIMuertos: %f\n", entropiaSiMuertos);
	fprintf(output, "EntropiaNO: %f\n", entropiaNo);
	fprintf(output, "EntropiaNOVivos: %f\n", entropiaNoVivos);
	fprintf(output, "EntropiaNOMuertos: %f\n", entropiaNoMuertos);
	fprintf(output, "Entropia Atributo: %f\n", entropiaAtributo);
	fprintf(output, "Entropia Clase: %f\n", entropiaC);
	fprintf(output, "Gananacia Informacion: %f\n\n", gain);

	heuristica.entropia = entropiaAtributo;
	heuristica.gainInfo = gain;
	heuristica.gainRatio = gainRatioA;

	return heuristica;
}


/** Busca el atributo con mayor ganancia de informacion normalizada */
int elegirAtributo(int numFilas, int numAtributos, float **tabla, FILE *output) {

	infoAtributo arrHeuristica[numAtributos];

	double maxEnt = 0;
	unsigned int a_best = -1;

	for (int i = 0; i < numAtributos; ++i) {
		arrHeuristica[i] = calculoEntropiaCat(numFilas, numAtributos, tabla, i, output);	
		printf("entropia: %f\n", arrHeuristica[i].entropia);
		printf("Gain Info: %f\n", arrHeuristica[i].gainInfo);
		if (arrHeuristica[i].gainInfo > maxEnt) {
			maxEnt = arrHeuristica[i].gainInfo;
			a_best = tabla[0][i];
		}	
	}

	return a_best;
}



/** Lee los datos del dataset y los almacena en una 
  * matriz de NUM_FILAS x NUM_ATRUBITOS + 1 y devuelve dicha matriz */ 
float **readData(unsigned int numFil, unsigned int numAtributos, FILE *output) {

	float **arrMatrix = (float**)malloc( (numFil + 1) * sizeof(float*));

	for (int i = 0; i < numFil + 1; ++i) {
		arrMatrix[i] = (float*)malloc( (numAtributos + 1) * sizeof(float));
	}

	/* En la primera fila almacenamos los atrubutos como numeros 1,..,NumAtributos */
	for (int i = 0; i < numAtributos; ++i) {
		arrMatrix[0][i] = i;
	}

	arrMatrix[0][numAtributos] = 99;

	FILE *dataset;
	if ( (dataset = fopen("datasetTest.csv", "r")) == NULL){
		perror("Fallo al abrir fichero");
		exit(342);
	}

	char *str = (char*)malloc(500*sizeof(char));

	/* Leer primera linea */
	fgets(str, 500, dataset);

	for (int i = 1; i < numFil + 1; ++i) {
		fgets(str, 500, dataset);
		sscanf(str, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", &arrMatrix[i][0], &arrMatrix[i][1], &arrMatrix[i][2], &arrMatrix[i][3], &arrMatrix[i][4], &arrMatrix[i][5], &arrMatrix[i][6], &arrMatrix[i][7], &arrMatrix[i][8], &arrMatrix[i][9], &arrMatrix[i][10]);
	}

	fclose(dataset);

	for (int i = 0; i < numFil + 1; ++i)
	{
		for (int j = 0; j < numAtributos + 1; ++j)
		{
			fprintf(output, "%f, ", arrMatrix[i][j]);
		}
		fprintf(output, "\n");
	}
	fprintf(output, "\n");


	return arrMatrix;
}


filtroInfo filtrarTabla(int numFil, int numAtributos, float **tabla, int atributo, float valorAtributo, FILE *output) {


	float **tablaFiltrada = (float**)malloc( (numFil + 1) * sizeof(float*));

	for (int i = 0; i < numFil + 1; ++i) {
		tablaFiltrada[i] = (float*)malloc( numAtributos * sizeof(float));
	}

	/* Buscamos el indice del atributo */
	unsigned int indexAtributo;
	int indexFil = 1; 
	int indexCol = 0;

	for (int i = 0; i < numAtributos + 1; ++i) {
		if (tabla[0][i] == atributo) {
			indexAtributo = i;
		} else { 
			tablaFiltrada[0][indexCol] = tabla[0][i];
			++indexCol;
		}
	}

	/*fprintf(output, "Index aTRIBUTO: %d \n", indexAtributo );
	fprintf(output, "VAlor: %f\n", valorAtributo);*/

	indexCol = 0;

	for (int i = 1; i < numFil + 1; ++i) {

		/* Hemos encontrado una fila que coincide con el valor del atributo */
		if (tabla[i][indexAtributo] == valorAtributo){
			indexCol = 0;
			for (int j = 0; j < numAtributos + 1; ++j){
				if (j != indexAtributo) {
					tablaFiltrada[indexFil][indexCol] = (float)tabla[i][j];
					++indexCol;
				}
			}
			++indexFil;
		}
	}


	/*fprintf(output, "IndexFil: %d\n", indexFil);
	fprintf(output, "\n filtro SUB-TABLA: \n");
	for (int i = 0; i < indexFil; ++i) {
		for (int j = 0; j < numAtributos; ++j)
		{
			fprintf(output, "%f, ", tablaFiltrada[i][j]);
		}
		fprintf(output, "\n");
	}
	fprintf(output, "\n");*/

	filtroInfo tableInfo;

	tableInfo.tabla = tablaFiltrada;
	tableInfo.numFil = indexFil - 1;

	return tableInfo;
}

nodo* construirArbolDecision(int numFil, int numAtributos, float **tabla, nodo* ptrNodo, FILE *output)
{

	/* No hay datos en la sub-tabla */
	if (numFil == 0) {
		return NULL;
	}

	/* Comprobamos si hemos llegado a una hoja y podemos tomar una decision */
	if ( esHomojenea(numFil, numAtributos, tabla) ) {/* || calcHeuristica(tabla) < UMBRAL_H )*/
		ptrNodo->hoja = true;
		ptrNodo->clase = tabla[1][numAtributos];
		fprintf(output, "Hoja: %d\n", ptrNodo->clase);
		return ptrNodo;
	} else {

		unsigned int atributoExp = elegirAtributo(numFil, numAtributos, tabla, output);

		ptrNodo->atributo = atributoExp;

		/** Para la cantidad de valores que puede tomar el atributo, 
		  * en nuestro caso todos los atrbutos pueden tomar solo dos
		  * valores: SI/NO */
		for (int i = 0; i < 2; ++i){

			int auxNumFil;

			nodo *nuevoNodo = (nodo*)malloc(sizeof(nodo)); 
			nuevoNodo->clase = i;
			ptrNodo->arrHijos[i] = i;
			nuevoNodo->hoja = false;
			nuevoNodo->atributo = atributoExp;
			nuevoNodo->izq = nuevoNodo->der = NULL;

			float **auxTabla = (float**)malloc(numFil * sizeof(float*));

			for (int j = 0; j < numFil; ++j) {
				auxTabla[j] = (float*)malloc( (numAtributos) * sizeof(float));
			}

			fprintf(output, "\nEstado Tabla Principal: \n");
			for (int j = 0; j < numFil + 1; ++j) {
				for (int z = 0; z < numAtributos + 1; ++z)
				{
					fprintf(output, "%f, ", tabla[j][z]);
				}
				fprintf(output, "\n");
			}
			fprintf(output, "\n");


			fprintf(output, "Mejor Atributo: %d\n", atributoExp);

			filtroInfo tableInfo = filtrarTabla(numFil, numAtributos, tabla, atributoExp, i, output);
			
			auxTabla = tableInfo.tabla;
			auxNumFil = tableInfo.numFil;


			fprintf(output, "\nAUX SUB-TABLA: \n");
			for (int j = 0; j < auxNumFil + 1; ++j) {
				for (int z = 0; z < numAtributos; ++z)
				{
					fprintf(output, "%f, ", auxTabla[j][z]);
				}
				fprintf(output, "\n");
			}
			fprintf(output, "\n");

			if ( i == 0  ) {
				fprintf(output, "Izquierda\n");
				ptrNodo->izq = construirArbolDecision(auxNumFil, numAtributos - 1, auxTabla, nuevoNodo, output);
			} else {
				fprintf(output, "derecha\n");
				ptrNodo->der = construirArbolDecision(auxNumFil, numAtributos - 1, auxTabla, nuevoNodo, output);
			}
		}
		
	}
	return ptrNodo;
}




/** Calcula si todas las filas de una sub-tabla perteneces a la misma clase.
  * En ese caso, llegamos al final de la rama y sabamos la decision */
bool esHomojenea(int numFil, int numAtributos, float **tabla) {

	int clase = tabla[1][numAtributos];
	for (int i = 1; i < numFil; ++i)
	{
		if (tabla[i][numAtributos] != clase)
			return false;
	}

	return true;

}


void mostrarPreorden(nodo *raiz, FILE *output) {
	if (raiz) {
        fprintf(output, "Atributo: %d\n", raiz->atributo);
        fprintf(output, "Clase: %d\n", raiz->clase);
        fprintf(output, "Es Hoja: %d\n", raiz->hoja);
        fprintf(output, "\n");
        mostrarPreorden(raiz->izq, output);
        mostrarPreorden(raiz->der, output);
    } else {
        return;
    }
}



