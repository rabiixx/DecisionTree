#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NUM_ENTRENAMIENTO 100    /* Numero de filas del dataset de entrenamiento */
#define NUM_TEST                  /* Numero de filas del dataset de testeo */ 


#define NUM_ATRIBUTOS 11          /* Numero de atributos del problema */
#define NUM_CLASES 2              /* Numero de clases */


void filtrarTabla(int numFilas, int numAtributos, float tabla[][numAtributos], int indexAtributo, float valorAtributo) {


	float tablaFiltrada[numFilas][numAtributos - 1];	/* Nueva tabla ya filtrada */
	unsigned int indexFil = 0;					/* Indice de filas para recorrer la nueva tabla filtrada */ 
	unsigned int indexCol = 0;					/* Indice de columnas para recorrer la nueva tabla filtrada */ 

	for (int i = 0; i < numFilas; ++i) {

		/* Hemos encontrado una fila que coincide con el valor del atributo */
		if (tabla[i][indexAtributo] == valorAtributo){
			printf("debug1: %d\n", i);
			indexCol = 0;
			for (int j = 0; j < numAtributos; ++j){
				if (j != indexAtributo) {
					tablaFiltrada[indexFil][indexCol] = tabla[i][j];
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

}

int main(int argc, char const *argv[]) {

	float arrMatrix[10][11];

	FILE *dataset;
	if ( (dataset = fopen("problem_book.csv", "r")) == NULL){
		perror("Fallo al abrir fichero");
		exit(342);
	}

	char *str = (char*)malloc(500*sizeof(char));

	/* Leer primera linea */
	fgets(str, 500, dataset);
	printf("Primera linea: %s\n", str );

	for (int i = 0; i < 10; ++i){
		fgets(str, 500, dataset);
		sscanf(str, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", &arrMatrix[i][0], &arrMatrix[i][1], &arrMatrix[i][2], &arrMatrix[i][3], &arrMatrix[i][4], &arrMatrix[i][5], &arrMatrix[i][6], &arrMatrix[i][7], &arrMatrix[i][8], &arrMatrix[i][9], &arrMatrix[i][10]);
		printf("Fila %d: %3f %3f %3f %3f %3f %3f %3f %3f %3f %3f %3f\n", i, arrMatrix[i][0], arrMatrix[i][1], arrMatrix[i][2], arrMatrix[i][3], arrMatrix[i][4], arrMatrix[i][5], arrMatrix[i][6], arrMatrix[i][7], arrMatrix[i][8], arrMatrix[i][9], arrMatrix[i][10]);
	}

	/*for (int i = 0; i < 10 ; ++i) {
		printf("Fila %d: %d %d %d %d %d %d %d %d %d %d %d\n", i, arrMatrix[i][0], arrMatrix[i][1], arrMatrix[i][2], arrMatrix[i][3], arrMatrix[i][4], arrMatrix[i][5], arrMatrix[i][6], arrMatrix[i][7], arrMatrix[i][8], arrMatrix[i][9], arrMatrix[i][10]);
	}*/

	float x = 1.000;

	if (1 == x)
		printf("hoala\n");

	fclose(dataset);

	filtrarTabla(10, NUM_ATRIBUTOS, arrMatrix, 4, 1.0);

	return 0;
}


