//tablero v3.0

#include "tablero_elementos.h"


void setCoordIni( coord *cIniJ1, coord *cIniJ2 ){
	
	int i;
	
	FILE *pf;
	pf= fopen ("CoordIni.txt", "r");
	
	for ( i = 0; i < DIM_PIEZASJ; i++){
		
		fscanf(pf, "%d,%d\t%d,%d\n", &cIniJ1[i].x, &cIniJ1[i].y, &cIniJ2[i].x, &cIniJ2[i].y);
	}
	
	fclose(pf);
}

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
	
	//Añadimos el centro.
	pTablero->coordRelativas[5][4] = 1;
}

void setTablero (tab *pTab, char ficha[][DCOL], int coordX, int coordY){
	
	
	coord temp;
	coord tempRel;
	
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
	
	temp.x = coordX;
	temp.y = coordY;
	
	tempRel = toRel(temp);
	
	pTab->coordRelativas[tempRel.x][tempRel.y] = 1;	

}


void borrarTablero (char dTab[][DIMTAB_Y], int coordX, int coordY){
	
	int i, j;
	
	for ( i = coordX; i<(coordX+(DFIL-1)); i++){
		
		for ( j = coordY; j < ( coordY +(DCOL-1)); j++)
			dTab[i][j] = ' ';
	}
}

void imprimir (char dTab [][DIMTAB_Y]){
	
	int i, j;
	
	for (i = 0; i < DIMTAB_X; i++){
			
		for (j = 0; j < DIMTAB_Y; j++){
				
			printf("%c",dTab[i][j]);
		}
	}
	
	printf("\n");	
}

coord toRel ( coord absolutas){
	
	coord temp;
	
	temp.x = (DIMTAB_REL - 1) - (ZFIL - absolutas.x)/ DFIL;
	temp.y = (absolutas.y - ZCOL)/DCOL;
	
	return temp; 
	
}

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

void saveGame(pieza *pJT, pieza *pJNT, pieza* pJ1, pieza*pJ2, int nPiezaJ1, int nPiezaJ2){
	
	int n, limite, i, j, turno, opcion;
	_Bool sobrescribir = 1;
	char aux, nombre[20];
	partida listaPartidas[MAX_SAVE];
	FILE *pf;
		
	n = leerPartidasGuardadas(pf, listaPartidas); //leerPartidasGuardadas.
	
	do{
	
		imprimirLista( listaPartidas, n, &limite, 1); //imprimir lista
		opcion = seleccionarPartidaGuardada( limite, n, &sobrescribir ); //seleccionar hueco de guardado.
		
	}while (!sobrescribir);
	

	if (opcion > n){
		
		printf ( "Elige un nombre para guardar la partida (max 20 caracteres):\n");
		fflush(stdin);
		scanf( "%20[^\n]",nombre);
		strcpy(listaPartidas[opcion-1].nombre, nombre);
		n++;
	}
	
	if ( pJT == pJ1) turno = 1;
	else turno = 2;
 
	listaPartidas[opcion - 1].turno = turno;
	listaPartidas[opcion - 1].nPiezJ1 = nPiezaJ1;
	listaPartidas[opcion - 1].nPiezJ2 = nPiezaJ2;
				
	for ( i = 0; i < DIM_PIEZASJ; i++){
		
		listaPartidas[opcion-1].coordSaveJ1[i] = pJ1[i].cActual;  
		listaPartidas[opcion-1].coordSaveJ2[i] = pJ2[i].cActual;
	} 
	
	pf = fopen("partidasGuardadas.txt", "w");
	if (pf==NULL) printf("No se puede acceder al fichero.\n");
	
	fprintf( pf, "%d\n", n );	
	
	for ( i = 0; i < n; i++){
		
		fprintf(pf, "%s;%d;%d;%d\n", listaPartidas[i].nombre, listaPartidas[i].turno, listaPartidas[i].nPiezJ1, listaPartidas[i].nPiezJ2);	
			
			for ( j = 0; j < DIM_PIEZASJ*2; j++){
				
				if ( j < DIM_PIEZASJ){
					
					fprintf(pf,"%d,%d\n", listaPartidas[i].coordSaveJ1[j].x, listaPartidas[i].coordSaveJ1[j].y);
					
				}else{
					
					fprintf(pf,"%d,%d\n", listaPartidas[i].coordSaveJ2[j - DIM_PIEZASJ].x, listaPartidas[i].coordSaveJ2[j - DIM_PIEZASJ].y);					
				}
			}
	}
	
	printf("Se ha gurdado la partida.\n");

	fclose(pf);
}

