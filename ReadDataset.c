#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[])
{
	
	long double arr[11];
	char delim[2] = ",";
	char *token;
	FILE *dataset;
	float test;
	char* pend;
	char *eos = "\0";

	if ( (dataset = fopen("problem_book2.csv", "r") ) == NULL){
		perror("fopen failed at opening the dataset");
		return EXIT_FAILURE;
	}

	

	char *str = (char*)malloc(200*sizeof(char));
	//fscanf(dataset, "%s", str);
	fgets(str, 200, dataset);

	fgets(str, 200, dataset);
	strcat(str, eos);

	printf("Frase: %s\n\n", str);

	token = strtok(str, delim);
	arr[0] = strtold(token, &pend);

	int i = 1;
	while (token != NULL) {
		//if (i == 11)
		//	break;
		printf(" %s\n", token);

		token = strtok(NULL, delim);

		arr[i] = strtold(token, &pend);
		i++;
	}

	printf("Datos: ");
	for (i = 0; i < 12; ++i)
	{
		printf(" %Lf, ", arr[i]);
	}

	return EXIT_SUCCESS;
}
