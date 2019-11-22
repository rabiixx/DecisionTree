#include <stdio.h>
#include <stdlib.h>



int main(int argc, char const *argv[])
{
	
	int matrix[5][10];
	size_t size = sizeof(matrix[0][1]) / sizeof(matrix[0][0]);

	printf("Size: %zu\n", size);

	return 0;
}