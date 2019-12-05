# Arbol De Decision 

Algoritmia - Arbol de deciones basado en ganancia de informacion


### Breve Descripcion

Arbol de decisiones implementado en C que trabaja con datos numericos, tanto categoricos como continuos.
Prediccion de la muerte de un personaje literario de Juego De Tronos.

### Descripcion Desarollo

Se decidio programar el algoritmo ID3 (Iterative Dichotomiser 3) inventado por Ross Quinl que se base en entropia y la ganancia de informacion.

El algoritmo es capaz de trabajar con atributos discretos y continuos (CART) debido a que los datos asi lo requerian.

Distinguimos dos fases dentro del algoritmo: 

* Fase de entrenamiento: en esta fase se construye el arbol de deciones a partir de los datos de entrenamiento proporcionados.
* Fase de testeo: en esta fase se predice la pertenencia de los nuevos datos de entrada a una clase a partir del arbol de decision contruido en la fase de entrenamiento


#### Fase de entrenamiento

Para la construccion del arbol se obtado por crear una estructura de datos de arbol binario que contiene los datos de cada nodo

#### Almacenamiento de datos
Datos de entrenamiento:

Para almacenar los datos de entrenamiento se ha decido almacenarlos en una matriz de numero de datos (filas) + 1 x numero de atributos + 1. 
En la primero fila de la matriz se almacenan los atributos representados mediante un numero, por tanto, en la primero fila se tienes los numeros asociados a los diferente atributos.
En la ultima columna de cada fila se almacena (excepto de la primera) la clase a la que pertenece cada dato (fila).
Y en la filas (exvepto la primera) se almacenan el valor de los atributos de cada dato.
Ejemplo: numero de atributo = 3 y numero de datos = 10

	-------------------------------------------------
	|			TABLA			|
	-------------------------------------------------
	| i\j |   0	|    1    |    2   |   3   	|
	-------------------------------------------------
	|     | Male	|  Book1  | Noble  | Clase 	|
	|------------------------------------------------
	| 0   |   0	|     1   |    2   |  NULL 	|
	| 1   -------------------------------------------
	| 1   |   1   	|    1	  |   0    |    0  	|
	| 2   |   1   	|    1	  |   0    |    0  	|
	| 3   |   1  	|    1    |   0    |    0  	|
	| 4   |   1   	|    1    |   0    |    0  	|
	| 5   |   1   	|    1    |   0    |    0  	|
	| 6   |   1   	|    1    |   0    |    0  	|
	| 7   |   1   	|    1    |   0    |    0  	|
	| 8   |   1   	|    1    |   0    |    0  	|
	| 9   |   1   	|    1    |   0    |    0  	|
	| 10  |   1   	|    1    |   0    |    0  	|
	-------------------------------------------------

## Como afrontar el problema

* Los atributos discretos (0 o 1) una vez son utilizados, son eliminados de la tabla
* Los atributos continuos sin embargo, no son nunca eliminados. Para evitar ramas infinitas
se establece un umbral de ganancia de informacion y por tanto, si la maxima ganancia de informacion
de un atributo continuo no supera dicho umbral, ese nodo se combierte en hoja y se escoge como clase
la clase mas frecuente dentro de ese conjunto de datos (sub-tabla).


### Prerequisitos

* Compilador: GCC

* Librerias: Librerias Estandares C Linux

* Sistema: Linux 

## Compilacion

Compilar todo

```
make clean 
```
```
make all 
```
```
./ejecutable 
```

## Compilacion DEGUB GDB

Compilar todo

```
make clean 
```
```
make debug
```
```
gdb 
```
```
file ejecutable 
```

## Version 1

* Solo incluye atributos categoricos

## Version 2

* Incluye tanto atributos categoricos como continuos


## Estilo de programacion

[coding-style.rst](https://github.com/torvalds/linux/blob/master/Documentation/process/coding-style.rst)

## Autores

* **Ruben Cherif Narvaez** - 99rubenche@gmail.com - [rabiixx](https://github.com/rabiixx)

