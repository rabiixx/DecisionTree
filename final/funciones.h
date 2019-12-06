
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <math.h>
#include <string.h>

/** Estructura de datos para alamacenar la heuristica de cada atributo */
typedef struct _infoAtributo {
	double entropia;
	double gainInfo;
	double gainRatio;
} infoAtributo;

/* Define la estructura de una nodo del arbol de decisiones */
typedef struct _nodo {
	unsigned int atributo;       /* Indica que atributo usar para dividir */
	float umbralA;               /* Si el atributo es continuo almacena su umbral */
  unsigned int clase;          /* Si es una hoja, indica la clase a la pertenece */
	bool hoja;						       /* Indica si el nodo es una hoja */
	float arrHijos[2];             /* Contiene el valor de los atributos de sus hijos */
	struct _nodo *izq;           /* Direccion de memoria del hijo izquierdo */
	struct _nodo *der;           /* Direccion de memoria del hijo derecho */
} nodo;


/* Contiene el numero de filas que contiene la tabla filtrada asi como la tabla filtrada */
typedef struct _filtroInfo {
	int numFil;
	float **tabla;
} filtroInfo;



#define NUM_FILAS_TRAIN 1000      /* Numero de filas del dataset de entrenamiento */
#define NUM_ATRIBUTOS 10          /* Numero de atributos del problema */
#define NUM_CLASES 2              /* Numero de clases */
#define UMBRAL_GAIN 0.01


#define clasePorDefecto 1           /* Clase por defecto */
#define NUM_FILAS_TEST 1000         /* Numero de filas del dataset de testeo */



/*** FUNCIONES ENTRENAMIENTO ***/

/* Calcula y devuelve la entropia, ganancia de informacion y ratio de ganancia */
infoAtributo calcularHeuristica(int numFilas, int numAtributos, float **tabla, int indexAtributo, float umbral, FILE *);

/* Elige el mejor atributo en base a la ganancia de informacion normalizada */
int elegirAtributo(int numFilas, int numAtributos, float **tabla, float umbral1, float umbral2, FILE *);

/* Contruye el arbol con los datos de entrenamiento */
nodo* construirArbolDecision(int numFil, int numAtributos, float **tabla, nodo* ptrNodo, FILE *output);

/** Devulve un nueva tabla en la cual se han eliminado 
  * las filas con valor valorAtributo y la columna del atributo. 
  * Devuelve una matriz de M x numAtributos */
filtroInfo filtrarTabla(int numFilas, int numAtributos, float **tabla, int indexAtributo, float valorAtributo, FILE *output);

/* Filtro de tabla para atributos continuos */
filtroInfo filtrarTablaCont(int numFil, int numAtributos, float **tabla, int atributo, float valorAtributo, float umbral, FILE *output);

/* Comprueba si todas las filas de una tabla pertenecen a la misma clase */
bool esHomojenea(int numFil, int numAtributos, float **tabla);

/* Si nos quedamos sin atributos pero con datos(filas), calcula el atributo mas frecuente de los datos */
int claseMasFrecuente(int numFil, int numAtributos, float **tabla);

/** Recorre la tabla almacenando y ordenando los valores del atritubo continuo.
  * Llama a la funcion discretizacion y devuelve el umbral del atributo */
float elegirUmbral(int numFil, int numAtributos, float **tabla, float atributo, FILE *);


/* Funcion de discretizacion que devulve un umbral del atributo coninuo */
float discretizacion(int numCol, float arr[][numCol], FILE *output);


int buscarAtributo(int numAtributos, float arrAtributos[], float atributo);



/*** FUNCIONES TESTEO ***/

/**
  * Funcion testDatosDT
  * Predice la clase a la que pertenece una fila (dato)
  * @param linea contiene los atributos del dato
  * @param ptrNodo raiz del arlbol binario de decisiones
  * @return prediccion clase predicha
  */
int testDatosDT(float *linea, nodo *ptrNodo);

/** 
  * Funcion analizarResultados
  * Analiza los resultados obtenidos y calcula la tasa de aciertos 
  * @param claseReales array que contiene las clase reales a las que pertenece cada dato
  * @param clasePredichass array que contiene las clase predichas a las que pertenece cada dato
  * @return EXIT_SUCCESS
*/int analizarResultados(float claseReales[], float clasesPredichas[]);



/*** FUNCIONES UTILIDAD ***/

/* Lee y almacena los datos en una matriz de [numFil+1] x [numAtributos + 1] */
float **readData(FILE *, unsigned int numFil, FILE *output);

void mostrarPreorden(nodo *raiz, FILE *output);

/* Imprime el arbol en anchura */
void printGivenLevel(nodo* root, int level); 

int height(nodo* node); 

void printLevelOrder(nodo* root);

/* Quicksort: utilizado para ordenar los valores de los atributos continuos */
void swap(float *a, float *b);

int partition (int numCol, float arr[][numCol], int low, int high);

void quickSort(int numCol, float arr[][numCol], int low, int high);

/* Muestra el arbol en preorden */
void mostrarPreorden(nodo *raiz, FILE *output);