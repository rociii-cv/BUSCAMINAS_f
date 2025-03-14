#include <iostream>
using namespace std; 
#include "celda.h"
#include "tablero.h"

void inicializar(tCelda& celda) {
	celda.estado = VACIA;
	celda.marcada = false;
	celda.visible = false;
	celda.numero = 0;
}

tEstado dame_estado(tCelda celda) {
	return celda.estado;
}

int dame_numero(tCelda celda) {
	return celda.numero;
}

bool es_visible(tCelda celda) {
	bool visible = false;
	if (celda.visible) visible = true;
	return visible;
}

bool es_mina(tCelda celda) {
	bool hayMina = false;
	if (celda.estado == MINA) hayMina = true;
	return hayMina;
}

bool esta_vacia(tCelda celda) {
	bool vacia = false; 
	if (celda.estado == VACIA) vacia = true; 
	return vacia; 
}
bool contiene_numero(tCelda celda) {
	bool numero = false; 
	if (celda.estado == NUMERO) numero = true;
	return numero; 
}

bool esta_marcada(tCelda celda) {
	bool marcada = false;
	if (celda.marcada) marcada = true;
	return marcada;
}

void descubrir_celda(tCelda& celda) {
	 celda.visible = true;
}

void ocultar_celda(tCelda& celda) {
	 celda.visible = false; 
}

void poner_mina(tCelda& celda) {
	celda.estado = MINA; 
}

void marcar_celda(tCelda& celda) {
	celda.marcada = true; 
}

void desmarcar_celda(tCelda& celda) {
	celda.marcada = false; 
}

void poner_numero(tCelda& celda, int num) {
	celda.estado = NUMERO; 
	celda.numero = num; 
}