#include <stdio.h>
#include <stdlib.h>

#define NUM_TRAIN 500

int readDataSet()
{

	FILE *dataset;

	long double dataMatrix[NUM_TRAIN][11];

	if ( (dataset = fopen("problem_book.csv", "r") ) == NULL){
		perror("fopen failed at opening the dataset");
		return EXIT_FAILURE;
	}

	char *str = (char*)malloc(200*sizeof(char));

	/* Leer primera linea */
	fgets(str, 200, dataset);


	unsigned int i = 0;
	while ( (fscanf(dataset, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f ", &arrMatrix[i][0], &arrMatrix[i][1], &arrMatrix[i][2], &arrMatrix[i][3], &arrMatrix[i][4], &arrMatrix[i][5], &arrMatrix[i][6], &arrMatrix[i][7], &arrMatrix[i][8], &arrMatrix[i][9], &arrMatrix[i][10])) != 0)
		++i;


	for (int i = 0; i < 50; ++i) {
		printf("%f %f %f %f %f %f %f %f %f %f %f\n", arrMatrix[i][0], arrMatrix[i][1], arrMatrix[i][2], arrMatrix[i][3], arrMatrix[i][4], arrMatrix[i][5], arrMatrix[i][6], arrMatrix[i][7], arrMatrix[i][8], arrMatrix[i][9], arrMatrix[i][10]);
	}


	return arrMatrix;

}


	