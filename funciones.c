#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "funciones.h"


/**
  * Calcula la entropia y la ganancia de informacion y la de un atributo categorico 
  * con una clase binaria
  */ 
infoAtribute calculoEntropiaCat(int numFilas, int numAtributos, float tabla[][numAtributos], int indexAtributo)
{

	/* DECLARACION DE VARIABLES */

	infoAtribute heuristica;					/* Estructura para almacenar los parametros de la heuristica */

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
	for (int i = 0; i < numFilas; ++i) {
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
		++i;
	}

	numVivos = numAtributoSiVivos + numAtributoNoVivos;
	numMuertos = numAtributoSiMuertos + numAtributoNoMuertos;

	/* CALCULO HEURISTICA */

	/* Se calcula la entropia de SI  -  E_Atributo(SI) */
	entropiaSiVivos = (numAtributoSiVivos / numAtributoSi) * ( log(numAtributoSiVivos / numAtributoSi) / log(2));

	entropiaSiMuertos = (numAtributoSiMuertos / numAtributoSi) * ( log(numAtributoSiMuertos / numAtributoSi) / log(2));

	entropiaSi = entropiaSiVivos + entropiaSiMuertos;

	double entropiaNo; 
	double entropiaNoVivos;
	double entropiaNoMuertos;

	/* Se calcula la entropia de NO  -  E_Atributo(NO) */
	entropiaNoVivos = (numAtributoNoVivos / numAtributoNo) * ( log(numAtributoNoVivos / numAtributoNo) / log(2));

	entropiaNoMuertos = (numAtributoNoMuertos / numAtributoNo) * ( log(numAtributoNoMuertos / numAtributoNo) / log(2));

	entropiaNo = entropiaNoVivos + entropiaNoMuertos;

	/* Calcula la entropia del atributo  -  E(Atributo) */
	double entropiaAtributo = ( (numAtributoSi / numFilas) * entropiaSi ) + ( (numAtributoNo / numFilas) * entropiaNo );

	/* Calcula E(C) */
	double entropiaVivos;
	double entropiaMuertos;
	double entropiaC;

	entropiaVivos = (numVivos / numFilas) * ( log(numVivos / numFilas) / log(2));
	entropiaMuertos = (numMuertos / numFilas) * ( log(numMuertos / numFilas) / log(2));
	entropiaC = entropiaMuertos + entropiaMuertos;


	/* Calcula la Ganancia de Informacion - Gain(Atributo) */
	double gain = entropiaC - entropiaAtributo;


	/* Ratio de Ganancia  -  GainRatio(A) = Gain(A) / SplitInfo(A) */
	double splitInfoTotal;
	double splitInfo1;
	double splitInfo2;

	splitInfo1 = (numAtributoSi / numFilas) * ( log(numAtributoSi / numFilas) / log(2) );
	splitInfo2 = (numAtributoNo / numFilas) * ( log(numAtributoNo / numFilas) / log(2) );
	splitInfoTotal = splitInfo1 + splitInfo2;

	double gainRatioA = (gain / splitInfoTotal);

	heuristica.entropia = entropiaAtributoM
	heuristica.gainInfo = gain;
	heuristica.gainRatio = gainRatioA;

	return heuristica;
}


