#pragma once
#ifndef celda_h
#define celda_h

typedef enum { NUMERO, VACIA, MINA } tEstado; 

typedef struct {
	bool visible;
	tEstado estado;
	int numero;
	bool marcada;
} tCelda;

void inicializar(tCelda& celda);
tEstado dame_estado(tCelda celda); 
int dame_numero(tCelda celda); 
bool es_visible(tCelda celda);
bool es_mina(tCelda celda);
bool esta_vacia(tCelda celda);
bool contiene_numero(tCelda celda);
bool esta_marcada(tCelda celda);
void descubrir_celda(tCelda& celda);
void ocultar_celda(tCelda& celda);
void poner_mina(tCelda& celda);
void marcar_celda(tCelda& celda);
void desmarcar_celda(tCelda& celda); 
void poner_numero(tCelda& celda, int num);

#endif