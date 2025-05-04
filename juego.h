#ifndef juego_h
#define juego_h
using namespace std;
#include "tablero.h"
#include "listaPosiciones.h"
#include "listaUndo.h"

typedef struct {
	tTablero tablero;
	int num_jugadas;
	bool mina_explotada;
	int num_minas;
	int num_descubiertas;
} tJuego;

void inicializar(tJuego& juego);
void inicializar_juego(tJuego& juego, int nfils, int ncols);
int dame_num_columnas(tJuego &juego);
int dame_num_minas(tJuego juego);
bool contiene_mina(tJuego juego, int fila, int columna);
bool es_visible(tJuego juego, int fila, int columna);
bool esta_marcada(tJuego juego, int fila, int columna);
bool esta_vacia(tJuego juego, int fila, int columna);
bool contiene_numero(tJuego juego, int fila, int columna);
bool dame_numero(tJuego &juego, int fila, int columna);
bool esta_completo(tJuego juego);
void poner_mina(tJuego& juego, int fila, int columna);
bool mina_explotada(tJuego& juego, int fila, int columna);
bool esta_terminado(tJuego& juego, int fila, int columna);
bool forzar_finalizacion(int fila, int columna);
void marcar_desmarcar(tJuego& juego, int fila, int columna);
void juega(tJuego& juego, int fila, int columna, tListaPosiciones& lista_pos, tListaUndo& lista_undo);
void descubrir_vacia(tJuego& juego, int fila, int columna, tListaPosiciones& lista_pos);
int calcula_nivel(tJuego juego); 
tJuego crear_juego(int num_fils, int num_cols, int num_minas);

#endif

