#include <stdio.h>
#include <string.h>

#define DIMTAB_X 63		//Dimensión del tablero(impresión).
#define DIMTAB_Y 146		//Dimensión del tablero(impresión).
#define DIMTAB_REL 10		//Dimensión del tablero relativa a las casillas.
#define DFIL 6 			//Desplazamiento de fila.
#define DCOL 14 		//Desplazamiento de columnas.
#define ZFIL 55 		//'Cero' de las filas.
#define ZCOL 5			//'Cero' de las columnas.
#define MFIL 7 			//Máximo de las filas.
#define MCOL 117 		//Maximo de las columnas. 
#define DIM_PIEZASJ 8		//Dimensión arreglo de piezas.(8 piezas por jugador).
#define MAX_SAVE 5

#define DIRTAB "prTabV2.txt" //Dirección del archivo del tablero.(*INNECESARIO AQUÍ YA QUE SOLO LO LLAMAMOS UNA VEZ*)
#include "fichas.h"


typedef struct {
	
	char coordAbsolutas[DIMTAB_X][DIMTAB_Y];
	_Bool coordRelativas[DIMTAB_REL][DIMTAB_REL];
}tab;

typedef struct {
	
	int x;
	int y;		
}coord;

typedef struct {
	
	char dFigura[5][DCOL];
	coord cActual;
	coord relativas;
}pieza;

typedef struct {
	
	char nombre[21];
	int turno;
	coord coordSaveJ1[DIM_PIEZASJ];
	coord coordSaveJ2[DIM_PIEZASJ];
	int nPiezJ1;
	int nPiezJ2;	
}partida;

void iniciarPartida(tab *pTablero, pieza*, pieza*, pieza*, pieza*, int, int *nJ1, int *nJ2, int *pnJ, char *mJ1, char *mJ2, char *mJ, _Bool *rCicloJuego );
void iniTablero(tab *pTablero, char dir[]);
void setTablero (tab *pTab, char ficha[][DCOL], int coordX, int coordY);
void borrarTablero (char dTab[][DIMTAB_Y], int coordX, int coordY);
void imprimir (char dTab [][DIMTAB_Y]);
coord toRel ( coord absolutas);
void getFicha(char dFicha[][DCOL], char dir[]);
coord getCoordIni(int jug, int i);
void saveGame(pieza *pJT, pieza *pJNT, pieza *pJ1, pieza *pJ2, int nPiezaJ1, int nPiezaJ2);
int leerPartidasGuardadas(FILE *pf, partida *listaPartidas);
void imprimirLista( partida *listaPartidas, int n, int *limite, int tipo);
int seleccionarPartidaGuardada(int limite, int *n, _Bool *sobrescribir );
void loadGame (tab *pTablero, pieza *J1, pieza *J2, _Bool **load, int **turno, int **nJ1, int **nJ2, _Bool **cJuego );
//codigo de prueba 
//void imprimirBool (_Bool [][DIMTAB_REL] ); 

