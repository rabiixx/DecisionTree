#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TRAIN 500


int main(int argc, char const *argv[])
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


	for (int i = 0; i < NUM_TRAIN; ++i){
		fscanf(dataset, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f ", &arr[i][0], &arr[i][1], &arr[i][2], &arr[i][3], &arr[i][4], &arr[i][5], &arr[i][6], &arr[i][7], &arr[i][8], &arr[i][9], &arr[i][10]);
	}

	return EXIT_SUCCESS;
}


	