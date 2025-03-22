#include "inputOutput.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include "juego.h"

using namespace std;


const char CHAR_MINA = '*';  // Mina

//LEE ARCHIVO INICIAL
bool leer_archivo(tJuego& juego, string filename) {
    bool open = true;
    ifstream archivo(filename);
    if (!archivo) {
        cerr << "Error al abrir el archivo " << filename << endl;
        open = false;
    }
    if (open) {
        archivo >> juego.tablero.nFils >> juego.tablero.nCols >> juego.num_minas;
        inicializar_tablero(juego.tablero, juego.tablero.nFils, juego.tablero.nCols);

        for (int i = 1; i <= juego.num_minas; i++) {
            int minaFila, minaColumna;
            archivo>> minaFila >> minaColumna;
            poner_mina(juego, minaFila, minaColumna);
        }
    }

    return open;
}

void pedir_pos(int& fila, int& columna) {
    cout << "Fila: ";
    cin >> fila;
    cout << "Columna: ";
    cin >> columna;
}

void comandos_especiales(tJuego& juego, int fila, int columna) {
    if (fila == -1 && columna == -1) {
        forzar_finalizacion(fila, columna);
    }
    else if (fila == -2 && columna == -2) {
        cout << "Posicion que se quiere marcar o desmarcar:" << endl;
        pedir_pos(fila, columna);
        if (esta_marcada(juego.tablero.datos[fila][columna])) {
            desmarcar_celda(juego.tablero.datos[fila][columna]);
        }
        else {
            marcar_celda(juego.tablero.datos[fila][columna]);
        }
    }
    else if (fila == -3 && columna == -3) { 
        //UNDO
    }
}

void color_numero(int numero) {
    switch (numero) {
    case 1: cout << BLUE; break;
    case 2: cout << GREEN; break;
    case 3: cout << RED; break;
    case 4: cout << DBLUE; break;
    case 5: cout << DGREEN; break;
    case 6: cout << DRED; break;
    default:
        break;
    }
}


void mostrar_separador(tJuego juego) {
    cout << "\t -+";
    for (int col = 0; col < juego.tablero.nCols; ++col) {
        cout << setw(N_HUECOS + 1) << setfill('-') << '+' << setfill(' ');
    }
    cout << endl;
}

void mostrar_celda(tJuego juego, int fila, int columna) {
    tCelda celda = juego.tablero.datos[fila][columna];

    if (!celda.visible && !celda.marcada) { //si está oculta y no marcada
        cout << BG_GRAY << GRAY << N_HUECOS << setfill(' ') << ' ' << RESET;
    }
    else {
        cout << BG_BLACK << BLACK;
        if (!celda.marcada) {
            if (celda.estado == MINA) {
                cout << RED << setw(N_HUECOS) << setfill(' ') << CHAR_MINA << RESET;
            }
            else {
                if (celda.estado == VACIA) {
                    cout << setw(N_HUECOS) << setfill(' ') << ' ' << RESET;
                }
                else {
                    if (celda.estado == NUMERO) {
                        int numero = celda.numero;
                        color_numero(numero);
                        cout << setw(N_HUECOS) << setfill(' ') << numero << RESET;
                    }
                    else {
                        cout << BG_RED << RED << setw(N_HUECOS) << setfill(' ') << ' ' << RESET;
                    }
                }
            }
        }
        else { //COLOR NARANJA SI LA CELDA ESTÁ MARCADA
            cout << BG_ORANGE << ORANGE << setw(N_HUECOS) << setfill(' ') << ' ' << RESET;
        }
    }
}


void mostrar_juego_consola(const tJuego& juego) {
    
    // mostrar el número de jugadas del juego
    
    // mostrar cabecera 
    cout << "\t  |";
    for (int col = 0; col < juego.tablero.nCols; col++) {
        cout << LBLUE << setw(N_HUECOS) << col << RESET << '|';
    }
    cout << endl;

    // mostrar separador
    mostrar_separador(juego);

    // mostrar tablero:
    for (int f = 0; f < juego.tablero.nFils; f++) {
        // mostrar numero de fila
        cout << "\t" << LBLUE << setw(2) << f << RESET << '|';
        // mostrar la fila
        for (int c = 0; c < juego.tablero.nCols; c++) {
            mostrar_celda(juego, f, c);
            cout << '|';
        }
        cout << endl;

        mostrar_separador(juego);
    }
    cout << endl;
}


