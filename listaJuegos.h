#ifndef listaJuegos_h
#define listaJuegos_h
using namespace std; 
#include "juego.h"

const int MAX_JUEGOS = 1; 

typedef tJuego* tPtrJuego; //declaro puntero del tipo tJuego

typedef struct {
	tPtrJuego* lista; 
	int cont; 
	int capacidad; 
}tListaJuegos;

void inicializar(tListaJuegos lista_juegos);
void destruye(tListaJuegos* lista_juegos);
int insertar(tListaJuegos* lista_juegos, tJuego* juego); 
int numero_juegos(tListaJuegos *lista_juegos);
bool es_vacia(tListaJuegos lista_juegos);
tJuego* dame_juego(tListaJuegos lista_juegos, int pos);
void eliminar(tListaJuegos lista_juegos, int pos);
void redimensionar(tListaJuegos*& lista_juegos);

#endif