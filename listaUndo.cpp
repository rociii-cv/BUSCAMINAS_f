#include <iostream>
using namespace std; 

#include "juego.h"
#include "listaPosiciones.h"


void inicializar(tListaUndo& lista_undo) {//inicializas lista undo al principio vacia porq no has hecho nada aun
	lista_undo.cont = 0;
	
}

void insertar_final(tListaUndo& lista_undo, 
	tListaPosiciones lista_pos) { //inserta la lista_pos (que tiene la ultima jugada con sus respectivas acciones) al final de la lista, (lista de listas)
	if (lista_undo.cont < MAX_UNDO) {
		lista_undo.lista[lista_undo.cont] = lista_pos;
		lista_undo.cont++;
	}
	else {
		for (int i = 0; i < MAX_UNDO - 1; i++) { //antes de meter en la ultima pos, desplazo para no cargarme anterior mov
			lista_undo.lista[i] = lista_undo.lista[i + 1];
		}
		lista_undo.lista[MAX_UNDO-1] = lista_pos;
	}
}

tListaPosiciones ultimos_movimientos(tListaUndo lista_undo) { //devuelve el ultimo elemento de la lista
	int cont = lista_undo.cont-1;
    tListaPosiciones ultimaPos = lista_undo.lista[cont];
	return ultimaPos;
}









