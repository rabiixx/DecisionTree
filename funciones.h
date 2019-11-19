#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _nodo{
	int atributo;
	int clase;
	bool hoja;
	struct _nodo *arrHijos[];

}nodo;



typedef struct _infoAtributo {
	double entropia;
	double gainInfo;
	double gainRatio;
} infoAtributo;



/**
  * Calcula la entropia y la ganancia de informacion de un atributo categorico 
  * con una clase binaria
  */ 
infoAtributo calculoHeuristicaCat();


/* Quicksort para poder ordenar los atributos continuos */
void quickSort(int arr[], int low, int high);  


/* Calcula el humbra de una atributo continuo */
double discretizacion();