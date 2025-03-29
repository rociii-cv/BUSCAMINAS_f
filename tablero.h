#ifndef tablero_h
#define tablero_h
using namespace std; 
#include "celda.h"

const int MAX_FILS = 100;
const int MAX_COLS = 100;

typedef struct {
	int nFils, nCols;
	tCelda datos[MAX_FILS][MAX_COLS];
} tTablero;

void inicializar(tTablero& tablero);
void inicializar_tablero(tTablero& tablero, int nfils, int ncols);
void num_filas(tTablero tablero, int tab);
void num_columnas(tTablero tablero, int tab);
tCelda dame_celda(tTablero tablero, int fila, int columna);
bool es_valida(tTablero tablero, int fila, int columna);
void poner_celda(tTablero& tablero, int fila, int columna, tCelda celda);

#endif
