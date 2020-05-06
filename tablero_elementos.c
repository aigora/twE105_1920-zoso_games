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


void getFicha(char dFicha[][DCOL], char dir[]){
	
	int i=0,j=0;
	char aux;
	FILE *pTFile;
	pTFile = fopen(dir,"r");
	
	while(fscanf(pTFile,"%c",&aux) != EOF){
		
		dFicha[i][j] = aux;
		
		if (aux == '\n'){
			j=-1;
			i++;
		}

		j++;
	}
	
	fclose(pTFile);			
}

coord getCoordIni(int jug, int i){
	
	coord paso[DIM_PIEZASJ];
	coord iniJ1[DIM_PIEZASJ]={	{POS1J1_X, POS1J1_Y}, {POS2J1_X, POS2J1_Y}, {POS3J1_X, POS3J1_Y}, {POS4J1_X, POS4J1_Y}, {POS5J1_X, POS5J1_Y}, {POS6J1_X, POS6J1_Y}, {POS7J1_X, POS7J1_Y}, {POS8J1_X, POS8J1_Y}	};
	coord iniJ2[DIM_PIEZASJ]={	{POS1J2_X, POS1J2_Y}, {POS2J2_X, POS2J2_Y}, {POS3J2_X, POS3J2_Y}, {POS4J2_X, POS4J2_Y}, {POS5J2_X, POS5J2_Y}, {POS6J2_X, POS6J2_Y}, {POS7J2_X, POS7J2_Y}, {POS8J2_X, POS8J2_Y}	};
	
	int k;
	
	for (k=0;k < DIM_PIEZASJ;k++){
		
		if (jug == 1)
			paso[k] = iniJ1[k];
			
		if (jug ==2)
			paso[k] = iniJ2[k];  		
	}

	return paso[i];

}
