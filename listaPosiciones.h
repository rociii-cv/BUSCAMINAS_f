#ifndef listaPosiciones_h
#define listaPosiciones_h
using namespace std; 

const int MAX_LISTA = 5;

typedef struct {
	int posx;
	int posy;
} tPosicion;

typedef struct {
	tPosicion* lista;
	int cont;
	int capacidad;
} tListaPosiciones;

void inicializar(tListaPosiciones& lista_pos);
void insertar_final(tListaPosiciones& lista_pos, int x, int y);
int longitud(tListaPosiciones& lista_pos);
int dame_posX(tListaPosiciones& lista_pos, int i);
int dame_posY(tListaPosiciones& lista_pos, int i);

#endif
