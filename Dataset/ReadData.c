#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[])
{

	FILE *dataset;

	long double arr[11];


	if ( (dataset = fopen("problem_book3.csv", "r") ) == NULL){
		perror("fopen failed at opening the dataset");
		return EXIT_FAILURE;
	}

	

	char *str = (char*)malloc(200*sizeof(char));

	fgets(str, 200, dataset);

	fscanf(dataset, "%Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf %Lf ", &arr[0], &arr[1], &arr[2], &arr[3], &arr[4], &arr[5], &arr[6], &arr[7], &arr[8], &arr[9], &arr[10]);

	for (int i = 0; i < 11; ++i)
	{
		printf("%Lf\n", arr[i]);
	}


	return EXIT_SUCCESS;
}
