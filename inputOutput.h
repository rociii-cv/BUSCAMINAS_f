#include "colors.h"
#include "juego.h"
#include <fstream>

const int N_HUECOS = 2; // huecos a dejar en el formato de las celdas.

using namespace std;

//void pedir_pos(int fila, int columna);
void mostrar_separador(tJuego juego);
void mostrar_celda(tJuego juego, int f, int c);
void color_numero(int numero);
void mostrar_juego_consola(tJuego juego);
void leer_archivo(tJuego& juego);