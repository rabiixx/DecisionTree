#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	
	FILE *dataset;

	if ( (dataset = fopen("problem_book.csv", "r") ) == NULL){
		perror("fopen failed at opening the dataset");
		return EXIT_FAILURE;
	}

	char *numDead = (char*)malloc(200*sizeof(char));
	int res;
	fscanf(dataset, "%s", numDead);

	//res = atoi(&numDead);

	printf("Number of Deads: %s\n", numDead);


	return EXIT_SUCCESS;
}