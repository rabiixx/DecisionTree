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
node* buildDecisionTree(vvs &table, node* nodePtr, vvs &tableInfo)
{
	if (tableIsEmpty(table)) {
		return NULL;
	}
	if (isHomogeneous(table)) {
		nodePtr->isLeaf = true;
		nodePtr->label = table[1][table[1].size()-1];
		return nodePtr;
	} else {
		string splittingCol = decideSplittingColumn(table);
		nodePtr->splitOn = splittingCol;
		int colIndex = returnColumnIndex(splittingCol, tableInfo);
		int iii;
		for (iii = 1; iii < tableInfo[colIndex].size(); iii++) {
			node* newNode = (node*) new node;
			newNode->label = tableInfo[colIndex][iii];
			nodePtr->childrenValues.push_back(tableInfo[colIndex][iii]);
			newNode->isLeaf = false;
			newNode->splitOn = splittingCol;
			vvs auxTable = pruneTable(table, splittingCol, tableInfo[colIndex][iii]);
			nodePtr->children.push_back(buildDecisionTree(auxTable, newNode, tableInfo));
		}
	}
	return nodePtr;
}