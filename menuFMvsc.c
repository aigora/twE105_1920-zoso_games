// Menu switch case.

#include "menuFMvsc.h"

void menuPrincipalSC ( int n, tab *pTablero, pieza *J1, pieza *J2, _Bool *rCicloJuego, _Bool *rSalir, _Bool *pLoad, int *pTurno, int *nJ1, int *nJ2){
	
	int opcion;
		
	do {
	
		//Imprime en pantalla las opciones del menu principal.
		printf ("Menu Principal:\n\n");
		printf ("\t1-Nueva Partida.\n");
		printf ("\t2-Continuar Partida.\n");
		printf ("\t3-Salir.\n\n\n");
		printf ("Seleccione una opcion.");
		scanf ("%d",&opcion);	

		switch (opcion){
			
								
			case 1: //Combinación básica.
										
				printf("Ha saleccionado %d por lo que se va a crear una combinacion de peones.\n\n", opcion);

					int i;
					
					iniTablero(pTablero, DIRTAB);

					for ( i = 0; i < DIM_PIEZASJ; i++){
		
						getFicha(J1[i].dFigura, DIRPEONJ1);
						J1[i].cActual = getCoordIni(1,i);
						setTablero( pTablero, J1[i].dFigura, J1[i].cActual.x, J1[i].cActual.y);
						
						getFicha(J2[i].dFigura, DIRPEONJ2);
						J2[i].cActual = getCoordIni(2,i);
						setTablero( pTablero, J2[i].dFigura, J2[i].cActual.x, J2[i].cActual.y);											
					}
														
					*rCicloJuego = 1;

					break;	
						
			case 2: // Continuar partida. 
			
				printf( "Ha seleccionado la opcion %d por lo que va a continuar una partida guardada\n", opcion);
				
				loadGame(pTablero, J1, J2, &pLoad, &pTurno, &nJ1, &nJ2, &rCicloJuego);
				break;
			
			case 3: //Salir del juego. 
				*rCicloJuego = 0;
				*rSalir = 1;
				break;
			
			default:
				
				printf("Opcion no valida\n");
				break;
				
		}//Fin switch.
		
	}while((opcion < 1) || (opcion > 4) );	
}
