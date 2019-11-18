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

	if ( (dataset = fopen("problem_book2.csv", "r") ) == NULL){
		perror("fopen failed at opening the dataset");
		return EXIT_FAILURE;
	}

	

	char *str = (char*)malloc(200*sizeof(char));
	//fscanf(dataset, "%s", str);
	fgets(str, 200, dataset);

	fgets(str, 200, dataset);
	char *p = strchr (str, '\n');

	*p = '\0';
	printf("Puntero: %p", p);
	printf("Puntero Valor: %c", *p);


	printf("Frase: %s", str);

	printf("dsnfkjdshfkjdsnkfjndskjfn\n");

	token = strtok(str, delim);
	arr[0] = strtold(token, &pend);

	int i = 2;
	while (token != NULL) {
		//if (i == 11)
		//	break;
		printf(" %s\n", token);

		token = strtok(NULL, delim);

		arr[i-1] = strtold(token, &pend);
		i++;
	}

	printf("Datos: ");
	for (i = 0; i < 12; ++i)
	{
		printf(" %Lf, ", arr[i]);
	}

	return EXIT_SUCCESS;
}
