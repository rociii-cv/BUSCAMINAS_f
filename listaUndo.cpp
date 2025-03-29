#include <iostream>
using namespace std; 

#include "juego.h"
#include "listaPosiciones.h"


void inicializar(tListaUndo& lista_undo, tListaPosiciones& lista_pos) {
	lista_undo.cont = 0;
	inicializar(lista_pos);
}

void insertar_final(tListaUndo& lista_undo, tListaPosiciones lista_pos) { 
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

tListaPosiciones ultimos_movimientos(tListaUndo lista_undo) {
	int cont = lista_undo.cont-1;
    tListaPosiciones ultimaPos = lista_undo.lista[cont];
	//cout << "cont:" << lista_undo.lista[cont].cont << endl;
	return ultimaPos;
}









