#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include "colors.h"

using namespace std;

#include "inputOutput.h"
#include "juego.h"


int main() {
    tJuego juego{};
  
    inicializar(juego);
    leer_archivo(juego);

    mostrar_juego_consola(juego);
    return 0;
}

