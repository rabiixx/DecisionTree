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

/* Librerias estandar de C */
#include "funciones_v2.h"


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


/** 
  * funcion elegirAtributo 
  * Busca el atributo con mayor ganancia de informacion dentro del conjunto de datos.
  * Si la mayor ganancia de informacion no supera el umbral establecido se devuelve -1.
  * @param numFil numero de filas del sub-conjunto de datos (sub-tabla)
  * @param numAtributos numero de atributos del sub-conjunto de datos (sub-tabla)
  * @param tabla conjunto de datos 
  * @param umbral1 umbral del primero atributo continuo (numero de muertes)
  * @param umbral2 umbral del segundo atributo continuo (popularidad)
  * @return el atributo con mayor ganancia de informacion 
	 */
int elegirAtributo(int numFilas, int numAtributos, float **tabla, float umbral1, float umbral2, FILE *output) {

	infoAtributo arrHeuristica[numAtributos];

	double maxEnt = -1;				/* Contiene el maximo de ganancia de informacion */
	unsigned int a_best = -1;		/* Contiene el atributo con mayor ganancia de informacion */


	/* Se calcula la ganancia de informacion de todos los atributos del conjunto */
	for (int i = 0; i < numAtributos; ++i) {

		/* Si es un artibuto continuo, le pasamos el umbral del atributo, si no, pasamos -1 */
		if (tabla[0][i] == 8) {
			arrHeuristica[i] = calcularHeuristica(numFilas, numAtributos, tabla, i, umbral1, output);
		} else if (tabla[0][i] == 9) {
			arrHeuristica[i] = calcularHeuristica(numFilas, numAtributos, tabla, i, umbral2, output);
		} else {	
			arrHeuristica[i] = calcularHeuristica(numFilas, numAtributos, tabla, i, -1, output);	
		}

		/* Se busca el atributo con mayor ganancia de informacion */
		if (arrHeuristica[i].gainInfo > maxEnt) {
			maxEnt = arrHeuristica[i].gainInfo;
			a_best = tabla[0][i];
		}	
	}

 	/*for (int i = 0; i < numAtributos; ++i)
	{
		fprintf(output, "\n Heuristica Atributo: %f\n", tabla[0][i]);
		fprintf(output, "Heuristica: %f\n", arrHeuristica[i].entropia);
		fprintf(output, "Heuristica: %f\n", arrHeuristica[i].gainInfo);
	}

	fprintf(output, "\nElegir Atributo: %d\n", a_best);
	fprintf(output, "Entropia Atributo: %f\n", maxEnt);*/

	/** Si la ganancia de informacion esta por debajo de umbral de ganancia 
	  * establecido por nosotros, se devuelve -1 */ 
	return (maxEnt < UMBRAL_GAIN) ? -1 : a_best;
}


