#include <iostream>
using namespace std; 

#include "listaJuegos.h"

void inicializar(tListaJuegos &lista_juegos) { //lista de juegos inicialmente vacia
	
	lista_juegos.cont = 0;
	lista_juegos.capacidad = MAX_JUEGOS;
	lista_juegos.lista = new tJuego * [lista_juegos.capacidad]; //creo array de datos dinámicos
}

/*
void inicializar(tListaJuegos*& lista_juegos) { //lista de juegos inicialmente vacia

	//Reservo espacio en memoria para la estructura tListaJuegos
	if (lista_juegos == NULL) { //chequeo que no apunte ya a una direccion
		lista_juegos = new tListaJuegos;
	}

	lista_juegos->cont = 0;
	lista_juegos->capacidad = MAX_JUEGOS;
	lista_juegos->lista = new tJuego * [lista_juegos->capacidad]; //creo array de datos dinámicos
}*/

void destruye(tListaJuegos *lista_juegos) { 

	//eliminar cada puntero del array:
	for (int i = 0; i < lista_juegos->cont; i++) {
		delete lista_juegos->lista[i];
	}

	//eliminar puntero a array dinámico:
	delete[] lista_juegos->lista;

	lista_juegos->cont = 0; 
}

int insertar(tListaJuegos* lista_juegos, tJuego* juego) {

	//obtengo el juego:
	tJuego nuevoJuego = *juego;

	int nivelNuevoJuego = calcula_nivel(nuevoJuego);
	
	//Encuentro pos donde insertarlo:
	int pos = 0;
	while (pos < lista_juegos->cont && (calcula_nivel(*(lista_juegos->lista[pos])) < nivelNuevoJuego)) {
		pos++;
	}

	//Chequeo que haya espacio en lista (capacidad), sino REDIMENSIONO array:
	if (lista_juegos->cont >= lista_juegos->capacidad) { //si hay espacio coloca de forma ordenada
		redimensionar(lista_juegos);
	}

	//Hago hueco en lista (desplazo PUNTEROS a la der):
	for (int i = pos; i < lista_juegos->cont - 1; i++) {

		tJuego* aux = lista_juegos->lista[i + 1];
		lista_juegos->lista[i + 1] = lista_juegos->lista[i];
		lista_juegos->lista[i] = aux;
	}
	//coloco nuevo juego en la pos encontrada:
	*(lista_juegos->lista[pos]) = nuevoJuego;

	return pos;
}

void redimensionar(tListaJuegos*& lista_juegos) { //le pongo el & para que pueda modificar el puntero

	lista_juegos->capacidad++; //redimensiono en 1 unidad.

	//creo nuevo array con puntero aux
	tJuego **listaAux = new tJuego * [lista_juegos->capacidad]; //vuelvo a crear array reservando memoria

	//Copio anterior lista en la nueva redimensionada:
	for (int i = 0; i < lista_juegos->cont; i++) {
		listaAux[i] = lista_juegos->lista[i];
	}

	//Solo elimino el array y no cada puntero de cada pos, porque esos me interesa mantenerlos:
	delete[] lista_juegos->lista; 
	
	//Actualizo mi puntero con la dirección de la nueva lista:
	lista_juegos->lista = listaAux; //hago q apunte a la misma direccion que ListaAux (q apunta a la nueva lista)
}


int numero_juegos(tListaJuegos *lista_juegos) {//devuelve el numero de jugadas que contiene
	return lista_juegos->cont; 
}

bool es_vacia(tListaJuegos lista_juegos) { //devuelve true si la lista de juegos esta vacia
	
	bool vacia = false;
	if (lista_juegos.cont == 0) {
		vacia = true;
	}
	return vacia;
}

tJuego* dame_juego(tListaJuegos lista_juegos, int pos) {

	tJuego* juegoPedido = lista_juegos.lista[pos];

	return juegoPedido; //devuelve el PUNTERO al juego pedido en pos
}

void eliminar(tListaJuegos lista_juegos, int pos) {

	delete lista_juegos.lista[pos]; //elimino puntero en esa posición (pos)

	//Recoloco el array (desplazo):
	for (int i = pos; i < lista_juegos.cont - 1; i++) {
		lista_juegos.lista[i] = lista_juegos.lista[i + 1];
	}

	lista_juegos.cont--;
}