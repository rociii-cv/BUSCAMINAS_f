#ifndef inputOutput_h
#define inputOutput_h

#include "colors.h"
#include "juego.h"
#include <fstream>

const int N_HUECOS = 2; // huecos a dejar en el formato de las celdas.

using namespace std;

void pedir_pos(int& fila, int& columna);
void comandos_especiales(tJuego& juego, int fila, int columna);
void mostrar_separador(tJuego juego);
void mostrar_celda(tJuego juego, int f, int c);
void color_numero(int numero);
void mostrar_juego_consola(const tJuego& juego);
bool leer_archivo(tJuego& juego, string filename);

#endif