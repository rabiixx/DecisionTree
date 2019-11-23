#include <stdio.h>
#include <stdlib.h>




int **fun(int **hack) {
	

	int numFil = 5;
	int numCol = 7;
	int cont = 100;

	int **auxMatrix = (int**)malloc(numFil * sizeof(int*));

	for (int i = 0; i < numFil; ++i) {
		auxMatrix[i] = (int*)malloc(numCol * sizeof(int));
	}	

	hack[1][1] = 67;

	for (int i = 0; i < numFil; ++i) {
		for (int j = 0; j < numCol; ++j) {
			auxMatrix[i][j] = cont++;
		}
	}

	auxMatrix[1][0] = hack[1][1];


	return auxMatrix;

}


int main(int argc, char const *argv[])
{

	int numFil = 5;
	int numCol = 7;
	int cont = 0;

	int **matrix = (int**)malloc(numFil * sizeof(int*));

	for (int i = 0; i < numFil; ++i) {
		matrix[i] = (int*)malloc(numCol * sizeof(int));
	}	



	int **tempMatrix = (int**)malloc(numFil * sizeof(int*));

	for (int i = 0; i < numFil; ++i) {
		tempMatrix[i] = (int*)malloc(numCol * sizeof(int));
	}	


	for (int i = 0; i < numFil; ++i) {
		for (int j = 0; j < numCol; ++j) {
			matrix[i][j] = cont++;
		}
	}


	for (int i = 0; i < numFil; ++i) {
		for (int j = 0; j < numCol; ++j) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}

	tempMatrix = fun(matrix);



	printf("adios\n");
	for (int i = 0; i < numFil; ++i) {
		for (int j = 0; j < numCol; ++j) {
			printf("%d\t", tempMatrix[i][j]);
		}
		printf("\n");
	}
	

	return 0;
}



