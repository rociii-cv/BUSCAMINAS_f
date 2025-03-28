#include <iostream>
using namespace std; 

#include "juego.h"
#include "listaPosiciones.h"


void inicializar(tListaUndo& lista_undo, tListaPosiciones& lista_pos) {
	lista_undo.cont = 0; 
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

void mostrar(tListaUndo lista_undo, tListaPosiciones lista_pos) {
	cout << "Lista UNDO:" << endl;
	cout << "Contador lista_undo: " << lista_undo.cont << endl;
	for (int j = 0; j < lista_pos.cont; j++) {
		cout << lista_pos.lista[j].posx << " , " << lista_pos.lista[j].posy
			 << endl;
	}
	cout << endl 
		<< lista_undo.lista[lista_undo.cont-1].lista[lista_pos.cont-1].posx << endl;
}

tListaPosiciones ultimos_movimientos(tListaUndo lista_undo) {
	cout << "Ultimos mov" << endl << lista_undo.lista[lista_undo.cont].cont << endl;
	return lista_undo.lista[lista_undo.cont]; 
}






