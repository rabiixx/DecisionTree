#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/** Indices Atributos
  * 0 --> Masculino
  * 1 --> Libro1
  * 2 --> Libro2
  * 3 --> Libro3
  * 4 --> Libro4
  * 5 --> Libro5
  * 6 --> Matrimonio
  * 7 --> Nobleza
  * 8 --> Muertes Realcionadas
  * 9 --> Popularidad 
  */

/** Indices tipos atributo
  * 1 --> Si
  * 0 --> No
  */

/** Indices clases
  * 1 -- > Vivo
  * 0 --> Muerto
  */
	


/* Define la estructura de una nodo del arbol de decisiones */
typedef struct _nodo {
	unsigned int atributo;			/* Indica que atributo usar para dividir */
	unsigned int clase;				/* Si es una hoja, indica la clase a la pertenece */
	bool hoja;						/* Indica si el nodo es una hoja */
	int *arrHijos[];				/* Contiene el valor de los atributos de sus hijos */
	struct _nodo *izq;				/* Direccion de memoria del hijo izquierdo */
	struct _nodo *der;				/* Direccion de memoria del hijo derecho */
} nodo;


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