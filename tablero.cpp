
#include <iostream>
using namespace std;
#include "tablero.h"
#include "celda.h"

void inicializar(tTablero& tablero) { //inicializamos el tablero a 0, para tenerlo vacío
	tablero.nCols = 0;
	tablero.nFils = 0;
}

void inicializar_tablero(tTablero& tablero, int nfils, int ncols) { //inicializamos un tablero de nfils, ncols, con las celdas vacías
	for (int i = 0; i < nfils; i++) {
		for (int j = 0; j < ncols; j++) {
			inicializar(tablero.datos[i][j]); //llamamos a INICIALIZAR de celda.cpp
		}
	}
}

/*NO LO USAMOS PORQUE CARGAMOS DIRECTAMENTE EN LA FUNCION INPUT OUTPUT
* 
//recibe numero de filas y columna DEL ARCHIVO (funcion InputOutput) y actualiza nfils y ncols
void num_filas(tTablero tablero, int tab) {
	tablero.nFils = tab;
}

void num_columnas(tTablero tablero, int tab) {
	tablero.nCols = tab;
}*/

tCelda dame_celda(tTablero tablero, int fila, int columna) { //devuelve la celda de una determinada posicion (tiene q ser correcta)
	return tablero.datos[fila][columna];
}

bool es_valida(tTablero tablero, int fila, int columna) { //devuelve true si la posicion es correcta (no se sale del tablero)
	bool valida = false;
	if (fila < tablero.nFils && fila >= 0) {
		if (columna < tablero.nCols && columna >= 0) {
			valida = true;
		}
	}
	return valida;
}

void poner_celda(tTablero& tablero, int fila, int columna, tCelda celda) { //asignamos el valor "celda" a una posicion del tablero
	tablero.datos[fila][columna] = celda;
}