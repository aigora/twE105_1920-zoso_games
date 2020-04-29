#include <stdio.h>
 
#define DIMTAB_X 63			//Dimensión del tablero(impresión).
#define DIMTAB_Y 146		//Dimensión del tablero(impresión).
#define DIMTAB_REL 10		//Dimensión del tablero relativa a las casillas.
#define DFIL 6 				//Desplazamiento de fila.
#define DCOL 14 			//Desplazamiento de columnas.
#define ZFIL 55 			//'Cero' de las filas.
#define ZCOL 5				//'Cero' de las columnas.
#define MFIL 7 				//Máximo de las filas.
#define MCOL 117 			//Maximo de las columnas. 
#define DIM_PIEZASJ 8		//Dimensión arreglo de piezas.(8 piezas por jugador).

#define DIRTAB "prTabV2.txt" //Dirección del archivo del tablero.(*INNECESARIO AQUÍ YA QUE SOLO LO LLAMAMOS UNA VEZ*)

typedef struct {
	
	char coordAbsolutas[DIMTAB_X][DIMTAB_Y];
	_Bool coordRelativas[DIMTAB_REL][DIMTAB_REL];
}tab;

typedef struct {
	
	int x;	//coordenada fila.
	int y;	//coordenada columna.
}coord;

typedef struct {
	
	char dFigura[5][DCOL];	//Dibujo de la pieza.
//	jugadores pertenencia;
//	int pertenencia;
	coord cActual;			//Cordenadas absolutas(Dibujo).
	coord relativas;		//Coordenadas relativas al tablero de juego.
}pieza;

void iniTablero(tab *pTablero, char[]);

//codigo de prueba 
//void imprimirBool (_Bool [][DIMTAB_REL] ); 

