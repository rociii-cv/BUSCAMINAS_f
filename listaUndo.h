#pragma once
#ifndef listaUndo_h
#define listaUndo_h
#include "listaPosiciones.h"

const int MAX_UNDO = 5; 

typedef struct {
	tListaPosiciones lista[MAX_UNDO];
	int cont;
} tListaUndo;

void inicializar(tListaUndo& lista_undo);
void insertar_final(tListaUndo& lista_undo, tListaPosiciones lista_pos);
void ultimos_movimientos(tListaUndo &lista_undo);

#endif 