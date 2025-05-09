#include <iostream>
using namespace std; 

#include "listaJuegos.h"

void inicializar(tListaJuegos*& lista_juegos) { //lista de juegos inicialmente vacia
	lista_juegos->cont = 0; 
	lista_juegos->capacidad = MAX_JUEGOS;

	//crear array din�mico:
	if (lista_juegos != NULL) { //chequeo que no apunte ya a una direccion
		lista_juegos->lista = new tJuego * [lista_juegos->capacidad];
	}
}

void destruye(tListaJuegos *lista_juegos) { 

	//eliminar cada puntero del array:
	for (int i = 0; i < lista_juegos->cont; i++) {
		delete lista_juegos->lista[i];
	}

	//eliminar puntero a array din�mico:
	delete[] lista_juegos->lista;

	lista_juegos->cont = 0; 
}

void insertar(tListaJuegos* lista_juegos, tJuego *juego) { //??

	int i = 0;


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

tJuego dame_juego(tListaJuegos lista_juegos, int pos) { //ojo estas devolviendo algo que ya esta creado, no hace falta ningun new
	tJuego vacio; 
	if (pos >= 0 && lista_juegos.cont && lista_juegos.lista[pos] != NULL) {
		return *(lista_juegos.lista[pos]); //copia el juego en la posicion
	}
	else {
		inicializar(vacio); 
	}
}

void eliminar(tListaJuegos *lista_juegos, int pos) {
	if (pos >= 0 && pos < lista_juegos->cont) {
		//recolocar las listas en el array
		for (int i = pos; i < lista_juegos->cont - 1; i++) {
			lista_juegos->lista[i] = lista_juegos->lista[i + 1]; 
		}
	}
	lista_juegos->cont--; 
}
