#include <iostream>
using namespace std; 
#include "listaPosiciones.h"


void inicializar(tListaPosiciones& lista_pos) { //lista inicialmente vacia
	lista_pos.cont = 0;
}

void insertar_final(tListaPosiciones& lista_pos, int x, int y) { //vas insertando en la lista las posiciones que metes 
	if (lista_pos.cont < MAX_LISTA) {
		lista_pos.lista[lista_pos.cont].posx = x;
		lista_pos.lista[lista_pos.cont].posy = y;
		lista_pos.cont++;
	}
	else { //en caso de que no hay espacio desplaza hacia la izquierda y luego coloca
		for (int i = 0; i < MAX_LISTA - 1; i++) { 
			lista_pos.lista[i] = lista_pos.lista[i + 1];
		}
		lista_pos.lista[MAX_LISTA-1].posx = x;
		lista_pos.lista[MAX_LISTA - 1].posy = y;
	}
}

int longitud(tListaPosiciones lista_pos) { //longitud de la lista (cuantas pos va ocupando)
	return lista_pos.cont;
}

int dame_posX(tListaPosiciones lista_pos, int i) { //valor de posX de elemento almacenado en la pos i
	return lista_pos.lista[i].posx;
}

int dame_posY(tListaPosiciones lista_pos, int i) {
	return lista_pos.lista[i].posy;
}
