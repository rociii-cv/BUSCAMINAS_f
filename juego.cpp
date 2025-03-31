#include <iostream>
using namespace std; 
#include "juego.h"
#include "tablero.h"
#include "celda.h"
#include "listaPosiciones.h"
#include "listaUndo.h"

void inicializar(tJuego& juego) { //creamos un juego vacío
	juego.mina_explotada = false;
	juego.num_descubiertas = 0;
	juego.num_jugadas = 0;
	juego.num_minas = 0;
	inicializar(juego.tablero); //función inicializar de tablero.cpp, para que no haya ni fils ni cols tp
}

void inicializar_juego(tJuego& juego, int nfils, int ncols) {//inicializamos el juego con un nº de fils y cols
	inicializar_tablero(juego.tablero, nfils, ncols);        //pero q tiene 0, no marcada, no visible y VACÍA
}

int dame_num_jugadas(const tJuego& juego) { //devuelve las jugadas q lleva el juego
	return juego.num_jugadas;
}

int dame_num_filas(tJuego juego) { //devuelve las filas q tien el tablero 
	return juego.tablero.nFils; 
}
int dame_num_columnas(tJuego juego) {//devuelve las columnas que tiene el tablero
	return juego.tablero.nCols;
}
int dame_num_minas(tJuego juego){//devuelve el nº de minas que hay en el juego
	return juego.num_minas; 
}

//las siguientes funciones utilizan funciones de celda.cpp 
bool contiene_mina(tJuego juego, int fila, int columna) { //devuelve si la pos es mina, tJuego-->struct dentro 
	return (es_mina(juego.tablero.datos[fila][columna])); //tTablero-->struct (tCelda matriz y nfils, ncols)
}

bool es_visible(tJuego juego,int fila, int columna) { //devuelve si la pos esta visible
	return (es_visible(juego.tablero.datos[fila][columna])); 
}

bool esta_marcada(tJuego juego, int fila,int columna){ //devuelve si la pos esta marcada
	return (esta_marcada(juego.tablero.datos[fila][columna]));
}

bool esta_vacia(tJuego juego, int fila, int columna) { //devuelve si la pos esta vacia
	return (esta_vacia(juego.tablero.datos[fila][columna]));
}
bool contiene_numero(tJuego juego, int fila, int columna) {//devuelve si la pos tiene nº
	return (contiene_numero(juego.tablero.datos[fila][columna]));
}
bool dame_numero(tJuego juego,int fila, int columna) { //te devuleve el nº que contiene la pos 
	return (dame_numero(juego.tablero.datos[fila][columna]));
}
// 

bool esta_completo(tJuego juego) { //devuelve true si todas las celdas del tablero, que no son minas, son visibles
	bool completo = true; //completo hasta que se demuestre lo contrario
	int f = 0;
	while (completo && (f < juego.tablero.nFils)) {
		for (int c = 0; c < juego.tablero.nCols; c++) {
			tCelda celda = juego.tablero.datos[f][c];
			if (!es_visible(celda)) { //si no está visible y llega a ser algo distinto de una mina --> FALSE
				if (dame_estado(celda) != MINA) completo = false;//si no visible y no mina todavía no esta completo
			}
		}
		f++;//analizamos otra pos aumentando el contador de fils, el de cols esta en el for
	} 
	return completo;
}

bool mina_explotada(const tJuego& juego, int fila, int columna) {//devuelve true si alguna mina ha sido descubierta
	bool siMina, siExplotada=false;
	siMina = es_mina(juego.tablero.datos[fila][columna]);
	if (siMina) { 
		siExplotada= es_visible(juego.tablero.datos[fila][columna]);// si hay mina y es visible --> TRUE
	}
	return siExplotada;
}

//se termina si explotas la mina o si ganaste (completo el tablero sin contar minas)
bool esta_terminado(const tJuego& juego, int fila, int columna) {
	bool siTerminada = false; 
	if ((esta_completo(juego)) || (mina_explotada(juego, fila, columna))) siTerminada = true; 
	return siTerminada;
}

bool forzar_finalizacion(int fila, int columna) { //funcion auxiliar para cuando quieres salirte del juego antes de terminarlo
	bool forzarFin = false;
	if (fila == -1 && columna == -1)  forzarFin = true;
	return forzarFin;
}

