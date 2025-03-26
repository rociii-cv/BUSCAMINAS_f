#include <iostream>
using namespace std; 
#include "listaUndo.h"


void inicializar(tListaUndo& lista_undo) {
	lista_undo.cont = 0; 
	//lista_undo.lista[MAX_UNDO] = { 0 };
}

void insertar_final(tListaUndo& lista_undo, tListaPosiciones lista_pos) { //lista_pos (un movimiento y lo q conlleve) se mete en la ultima pos del lista_undo
	for (int i = 0; i < MAX_UNDO-1; i++) { //antes de meter en la ultima pos, desplazo para no cargarme anterior mov
		lista_undo.lista[i] = lista_undo.lista[i + 1];
	}
	lista_undo.lista[lista_undo.pos_final] = lista_pos;
	lista_undo.cont++;
}

tListaPosiciones ultimos_movimientos(tListaUndo lista_undo) {
	return lista_undo.lista[lista_undo.cont]; 
}


