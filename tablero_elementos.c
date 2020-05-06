//tablero v3.0


#include <stdio.h>
#include "tablero_elementos.h"

void iniTablero(tab *pTablero, char dir[]){
	
	int i=0, j=0;
	FILE *pTFile;
	char aux;
	pTFile = fopen(dir,"r");
	
	while(fscanf(pTFile,"%c",&aux) != EOF){
		
		pTablero->coordAbsolutas[i][j] = aux;
		
		if (aux == '\n'){
			j=-1;
			i++;
		}
	j++;
	}

	fclose(pTFile);		
	
	for (i=0; i < DIMTAB_REL; i++){
		for (j=0 ; j < DIMTAB_REL; j++){
			
			pTablero->coordRelativas[i][j] = 0;
		}
	}	
}

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

//void imprimirBool ( _Bool bTab[][DIMTAB_REL]){
//	
//	int i, j;
//	
//	for (i = 0; i < 10; i++){
//			
//		for (j = 0; j<10; j++){
//				
//			printf("%d",bTab[i][j]);
//		}
//		
//		printf("\n");
//	}		
//}
