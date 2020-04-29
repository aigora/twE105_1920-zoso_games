#include <stdio.h>
 
#define DIMTAB_X 63			//Dimensi�n del tablero(impresi�n).
#define DIMTAB_Y 146		//Dimensi�n del tablero(impresi�n).
#define DIMTAB_REL 10		//Dimensi�n del tablero relativa a las casillas.
#define DFIL 6 				//Desplazamiento de fila.
#define DCOL 14 			//Desplazamiento de columnas.
#define ZFIL 55 			//'Cero' de las filas.
#define ZCOL 5				//'Cero' de las columnas.
#define MFIL 7 				//M�ximo de las filas.
#define MCOL 117 			//Maximo de las columnas. 
#define DIM_PIEZASJ 8		//Dimensi�n arreglo de piezas.(8 piezas por jugador).

#define DIRTAB "prTabV2.txt" //Direcci�n del archivo del tablero.(*INNECESARIO AQU� YA QUE SOLO LO LLAMAMOS UNA VEZ*)

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

