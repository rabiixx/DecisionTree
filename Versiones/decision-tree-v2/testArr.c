#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(float *a, float *b)  
{  
    int t = *a;  
    *a = *b;  
    *b = t;  
}  
  
/* This function takes last element as pivot, places  
the pivot element at its correct position in sorted  
array, and places all smaller (smaller than pivot)  
to left of pivot and all greater elements to right  
of pivot */
int partition (int numCol, float arr[][numCol], int low, int high)  
{  
    int pivot = arr[0][high]; // pivot  
    int i = (low - 1); // Index of smaller element  
  
    for (int j = low; j <= high - 1; j++)  
    {  
        // If current element is smaller than the pivot  
        if (arr[0][j] < pivot)  
        {  
            i++; // increment index of smaller element  
            swap(&arr[0][i], &arr[0][j]);
            swap(&arr[1][i], &arr[1][j]);  
  
        }  
    }  
    swap(&arr[0][i + 1], &arr[0][high]);
    swap(&arr[1][i + 1], &arr[1][high]);  
    return (i + 1);  
}  
  
/* The main function that implements QuickSort  
arr[] --> Array to be sorted,  
low --> Starting index,  
high --> Ending index */
void quickSort(int numCol, float arr[][numCol], int low, int high)  
{  
    if (low < high)  
    {  
        /* pi is partitioning index, arr[p] is now  
        at right place */
        int pi = partition(numCol, arr, low, high);  
  
        // Separately sort elements before  
        // partition and after partition  
        quickSort(numCol, arr, low, pi - 1);  
        quickSort(numCol, arr, pi + 1, high);  
    }  
}

/* Calculo humbral atributo continuo */
/**
  * input: array[2][N] que contiene en la priemra fila los valores del atributo
  * y en la segunda fila la clase a la que pertence: Vivo / Muerto */
double discretizacion(int numCol, float arr[][numCol], FILE *output) 
{

	/* Numero de columnas de la matriz */
	// size_t N = ( sizeof(arr[0]) / sizeof(arr[0][0]) );

 	/* 2. Calcular la entropía para cada pareja de valores en los que la clase cambie */
	float indexElegidos[2][numCol];			/* 1. Fila--> Indice, 2. Fila-->Entropia */
	unsigned int index = 0;		/* Indice del array de indices de los elegidos */

	unsigned int clase = arr[1][0];

	for (int i = 0; i < numCol; ++i) {
		if ( arr[1][i] != clase ){
			indexElegidos[0][index] = i;
			clase = arr[1][i];			
			++index;
		}
	}

	fprintf(output, "Array Discretizado: \n");
	for (int i = 0; i < index; ++i)
	{
		fprintf(output, "%f:%f, ", arr[0][(int) indexElegidos[0][i]], arr[1][(int) indexElegidos[0][i]]);
	}
	fprintf(output, "\n");

	/* 3. Elegir como umbral la media del par de valores que minimice la entropía */
	unsigned int numAtributosMenores;
	unsigned int numAtributosMayores;

	unsigned int numSiMenores = 0;
	unsigned int numNoMenores = 0; 
	unsigned int numSiMayores = 0;
	unsigned int numNoMayores = 0;

	fprintf(output, "\nArr: \n");
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < numCol; ++j)
		{
			fprintf(output, "%f, ", arr[i][j]);
		}
		fprintf(output, "\n");
	}
	fprintf(output, "\n");

	for (int i = 0; i < index; ++i)
	{

		numAtributosMenores = indexElegidos[0][i];
		numAtributosMayores = numCol - indexElegidos[0][i];

		for (int j = 0; j < numAtributosMenores; ++j){
			if (arr[1][j] == 1)
				++numSiMenores;
		}

		numNoMenores = numAtributosMenores - numSiMenores;
		fprintf(output, "numSiMenores: %d\n", numSiMenores);
		fprintf(output, "numNoMenores: %d\n", numNoMenores);

		for (int j = numAtributosMenores + 1; j < numCol; ++j){
			if (arr[1][j] == 1)
				++numSiMayores;
		}

		numNoMayores = numAtributosMayores - numSiMayores;

		fprintf(output, "numAtributosMenores: %d\n", numAtributosMenores);
		fprintf(output, "numAtributosMayores: %d\n", numAtributosMayores);
		fprintf(output, "numSiMenores: %d\n", numSiMenores);
		fprintf(output, "numNoMenores: %d\n", numNoMenores);
		fprintf(output, "numSiMayores: %d\n", numSiMayores);
		fprintf(output, "numNoMayores: %d\n\n", numNoMayores);

		double entropiaMenorSi;
		double entropiaMenorNo;
		double entropiaMayorSi;
		double entropiaMayorNo;
		double entropia1;
		double entropia2;


		entropiaMenorSi = ( (numSiMenores / numAtributosMenores) * (- log(numSiMenores / numAtributosMenores) / log(2)) );
		entropiaMenorNo = ( (numNoMenores / numAtributosMenores) * (- log(numNoMenores / numAtributosMenores) / log(2)) );

		entropia1 = ( (numSiMenores / numCol) * entropiaMenorSi) + (numNoMenores / numCol) * entropiaMenorNo;


		entropiaMayorSi = ( (numSiMayores / numAtributosMayores) * (- log(numSiMayores / numAtributosMayores) / log(2)) );
		entropiaMayorNo = ( (numNoMenores / numAtributosMayores) * (- log(numNoMenores / numAtributosMayores) / log(2)) );

		entropia2 = ( (numSiMayores / numCol) * entropiaMayorSi) + (numNoMayores / numCol) * entropiaMayorNo;

		indexElegidos[1][i] = entropia1 + entropia2;

	}






	/* Buscamos el atributo con menor entropia */
	/*unsigned int indexMinEntropia;
	unsigned int minEntropiaValue;
	int minEntropia = 1;

	for (int i = 0; i < index; ++i) {
		if ( indexElegidos[1][i] < minEntropia ) {
			minEntropia = indexElegidos[1][i];
			indexMinEntropia = i;
		}
	}*/

	/*minEntropiaValue = arr[0][ indexElegidos[0][indexMinEntropia] ];
	double umbral1 = minEntropiaValue; /* Esto esta puesto por comprension */

	/* Buscamos atributo de otra clase por la izquierda */	

	/*double umbral2;

	clase = arr[1][ indexElegidos[0][indexMinEntropia] ];
	for (int i = indexElegidos[0][indexMinEntropia]; i < 0 ; --i) {
		if (arr[1][i] != clase)
			num = arr[0][i];
	}*/

	/* Calculamos el humbral */
	/*double umbral = (umbral1 + umbral2) / 2;

	return umbral;*/

}

int main(int argc, char const *argv[])
{


	FILE *output = fopen("output.txt", "w");


	int numFil = 10;
	float arr[2][10] = {{20, 23, 23, 27, 30, 40, 52, 63, 65, 70}, 
							{0, 1, 1, 1, 0, 0, 1, 1, 1, 1}};

	printf("Array Desordenado: ");
	for (int i = 0; i < numFil; ++i)
	 {
	 	printf("%f:%f ", arr[0][i], arr[1][i]);
	 } 
	 printf("\n\n");
	quickSort(numFil, arr, 0, numFil - 1);

	printf("Array Ordenado: ");
	for (int i = 0; i < numFil; ++i)
	 {
	 	printf("%f:%f ", arr[0][i], arr[1][i]);
	 
	 }
	 printf("\n\n"); 

 	discretizacion(numFil, arr, output);



	return 0;
}