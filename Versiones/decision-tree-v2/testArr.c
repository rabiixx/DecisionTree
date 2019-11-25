#include <stdio.h>
#include <stdlin.h>




void fun(int arr[]) {

	int N = (int) ( sizeof(arr)  / sizeof(arr[0]) );
	printf("Vqalor de N: %d\n", N);
	printf("Array: ");
	for (int i = 0; i < N; ++i)
	{	
		printf("%d, \n", arr[i]);
	}


}


int main(int argc, char const *argv[])
{
	
	int arr[2][6];
	int cont = 0;

	for (int i = 0; i < 6; ++i){
		arr[0][i] = cont++;
	}





	return 0;
}