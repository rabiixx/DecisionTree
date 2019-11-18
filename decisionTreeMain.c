#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ATRIBUTOS 10
#define NUM_CLASES 2

int main(int argc, char const *argv[]) {

	/*size_t size = 20 * sizeof(char);


	char *str_atributos = (char*)malloc(10 * size);*/

	char *str_atributos[] = {"Masculino", "Libro1", "Libro2", "Libro3", "Libro4", "Libro5", "Matrimonio", "Nobleza", "MuertesR", "Popularidad"};

	printf("Atributos: ");
	for (int i = 0; i < NUM_ATRIBUTOS; ++i){
		printf("%s, ", str_atributos[i]);
	}
	printf("\n");


	/*char **str;
	str = (char**)malloc(2*sizeof(char*));

	for (int i = 0; i < 2; ++i){
		str[i] = (char*)malloc(20*sizeof(char));
	}	

	//str = {"Vivo", "Muerto"};
	str[0] = "Vivo";
	str[1] = "mueto";
	printf("%s\n", str[0]);
	printf("%s\n", str[1]);*/

	char *arrClases[2] = {"Vivo", "Muerto"};
	for (int i = 0; i < NUM_CLASES; ++i){
		printf("%s, ", arrClases[i]);
	}
	printf("\n");


	return 0;
}