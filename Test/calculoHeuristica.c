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
#include "funciones_v2.h"



double calcularEntropia(double num1, double num2) {

	if ( num1 != 0 ) {
		return ( (double)num1 / (double)num2) * ( log( ( (double)num2 / (double)num1) ) / log(2));
	} else {
		return 0;
	}

}
/**
  * Funcion calcularEntropia
  * Calcula la entropia, ganancia de informacion y ratio de ganancia de un 
  * atributo continuo o discreto.
  * @param numFilas de datos de la tabla
  * @param numero de atributos de la tabla
  * @param tabla que contien todos los datos
  * @param indice del atributo del que se desea calcular la entropia
  * @param umbral de atributo continuo
  * @see infoAtributo
  * @return entropia, ganancia de informacion y ratio de ganancia
   */ 
infoAtributo calcularHeuristica(int numFilas, int numAtributos, float **tabla, int indexAtributo, float umbral, FILE *output)
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

	/** Se recorre la tabla con el fin de obtener los datos 
	  * que nos interesan para el calculo de la heuristica */
	if (umbral != -1) {				/* Atributo continuo */
		for (int i = 1; i < numFilas + 1; ++i) {
			if (tabla[i][indexAtributo] <= umbral) {
				++numAtributoSi;
				if (tabla[i][numAtributos] == 1)
					++numAtributoSiVivos;
				else
					++numAtributoSiMuertos;
			} else {
				++numAtributoNo;
				if (tabla[i][numAtributos] == 0)
					++numAtributoNoVivos;
				else 
					++numAtributoNoMuertos;
			}
		}
	} else { 						/* Atributo categorico */
		for (int i = 1; i < numFilas + 1; ++i) {
			if (tabla[i][indexAtributo] == 1) {
				++numAtributoSi;
				if (tabla[i][numAtributos] == 1)
					++numAtributoSiVivos;
				else
					++numAtributoSiMuertos;
			} else {
				++numAtributoNo;
				if (tabla[i][numAtributos] == 0)
					++numAtributoNoVivos;
				else 
					++numAtributoNoMuertos;
			}
		}
	}

	numVivos = numAtributoSiVivos + numAtributoNoVivos;
	numMuertos = numAtributoSiMuertos + numAtributoNoMuertos;

	/* CALCULO HEURISTICA */

	/* Se calcula la entropia de SI  -  E_Atributo(SI) */
	/*if ( numAtributoSiVivos != 0 ) {
		entropiaSiVivos = ( (double)numAtributoSiVivos / (double)numAtributoSi ) * ( log( ( (double)numAtributoSi / (double)numAtributoSiVivos) ) / log(2));
	} else {
		entropiaSiVivos = (double) 0;
	}*/

	entropiaSiVivos = calcularEntropia(numAtributoSiVivos, numAtributoSi);

	/*if ( numAtributoSiMuertos != 0 ){
		entropiaSiMuertos = ( (double)numAtributoSiMuertos / (double)numAtributoSi ) * ( log( ( (double)numAtributoSi / (double)numAtributoSiMuertos) ) / log(2));
	} else {
		entropiaSiMuertos = (double) 0;
	}*/

	entropiaSiMuertos = calcularEntropia(numAtributoSiMuertos, numAtributoSi);

	entropiaSi = (double) (entropiaSiVivos + entropiaSiMuertos);

	double entropiaNo; 
	double entropiaNoVivos;
	double entropiaNoMuertos;

	/* Se calcula la entropia de NO  -  E_Atributo(NO) */

	/*if ( numAtributoNoVivos != 0 ) {
		entropiaNoVivos = ( (double)numAtributoNoVivos / (double)numAtributoNo) * ( log( ( (double)numAtributoNo / (double) numAtributoNoVivos) ) / log(2));
	} else {
		entropiaNoVivos = (double) 0;
	}*/

	entropiaNoVivos = calcularEntropia(numAtributoNoVivos, numAtributoNo);

	/*if ( numAtributoNoMuertos != 0 ) {
		entropiaNoMuertos = ( (double)numAtributoNoMuertos / (double)numAtributoNo) * ( log( ( (double) numAtributoNo / (double)numAtributoNoMuertos) ) / log(2));
	} else {
		entropiaNoMuertos = (double) 0;
	}*/

	entropiaNoMuertos = calcularEntropia(numAtributoNoMuertos, numAtributoNo);

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

	entropiaVivos = calcularEntropia(numVivos, numFilas);


	if ( ( (double)numMuertos / (double)numFilas) != 0) {
		entropiaMuertos = ( (double)numMuertos / (double)numFilas) * ( log( ( (double)numFilas / (double)numMuertos)) / log(2));
	} else {
		entropiaMuertos = (double) 0;
	}

	entropiaMuertos = calcularEntropia(numMuertos, numFilas);

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

	/*fprintf(output, "Informacion Atributo %d: \n", indexAtributo);
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
	fprintf(output, "Gananacia Informacion: %f\n\n", gain);*/

	heuristica.entropia = entropiaAtributo;
	heuristica.gainInfo = gain;
	heuristica.gainRatio = gainRatioA;

	return heuristica;
}


