#include <iostream>
using namespace std; 
#include "juego.h"
#include "tablero.h"
#include "celda.h"
#include "listaPosiciones.h"

void inicializar(tJuego& juego) {
	juego.mina_explotada = false;
	juego.num_descubiertas = 0;
	juego.num_jugadas = 0;
	juego.num_minas = 0;
	inicializar(juego.tablero); //función inicializar de tablero.cpp
}

void inicializar_juego(tJuego& juego, int nfils, int ncols) {
	inicializar_tablero(juego.tablero, nfils, ncols);
}

int dame_num_jugadas(const tJuego& juego) {
	return juego.num_jugadas;
}

int dame_num_filas(tJuego juego) {
	return juego.tablero.nFils; 
}
int dame_num_columnas(tJuego juego) {
	return juego.tablero.nCols;
}
int dame_num_minas(tJuego juego){
	return juego.num_minas; 
}

//las siguientes funciones utilizan funciones de celda.cpp 
bool contiene_mina(tJuego juego, int fila, int columna) {
	return (es_mina(juego.tablero.datos[fila][columna])); 
}

bool es_visible(tJuego juego,int fila, int columna) {
	return (es_visible(juego.tablero.datos[fila][columna])); 
}

bool esta_marcada(tJuego juego, int fila,int columna){
	return (esta_marcada(juego.tablero.datos[fila][columna]));
}

bool esta_vacia(tJuego juego, int fila, int columna) {
	return (esta_vacia(juego.tablero.datos[fila][columna]));
}
bool contiene_numero(tJuego juego, int fila, int columna) {
	return (contiene_numero(juego.tablero.datos[fila][columna]));
}
bool dame_numero(tJuego juego,int fila, int columna) {
	return (dame_numero(juego.tablero.datos[fila][columna]));
}

bool esta_completo(tJuego juego) {
	bool completo = true; //completo hasta que se demuestre lo contrario
	tCelda celda; //auxiliar para simplificar escritura
	int f=0, c = 0;
	while (completo && (f < juego.tablero.nFils) && (c < juego.tablero.nCols)) {
		celda = juego.tablero.datos[f][c];
		if (es_visible(celda) == false) { //busca condicion de fallo (que demuestre que no está completo)
			if (dame_estado(celda) != MINA) completo = false;
		}
		f++;
		c++;
	}
	return completo;
}

bool mina_explotada(tJuego juego, int fila, int columna) {
	bool siMina, siExplotada=false;
	siMina = es_mina(juego.tablero.datos[fila][columna]);
	if (siMina) {
		siExplotada= es_visible(juego.tablero.datos[fila][columna]);
	}
	return siExplotada;
}

//se termina si explotas la mina o si ganaste (completo el tablero sin contar minas)
bool esta_terminado(tJuego juego, int fila, int columna) {
	bool siTerminada = false; 
	if (esta_completo(juego) && mina_explotada(juego, fila, columna)) siTerminada = true;
	return siTerminada;
}

void marcar_desmarcar(tJuego& juego, int fila, int columna) {
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

void poner_mina(tJuego& juego, int fila, int columna) {
	
	if (!es_mina(juego.tablero.datos[fila][columna]) && es_valida(juego.tablero, fila, columna)) { //chequeo posicion válida y que ya no contenga mina:
		poner_mina(juego.tablero.datos[fila][columna]); //estado de la celda = MINA

		//actualiza posiciones vecinas (numeros):			TENGO QUE VOLVER A CHEAQUEAR SI ES VALIDA PARA EVITAR EN LOS BORDE ACTUALIZAR LAS QUE ESTEN FUERA
		// FUERA DE FUNCIÓN
		for (int i = fila - 1; i <= fila + 1; i++) {
			for (int j = columna - 1; j <= columna + 1; j++) {
				if (!es_mina(juego.tablero.datos[i][j])) { //mientras que la celda NO sea MINA
					if (esta_vacia(juego.tablero.datos[i][j])) { //si celda esta vacía pone estado en NUMERO y le asigna un 1
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


void juega(tJuego& juego, int fila, int columna, tListaPosiciones& lista_pos) {// hola
	tCelda celda = juego.tablero.datos[fila][columna]; 
	if (es_valida(juego.tablero, fila, columna) && !es_visible(celda) && !esta_marcada(celda)) {
		descubrir_celda(juego.tablero.datos[fila][columna]); 
		//	CONVIENE METERLO EN OTRA FUNCIÓN
		lista_pos.lista[lista_pos.cont].posx = fila; 
		lista_pos.lista[lista_pos.cont].posy = columna;
		lista_pos.cont++;

		if (!es_mina(celda) && esta_vacia(celda)){ //si se cumple esto actualiza
			for (int i = fila - 1; i <= fila + 1; i++) {
				for (int j = columna - 1; j <= columna + 1; j++) {	
					tCelda celdaAdy = juego.tablero.datos[i][j];
					if (es_valida(juego.tablero, i, j) && !es_visible(celdaAdy) && !esta_marcada(celdaAdy)) { //si no se salen del tablero actualiza:
						descubrir_celda(juego.tablero.datos[i][j]);
						//INSERTAR EN LISTA_POS

					}
				}
			}
			//VOLVER A VER SI ES VALIDA
			//QUE NO SEA LA PRINCIPAL
			//FUNCION RECURSIVA JUEGA PARA SI DESCUBRE OTRA MÁS QUE ESTÉ VACÍA

		}

	}
}