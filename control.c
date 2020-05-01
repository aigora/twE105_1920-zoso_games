//Cuerpo de control
//
//Distintas funciones para determinar acciones y reglas del juego.


#include <stdio.h>
#include <string.h>
#include "control.h"

//Funci�n que calcula la cantidad de movimiento:

int nDistMov( pieza *pJT, pieza *pJ1, pieza *pJ2, coord pSelec){
	
	int xFijo = pSelec.x;
	int yFijo = pSelec.y;
	int i, j, nMov=0;
	
	if (pJT == pJ1){	//Si el turno es del jugador 1.
		
		for (i = ZCOL; i <= MCOL; i+=DCOL){	//Contamos las piezas que hay en esa fila.
			
			for ( j =0; j < DIM_PIEZASJ; j++){
				
				if ((( pJ1[j].cActual.x == xFijo)&&(pJ1[j].cActual.y == i)) || (( pJ2[j].cActual.x == xFijo)&&(pJ2[j].cActual.y == i)))
					nMov++;	//Si encontramos piezas las vamos sumando.	
			}
		}
	}else if (pJT == pJ2){	//Si el turno es del jugador 2.
		
		for (i = ZFIL; i>=MFIL; i-=DFIL){	//Contamos las piezas que hay en esa columna.
			
			for ( j =0; j < DIM_PIEZASJ; j++){
				
				if ((( pJ1[j].cActual.x == i)&&(pJ1[j].cActual.y == yFijo)) || (( pJ2[j].cActual.x == i)&&(pJ2[j].cActual.y == yFijo)))	
					nMov++;	//Si encontramos piezas las vamos sumando.
				
			}
		}
	}
		
	return nMov;
}

//Funcion que se encarga de comprobar si realmente nos podemos mover a una casilla con la cantidad de movimientos disponibles teniendo en cuenta otros elementos en el tablero:

_Bool checkMovimiento( _Bool tabRel[][DIMTAB_REL], _Bool track [][DIMTAB_REL], int x, int y, coord destino, int nMov){
	
	_Bool comprobar;	// Se utiliza para gestionar el seguimiento.
	int dx, dy;		//Variables para desplazar seg�n la ruta preferente. ( La m�s directa sin contar obst�culos ).
	coord actual = {x,y}; 	//Coordenas actuales con las que se comprobar� la ruta preferente. 
	
	// Comprobamos si esta en el tablero, si queda movimiento, si hay obst�culos en el tablero o si ha estado en esa casilla antes.
	if ( x < 0 || x > 9 || y < 0 || y > 9 || nMov < 0 || tabRel[x][y] || track[x][y] ) 
		return 0;
		
	setDirecciones( actual, destino, &dx, &dy);		// Establecemos la direcci�n de los desplazamientos.
	track [x][y] = 1;	//Marcamos la casilla en la que estamos para el seguimiento.	

	// Si se ha alcanzado la casilla destino devolvemos 'true'.
	// Nos momevos primero por columnas y despu�s por filas.
	// Si no estamos en la columna de la casilla destino: recursividad primero por columnas.
	// Si hemos alcanzado la columna: recursividad primero por filas.
	if (x == destino.x && y == destino.y){
			return 1;
			
	}else if ( y != destino.y){
		comprobar = ( checkMovimiento(tabRel, track, x, y+dy, destino, nMov - 1) || checkMovimiento(tabRel, track, x+dx, y, destino, nMov-1) || checkMovimiento(tabRel, track, x-dx, y, destino, nMov-1) || checkMovimiento(tabRel, track, x, y-dy, destino, nMov-1) );		
		
	}else if ( x != destino.x){
		comprobar = ( checkMovimiento(tabRel, track, x+dx, y, destino, nMov - 1) || checkMovimiento(tabRel, track, x, y+dy, destino, nMov-1) || checkMovimiento(tabRel, track, x, y-dy, destino, nMov-1) || checkMovimiento(tabRel, track, x-dx, y, destino, nMov-1) );
	}
	
	// Si no se puede dejamos libre el camino que hemos seguido. 
	if (comprobar){				
		return 1;
	}
	else{		
		track[x][y] = 0;
		return 0;
	}
}

//Inicializa/Resetea el track:

void iniTrack( _Bool v[][DIMTAB_REL]){
	
	int i,j;
	
	for (i = 0; i <10 ; i++ ){
		
		for (j=0; j<10; j++)
			v[i][j] = 0;				
	}
}

//Determina la direccion de movimiento para chekMovimiento:

void setDirecciones(coord temp, coord destino, int *dx, int *dy){
	
	if ( temp.x <= destino.x)  //La ficha est� por encima de la casilla destino -> avanzamos hacia abajo.
		*dx = 1;
	else
		*dx = -1;	//Hacia arriba.
		
	if ( temp.y <= destino.y)  // La ficha est� a la izquierda de la casilla destino -> avanzamos a la derecha.
		*dy = 1;
	else 
		*dy = -1;	//Hacia la izquierda.
		
}

//Determina si una pieza a cruzado la meta que le corresponde:

_Bool checkPiezaMeta(pieza *pJT, pieza *J1, pieza *J2, coord *casilla){
	
	_Bool meta; //Bool de retorno;
	
	if ( (pJT == J1) && ( casilla->x == 0))
		meta = 1;
	else if ((pJT == J2) && (casilla->y == 9))
		meta = 1;
	else 
		meta = 0;
		
	return meta;
}
