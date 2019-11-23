#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define NUM_ENTRENAMIENTO 10   /* Numero de filas del dataset de entrenamiento */
#define NUM_TEST                  /* Numero de filas del dataset de testeo */ 


#define NUM_ATRIBUTOS 11          /* Numero de atributos del problema */
#define NUM_CLASES 2              /* Numero de clases */


typedef struct _infoAtributo {
	double entropia;
	double gainInfo;
	double gainRatio;
} infoAtributo;

/**
  * Calcula la entropia y la ganancia de informacion y la de un atributo categorico 
  * con una clase binaria
  */ 
infoAtributo calculoEntropiaCat(int numFilas, int numAtributos, float **tabla, int indexAtributo)
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
	for (int i = 0; i < numFilas; ++i) {
		if (tabla[i][indexAtributo] == 1) {
			printf("hola\n");
			++numAtributoSi;
			if (tabla[i][numAtributos - 1] == 1)
				++numAtributoSiVivos;
			else
				++numAtributoSiMuertos;
		} else {
			printf("adiso\n");
			++numAtributoNo;
			if (tabla[i][numAtributos - 1] == 0)
				++numAtributoNoVivos;
			else 
				++numAtributoNoMuertos;
		}
	}

	numVivos = numAtributoSiVivos + numAtributoNoVivos;
	numMuertos = numAtributoSiMuertos + numAtributoNoMuertos;

	printf("Informacion: \n");
	printf("Numero AtributosSI: %d\n", numAtributoSi);
	printf("Numero AtributosNO: %d\n", numAtributoNo);
	printf("Numero AtributosSIVivos: %d\n", numAtributoSiVivos);
	printf("Numero AtributosSIMuertos: %d\n", numAtributoSiMuertos);
	printf("Numero AtributosNOVivos: %d\n", numAtributoNoVivos);
	printf("Numero AtributosNOMuertos: %d\n", numAtributoNoMuertos);
	printf("Numero VIvos; %d\n", numVivos);
	printf("Numero Muertos; %d\n", numMuertos);




	/* CALCULO HEURISTICA */

	/* Se calcula la entropia de SI  -  E_Atributo(SI) */
	entropiaSiVivos = ( (double)numAtributoSiVivos / (double)numAtributoSi ) * ( log( ( (double)numAtributoSi / (double)numAtributoSiVivos) ) / log(2));


	printf("Entropia Si Vivos: %f\n", entropiaSiVivos);

	entropiaSiMuertos = ( (double)numAtributoSiMuertos / (double)numAtributoSi ) * ( log( ( (double)numAtributoSi / (double)numAtributoSiMuertos) ) / log(2));

	printf("Entropia Si Muertos: %f\n", entropiaSiMuertos);

	entropiaSi = (double) (entropiaSiVivos + entropiaSiMuertos);

	printf("Entropia SI: %f\n", entropiaSi);

	double entropiaNo; 
	double entropiaNoVivos;
	double entropiaNoMuertos;

	/* Se calcula la entropia de NO  -  E_Atributo(NO) */
	entropiaNoVivos = ( (double)numAtributoNoVivos / (double)numAtributoNo) * ( log( ( (double)numAtributoNo / (double) numAtributoNoVivos) ) / log(2));

	entropiaNoMuertos = ( (double)numAtributoNoMuertos / (double)numAtributoNo) * ( log( ( (double) numAtributoNo / (double)numAtributoNoMuertos) ) / log(2));

	entropiaNo = (double) (entropiaNoVivos + entropiaNoMuertos);

	/* Calcula la entropia del atributo  -  E(Atributo) */
	double entropiaAtributo = ( ( (double)numAtributoSi / (double)numFilas) * entropiaSi ) + ( ( (double)numAtributoNo / (double)numFilas) * entropiaNo );

	/* Calcula E(C) */
	double entropiaVivos;
	double entropiaMuertos;
	double entropiaC;

	entropiaVivos = ( (double)numVivos / (double)numFilas ) * ( log( ( (double)numFilas / (double)numVivos)) / log(2));
	entropiaMuertos = (numMuertos / numFilas) * ( log( ( (double)numFilas / (double)numMuertos)) / log(2));
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

	heuristica.entropia = entropiaAtributo;
	heuristica.gainInfo = gain;
	heuristica.gainRatio = gainRatioA;

	return heuristica;
}


/** Se encarga de elegir el mejor atributo (mejor heuristica) y devuelve su indice */
void elegirAtributo(int numFilas, int numAtributos, float **tabla) {

	infoAtributo arrHeuristica[numAtributos];


	for (int i = 0; i < numAtributos; ++i) {
		arrHeuristica[i] = calculoEntropiaCat(numFilas, numAtributos, tabla, i);	
		printf("Atributo %d: \n", i);
		printf("Entropia: %f\n", arrHeuristica[i].entropia);
		printf("Gain Info: %f\n", arrHeuristica[i].gainInfo);
		printf("Gain Ratio: %f\n", arrHeuristica[i].gainRatio);
	}
}


int main(int argc, char const *argv[])
{

	float **arrMatrix = (float**)malloc(NUM_ENTRENAMIENTO * sizeof(float*));

	for (int i = 0; i < NUM_ENTRENAMIENTO; ++i) {
		arrMatrix[i] = (float*)malloc(NUM_ATRIBUTOS * sizeof(float));
	}

	FILE *dataset;
	if ( (dataset = fopen("problem_book.csv", "r")) == NULL){
		perror("Fallo al abrir fichero");
		exit(342);
	}

	char *str = (char*)malloc(500*sizeof(char));

	/* Leer primera linea */
	fgets(str, 500, dataset);
	printf("Primera linea: %s\n", str );


	printf("Read Datos: \n");
	for (int i = 0; i < NUM_ENTRENAMIENTO; ++i){
		fgets(str, 500, dataset);
		sscanf(str, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", &arrMatrix[i][0], &arrMatrix[i][1], &arrMatrix[i][2], &arrMatrix[i][3], &arrMatrix[i][4], &arrMatrix[i][5], &arrMatrix[i][6], &arrMatrix[i][7], &arrMatrix[i][8], &arrMatrix[i][9], &arrMatrix[i][10]);
		printf("Fila %d: %3f %3f %3f %3f %3f %3f %3f %3f %3f %3f %3f\n", i, arrMatrix[i][0], arrMatrix[i][1], arrMatrix[i][2], arrMatrix[i][3], arrMatrix[i][4], arrMatrix[i][5], arrMatrix[i][6], arrMatrix[i][7], arrMatrix[i][8], arrMatrix[i][9], arrMatrix[i][10]);
	}
	printf("\n\n");


	elegirAtributo(NUM_ENTRENAMIENTO, NUM_ATRIBUTOS, arrMatrix);



	return 0;
}