void marcar_desmarcar(tJuego& juego, int fila, int columna) { //si celda marcada-->se desamarca o viceversa (despues con -3 -3)
	tCelda celda = juego.tablero.datos[fila][columna]; //aux
	if (es_valida(juego.tablero, fila, columna)) {
		if (esta_marcada(celda)) {
			desmarcar_celda(juego.tablero.datos[fila][columna]);
		}
		else {
			marcar_celda(juego.tablero.datos[fila][columna]);
		}
	}
}

void poner_mina(tJuego& juego, int fila, int columna) {// funcion para meter una mina en una celda, incrementar las 
	tCelda celda = juego.tablero.datos[fila][columna];//celdas vecinas en 1 (cnd sea posible) para que indiquen la celda con mina a su alrededor
	if (!es_mina(celda) && es_valida(juego.tablero, fila, columna)) { //chequeo posicion válida y que ya no contenga mina:
		poner_mina(juego.tablero.datos[fila][columna]); //estado de la celda = MINA

		//actualiza posiciones vecinas (numeros):
		for (int i = fila - 1; i <= fila + 1; i++) {
			for (int j = columna - 1; j <= columna + 1; j++) {
				if (!es_mina(juego.tablero.datos[i][j]) && es_valida(juego.tablero, i, j)) { //mientras que la celda NO sea MINA
					if (esta_vacia(juego.tablero.datos[i][j])) { //si celda esta VACIA pone estado en NUMERO y le asigna un 1
						poner_numero(juego.tablero.datos[i][j], 1);
					}
					else {
						juego.tablero.datos[i][j].numero = dame_numero(juego.tablero.datos[i][j]) + 1; //suma 1 al numero que ya tenía la celda
					}
				}
			}
		}
	}
}


void juega(tJuego& juego, int fila, int columna, tListaPosiciones& lista_pos, tListaUndo& lista_undo) { //intenta descubrir la celda de la pos marcada
	if (es_valida(juego.tablero, fila, columna)) { // ver su valida la pos 
		if (!es_visible(juego.tablero.datos[fila][columna]) && !esta_marcada(juego.tablero.datos[fila][columna])) { // si no marcada y no visible
			descubrir_celda(juego.tablero.datos[fila][columna]); //descubre celda
			inicializar(lista_pos); //incializo porque sino lista_pos acumula las anteriores jugadas
			insertar_final(lista_pos, fila, columna); //añades jugada en la listaPosiciones
			juego.num_jugadas++; //suma jugada

			if (esta_vacia(juego.tablero.datos[fila][columna])) { //si la celda que se seleccionó está vacía actualiza adyacentes a ella.
				for (int i = fila - 1; i <= fila + 1; i++) {
					for (int j = columna - 1; j <= columna + 1; j++) {
						if (es_valida(juego.tablero, i, j) && !es_visible(juego.tablero.datos[i][j])
							&& !esta_marcada(juego.tablero.datos[i][j])) {
							descubrir_celda(juego.tablero.datos[i][j]);
							insertar_final(lista_pos, i, j); //voy añadiendo las posiciones descubiertas en la lista_pos
							if(esta_vacia(juego.tablero.datos[i][j])) descubrir_vacia(juego, i, j, lista_pos); //si vacia-->descubres
						}
					}
				}
			}
		}
		if (fila != -3 && columna != -3) { //comando para hacer el undo
			insertar_final(lista_undo, lista_pos); //inserto toda la lista_posiciones de esa jugada en mi lista_undo
		}
	}
}

void descubrir_vacia(tJuego& juego, int fila, int columna, tListaPosiciones& lista_pos) {//descubres la celda, funs de celda.cpp (descu) y de listapos
	for (int i = fila - 1; i <= fila + 1; i++) { //fula -1 (para que se corresponda con la pos insertada, pq matriz empieza en 0)
		for (int j = columna - 1; j <= columna + 1; j++) {
			if (es_valida(juego.tablero, i, j) && !es_visible(juego.tablero.datos[i][j])
				&& !esta_marcada(juego.tablero.datos[i][j])) {
				descubrir_celda(juego.tablero.datos[i][j]);
				insertar_final(lista_pos, i, j); //añades jugada
			}
		}
	}
}