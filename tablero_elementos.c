//tablero v3.0


#include <stdio.h>
#include "tablero_elementos.h"


void setTablero (tab *pTab, char ficha[][DCOL], int coordX, int coordY){
	
	int i,j;
	int m =0;
	int k =0;
	
	for (i = coordX; i<(coordX+(DFIL-1)); i++){		//Bucle que introduce la ficha peon en la matriz.
			
		for (j = coordY; j<(coordY+(DCOL-1)); j++){
				
			pTab->coordAbsolutas[i][j]=ficha[k][m];
			m++;
		}
		m=0;
		k++;
	}
	
//	i = toRelX(coordX);
//	j = toRelY(coordY);
	
	pTab->coordRelativas[i][j] = 1;	
}

void borrarTablero (char dTab[][DIMTAB_Y], int coordX, int coordY){
	
	int i, j;
	
	for ( i = coordX; i<(coordX+(DFIL-1)); i++){
		
		for ( j = coordY; j < ( coordY +(DCOL-1)); j++)
			dTab[i][j] = ' ';
	}
}
