#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NUM_ENTRENAMIENTO 10   /* Numero de filas del dataset de entrenamiento */
#define NUM_TEST                  /* Numero de filas del dataset de testeo */ 


#define NUM_ATRIBUTOS 11          /* Numero de atributos del problema */
#define NUM_CLASES 2              /* Numero de clases */


float **filtrarTabla(int numFilas, int numAtributos, float **tabla, int indexAtributo, float valorAtributo) {


	float **tablaFiltrada = (float**)malloc(NUM_ENTRENAMIENTO * sizeof(float*));

	for (int i = 0; i < NUM_ENTRENAMIENTO; ++i) {
		tablaFiltrada[i] = (float*)malloc(NUM_ATRIBUTOS * sizeof(float));
	}

	int indexFil = 0; 
	int indexCol = 0;



	for (int i = 0; i < NUM_ENTRENAMIENTO; ++i) {

		/* Hemos encontrado una fila que coincide con el valor del atributo */
		if (tabla[i][indexAtributo] == valorAtributo){
			indexCol = 0;
			for (int j = 0; j < NUM_ATRIBUTOS; ++j){
				if (j != indexAtributo) {
					tablaFiltrada[indexFil][indexCol] = (float)tabla[i][j];
					++indexCol;
				}
			}
			++indexFil;
		}
	}

	printf("IndexFil: %d\n", indexFil);

	for (int i = 0; i < indexFil ; ++i) {
		printf("Fila %d: %3f %3f %3f %3f %3f %3f %3f %3f %3f %3f\n", i, tablaFiltrada[i][0], tablaFiltrada[i][1], tablaFiltrada[i][2], tablaFiltrada[i][3], tablaFiltrada[i][4], tablaFiltrada[i][5], tablaFiltrada[i][6], tablaFiltrada[i][7], tablaFiltrada[i][8], tablaFiltrada[i][9]);
	}
	printf("\n\n");


	return tablaFiltrada;

}

int main(int argc, char const *argv[]) {


	system("clear");

	float **arrMatrix = (float**)malloc(NUM_ENTRENAMIENTO * sizeof(float*));
	float **newMatrix = (float**)malloc(NUM_ENTRENAMIENTO * sizeof(float*));

	for (int i = 0; i < NUM_ENTRENAMIENTO; ++i) {
		arrMatrix[i] = (float*)malloc(NUM_ATRIBUTOS * sizeof(float));
	}	

	for (int i = 0; i < NUM_ENTRENAMIENTO; ++i) {
		newMatrix[i] = (float*)malloc(NUM_ATRIBUTOS * sizeof(float));
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

	fclose(dataset);

	newMatrix = filtrarTabla(NUM_ENTRENAMIENTO, NUM_ATRIBUTOS, arrMatrix, 4, 1.0);

	printf("NewMatrix: \n");
	for (int i = 0; i < NUM_ENTRENAMIENTO ; ++i) {
		printf("Fila %d: %3f %3f %3f %3f %3f %3f %3f %3f %3f %3f\n", i, newMatrix[i][0], newMatrix[i][1], newMatrix[i][2], newMatrix[i][3], newMatrix[i][4], newMatrix[i][5], newMatrix[i][6], newMatrix[i][7], newMatrix[i][8], newMatrix[i][9]);
	}

	return 0;
}


