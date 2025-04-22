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

inicializar(lista_juegos); 
destruye(lista_juegos); 
insertar(lista_juegos, juego); 
numero_juego(lista_juegos); 
es_vacia(lista_juegos); 
dame_juego(lista_juegos, pos); 
eliminar(lista_juegos, pos); 

#endif