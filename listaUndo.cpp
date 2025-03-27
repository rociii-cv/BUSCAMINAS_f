#include <iostream>
using namespace std; 
#include "listaUndo.h"
#include "juego.h"


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

void mostrar(tListaUndo lista_undo, tListaPosiciones lista_pos) {
	cout << "Lista UNDO:" << endl;
	cout << "Contador lista_undo: " << lista_undo.cont << endl;
	for (int j = 0; j < lista_pos.cont; j++) {
		cout << lista_pos.lista[j].posx << " , " << lista_pos.lista[j].posy
			 << endl;
	}
}

tListaPosiciones ultimos_movimientos(tListaUndo lista_undo) {
	return lista_undo.lista[lista_undo.cont]; 
}

//volver a ocultar las celdas descubiertas (UNDO):
void ocultar_undo(tJuego& juego, tListaUndo lista_undo) {
	tListaPosiciones lista_pos = ultimos_movimientos(lista_undo); //guardo en lista_pos el array con el ultimo movimiento de juega
	int cont = longitud(lista_pos);								 //me devuelve la longitud del ultimo movimiento (long de lista_pos)
	
	for (int i = 0; i < cont; i++) {
		//tengo que obtener la celda en específico que quiero volver a ocultar
		// para ello puedo pedir la pos de x e y
		//ocultar_celda(juego.tablero.datos[])
	}
} 


