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
  
    inicializar(juego); //inicializamos juego con funcion de juego.cpp

    cout << "NOMBRE ARCHIVO: ";
    string filename;
    cin >> filename;
    if (leer_archivo(juego, filename)) {//metemos archivos que tienen la info del juego
        tListaPosiciones lista_pos;
        tListaUndo lista_undo;
        inicializar(lista_undo, lista_pos);//inicializamos listas undo y pos a 0

        mostrar_juego_consola(juego); //se muestra el juego, con encabezado, num jugadas...
        cout << endl;
        int fila = 0, columna = 0;
        pedir_pos(fila, columna); //usuario inserta pos
        juega(juego, fila, columna, lista_pos, lista_undo); //llamas a juega para q haga lo relacionado con la pos instroducida
        comandos_especiales(juego, fila, columna, lista_undo);// por si el user quiere marcar, undo, o salirse del juego


        //repite mientras el juego no esté acabado:
        while (!esta_terminado(juego, fila, columna) && !forzar_finalizacion(fila, columna)) {
            mostrar_juego_consola(juego);
            cout << endl;
            pedir_pos(fila, columna);
            juega(juego, fila, columna, lista_pos, lista_undo);
            comandos_especiales(juego, fila, columna, lista_undo);
        }
        mostrar_juego_consola(juego); //muestra una ultima vez para que se vea la posicion de la mina explotada

        if (esta_terminado(juego, fila, columna) || forzar_finalizacion(fila, columna)) {
            if (forzar_finalizacion(fila, columna)) { //si user quiere abandonar el juego
                cout << "JUEGO FINALIZADO CON OPERANDO (-1, -1)!!! " << endl;
            }
            else if (esta_completo(juego)) { // si todas las pos q no son mina estan descubiertas
                cout << "GANASTE!!! " << endl << "\nJUEGO TERMINADO." << endl;
            } //si ha explotado una mina
            else cout << "MINA EXPLOTADA!!! " << endl << "\nJUEGO TERMINADO." << endl;

        }
    }
   
    return 0;
}