/** Se encarga de elegir el mejor atributo (mejor heuristica) y devuelve su indice */
int elegirAtributo(int numFilas, int numAtributos, float tabla[][numAtributos], int indexAtributo) {


	for (int i = 0; i < numAtributos; ++i) {
		calculoEntropiaCat(numFilas, numAtributos, tabla[][numAtributos], indexAtributo);	



}




/* Implementacion QuickSort en C */
  
// A utility function to swap two elements  
void swap(int* a, int* b)  
{  
    int t = *a;  
    *a = *b;  
    *b = t;  
}  
  
/* This function takes last element as pivot, places  
the pivot element at its correct position in sorted  
array, and places all smaller (smaller than pivot)  
to left of pivot and all greater elements to right  
of pivot */
int partition (int arr[], int low, int high)  
{  
    int pivot = arr[high]; // pivot  
    int i = (low - 1); // Index of smaller element  
  
    for (int j = low; j <= high - 1; j++)  
    {  
        // If current element is smaller than the pivot  
        if (arr[j] < pivot)  
        {  
            i++; // increment index of smaller element  
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  
  
/* The main function that implements QuickSort  
arr[] --> Array to be sorted,  
low --> Starting index,  
high --> Ending index */
void quickSort(int arr[], int low, int high)  
{  
    if (low < high)  
    {  
        /* pi is partitioning index, arr[p] is now  
        at right place */
        int pi = partition(arr, low, high);  
  
        // Separately sort elements before  
        // partition and after partition  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
}  


/* Calculo humbral atributo continuo */
/**
  * input: array[2][N] que contiene en la priemra fila los valores del atributo
  * y en la segunda fila la clase a la que pertence: Vivo / Muerto */
double discretizacion(unsigned int N ,arr[][N]) 
{

	/* 1. Ordenar arrray ascendentemente mediante el valor del atributo */
	quickSort(arr, 0, N);

 	/* 2. Calcular la entropía para cada pareja de valores en los que la clase cambie */
	indexElegidos[2][N];			/* 1. Fila--> Indice, 2. Fila-->Entropia */
	unsigned int index = 0;		/* Indice del array de indices de los elegidos */

	unsigned int clase = arr[1][0];

	for (int i = 0; i < N; ++i) {
		if ( arr[1][i] != clase ){
			indexElegidos[0][index] = i;
			++index;
		}
	}

	/* 3. Elegir como umbral la media del par de valores que minimice la entropía */
	unsigned int numAtributosMenores;
	unsigned int numAtributosMayores;

	unsigned int numSiMenores;
	unsigned int numNoMenores; 
	unsigned int numSiMayores;
	unsigned int numNoMayores;

	for (int i = 0; i < index; ++i)
	{

		numAtributosMenores = indexElegidos[0][i];
		numAtributosMayores = N - indexElegidos[0][i];

		for (int j = 0; j < numAtributosMenores; ++j){
			if (arr[1][j] == 1)
				++numSiMenores;
		}

		numNoMenores = numAtributosMenores - numSiMenores;

		for (int j = numAtributosMenores + 1; j < N; ++j){
			if (arr[1][j] == 1)
				++numSiMayores;
		}

		numNoMayores = numAtributosMayores - numSiMayores;

		
		double entropiaMenorSi;
		double entropiaMenorNo;
		double entropiaMayorSi;
		double entropiaMayorNo;
		double entropia1;
		double entropia2;


		entropiaMenorSi = ( (numSiMenores / numAtributosMenores) * (- log(numSiMenores / numAtributosMenores) / log(2)) ) 
		entropiaMenorNo = ( (numNoMenores / numAtributosMenores) * (- log(numNoMenores / numAtributosMenores) / log(2)) )

		entropia1 = ( (numSiMenores / N) * entropiaMenorSi) + (numNoMenores / N) * entropiaMenorNo;


		entropiaMayorSi = ( (numSiMayores / numAtributosMayores) * (- log(numSiMayores / numAtributosMayores) / log(2)) ) 
		entropiaMayorNo = ( (numNoMenores / numAtributosMayores) * (- log(numNoMenores / numAtributosMayores) / log(2)) )

		entropia2 = ( (numSiMayores / N) * entropiaMayorSi) + (numNoMayores / N) * entropiaMayorNo;

		indexElegidos[1][i] = entropia1 + entropia2;

	}



	/* Buscamos el atributo con menor entropia */
	unsigned int indexMinEntropia;
	unsigned int minEntropiaValue;
	int minEntropia = 1;

	for (int i = 0; i < index; ++i) {
		if ( indexElegidos[1][i] < minEntropia ) {
			minEntropia = indexElegidos[1][i];
			indexMinEntropia = i;
		}
	}

	minEntropiaValue = arr[0][ indexElegidos[0][indexMinEntropia] ];
	double umbral1 = minEntropiaValue; /* Esto esta puesto por comprension */

	/* Buscamos atributo de otra clase por la izquierda */	

	double umbral2;

	clase = arr[1][ indexElegidos[0][indexMinEntropia] ];
	for (int i = indexElegidos[0][indexMinEntropia]; i < 0 ; --i) {
		if (arr[1][i] != clase)
			num = arr[0][i];
	}

	/* Calculamos el humbral */
	double umbral = (umbral1 + umbral2) / 2;

	return humbral;

}


/** Contsruye un arbol binario de decision */


nodo* construirArbolDecision(float tabla[][], nodo* ptrNodo)
{
	if (tablaVacia(tabla)) {
		return NULL;
	}

	if (esHomojenea(table) || calcHeuristica(tabla) < UMBRAL_H ) {
		ptrNodo->hoja = true;
		nodePtr->clase = table[1][NUM_ATRIBUTOS];
		return ptrNodo;
	} else {

		unsigned int atributoExp = elegirAtributoExp(tabla);

		ptrNodo->atributo = atributoExp;

		/** Para la cantidad de valores que puede tomar el atributo, 
		  * en nuestro caso todos los atrbutos pueden tomar solo dos
		  * valores: SI/NO */
		for (int i = 0; i < 2; ++i){
			
			nodo *nuevoNodo = (nodo*)malloc(sizeof(nodo)); 
			nuevoNodo->clase = i;
			nuevoNodo->arrHijos[i] = i;
			nuevoNodo->hoja = false;
			nuevoNodo->atributo = atributoExp;
			
			auxTabla = pruneTable(tabla, atributoExp, i);
			if ( i == 0) {
				nuevoNodo->izq = construirArbolDecision(auxTabla, nuevoNodo);
			} else {
				nuevoNodo->der = construirArbolDecision(auxTabla, nuevoNodo);
			}
		}
		
	}
	return nodo;
}


/** Funcion filtrarTabla: 
  * Esta funcion creara una nueva tabla auxiliar donde se eliminaran todas aquellas filas
  * que contenga el valor que se le pase a la funcion en el atribute que se le pase */


matrix** filtrarTabla(int numFilas, int numAtributos, tabla[][numAtributos], indexAtributo, valorAtributo) {


	float tablaFiltrada[][numAtributos - 1];	/* Nueva tabla ya filtrada */
	unsigned int indexFil = 0;					/* Indice de filas para recorrer la nueva tabla filtrada */ 
	unsigned int indexCol = 0;					/* Indice de columnas para recorrer la nueva tabla filtrada */ 

	for (int i = 0; i < numFilas; ++i) {

		/* Hemos encontrado una fila que coincide con el valor del atributo */
		if (tabla[i][indexAtributo] == valorAtributo){
			indexFil = 0;
			for (int j = 0; j < numAtributos -1; ++j){
				if (j != indexAtributo) {
					tablaFiltrada[indexFil][indexCol] = tabla[i][j];
				}
				++indexCol;
			}
			++indexFil;
		}
	}

	return tablaFiltrada;
}


