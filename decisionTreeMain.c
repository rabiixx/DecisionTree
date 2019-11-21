#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NUM_FILAS 100
#define NUM_ATRIBUTOS 10
#define NUM_CLASES 2

int main(int argc, char const *argv[]) {

	/*size_t size = 20 * sizeof(char);


	char *str_atributos = (char*)malloc(10 * size);*/

	char *str_atributos[] = {"Masculino", "Libro1", "Libro2", "Libro3", "Libro4", "Libro5", "Matrimonio", "Nobleza", "MuertesR", "Popularidad"};

	char *arrClases[2] = {"Vivo", "Muerto"};



	nodo *raiz = NULL;
	raiz = construirArbol(tabla, raiz, arrAtributos);


	return 0;
}


/**
  * 1. Para evitar ramas infinitas pordemos fijar una constante alfa;
  * cuando la heuristica sea menor que alfa dejamos de expandir dicha rama
  * 2. Tener en cuenta que un atributo puede a ver si sido aplicado sobre 
  * un conjunto de datos y por tanto no puede ser utilizado sobre un subconjutno
  * de dicho conjunto 
  * /


The algorithm that builds the decision tree is a recursive algorithm and is implemented in the function `buildDecisionTree()` which is defined in `functions.cpp`. The algorithm works as follows:

    if the sub-table passed to the algorithm is empty
        return NULL;    // since there is no data in the table
    if the sub-table passed to the algorithm is homogeneous (if all the rows have the same value for the last column)
        mark this node as a leaf node;
        label this node with the value of the last column
        return a pointer to this node
    else
        decide a column to split the table on based on information gain
        set the node's splitOn value to this column's name
        for all the values that the splitting column can take:
            create a new node
            set the new node as the current node's child node
            prune the sub-table so that all the rows with this value of the last column are removed
            recursively call the function by passing it the new pruned table and the new node

The splitting column is decided based on information gain. This information gain is calculated using entropy which is a measure of randomness of information. The less random a split leaves the table in, the more information we can gain from it.
So we split the table on the column which gives us the most information gain (least entropy).


 */





