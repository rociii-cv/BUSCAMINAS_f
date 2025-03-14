#include <iostream>
using namespace std; 
#include "tablero.h"
#include "celda.h"

void inicializar(tTablero& tablero) {
	tablero.nCols = 0; 
	tablero.nFils = 0; 
}

void inicializar_tablero(tTablero& tablero,int nfils,int ncols) {
	for (int i = 0; i < nfils; i++) {
		for (int j = 0; j < ncols; j++) {
			inicializar(tablero.datos[i][j]); //llamamos a inicializar de celda.cpp
		}
	}
}

/*/recibe numero de filas y columna DEL ARCHIVO (funcion InputOutput) y actualiza nfils y ncols
void num_filas(tTablero tablero, int tab) {
	//tablero.nFils = tab
	tablero.nFils = 3;
}

void num_columnas(tTablero tablero, int tab) {
	//tablero.nCols = tab;
	tablero.nCols = 3;
}*/

tCelda dame_celda(tTablero tablero, int fila, int columna) {
	return tablero.datos[fila][columna];
}

bool es_valida(tTablero tablero, int fila, int columna) {
	bool valida = false;
	if (fila < tablero.nFils && fila>=0) {
		if (columna < tablero.nCols && columna >= 0) {
			valida = true;
		}
	}
	return valida;
}

void poner_celda(tTablero& tablero, int fila, int columna, tCelda celda) {
	tablero.datos[fila][columna] = celda;
}
