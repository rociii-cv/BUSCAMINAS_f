#include <iostream>
using namespace std; 

#include "listaJuegos.h"

void inicializar(tListaJuegos& lista_juegos) { //lista de juegos inicialmente vacia
	lista_juegos.cont = 0; 
}

void destruye(tListaJuegos& lista_juegos) { //eliminar toda la lista de juegos 
	lista_juegos.capacidad = 0; //eliminas capacidad pq quieres borrarlo todo
	inicializar(lista_juegos);  //(redundante, revisar)
}

void insertar(tListaJuegos& lista_juegos, tJuego juego) {

}
