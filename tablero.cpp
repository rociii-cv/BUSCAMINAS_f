
#include <iostream>
using namespace std;
#include "tablero.h"
#include "celda.h"

void inicializar(tTablero& tablero) {
	tablero.nCols = 0;
	tablero.nFils = 0;
}

//inicializa tablero: carga sus dimensiones e ini celdas
void inicializar_tablero(tTablero& tablero, int nfils, int ncols) { 
	tablero.nFils = nfils;
	tablero.nCols = ncols;
	for (int i = 0; i < nfils; i++) {
		for (int j = 0; j < ncols; j++) {
			inicializar(tablero.datos[i][j]); //llamamos a INICIALIZAR de celda.cpp
		}
	}
}

int num_filas(tTablero &tab) {
	return tab.nFils;
}

int num_columnas(tTablero &tab) {
	return tab.nCols;
}

tCelda dame_celda(tTablero &tablero, int fila, int columna) { 
	return tablero.datos[fila][columna];
}

bool es_valida(tTablero& tablero, int fila, int columna) {
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