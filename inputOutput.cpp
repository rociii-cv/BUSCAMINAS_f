#include "inputOutput.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

#include "juego.h"
#include "listaUndo.h"
#include "listaJuegos.h"
#include <cctype>
#include <string>

using namespace std;

const char CHAR_MINA = '*';  // Mina


bool leer_archivo(tJuego& juego, string filename) {

    bool open = true;
    ifstream archivo;
    archivo.open(filename);

    if (archivo.is_open()) {

        int fils, cols;
        archivo >> fils >> cols >> juego.num_minas;
        inicializar_tablero(juego.tablero, fils, cols);

        for (int i = 1; i <= juego.num_minas; i++) {
            int minaFila, minaColumna;

            archivo >> minaFila >> minaColumna;
            poner_mina(juego, minaFila, minaColumna);
        }
    }
    else {
        cout << "Error al abrir el archivo " << filename << endl;
        open = false;
    }

    archivo.close();
    return open;
}

bool cargar_juegos(tListaJuegos lista_juegos) {
    bool carga = true;

    cout << "Nombre archivo Lista de juegos: ";
    string file;
    cin >> file;

    ifstream archivo;
    archivo.open(file);

    if (archivo.is_open()) {

        int num_juegos, dimFils, dimCols, num_minas, posx, posy;

        archivo >> num_juegos; //esto no hace falta guardarlo en la lista

        for (int i = 0; i < num_juegos; i++) {
            
            tJuego* ptr;
            ptr = new tJuego;

            archivo >> dimFils >> dimCols;
            inicializar_tablero(ptr->tablero, dimFils, dimCols);

            archivo >> num_minas; 
            ptr->num_minas = num_minas;

            for (int j = 0; j < num_minas; j++) {
                archivo >> posx >> posy;
                poner_mina(*ptr, posx, posy); //*ptr equivale a pasar el juego por referencia
            }

            lista_juegos.lista[i] = ptr;
            lista_juegos.cont++;
        }
    }
    else {
        cout << "Error abriendo lista de juegos" << endl;
        carga = false;
    }
    return carga;
}

void mostrar_juegos(tListaJuegos lista_juegos) {

    cout << "Mostrando lista de jeugos por orden de dificultad..." << endl;

    for (int i = 0; i < lista_juegos.cont; i++) {
        cout << "Juego " << lista_juegos.cont << ":" << endl;
        cout << "   Dimension: " << dame_num_filas(*lista_juegos.lista[i]) << " x "
            << dame_num_columnas(*lista_juegos.lista[i]) << endl;
        cout << "   Minas: " << dame_num_minas(*lista_juegos.lista[i]) << endl;
    }
}

bool guardad_juegos(tListaJuegos* lista_juegos) {
    bool carga = true;

    cout << "Nombre de fichero para almacenar juegos: ";
    string fichero;
    cin >> fichero;

    ofstream archivo;
    archivo.open(fichero);

    if (archivo.is_open()) {





    }
    else {
        cout << "Error abriendo archivo " << fichero << endl;
        carga = false;
    }

    archivo.close();
    return carga;
}

int comprobarNum(string caracter) {
    bool valido = true;  
    int numero;
    int longitud = caracter.length(); 

    if (caracter[0] != '-' && !isdigit(caracter[0])) valido = false; //si el caracter es distinto de - y ademas no es numero-->FALSE
    if (longitud == 1 && caracter[0] == '-') valido = false;        //si el caracter tiene longitud 1 y es - -->FALSE (pq queremos tener en cuenta el - solo para los comandos especiales, por el solo seria una pos incorrecta)
    
    if (valido) {
        for (int i = 1; i < caracter.length(); i++) {
            if (!isdigit(caracter[i])) { // si no tiene digito -->FALSE
                valido = false;
            }
        }
    }
    //si son digitos 
    if (valido) {
        numero = stoi(caracter); //funcion que me convierte el string en un int
    }
    else {
        numero = -10; 
    }
    return numero;
}


void pedir_pos(int& fila, int& columna) { 
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
        if (esta_marcada(celda)) {

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


