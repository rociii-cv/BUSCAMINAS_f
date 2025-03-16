#include <iostream>
using namespace std; 
#include "listaPosiciones.h"


void inicializar(tListaPosiciones& lista_pos) {
	lista_pos.cont = 0;
	lista_pos = { 0 };
	lista_pos.final_lista = MAX_LISTA-1; 
}

void insertar_final(tListaPosiciones& lista_pos, int x, int y) {
	lista_pos.lista[lista_pos.final_lista].posx = x;
	lista_pos.lista[lista_pos.final_lista].posy = y;
	lista_pos.final_lista--; //decremento la posicion del final lista
	lista_pos.cont++;
}

int longitud(tListaPosiciones lista_pos) {
	return lista_pos.cont;
}

int dame_posX(tListaPosiciones lista_pos, int i) {
	return lista_pos.lista[i].posx;
}

int dame_posY(tListaPosiciones lista_pos, int i) {
	return lista_pos.lista[i].posy;
}
