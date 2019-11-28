

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#define NUM_FILAS 15    /* Numero de filas del dataset de entrenamiento */

#define NUM_ATRIBUTOS 10          /* Numero de atributos del problema */
#define NUM_CLASES 2              /* Numero de clases */



int main(int argc, char const *argv[]) {

	system("clear");

	/* Declaracion de una matriz mediante punteros */
	float **tabla = (float**)malloc( (NUM_FILAS + 1) * sizeof(float*));

	for (int i = 0; i < NUM_FILAS + 1; ++i) {
		tabla[i] = (float*)malloc( (NUM_ATRIBUTOS + 1) * sizeof(float));
	}

	FILE *inputData, *outputData;
	FILE *output = fopen("output.txt", "w");

	if ( (inputData = fopen("problem_book1.csv", "r")) == NULL ) {
		printf("Error al abrir fichero: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	/* Se leen los datos de entrenamieto */
	tabla = readData(inputData, NUM_FILAS, NUM_ATRIBUTOS, output);
	fclose(inputData);




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