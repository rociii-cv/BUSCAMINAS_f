#ifndef listaJuegos_h
#define listaJuegos_h
using namespace std; 
#include "juego.h"

const int MAX_JUEGOS = 1; 

typedef struct {
	tJuego** lista; 
	int cont; 
	int capacidad; 
}tListaJuegos;

void inicializar(tListaJuegos*& lista_juegos);
void destruye(tListaJuegos* lista_juegos);
int insertar(tListaJuegos* lista_juegos, tJuego* juego); 
int numero_juegos(tListaJuegos lista_juegos);
bool es_vacia(tListaJuegos lista_juegos);
//dame_juego(lista_juegos, pos); 
//eliminar(lista_juegos, pos); 

#endif