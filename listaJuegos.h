#ifndef listaJuegos_h
#define listaJuegos_h
using namespace std; 
#include "juego.h"

const int MAX_JUEGOS = 1; 

typedef struct {
	tJuego** lista; //lista es array dinamico de punteros de tJuego
	int cont;       //elementos usados
	int capacidad;	//posiciones en total del array
}tListaJuegos;

void inicializar(tListaJuegos*& lista_juegos);
void destruye(tListaJuegos* lista_juegos);
void insertar(tListaJuegos* lista_juegos, tJuego* juego); 
int numero_juegos(tListaJuegos lista_juegos);
bool es_vacia(tListaJuegos lista_juegos); 
tJuego dame_juego(tListaJuegos lista_juegos, int pos); 
void eliminar(tListaJuegos lista_juegos, int pos);

#endif