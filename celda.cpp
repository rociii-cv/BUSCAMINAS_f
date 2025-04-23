#include <iostream>
using namespace std; 
#include "celda.h"
#include "tablero.h"

void inicializar(tCelda& celda) { //inicializa la celda a VACIA, no marcada, no visible, y con nº 0
	celda.estado = VACIA;
	celda.marcada = false;
	celda.visible = false;
	celda.numero = 0;
}

tEstado dame_estado(tCelda celda) { //devuelve el estado de la celda, tEstado-->array, tCelda--->stuct dnd esta el tEstado estado
	return celda.estado;
}

int dame_numero(tCelda celda) { //devuelve el nº de la celda
	return celda.numero;
}

bool es_visible(tCelda celda) { //devielve true si el contenido es visible 
	bool visible = false;
	if (celda.visible) visible = true;
	return visible;
}

bool es_mina(tCelda celda) { //devuelve true si hay mina
	bool hayMina = false;
	if (celda.estado == MINA) hayMina = true;
	return hayMina;
}

bool esta_vacia(tCelda celda) { //devuelve true si esta vacía
	bool vacia = false; 
	if (celda.estado == VACIA) vacia = true; 
	return vacia; 
}
bool contiene_numero(tCelda celda) { //devuelve true si tiene un nº !=0
	bool numero = false; 
	if (celda.estado == NUMERO) numero = true;
	return numero; 
}

bool esta_marcada(tCelda celda) { //devuelve true si está marcada
	bool marcada = false;
	if (celda.marcada) marcada = true;
	return marcada;
}

void descubrir_celda(tCelda& celda) { //para destapar la celda
	 celda.visible = true;
}

void ocultar_celda(tCelda& celda) { //tapar la celda
	 celda.visible = false; 
}

void poner_mina(tCelda& celda) {//cambia el estado de la celda a MINA
	celda.estado = MINA; 
}

void marcar_celda(tCelda& celda) { //marcar la celda
	celda.marcada = true; 
}

void desmarcar_celda(tCelda& celda) { //desmarcar la celda
	celda.marcada = false; 
}

void poner_numero(tCelda& celda, int num) { //cambia el estado de la celda a NUMERO y mete el valor num
	celda.estado = NUMERO; 
	celda.numero = num; 
}
