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

int dame_num_filas(tJuego &juego) { //devuelve las filas q tien el tablero 
	return num_filas(juego.tablero);
}

int dame_num_columnas(tJuego &juego) {//devuelve las columnas que tiene el tablero
	return num_columnas(juego.tablero);
}

int dame_num_minas(tJuego &juego){//devuelve el nº de minas que hay en el juego
	return juego.num_minas; 
}

//las siguientes funciones utilizan funciones de celda.cpp 
bool contiene_mina(tJuego juego, int fila, int columna) { //devuelve si la pos es mina, tJuego-->struct dentro 
	tCelda celda= dame_celda(juego.tablero, fila, columna);
	return (es_mina(celda)); //tTablero-->struct (tCelda matriz y nfils, ncols)
}

bool es_visible(tJuego juego,int fila, int columna) { //devuelve si la pos esta visible
	tCelda celda = dame_celda(juego.tablero, fila, columna);
	return (es_visible(celda)); 
}

bool esta_marcada(tJuego &juego, int fila,int columna){ //devuelve si la pos esta marcada
	tCelda celda = dame_celda(juego.tablero, fila, columna);
	return (esta_marcada(celda));
}

bool esta_vacia(tJuego juego, int fila, int columna) { //devuelve si la pos esta vacia
	tCelda celda = dame_celda(juego.tablero, fila, columna);
	return (esta_vacia(celda));
}
bool contiene_numero(tJuego juego, int fila, int columna) {//devuelve si la pos tiene nº
	tCelda celda = dame_celda(juego.tablero, fila, columna);
	return (contiene_numero(celda));
}
bool dame_numero(tJuego &juego,int fila, int columna) { //te devuleve el nº que contiene la pos 
	tCelda celda = dame_celda(juego.tablero, fila, columna);
	return (dame_numero(celda));
}

bool esta_completo(tJuego juego) { 
	bool completo = true; 
	int f = 0;
	int tableroFils = num_filas(juego.tablero);
	int tableroCols = num_columnas(juego.tablero);
	while (completo && (f < tableroFils)) {
		for (int c = 0; c < tableroCols; c++) {
			tCelda celda = dame_celda(juego.tablero, f, c);
			if (!es_visible(celda)) { //si no está visible y llega a ser algo distinto de una mina --> FALSE
				if (dame_estado(celda) != MINA) completo = false;//si no visible y no mina todavía no esta completo
			}
		}
		f++;
	} 
	return completo;
}

bool mina_explotada(tJuego& juego, int fila, int columna) {
	bool siMina, siExplotada=false;
	tCelda celda= dame_celda(juego.tablero, fila, columna);
	siMina = es_mina(celda);
	if (siMina) { 
		siExplotada= es_visible(celda);// si hay mina y es visible --> TRUE
	}
	return siExplotada;
}

//se termina si explotas la mina o si ganaste (completo el tablero sin contar minas)
bool esta_terminado(tJuego& juego, int fila, int columna) {
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
	tCelda celda = dame_celda(juego.tablero, fila, columna); //aux
	if (es_valida(juego.tablero, fila, columna)) {
		if (esta_marcada(celda)) {
			desmarcar_celda(celda);
		}
		else {
			marcar_celda(celda);
		}
		poner_celda(juego.tablero, fila, columna, celda);
	}
}

void poner_mina(tJuego& juego, int fila, int columna) {

	tCelda celda = dame_celda(juego.tablero, fila, columna);

	if (!es_mina(celda) && es_valida(juego.tablero, fila, columna)) { //chequeo posicion válida y que no contenga mina
		
		poner_mina(celda); 
		poner_celda(juego.tablero, fila, columna, celda); 

		//Actualiza posiciones vecinas (numeros):
		for (int i = fila - 1; i <= fila + 1; i++) {
			for (int j = columna - 1; j <= columna + 1; j++) {

				if (es_valida(juego.tablero, i, j) && !es_mina(dame_celda(juego.tablero, i, j))) {
					tCelda celdaVecina = dame_celda(juego.tablero, i, j);

					if (esta_vacia(celdaVecina)) { //si celda esta VACIA pone estado en NUMERO y le asigna un 1
						poner_numero(celdaVecina, 1);
					}
					else {
						celdaVecina.numero = dame_numero(celdaVecina) + 1; //suma 1 al numero que ya tenía la celda
					}
					poner_celda(juego.tablero, i, j, celdaVecina);
				}
			}
		}
	}
}

void juega(tJuego& juego, int fila, int columna, tListaPosiciones& lista_pos, tListaUndo& lista_undo) { //intenta descubrir la celda de la pos marcada

	tCelda celda = dame_celda(juego.tablero, fila, columna);

	if (es_valida(juego.tablero, fila, columna)) {				// ver su valida la pos 

		if (!es_visible(celda) && !esta_marcada(celda)) {		// si no marcada y no visible
			
			if (esta_vacia(celda)) {
				descubrir_vacia(juego, fila, columna, lista_pos);
			}
			else {
				descubrir_celda(celda);								//descubre celda
				poner_celda(juego.tablero, fila, columna, celda);

				inicializar(lista_pos);								//incializo porque sino lista_pos acumula las anteriores jugadas
				insertar_final(lista_pos, fila, columna);		    //añades jugada en la listaPosiciones
				juego.num_jugadas++;
			}
		}
	}
	if (fila != -3 && columna != -3) { //comando para hacer el undo
		insertar_final(lista_undo, lista_pos); //inserto toda la lista_posiciones de esa jugada en mi lista_undo
	}
}

//si se llama a esta función significa que la celda que estaba en la pos [fila][columna] estaba vacía
//Asi que se busca descubrir sus 8 adyacentes (si entre esas 8 hay otra vacía --> f. recursiva)
void descubrir_vacia(tJuego& juego, int fila, int columna, tListaPosiciones& lista_pos) {
	
	if (es_valida(juego.tablero, fila, columna)) {

		tCelda celda = dame_celda(juego.tablero, fila, columna);

		descubrir_celda(celda);
		poner_celda(juego.tablero, fila, columna, celda);
		insertar_final(lista_pos, fila, columna); //voy añadiendo las posiciones descubiertas en la lista_pos

		for (int i = fila - 1; i <= fila + 1; i++) {
			for (int j = columna - 1; j <= columna + 1; j++) {

				if (es_valida(juego.tablero, i, j)) {

					tCelda celdaAdy = dame_celda(juego.tablero, i, j);

					if (esta_vacia(celdaAdy) && !es_visible(celdaAdy)) {
						descubrir_vacia(juego, i, j, lista_pos);
					}
					else if (contiene_numero(celdaAdy) && !es_visible(celdaAdy)){

						descubrir_celda(celdaAdy);
						poner_celda(juego.tablero, i, j, celdaAdy);
						insertar_final(lista_pos, i, j); 
					}
				}
			}
		}
	}
}

int calcula_nivel(tJuego &juego) {

	int dimension = num_filas(juego.tablero) * num_columnas(juego.tablero);
	int dificultad = dimension / juego.num_minas;

	return dificultad; //cuanto mayor es el número más fácil es el juego
}