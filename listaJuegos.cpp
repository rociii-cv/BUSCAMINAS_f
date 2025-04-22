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

int numero_juegos(tListaJuegos lista_juegos) {//devuelve el numero de jugadas que contiene
	return lista_juegos.cont; 
}

bool es_vacia(tListaJuegos lista_juegos) { //devuelve si la lista de juegos esta vacia
	lista_juegos.capacidad = false;  //al principio lo pensamos como que esta llena
	if (lista_juegos.capacidad != MAX_JUEGOS) {
		lista_juegos.capacidad = true; 
	}
	return lista_juegos.capacidad; 
}