int leerPartidasGuardadas(FILE *pf, partida *listaPartidas){
	
	int i,j,r;
	
		pf = fopen("partidasGuardadas.txt", "r");
	
	fscanf(pf, "%d\n", &r);
		
	for( i = 0; i < r; i++ ){
			
		fscanf(pf, "%[^;];%d;%d;%d\n", listaPartidas[i].nombre, &listaPartidas[i].turno, &listaPartidas[i].nPiezJ1, &listaPartidas[i].nPiezJ2);
			
		for ( j = 0; j < DIM_PIEZASJ*2; j++){
				
				if ( j < DIM_PIEZASJ){
					
					fscanf(pf,"%d,%d\n", &listaPartidas[i].coordSaveJ1[j].x, &listaPartidas[i].coordSaveJ1[j].y);				
				}else{
					
					fscanf(pf,"%d,%d\n", &listaPartidas[i].coordSaveJ2[j - DIM_PIEZASJ].x, &listaPartidas[i].coordSaveJ2[j - DIM_PIEZASJ].y);					
				}
			}	
		}
	
	fclose(pf);
	
	return r;
	
}

void imprimirLista( partida *listaPartidas, int n, int *limite, int tipo){
	
	int i;
	
	printf ( "Seleccione donde quiere guardar la partida (Maximo 5 partidas):\n");
	
	for ( i = 0; i < n; i++){
		
		printf( "%d %s\n", i + 1, listaPartidas[i].nombre);
	}
	
	if ( tipo == 1 ){
	
		if (n < MAX_SAVE){
			 
			printf("%d %s\n", i + 1, "Nuevos datos de guardado\n");
			*limite = n + 1;
			
		}else *limite = n;
	}
}

int seleccionarPartidaGuardada(int limite, int n, _Bool *sobrescribir ){
	
	int opcion;
	int ntemp = n;
	char aux;
	
	do {
			
		fflush(stdin); 	
		scanf( "%d", &opcion);
		
		if ( opcion < 1 || opcion > limite) printf ("No hay una partida guardada en la opcion seleccionada.\n");		

	}while ( opcion < 1 || opcion > limite);
	
	if ( opcion <= ntemp){
		
		do{
				
			printf ("Hay una partida guardada en ese hueco. Desea sobrescribir la partida? (s/n)");
			
			fflush(stdin);
			scanf( "%c", &aux);
			
			if ( aux != 's' && aux != 'n') printf ( "Opcion no valida.\n");
			
		}while ( aux != 's' && aux != 'n');
			
		if ( aux == 's') *sobrescribir = 1;
		else *sobrescribir = 0;
	}
//	}else ntemp++;
	
	
//	*n = ntemp;
		
	return opcion;	
}

void loadGame (tab *pTablero, pieza *J1, pieza *J2, _Bool **load, int **turno, int **nJ1, int **nJ2, _Bool **cJuego  ){
	
	int n, limite, i, j, opcion;
	partida listaPartidas[MAX_SAVE];
	FILE *pf;	
	
	n = leerPartidasGuardadas(pf, listaPartidas); //leerPartidasGuardadas.	
	
	if ( n == 0){
		
		printf ("No hay partidas guardadas.\n");
		**load = 0;
		**cJuego = 0;
		
	}
	else{
		
		**load = 1;
		**cJuego = 1;
		iniTablero(pTablero, DIRTAB);
		
		do{
		
			imprimirLista( listaPartidas, n, &limite, 2);		
			scanf( "%d", &opcion);		

		}while ( opcion < 1 || opcion > limite);
	
		// cargar variables.
		
		**nJ1 = listaPartidas[opcion - 1].nPiezJ1;
		**nJ2 = listaPartidas[opcion - 1].nPiezJ2;
		
		for ( i = 0; i < DIM_PIEZASJ; i++){
		
			J1[i].cActual = listaPartidas[opcion - 1].coordSaveJ1[i];
			if ( (J1[i].cActual.x != -1) && (J1[i].cActual.y != -1) ){
				J1[i].relativas = toRel(J1[i].cActual);
				getFicha(J1[i].dFigura, DIRPEONJ1);
				setTablero( pTablero, J1[i].dFigura, J1[i].cActual.x, J1[i].cActual.y);				
			
			}
			
			J2[i].cActual = listaPartidas[opcion - 1].coordSaveJ2[i];	
			if ( (J2[i].cActual.x != -1) && (J2[i].cActual.y != -1) ){				

				J2[i].relativas = toRel(J2[i].cActual);	
				getFicha(J2[i].dFigura, DIRPEONJ2);
				setTablero( pTablero, J2[i].dFigura, J2[i].cActual.x, J2[i].cActual.y);	
			}
		}
		
		**turno = listaPartidas[opcion - 1].turno;	
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
