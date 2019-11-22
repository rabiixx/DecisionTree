#include <stdio.h>
#include <stdlib.h>



/*
int **fun(int arr[]) {
	


	int *arrF = (int*)malloc(10 * sizeof(int));

	arrF[0] = 3463;
	arrF[1] = 3463;
	arrF[2] = 3463;
	arrF[3] = 3463;


	return arrF;

}*/


int main(int argc, char const *argv[])
{
	printf("sapfsd\n");

	/* Array de punteros */
	int *matrix[6];

	int x = 34;
	int y = 43;

	matrix[0] = &x;
	matrix[1] = &y;

	for (int i = 0; i < 2; ++i){
		printf("%d\t", *(matrix[i]));
	}

	return 0;
}



