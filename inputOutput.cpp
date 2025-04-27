#include "inputOutput.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

#include "juego.h"
#include "listaUndo.h"
#include <cctype>
#include <string>

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

        int fils, cols;
        archivo >> fils >> cols >> juego.num_minas;
        inicializar_tablero(juego.tablero, fils, cols);

        for (int i = 1; i <= juego.num_minas; i++) {
            int minaFila, minaColumna;
            archivo>> minaFila >> minaColumna;
            poner_mina(juego, minaFila, minaColumna);
        }
    }

    archivo.close();
    return open;
}

int comprobarNum(string caracter) {// funcion para comprobar que lo que introduce el user
    bool valido = true;            //es un numero valido (teneiendo en cuenta los comandos especiales)
    int numero;
    int longitud = caracter.length();// para leer el array del caracter introducido

    if (caracter[0] != '-' && !isdigit(caracter[0])) valido = false; //si el caracter es distinto de - y ademas no es numero-->FALSE
    if (longitud == 1 && caracter[0] == '-') valido = false;//si el caracter tiene longitud 1 y es - -->FALSE (pq queremos tener en cuenta el - solo para los comandos especiales, por el solo seria una pos incorrecta)
    
    if (valido) {
        for (int i = 1; i < caracter.length(); i++) {// for para recorrer el array del caracter 
            if (!isdigit(caracter[i])) { // si no tiene digito -->FALSE
                valido = false;
            }
        }
    }
    //si son digitos 
    if (valido) {// si el string es valido
        numero = stoi(caracter);//funcion que me convierte el string en un int
    }
    else { // si no es valido, te devuelve cualquier nº (p.e -10) 
        numero = -10;// valor negativo, distinto de -1 -2 -3 (comandos especiales), para que no se confunda con una casilla (te tiene que devolver algo si o si) 
    }
    return numero;

}


void pedir_pos(int& fila, int& columna) { //pedir posicion al user, llamando a la fun q comprueba si esa pos es valida (q no sea un caracter extraño)
    string strFil, strCol;
    cout << "-Fila: ";
    cin >> strFil;
    fila = comprobarNum(strFil);
    cout << "-Columna: ";
    cin >> strCol;
    columna = comprobarNum(strCol);
}

void comandos_especiales(tJuego& juego, int fila, int columna, tListaUndo& lista_undo) {

    if (fila == -1 && columna == -1) {
        forzar_finalizacion(fila, columna); //fun de salirse del juego antes de acabar
    }

    else if (fila == -2 && columna == -2) { //marcar, desmarcar
        cout << "\nPosicion que se quiere marcar o desmarcar:" << endl << endl;;
        pedir_pos(fila, columna);

        tCelda celda= dame_celda(juego.tablero, fila, columna);
        if (esta_marcada(celda)) {//no se puede hacer, pq accedes a valores privados del tablero (VIOLAS PCPIO MODULARIDAD)

            desmarcar_celda(celda);
        }
        else {
            marcar_celda(celda);
        }
        poner_celda(juego.tablero, fila, columna, celda);
    }

    else if (fila == -3 && columna == -3) { //hacer undo

        if (lista_undo.cont < 0) {
            cout << "MAXIMO ALCANZADO: ya no se pueden hacer mas undo" << endl;
        }
        else {
            cout << "Deshaciendo movimiento..." << endl;
            tListaPosiciones lista_pos = (ultimos_movimientos(lista_undo));
            int cont = longitud(lista_pos);
            for (int i = 0; i < cont; i++) {
                int x = dame_posX(lista_pos, i);
                int y = dame_posY(lista_pos, i);

                tCelda celda= dame_celda(juego.tablero, x, y);
                ocultar_celda(celda);//ocultas las celdas descubiertas en el ultimo mov
                poner_celda(juego.tablero, x, y, celda);
            }
            lista_undo.cont--;//decrementas cont pq esa jugada ya no esta, la has deshecho
        }      
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

void mostrar_celda(tJuego &juego, int fila, int columna) {
    
    tCelda celda = dame_celda(juego.tablero, fila, columna);

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

void mostrar_cabecera(tJuego juego) {
    cout << endl;
    cout << "            BUSCAMINAS" << endl;
    cout << "           ------------" << endl;
}

void mostrar_juego_consola(tJuego &juego) {
    
    // mostrar cabecera FUNCION
    mostrar_cabecera(juego); 
   
    // mostrar el número de jugadas 
    cout << "Numero de Jugadas: " << juego.num_jugadas << endl << endl;

    cout << "\t  |";

    int tableroCols= num_columnas(juego.tablero);
    for (int col = 0; col < tableroCols; col++) {
        cout << LBLUE << setw(N_HUECOS) << col << RESET << '|';
    }
    cout << endl;

    // mostrar separador
    mostrar_separador(juego);

    // mostrar tablero:
    int tableroFils = num_filas(juego.tablero);
    for (int f = 0; f < tableroFils; f++) {
        // mostrar numero de fila
        cout << "\t" << LBLUE << setw(2) << f << RESET << '|';
        // mostrar la fila
        for (int c = 0; c < tableroCols; c++) {
            mostrar_celda(juego, f, c);
            cout << '|';
        }
        cout << endl;

        mostrar_separador(juego);
    }
    cout << endl;
}