/** Calcula la entropia */
double calcularEntropia(double num1, double num2) {

	if ( num1 != 0 ) {
		return ( num1 / num2 ) * ( log( num2 / num1 ) / log(2) );
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
	double entropiaSiVivos = calcularEntropia(numAtributoSiVivos, numAtributoSi);
	double entropiaSiMuertos = calcularEntropia(numAtributoSiMuertos, numAtributoSi);
	double entropiaSi = entropiaSiVivos + entropiaSiMuertos;

	/* Se calcula la entropia de NO  -  E_Atributo(NO) */
	double entropiaNoVivos = calcularEntropia(numAtributoNoVivos, numAtributoNo);
	double entropiaNoMuertos = calcularEntropia(numAtributoNoMuertos, numAtributoNo);
	double entropiaNo = entropiaNoVivos + entropiaNoMuertos;

	/* Calcula la entropia del atributo  -  E(Atributo) */
	double entropiaAtributo = ( ( (double)numAtributoSi / (double)numFilas) * entropiaSi ) + ( ( (double)numAtributoNo / (double)numFilas) * entropiaNo );

	/* Calcula E(C) */
	double entropiaVivos = calcularEntropia(numVivos, numFilas);
	double entropiaMuertos = calcularEntropia(numMuertos, numFilas);
	double entropiaC = (double) (entropiaVivos + entropiaMuertos);

	/* Calcula la Ganancia de Informacion - Gain(Atributo) */
	double gain = (double) (entropiaC - entropiaAtributo);

	/* Ratio de Ganancia  -  GainRatio(A) = Gain(A) / SplitInfo(A) */
	double splitInfo1 = calcularEntropia(numAtributoSi, numFilas);
	double splitInfo2 = calcularEntropia(numAtributoNo, numFilas);
	double splitInfoTotal = splitInfo1 + splitInfo2;

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
	fprintf(output, "Gain Ratio: %f\n", gainRatioA);

	heuristica.entropia = entropiaAtributo;
	heuristica.gainInfo = gain;
	heuristica.gainRatio = gainRatioA;

	return heuristica;
}


/** 
  * funcion filtrarTabla 
  *	Se eliminan aquellas filas que sean menores / mayores que el umbral recibido como paramentro.
  * Si i = 0, se eliminan todas aquellas filas que sean menores que el umbral del atributo continuo
  * Si i = 1, se eliminan todas aquellas filas que sean mayores que el umbral del atributo continuo 
  * @param numFil numero de filas del sub-conjunto de datos (sub-tabla)
  * @param numAtributos numero de atributos del sub-conjunto de datos (sub-tabla)
  * @param tabla conjunto de datos 
  * @param atributo a filtrar (eliminar)
  * @param valor del atributo a eliminar 
  * @param umbral si el atributo es continuo se le pasa el umbral para poder filtrar
  * @return la nueva tabla filtrada y el numero de filas que contiene
  */
filtroInfo filtrarTablaCont(int numFil, int numAtributos, float **tabla, int atributo, float valorAtributo, float umbral, FILE *output) {
	
	/*fprintf(output, "Filtrar Atributo: %d", atributo );

	fprintf(output, "Umbral de filtro: %f \n", umbral);


	fprintf(output, "\n Tabla antes de filtrar cont: \n");
	for (int i = 0; i < numFil; ++i) {
		for (int j = 0; j < numAtributos + 1; ++j)
		{
			fprintf(output, "%f, ", tabla[i][j]);
		}
		fprintf(output, "\n");
	}
	fprintf(output, "\n");*/


	/* Creamos matriz auxiliar donde se guarda el sub-conjunto de datos */
	float **tablaFiltrada = (float**)malloc( (numFil + 1) * sizeof(float*));

	for (int i = 0; i < numFil + 1; ++i) {
		tablaFiltrada[i] = (float*)malloc( numAtributos * sizeof(float));
	}

	/* Buscamos el indice del atributo continuo */
	unsigned int indexAtributo;
	int indexFil = 1; 
	int indexCol = 0;

	for (int i = 0; i < numAtributos; ++i) {
	
		if (tabla[0][i] == atributo)
			indexAtributo = i;

		tablaFiltrada[0][i] = tabla[0][i];
	}

	/* Se eliminan aquellas filas cuyo valor del atributo sea menor que umbral del atributo */
	if (valorAtributo == 0){
		for (int i = 1; i < numFil + 1; ++i) {
			if (tabla[i][indexAtributo] <= umbral){
				for (int j = 0; j < numAtributos + 1; ++j) {
					tablaFiltrada[indexFil][j] = (float) tabla[i][j];
				}
				++indexFil;
			}
		}

	/* Se eliminan aquellas filas cuyo valor del atributo sea mayor que umbral del atributo */
	} else if (valorAtributo == 1) {
		for (int i = 1; i < numFil + 1; ++i) {
			if (tabla[i][indexAtributo] > umbral){
				for (int j = 0; j < numAtributos + 1; ++j) {
					tablaFiltrada[indexFil][j] = (float) tabla[i][j];
				}
				++indexFil;
			}
		}
	}


	/*fprintf(output, "\n Tabla despues de filtrar cont: \n");
	for (int i = 0; i < indexFil; ++i) {
		for (int j = 0; j < numAtributos + 1; ++j)
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

/** 
  * Funcion filtrarTabla 
  * Elimina todas aquellas filas cuyo valor del atributo discreto no coincida con el
  * valor pasado como parametro. 
  * Elimna la columna completa del atributo 
  * @param numFil numero de filas del sub-conjunto de datos (sub-tabla)
  * @param numAtributos numero de atributos del sub-conjunto de datos (sub-tabla)
  * @param tabla conjunto de datos 
  * @param atributo a filtrar (eliminar)
  * @param valor del atributo a eliminar 
  * @param umbral si el atributo es continuo se le pasa el umbral para poder filtrar
  * @return la nueva tabla filtrada y el numero de filas que contiene
  */
filtroInfo filtrarTabla(int numFil, int numAtributos, float **tabla, int atributo, float valorAtributo, FILE *output) {


	/*fprintf(output, "Filtrar Atributo: %d", atributo );

	fprintf(output, "\n filtrar tabla 1: \n");
	for (int i = 0; i < numFil + 1; ++i) {
		for (int j = 0; j < numAtributos + 1; ++j)
		{
			fprintf(output, "%f, ", tabla[i][j]);
		}
		fprintf(output, "\n");
	}
	fprintf(output, "\n");*/

	/* Creamos matriz auxiliar donde se guarda el sub-conjunto de datos */
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

	/** Se añaden a la nueva matriz todas aquellas filas cuyo valor coincida con el valor del atributo pasado
	  * como parametro */
	for (int i = 1; i < numFil + 1; ++i) {

		/* Hemos encontrado una fila que coincide con el valor del atributo */
		if (tabla[i][indexAtributo] == valorAtributo) {
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


	/*fprintf(output, "\n filtrar Tabla 2: \n");
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

/**
  * funcion recursiva construirArbol 
  * @param numFil numero de filas del conjunto de datos (sub-tabla)
  * @param numAtributos numero de atributos del conjunto (sub-tabla)
  * @param tabla conjunto de datos
  * @param ptrNodo nodo del arbol en el que nos encontramos
  * @return NULL conjunto vacio
  * @return ptrNodo si hemos llegado a tomar una decision (es hoja)
  */
nodo* construirArbolDecision(int numFil, int numAtributos, float **tabla, nodo* ptrNodo, FILE *output)
{

	/* La sub-tabla esta vacia (conjunto de datos vacio) */
	if ( numFil == 0 ) {
		return NULL;
	}

	/** Si en el conjunto de datos son todos de la misma clase, se pone el nodo como 
	 * hoja y se elige la clase */
	if ( esHomojenea(numFil, numAtributos, tabla) ) {
		
		ptrNodo->hoja = true;
		ptrNodo->clase = tabla[1][numAtributos];
		fprintf(output, "Hoja: %d\n", ptrNodo->clase);
		return ptrNodo;
	
	} else {

		/* Calculamos los umbrales del los atributos Muertes y Popularidad respectivamente */
		float umbral1 = elegirUmbral(numFil, numAtributos, tabla, 8, output);
		float umbral2 = elegirUmbral(numFil, numAtributos, tabla, 9, output);

		/*printf("Umbral Muertes: %f\n", umbral1);
		printf("Umbral Popularidad: %f\n", umbral2);*/
		

		/* Calculamos cual es el atributo con mayor ganancia de informacion */
		unsigned int atributoExp = elegirAtributo(numFil, numAtributos, tabla, umbral1, umbral2, output);
	

		/** Si el atributo con mayor ganancia de informaciuon esta por debajo del
		  * umbral de ganancia, el nodo se pone como hoja y se elige la clase
		  * mas frecuente como decision */
		if (atributoExp == -1) {
			ptrNodo->hoja = true;
			ptrNodo->clase = claseMasFrecuente(numFil, numAtributos, tabla);
			return ptrNodo;
		}


		//fprintf(output, "Atributo escogido: %d\n", atributoExp);


		/** Si el atributo escogido es continuo guardamos el umbral 
		  * para luego en la fase de testeo sabes en que rama se 
		  * debe buscar */
		if ( atributoExp == 8 ) {
			ptrNodo->umbralA = umbral1;
		} else if (atributoExp == 9 ) {
			ptrNodo->umbralA = umbral2;
		} else {
			ptrNodo->umbralA = (float) -1;
		}

		ptrNodo->atributo = atributoExp;

		/** Para la cantidad de valores que puede tomar el atributo, 
		  * en nuestro caso todos los atrbutos pueden tomar solo dos
		  * valores: SI/NO */
		for (int i = 0; i < 2; ++i) {

			int auxNumFil;		/* Nuevo numero de filas del conjunto despues de filtrar */

			nodo *nuevoNodo = (nodo*)malloc(sizeof(nodo)); 		/* Creamos un nuevo nodo */
			nuevoNodo->clase = i;								/* Asignamos la clase del nuevo nodo 0/1 */
			ptrNodo->arrHijos[i] = i;						
			nuevoNodo->hoja = false;
			nuevoNodo->atributo = atributoExp;
			//nuevoNodo->izq = nuevoNodo->der = NULL;

		
			/* Nueva tabla auxiliar que almacenara el conjunto de datos filtrado */
			float **auxTabla = (float**)malloc(numFil * sizeof(float*));

			for (int j = 0; j < numFil; ++j) {
				auxTabla[j] = (float*)malloc( (numAtributos) * sizeof(float));
			}

			/*fprintf(output, "\nEstado Tabla Principal: \n");
			for (int j = 0; j < numFil + 1; ++j) {
				for (int z = 0; z < numAtributos + 1; ++z)
				{
					fprintf(output, "%f, ", tabla[j][z]);
				}
				fprintf(output, "\n");
			}
			fprintf(output, "\n");*/


			/*fprintf(output, "Mejor Atributo: %d\n", atributoExp);
			fprintf(output, "Umbral1: %f", umbral1 );
			fprintf(output, "Umbral2: %f", umbral2 );*/

			
			/* Si el atributo escogido no es continuo, eliminamos el atributo de la tabla */
			if ( (atributoExp != 8) && (atributoExp != 9) ) {
				
				/* Filtramos la nueva tabla */
				filtroInfo tableInfo = filtrarTabla(numFil, numAtributos, tabla, atributoExp, i, output);
				auxTabla = tableInfo.tabla;
				auxNumFil = tableInfo.numFil;
				
				if ( i == 0 ) {
					ptrNodo->izq = construirArbolDecision(auxNumFil, numAtributos - 1, auxTabla, nuevoNodo, output);
				} else {
					ptrNodo->der = construirArbolDecision(auxNumFil, numAtributos - 1, auxTabla, nuevoNodo, output);
				}

			/** Si el atributo escogido es continuo, solamente eliminamos aquellas filas que sean
			  * menores / mayores que el umbral del atributo, pero no eliminamos el atributo de la 
			  * tabla puesto que puede volver a ser utilizado  */
			} else {

				filtroInfo tableInfo;

				if ( atributoExp == 8 )
					tableInfo = filtrarTablaCont(numFil, numAtributos, tabla, atributoExp, i, umbral1, output);
				else if ( atributoExp == 9 )
					tableInfo = filtrarTablaCont(numFil, numAtributos, tabla, atributoExp, i, umbral2, output);
				
				auxTabla = tableInfo.tabla;
				auxNumFil = tableInfo.numFil;

				if ( i == 0 ) {
					ptrNodo->izq = construirArbolDecision(auxNumFil, numAtributos, auxTabla, nuevoNodo, output);
				} else {
					ptrNodo->der = construirArbolDecision(auxNumFil, numAtributos, auxTabla, nuevoNodo, output);
				}
			}
		}
		
	}
	return ptrNodo;
}




/** 
  * Funcion esHomojenea
  * Comprueba si todas las filas de una sub-tabla perteneces a la misma clase.
  * @param numFil numero de filas del conjunto 
  * @param numAtributos numero de atributos del conjunto
  * @param tabla conjunto de datos
  * @return true si todos los datos pertenecen a la misma clase, si no, false.
  */
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
  * Funcion claseMasFrecuente 

Busca la clase mas frecuente dentro de una tabla de datos y la devuelve */
int claseMasFrecuente(int numFil, int numAtributos, float **tabla) {

	const int claseVivo = 1;
	const int claseMuerto = 0;

	int contClaseVivo = 0;
	int contClaseMuerto = 0;

	for (int i = 1; i < numFil + 1; ++i) {
		if (tabla[i][numAtributos] == claseVivo)
			++contClaseVivo;
		else
			++contClaseMuerto;
	}

	return (contClaseVivo >= contClaseMuerto) ? claseVivo : claseMuerto;

}


/* Function to print level 
order traversal a tree*/
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



float elegirUmbral(int numFil, int numAtributos, float **tabla, float atributo, FILE *output) {


	float arr[2][numFil];		/* 1.Fila: valor atributo, 2.Fila: Clase */
	unsigned int indexAtributo;

	/* Buscamos el indice del atributo */
	int i;
	for (i = 0; i < numAtributos; ++i) {
		if (tabla[0][i] == atributo) {
			indexAtributo = i;
			break;
		}
	}

	if (i == numAtributos) {
		return (float) -1;
	}

	//fprintf(output, "IndexAtributo: %d\n", indexAtributo);

	/* Recorremos la tabla y almacenamos los valores del atributo en una nueva tabla*/
	for (i = 1; i < numFil + 1; ++i) {
		arr[0][i - 1] = tabla[i][indexAtributo];
		arr[1][i - 1] = tabla[i][numAtributos];
	}


	/*fprintf(output, "discretizacion 1: \n");
	for (int i = 0; i < numFil; ++i)
	{
		fprintf(output, "%f, ", arr[0][i]);
	}
	fprintf(output, "\n\ndiscretizacion 2: \n");
	for (int i = 0; i < numFil; ++i)
	{
		fprintf(output, "%f, ", arr[1][i]);
	}
	fprintf(output, "\n\n");*/

	/* Ordenamos el arr y llamamos a la funcion de discretizacion */
	quickSort(numFil, arr, 0, numFil - 1);

	/*fprintf(output, "discretizacion 1: \n");
	for (int i = 0; i < numFil; ++i)
	{
		fprintf(output, "%f, ", arr[0][i]);
	}
	fprintf(output, "\n\ndiscretizacion 2: \n");
	for (int i = 0; i < numFil; ++i)
	{
		fprintf(output, "%f, ", arr[1][i]);
	}
	fprintf(output, "\n\n");*/

	
	return discretizacion(numFil, arr, output);

}


void swap(float *a, float *b)  
{  
    float t = *a;  
    *a = *b;  
    *b = t;  
}  
  
/* This function takes last element as pivot, places  
the pivot element at its correct position in sorted  
array, and places all smaller (smaller than pivot)  
to left of pivot and all greater elements to right  
of pivot */
int partition (int numCol, float arr[][numCol], int low, int high)  
{  
    float pivot = arr[0][high]; // pivot  
    int i = (low - 1); // Index of smaller element  
  
    for (int j = low; j <= high - 1; j++)  
    {  
        // If current element is smaller than the pivot  
        if (arr[0][j] < pivot)  
        {  
            i++; // increment index of smaller element  
            swap(&arr[0][i], &arr[0][j]);
            swap(&arr[1][i], &arr[1][j]);  
  
        }  
    }  
    swap(&arr[0][i + 1], &arr[0][high]);
    swap(&arr[1][i + 1], &arr[1][high]);  
    return (i + 1);  
}  
  
/* The main function that implements QuickSort  
arr[] --> Array to be sorted,  
low --> Starting index,  
high --> Ending index */
void quickSort(int numCol, float arr[][numCol], int low, int high)  
{  
    if (low < high)  
    {  
        /* pi is partitioning index, arr[p] is now  
        at right place */
        int pi = partition(numCol, arr, low, high);  
  
        // Separately sort elements before  
        // partition and after partition  
        quickSort(numCol, arr, low, pi - 1);  
        quickSort(numCol, arr, pi + 1, high);  
    }  
}

/* Calculo humbral atributo continuo */
/**
  * input: array[2][N] que contiene en la priemra fila los valores del atributo
  * y en la segunda fila la clase a la que pertence: Vivo / Muerto */
float discretizacion(int numCol, float arr[][numCol], FILE *output) 
{


	/*fprintf(output, "discretizacion 1: \n");
	for (int i = 0; i < numCol; ++i)
	{
		fprintf(output, "%f, ", arr[0][i]);
	}
	fprintf(output, "\n\ndiscretizacion 2: \n");
	for (int i = 0; i < numCol; ++i)
	{
		fprintf(output, "%f, ", arr[1][i]);
	}
	fprintf(output, "\n\n");*/


	/* Numero de columnas de la matriz */
	// size_t N = ( sizeof(arr[0]) / sizeof(arr[0][0]) );

 	/* 2. Calcular la entropía para cada pareja de valores en los que la clase cambie */
	float indexElegidos[2][numCol];			/* 1. Fila--> Indice, 2. Fila-->Entropia */
	unsigned int index = 0;		/* Indice del array de indices de los elegidos */

	float clase = arr[1][0];

	for (int i = 0; i < numCol; ++i) {
		if ( arr[1][i] != clase ){
			indexElegidos[0][index] = i;
			clase = arr[1][i];			
			++index;
		}
	}

	/*fprintf(output, "indexElegidos: \n");
	for (int i = 0; i < index; ++i)
	{
		fprintf(output, "%f\n",indexElegidos[0][i] );
	}
	fprintf(output, "\n\n");*/

	/* 3. Elegir como umbral la media del par de valores que minimice la entropía */

	for (int i = 0; i < index; ++i)
	{

		unsigned int numAtributosMenores;
		unsigned int numAtributosMayores;

		unsigned int numSiMenores = 0;
		unsigned int numNoMenores = 0; 
		unsigned int numSiMayores = 0;
		unsigned int numNoMayores = 0;

		numAtributosMenores = indexElegidos[0][i];
		numAtributosMayores = numCol - indexElegidos[0][i];

		for (int j = 0; j < numAtributosMenores; ++j){
			if (arr[1][j] == 1)
				++numSiMenores;
		}

		numNoMenores = numAtributosMenores - numSiMenores;

		for (int j = numAtributosMenores; j < numCol; ++j){
			if (arr[1][j] == 1)
				++numSiMayores;
		}

		numNoMayores = numAtributosMayores - numSiMayores;

		/*fprintf(output, "numAtributosMenores: %d\n", numAtributosMenores);
		fprintf(output, "numAtributosMayores: %d\n", numAtributosMayores);
		fprintf(output, "numSiMenores: %d\n", numSiMenores);
		fprintf(output, "numNoMenores: %d\n", numNoMenores);
		fprintf(output, "numSiMayores: %d\n", numSiMayores);
		fprintf(output, "numNoMayores: %d\n\n", numNoMayores);*/

		double entropiaMenorSi = 0;
		double entropiaMenorNo = 0;
		double entropiaMayorSi = 0;
		double entropiaMayorNo = 0;
		double entropia1 = 0;
		double entropia2 = 0;


		if ( (numSiMenores != 0) && (numSiMenores != numAtributosMenores) )
			entropiaMenorSi = ( ( (double)numSiMenores / (double)numAtributosMenores ) * (- log( (double)numSiMenores / (double)numAtributosMenores) / log(2)) );

		if ( (numNoMenores != 0) && (numNoMenores != numAtributosMenores) )
			entropiaMenorNo = ( ( (double)numNoMenores / (double)numAtributosMenores) * (- log( (double)numNoMenores / (double)numAtributosMenores) / log(2) ) );

		entropia1 = ( (double)numAtributosMenores / (double)numCol) * (entropiaMenorSi + entropiaMenorNo);

		if ( (numSiMayores != 0) && (numSiMayores != numAtributosMayores) )
			entropiaMayorSi = ( ( (double)numSiMayores / (double)numAtributosMayores) * (- log( (double)numSiMayores / (double)numAtributosMayores) / log(2)) );
		
		if ( (numNoMayores != 0) && (numNoMayores != numAtributosMayores) )
			entropiaMayorNo = ( ( (double)numNoMayores / (double)numAtributosMayores) * (- log( (double)numNoMayores / (double)numAtributosMayores) / log(2)) );

		entropia2 = ( (double)numAtributosMayores / (double)numCol) * (entropiaMayorSi + entropiaMayorNo); 

		indexElegidos[1][i] = entropia1 + entropia2;

		/*fprintf(output, "entropiaMenorSi: %f\n", entropiaMenorSi);
		fprintf(output, "entropiaMenorNo: %f\n", entropiaMenorNo);
		fprintf(output, "entropiaMayorSi: %f\n", entropiaMayorSi);
		fprintf(output, "entropiaMayorNo: %f\n", entropiaMayorNo);
		fprintf(output, "entropia1: %f\n", entropia1);
		fprintf(output, "entropia2: %f\n", entropia2);
		fprintf(output, "Entropia Total: %f\n\n", indexElegidos[1][i]);*/


	}



	/* Buscamos el valor del atributo con menor entropia */
	unsigned int indexMinEntropia;
	float minEntropiaValue;
	float minEntropia = 1;

	//fprintf(output, "Entropias Elegidos: \n");
	for (int i = 0; i < index; ++i) {
		//fprintf(output, "%f ", indexElegidos[1][i]);
		if ( indexElegidos[1][i] < minEntropia ) {
			minEntropia = indexElegidos[1][i];
			indexMinEntropia = indexElegidos[0][i];
		}
	}

	minEntropiaValue = arr[0][indexMinEntropia];

	float umbral1 = minEntropiaValue; /* Esto esta puesto por comprension */

	/* Buscamos atributo de otra clase por la izquierda */	

	float umbral2;

	clase = arr[1][indexMinEntropia];

	//printf("Clase: %f\n", clase);

	for (int i = indexMinEntropia; i > 0 ; --i) {
		if (arr[1][i] != clase){
			umbral2 = arr[0][i];
			break;
		}
	}

	/* Calculamos el humbral */
	float umbral = (float) ( (umbral1 + umbral2) / 2);
	/*printf("Umbral1: %f\n", umbral1);
	printf("Umbral2: %f\n", umbral2);
	printf("Umbral Final\n\n: %f\n", umbral);*/

	return umbral;
}



bool estaAtrbibuto(int numAtributos, float **tabla, float atributo) {
	
	for (int i = 0; i < numAtributos; ++i){
		if (tabla[0][i] == atributo)
			return true;	
	}

	return false;

}