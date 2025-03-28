#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

#include "colors.h"
#include "inputOutput.h"
#include "juego.h"
#include "listaPosiciones.h"
#include "listaUndo.h"


int main() {
    tJuego juego{};
  
    inicializar(juego);

    cout << "NOMBRE ARCHIVO: ";
    string filename;
    cin >> filename;
    if (leer_archivo(juego, filename)) {
        tListaPosiciones lista_pos;
        tListaUndo lista_undo;
        inicializar(lista_pos);
        inicializar(lista_undo, lista_pos);

        mostrar_juego_consola(juego);
        int fila = 0, columna = 0;
        pedir_pos(fila, columna);
        juega(juego, fila, columna, lista_pos, lista_undo);
        comandos_especiales(juego, fila, columna, lista_undo);

        //repite mientras el juego no esté acabado:
        while (!esta_terminado(juego, fila, columna) && !forzar_finalizacion(fila, columna)) {
            mostrar_juego_consola(juego);
            pedir_pos(fila, columna);
            comandos_especiales(juego, fila, columna, lista_undo);
            juega(juego, fila, columna, lista_pos, lista_undo);
        }
        mostrar_juego_consola(juego); //muestra una ultima vez para que se vea la posicion de la mina explotada

        if (esta_terminado(juego, fila, columna) || forzar_finalizacion(fila, columna)) {
            if (forzar_finalizacion(fila, columna)) {
                cout << "JUEGO FINALIZADO CON OPERANDO (-1, -1)!!! " << endl;
            }
            else if (esta_completo(juego)) {
                cout << "GANASTE!!! " << endl << "\nJUEGO TERMINADO." << endl;
            }
            else cout << "MINA EXPLOTADA!!! " << endl << "\nJUEGO TERMINADO." << endl;

        }
    }
   
    return 0;
}

