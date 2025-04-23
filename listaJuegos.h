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
void destruye(tListaJuegos& lista_juegos);
void insertar(tListaJuegos& lista_juegos, tJuego juego); 
int numero_juegos(tListaJuegos lista_juegos);
//es_vacia(lista_juegos); 
//dame_juego(lista_juegos, pos); 
//eliminar(lista_juegos, pos); 

#endif