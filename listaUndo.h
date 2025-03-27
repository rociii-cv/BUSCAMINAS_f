#ifndef listaUndo_h
#define listaUndo_h
#include "listaPosiciones.h"

const int MAX_UNDO = 5; 

typedef struct {
	tListaPosiciones lista[MAX_UNDO];
	int cont;
	//int pos_final = MAX_UNDO - 1; 
} tListaUndo;

void inicializar(tListaUndo& lista_undo);
void insertar_final(tListaUndo& lista_undo, tListaPosiciones lista_pos);
tListaPosiciones ultimos_movimientos(tListaUndo lista_undo);

#endif 