#pragma once
#ifndef listaPosiciones_h
#define listaPosiciones_h
using namespace std; 

const int MAX_LISTA = 100;

typedef struct {
	int posx;
	int posy;
} tPosicion;

typedef struct {
	tPosicion lista[MAX_LISTA];
	int cont;
} tListaPosiciones;

/*
inicializar(lista_pos);
insertar_final(lista_pos, x, y);
longitud(lista_pos);
dame_posX(lista_pos, i);
dame_posY(lista_pos, i);*/

#endif
