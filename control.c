//Cabecera de Control.
//
//Distintas funciones para determinar acciones y reglas del juego.



#include <stdio.h>
#include "control.h"
		

coord getCoordInput( char *mInfoJ, char *mInfoA){
	
	int col, fil;
	const int mcol = 'A', mfil = 1;
	coord cInput = {0,0};
	
	do {
		
		printf ("\n%s seleccione las coordenadas de la %s \n", mInfoJ, mInfoA);
		fflush (stdin);
		scanf ("%c%d", &col, &fil);
	}while ( (col < 'A') || (col>'J') || (fil < 1) || (fil > 10) );

	//Establecemos las coordenadas a relativas(origen A1 (5,55):
	col -=mcol;
	fil -=mfil;	
	cInput.x = ZFIL - DFIL*fil;
	cInput.y = ZCOL + DCOL*col;
	
	return cInput;	
}

_Bool checkCoordP(pieza *pJT, pieza *pJNT, coord seleccionada, int *nPos){
	
	_Bool continuar;
	
	int i, nada = 0;
	
	for ( i=0; i<8; i++){
		
		if(( pJT[i].cActual.x == seleccionada.x)&&(pJT[i].cActual.y == seleccionada.y)){
			*nPos = i;
			continuar = 1;
		}
		else 
			nada++;
	}
	
	for ( i=0; i<8; i++){
		
		if(( pJNT[i].cActual.x == seleccionada.x)&&(pJNT[i].cActual.y == seleccionada.y)){
			continuar = 0;
			printf ("Esa pieza le pertenece al otro jugador\n");
		}
		else 
			nada++;
	}
	
	if (nada == 16){
		continuar = 0;
		printf("No hay ficha en esa casilla\n");
	}
	
	return continuar;
}

_Bool checkCoordC(pieza *pJT, pieza *pJNT, pieza *pJ1, pieza *pJ2, coord temp, coord *nJ){
	
	_Bool continuar = 0;
	int nada = 0; 
	int i;
	
		
	for (i= 0; i<8; i++){
			
		if (( pJT[i].cActual.x == temp.x)&&( pJT[i].cActual.y == temp.y)){
			continuar = 0;
			printf ("En esa casilla ya hay una pieza.\n");
			break;
		}else if (( pJNT[i].cActual.x == temp.x)&&( pJNT[i].cActual.y == temp.y)){
			continuar = 0;
			printf ("En esa casilla ya hay una pieza.\n");
			break;
		}else 
			continuar = 1;
				
	}
	
	for (i=0; i<24; i++){
		
		if (( nJ[i].x == temp.x)&&( nJ[i].y == temp.y)){
			continuar = 0;
			printf("No puedes mover una pieza a esa casilla.\n");
		}	
	}
	
	
	if ((pJT == pJ1) && (temp.y == 131)){
		continuar = 0;
		printf("El Jugador 1 no puede salir del tablero en esa direccion\n");
	}
	
	if (( pJT == pJ2) && (temp.x == 1)){
		continuar = 0;
		printf("El jugador 2 no puede salir del tablero en esa direccion\n");
	}
	
	return continuar;	
}

//Función que calcula la cantidad de movimiento:

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

_Bool checknMov(coord cFicha, coord cDestino, int nMov){ //funcion que va a comprobrar si es posible moverse hasta el destino 
	
	int nMovRel, nMovCol, nMovFil; // nMovRel: variable aux para acotar las iteraciones; nMovX: distancia en columnas hasta el destino; nMovY: distancia hasta el destino en filas.
	_Bool cont = 0;
	
	nMovCol = abs(cDestino.y - cFicha.y) / DCOL; 
	nMovFil = abs(cDestino.x - cFicha.x) / DFIL;
	nMovRel = nMov - nMovCol - nMovFil; 
	
	if (nMovRel < 0){  // Comprueba si esta demasiado lejos de primeras.
	
		printf("No dispone de la cantidad de movimiento suficiente para moverse a la casilla seleccionada.\n");
	}
	else cont =1;


	return cont;
}

_Bool checkMovimiento( _Bool tabRel[][DIMTAB_REL], _Bool track [][DIMTAB_REL], int x, int y, coord destino, int nMov){
	
	_Bool comprobar;	// Se utiliza para gestionar el seguimiento.
	int dx, dy;		//Variables para desplazar según la ruta preferente. ( La más directa sin contar obstáculos ).
	coord actual = {x,y}; 	//Coordenas actuales con las que se comprobará la ruta preferente. 
	
	// Comprobamos si esta en el tablero, si queda movimiento, si hay obstáculos en el tablero o si ha estado en esa casilla antes.
	if ( x < 0 || x > 9 || y < 0 || y > 9 || nMov < 0 || tabRel[x][y] || track[x][y] ) 
		return 0;

	setDirecciones( actual, destino, &dx, &dy);		// Establecemos la dirección de los desplazamientos.
	track [x][y] = 1;	//Marcamos la casilla en la que estamos para el seguimiento.	

	// Si se ha alcanzado la casilla destino devolvemos 'true'.
	// Nos momevos primero por columnas y después por filas.
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

void iniTrack( _Bool v[][DIMTAB_REL]){
	
	int i,j;
	
	for (i = 0; i <10 ; i++ ){
		
		for (j=0; j<10; j++)
			v[i][j] = 0;				
	}
}

void setDirecciones(coord temp, coord destino, int *dx, int *dy){
	
	if ( temp.x <= destino.x)  //La ficha está por encima de la casilla destino -> avanzamos hacia abajo.
		*dx = 1;
	else
		*dx = -1;	//Hacia arriba.
		
	if ( temp.y <= destino.y)  // La ficha está a la izquierda de la casilla destino -> avanzamos a la derecha.
		*dy = 1;
	else 
		*dy = -1;	//Hacia la izquierda.
		
}

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

_Bool finTurno(){
	
	char aux;
	_Bool retorno;
	
	do {
		
		printf ("Continuar la partida? (S/N)\n");
		fflush(stdin);
		scanf("%c",&aux);
		if ( aux == 'S') retorno = 1;
		else if (aux == 'N') retorno = 0;
		else printf("Opcion no valida\n");
		
	}while ( aux != 'S' && aux != 'N' );
	
	return retorno;

}
