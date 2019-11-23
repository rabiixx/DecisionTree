#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define NUM_ENTRENAMIENTO 10   /* Numero de filas del dataset de entrenamiento */
#define NUM_TEST                  /* Numero de filas del dataset de testeo */ 


#define NUM_ATRIBUTOS 11          /* Numero de atributos del problema */
#define NUM_CLASES 2              /* Numero de clases */


FILE *output;

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

	fprintf(output, "Informacion Atributo %d: \n", indexAtributo);
	fprintf(output, "Numero AtributosSI: %d\n", numAtributoSi);
	fprintf(output, "Numero AtributosNO: %d\n", numAtributoNo);
	fprintf(output, "Numero AtributosSIVivos: %d\n", numAtributoSiVivos);
	fprintf(output, "Numero AtributosSIMuertos: %d\n", numAtributoSiMuertos);
	fprintf(output, "Numero AtributosNOVivos: %d\n", numAtributoNoVivos);
	fprintf(output, "Numero AtributosNOMuertos: %d\n", numAtributoNoMuertos);
	fprintf(output,"Numero VIvos; %d\n", numVivos);
	fprintf(output, "Numero Muertos; %d\n\n", numMuertos);

	/* CALCULO HEURISTICA */

	/* Se calcula la entropia de SI  -  E_Atributo(SI) */
	if ( ( (double)numAtributoSiVivos / (double)numAtributoSi ) != 0 ) {
		entropiaSiVivos = ( (double)numAtributoSiVivos / (double)numAtributoSi ) * ( log( ( (double)numAtributoSi / (double)numAtributoSiVivos) ) / log(2));
	} else {
		entropiaSiVivos = (double) 0;
	}

	if ( ( (double)numAtributoSiMuertos / (double)numAtributoSi ) != 0 ){
		entropiaSiMuertos = ( (double)numAtributoSiMuertos / (double)numAtributoSi ) * ( log( ( (double)numAtributoSi / (double)numAtributoSiMuertos) ) / log(2));
	} else {
		entropiaSiMuertos = (double) 0;
	}

	entropiaSi = (double) (entropiaSiVivos + entropiaSiMuertos);

	double entropiaNo; 
	double entropiaNoVivos;
	double entropiaNoMuertos;

	/* Se calcula la entropia de NO  -  E_Atributo(NO) */

	if (( (double)numAtributoNoVivos / (double)numAtributoNo) != 0) {
		entropiaNoVivos = ( (double)numAtributoNoVivos / (double)numAtributoNo) * ( log( ( (double)numAtributoNo / (double) numAtributoNoVivos) ) / log(2));
	} else {
		entropiaNoVivos = (double) 0;
	}

	if ( ( (double)numAtributoNoMuertos / (double)numAtributoNo) != 0) {
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

	heuristica.entropia = entropiaAtributo;
	heuristica.gainInfo = gain;
	heuristica.gainRatio = gainRatioA;

	return heuristica;
}


/** Se encarga de elegir el mejor atributo (mejor heuristica) y devuelve su indice */
void elegirAtributo(int numFilas, int numAtributos, float **tabla) {

	infoAtributo arrHeuristica[numAtributos];

	double maxEnt = 0;
	unsigned int indexMaxEnt = 0;

	for (int i = 0; i < numAtributos; ++i) {
		arrHeuristica[i] = calculoEntropiaCat(numFilas, numAtributos, tabla, i);	
		//if (arrHeuristica[i].ga)	
		printf("Atributo %d: \n", i);
		printf("Entropia: %f\n", arrHeuristica[i].entropia);
		printf("Gain Info: %f\n", arrHeuristica[i].gainInfo);
		printf("Gain Ratio: %f\n", arrHeuristica[i].gainRatio);
	}
}


int main(int argc, char const *argv[])
{

	system("clear");

	float **arrMatrix = (float**)malloc(NUM_ENTRENAMIENTO * sizeof(float*));

	for (int i = 0; i < NUM_ENTRENAMIENTO; ++i) {
		arrMatrix[i] = (float*)malloc(NUM_ATRIBUTOS * sizeof(float));
	}

	FILE *dataset;
	if ( (dataset = fopen("problem_book.csv", "r")) == NULL){
		perror("Fallo al abrir fichero");
		exit(342);
	}

	if( (output = fopen("output.txt", "a")) == NULL) {
		perror("Error abriendo fichero output");
		exit(EXIT_FAILURE);
	} 

	char *str = (char*)malloc(500*sizeof(char));

	/* Leer primera linea */
	fgets(str, 500, dataset);
	printf("Primera linea: %s\n", str );


	printf("Read Datos: \n");
	for (int i = 0; i < NUM_ENTRENAMIENTO; ++i){
		fgets(str, 500, dataset);
		sscanf(str, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", &arrMatrix[i][0], &arrMatrix[i][1], &arrMatrix[i][2], &arrMatrix[i][3], &arrMatrix[i][4], &arrMatrix[i][5], &arrMatrix[i][6], &arrMatrix[i][7], &arrMatrix[i][8], &arrMatrix[i][9], &arrMatrix[i][10]);
		fprintf(output, "Fila %d: %3f %3f %3f %3f %3f %3f %3f %3f %3f %3f %3f\n", i, arrMatrix[i][0], arrMatrix[i][1], arrMatrix[i][2], arrMatrix[i][3], arrMatrix[i][4], arrMatrix[i][5], arrMatrix[i][6], arrMatrix[i][7], arrMatrix[i][8], arrMatrix[i][9], arrMatrix[i][10]);
	}
	fprintf(output, "\n\n");


	elegirAtributo(NUM_ENTRENAMIENTO, NUM_ATRIBUTOS, arrMatrix);


	fclose(output);
	fclose(dataset);

	return 0;
}