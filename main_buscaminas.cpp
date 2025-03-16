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


int main() {
    tJuego juego{};
  
    inicializar(juego);

    cout << "NOMBRE ARCHIVO: ";
    string filename;
    cin >> filename;
    if (leer_archivo(juego, filename)) {
        tListaPosiciones lista_pos;
        inicializar(lista_pos);

        mostrar_juego_consola(juego);
        int fila = 0, columna = 0;
        pedir_pos(fila, columna);
        juega(juego, fila, columna, lista_pos);

        //repite mientras el juego no est� acabado:
        while (!esta_terminado(juego, fila, columna)) {
            mostrar_juego_consola(juego);
            pedir_pos(fila, columna);
            juega(juego, fila, columna, lista_pos);
        }
        mostrar_juego_consola(juego); //muestra una ultima vez para que se vea la posicion de la mina explotada

        if (esta_terminado(juego, fila, columna)) {
            cout << "MINA EXPLOTADA!!! " << endl << "\nJUEGO TERMINADO." << endl;
        }
    }

   
    return 0;
}

