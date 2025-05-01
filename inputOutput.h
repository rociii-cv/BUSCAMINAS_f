#ifndef inputOutput_h
#define inputOutput_h

#include "colors.h"
#include "juego.h"
#include "listaUndo.h"
#include "listaJuegos.h"
#include <fstream>

const int N_HUECOS = 2; // huecos a dejar en el formato de las celdas.

using namespace std;

void pedir_pos(int& fila, int& columna);
void comandos_especiales(tJuego& juego, int fila, int columna, tListaUndo& lista_undo);
void mostrar_separador(tJuego juego);
void mostrar_celda(tJuego &juego, int f, int c);
void color_numero(int numero);
void mostrar_juego_consola(tJuego& juego);
bool leer_archivo(tJuego& juego, string filename);
int comprobarNum(string caracter);
void mostrar_cabecera(tJuego juego); 
bool cargar_juegos(tListaJuegos lista_juegos);
void mostrar_juegos(tListaJuegos lista_juegos);
bool guardad_juegos(tListaJuegos* lista_juegos);

#endif