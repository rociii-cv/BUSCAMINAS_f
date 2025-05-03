
//MICAELA AGNOLINI Y ROCIO CARVAJAL
//Grupo F

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
#include "listaJuegos.h"


int main() {

    tJuego juego{};
    inicializar(juego);

    tListaJuegos lista_juegos{};
    inicializar(lista_juegos);

    cout << "Juego nuevo (opcion 1) o juego existente (opcion 2): ";
    int opcion;
    cin >> opcion;

    bool algun_juego_cargado = false; //devuelve si algún juego fue cargado

    switch (opcion)
    {
    case 1:

        cout << "Numero de filas (>=2) y columnas (>=2) del tablero: ";
        int fil, cols;
        cin >> fil >> cols;
        cout << "Numero de minas (<8): ";
        int num_minas;
        cin >> num_minas;
        //LLAMAR A juego_aleatorio()
        /*if (juego_aleatorio()) {
            algun_juego_cargado=true;
        }*/   

        break;

    case 2:
        //si no hay juegos en el fichero se crea de forma aleatoria un nuevo juego: juego_aleatorio()
        if (cargar_juegos(lista_juegos)) { //cargo fichero con la lista de juegos 

            algun_juego_cargado = true;
            mostrar_juegos(lista_juegos);

            cout << "Selecciona la partida: ";
            int partida;
            cin >> partida;

            //chequeo que el puntero apunte a algo, y que la opcion seleccionada (partida) sea válida:
            if (lista_juegos.lista!= NULL && (partida < lista_juegos.cont && partida >= 0)) {
                juego = *(lista_juegos.lista[partida]); //cargo ese juego seleccionado
            }
        }
        break;

    default:
        cout << "Opcion no valida" << endl;
        break;
    }

    if (algun_juego_cargado) { //si se logró cargar un juego de la lista o crear uno existente se comienza a jugar.

        tListaUndo lista_undo;
        inicializar(lista_undo);
        tListaPosiciones lista_pos;
        inicializar(lista_pos);

        mostrar_juego_consola(juego); //se muestra el juego, con encabezado, num jugadas...
        cout << endl;

        int fila = 0, columna = 0;

        pedir_pos(fila, columna);
        juega(juego, fila, columna, lista_pos, lista_undo); 
        comandos_especiales(juego, fila, columna, lista_undo);

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
            else if (esta_completo(juego)) { 
                cout << "GANASTE!!! " << endl << "\nJUEGO TERMINADO." << endl;
            } 
            else cout << "MINA EXPLOTADA!!! " << endl << "\nJUEGO TERMINADO." << endl;
        }
    }
   
    return 0;
}

