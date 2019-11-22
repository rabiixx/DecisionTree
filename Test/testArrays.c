#include <stdio.h>
#include <stdlib.h>




int *fun(int arr[]) {
	


	int *arrF = (int*)malloc(10 * sizeof(int));

	arrF[0] = 3463;
	arrF[1] = 3463;
	arrF[2] = 3463;
	arrF[3] = 3463;


	return arrF;

}


int main(int argc, char const *argv[])
{
	

	int arr[] = {5, 3 ,123, 23};

	size_t N = sizeof(arr) / sizeof(arr[0]);


printf("Array1\n");
	for (int i = 0; i < N; ++i)
	{
		printf("%d\t", arr[i]);
	}
printf("\n");


	int *arrTemp = (int*)malloc(10 * sizeof(int));

	arrTemp = fun(arr);

	printf("Array1\n");
	for (int i = 0; i < N; ++i)
	{
		printf("%d\t", arrTemp[i]);
	}
	printf("\n");

	return 0;
}



