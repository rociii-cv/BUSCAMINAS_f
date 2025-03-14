#pragma once
#ifndef juego_h
#define juego_h
using namespace std;
#include "tablero.h"

typedef struct {
	tTablero tablero;
	int num_jugadas;
	bool mina_explotada;
	int num_minas;
	int num_descubiertas;
} tJuego;

void inicializar(tJuego& juego);
void inicializar_juego(tJuego& juego, int nfils, int ncols);
int dame_num_jugadas(tJuego juego);
int dame_num_filas(tJuego juego);
int dame_num_columnas(tJuego juego);
int dame_num_minas(tJuego juego);
bool contiene_mina(tJuego juego, int fila, int columna);
bool es_visible(tJuego juego, int fila, int columna);
bool esta_marcada(tJuego juego, int fila, int columna);
bool esta_vacia(tJuego juego, int fila, int columna);
bool contiene_numero(tJuego juego, int fila, int columna);
bool dame_numero(tJuego juego, int fila, int columna);
bool esta_completo(tJuego juego);
void poner_mina(tJuego& juego, int fila, int columna);
/*mina_explotada(juego);
esta_terminado(juego);

marcar_desmarcar(juego, fila, columna);
juega(juego, fila, columna, lista_pos);*/

#endif