/** Busca el atributo con mayor ganancia de informacion normalizada */
int elegirAtributo(int numFilas, int numAtributos, float **tabla, float umbral1, float umbral2, FILE *output) {

	infoAtributo arrHeuristica[numAtributos];

	double maxEnt = -1;
	unsigned int a_best = -1;

	for (int i = 0; i < numAtributos; ++i) {

		/* Si es un artibuto continuo, le pasamos el umbral del atributo, si no, pasamos -1 */
		if (tabla[0][i] == 8) {
			arrHeuristica[i] = calcularEntropia(numFilas, numAtributos, tabla, i, umbral1, output);
		} else if (tabla[0][i] == 9) {
			arrHeuristica[i] = calcularEntropia(numFilas, numAtributos, tabla, i, umbral2, output);
		} else {	
			arrHeuristica[i] = calcularEntropia(numFilas, numAtributos, tabla, i, -1, output);	
		}

		/* Se escoge el atributo con mayor ganancia de informacion */
		if (arrHeuristica[i].gainInfo > maxEnt) {
			maxEnt = arrHeuristica[i].gainInfo;
			a_best = tabla[0][i];
		}	
	}

	/** Si la ganancia de informacion esta por debajo de umbral de ganancia 
	  * establecido por nosotros, se devuelve -1 */  

	/*for (int i = 0; i < numAtributos; ++i)
	{
		fprintf(output, "\n Heuristica Atributo: %f\n", tabla[0][i]);
		fprintf(output, "Heuristica: %f\n", arrHeuristica[i].entropia);
		fprintf(output, "Heuristica: %f\n", arrHeuristica[i].gainInfo);
	}

	fprintf(output, "\nElegir Atributo: %d\n", a_best);
	fprintf(output, "Entropia Atributo: %f\n", maxEnt);*/


	return (maxEnt < UMBRAL_GAIN) ? -1 : a_best;
}



int main(int argc, char const *argv[])
{


	system("clear");

	/* Declaracion de una matriz mediante punteros */
	float **tablaTrain = (float**)malloc( (NUM_FILAS_TRAIN + 1) * sizeof(float*));

	for (int i = 0; i < NUM_FILAS_TRAIN + 1; ++i) {
		tablaTrain[i] = (float*)malloc( (NUM_ATRIBUTOS + 1) * sizeof(float));
	}


	if ( (trainData = fopen("trainData2.dat", "r")) == NULL ) {
		printf("Error al abrir fichero: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	FILE *output = fopen("out.txt", "w");
	
	tablaTrain = readData();

	elegirAtributo(10, 10, tablaTrain, output);


	return 0;
}


/** Lee los datos del dataset y los almacena en una 
  * matriz de NUM_FILAS x NUM_ATRUBITOS + 1 y devuelve dicha matriz */ 
float **readData(FILE *dataset, unsigned int numFil, FILE *output) {

	float **arrMatrix = (float**)malloc( (numFil + 1) * sizeof(float*));

	for (int i = 0; i < numFil + 1; ++i) {
		arrMatrix[i] = (float*)malloc( (NUM_ATRIBUTOS + 1) * sizeof(float));
	}

	/* En la primera fila almacenamos los atrubutos como numeros 1,..,NumAtributos */
	for (int i = 0; i < NUM_ATRIBUTOS; ++i) {
		arrMatrix[0][i] = i;
	}

	arrMatrix[0][NUM_ATRIBUTOS] = 99;

	char *str = (char*)malloc(500 * sizeof(char));

	/* Leer primera linea */
	fgets(str, 500, dataset);

	for (int i = 1; i < numFil + 1; ++i) {
		fgets(str, 500, dataset);
		sscanf(str, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", &arrMatrix[i][0], &arrMatrix[i][1], &arrMatrix[i][2], &arrMatrix[i][3], &arrMatrix[i][4], &arrMatrix[i][5], &arrMatrix[i][6], &arrMatrix[i][7], &arrMatrix[i][8], &arrMatrix[i][9], &arrMatrix[i][10]);
	}

	//fprintf(output, "READDATA: \n");

	/*for (int i = 0; i < numFil + 1; ++i)
	{
		for (int j = 0; j < NUM_ATRIBUTOS + 1; ++j)
		{
			fprintf(output, "%f, ", arrMatrix[i][j]);
		}
		fprintf(output, "\n");
	}
	fprintf(output, "\n");*/


	return arrMatrix;
}