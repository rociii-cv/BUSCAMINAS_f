#include <iostream>
using namespace std; 

#include "listaJuegos.h"

void inicializar(tListaJuegos*& lista_juegos) { //lista de juegos inicialmente vacia
	lista_juegos->cont = 0; 
	lista_juegos->capacidad = MAX_JUEGOS;

	//crear array dinámico:
	if (lista_juegos != NULL) { //chequeo que no apunte ya a una direccion
		lista_juegos->lista = new tJuego * [lista_juegos->capacidad];
	}
}

void destruye(tListaJuegos *lista_juegos) { 

	//eliminar cada puntero del array:
	for (int i = 0; i < lista_juegos->cont; i++) {
		delete lista_juegos->lista[i];
	}

	//eliminar puntero a array dinámico:
	delete[] lista_juegos->lista;

	lista_juegos->cont = 0; 
}

void insertar(tListaJuegos* lista_juegos, tJuego *juego) {

	int i = 0;
	while ((i < lista_juegos->cont) && calcula_nivel(lista_juegos->lista[i])) {

	}

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
