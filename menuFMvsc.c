// Menu switch case.

#include "menuFMvsc.h"

void menuPrincipalSC ( int n, tab *pTablero, pieza *J1, pieza *J2, _Bool *rCicloJuego, _Bool *rSalir){
	
	int opcion;
	int opcion1;
	int opcion11;
		
	do {
	
		//Imprime en pantalla las opciones del menu principal.
		printf ("Menu Principal:\n\n");
		printf ("\t1-Nueva Partida.\n");
		printf ("\t2-Continuar Partida.\n");
		printf ("\t3-Estadisticas.\n");
		printf ("\t4-Salir.\n\n\n");
		printf ("Seleccione una opcion.");
		scanf ("%d",&opcion);	

		switch (opcion){
			
			case 1: //Menú nueva partida.(1.)
		
//				printf("Ha saleccionado %d por lo que se va a crear una nueva partida.\n\n", opcion);
			
				do {
				
					//Imprime en pantalla las opciones del menu nueva partida.	
					printf ("Nueva partida:\n\n");
					printf ("\t1-Nueva combinacion.\n");
					printf ("\t2-Seleccionar combinacion.\n");
					printf ("\t3-Atras.\n\n\n");
					printf ("Seleccione una opcion.");
					scanf ("%d",&opcion1);
			
					switch (opcion1){

						case 1: // Menú crear combinación.(1.1)
					
							printf("Ha saleccionado %d por lo que se va a crear una combinacion nueva\n\n", opcion1);
						
							do {
							
							 	//Imprime en pantalla las opciones del menu combinacion nueva.
								printf ("Menu crear combinacion:\n\n");
								printf ("\t1-Combinacion basica.\n");
								printf ("\t2-Combinacion media.\n");
								printf ("\t3-Combinacion avanzada.\n");
								printf ("\t4-Atras.\n\n\n");
								printf ("Seleccione una opcion.");
								scanf ("%d",&opcion11);
							
								switch (opcion11){
								
									case 1: //Combinación básica.
										
										printf("Ha saleccionado %d por lo que se va a crear una combinacion de peones.\n\n", opcion11);

										iniTablero(pTablero, DIRTAB);

										int i, j;
	
										for ( i = 0; i < DIM_PIEZASJ; i++){
		
											getFicha(J1[i].dFigura, DIRPEONJ1);
											J1[i].cActual = getCoordIni(1,i);
//											J1[i].pertenencia = 1;
//											setTablero(pTablero->coordAbsolutas, pTablero->coordRelativas, J1[i].dFigura, J1[i].cActual.x,J1[i].cActual.y);
											setTablero( pTablero, J1[i].dFigura, J1[i].cActual.x, J1[i].cActual.y);
											getFicha(J2[i].dFigura, DIRPEONJ2);
											J2[i].cActual = getCoordIni(2,i);
//											J2[j].pertenencia = 2;
//											setTablero(pTablero->coordAbsolutas, pTablero->coordRelativas, J2[i].dFigura, J2[i].cActual.x,J2[i].cActual.y);
											setTablero( pTablero, J2[i].dFigura, J2[i].cActual.x, J2[i].cActual.y);											
										}
									
										*rCicloJuego = 1;
										imprimir(pTablero->coordAbsolutas);
										break;
									
									case 2: //Combinación media.
										printf( "Ha seleccionado %d por lo que va a regresesar al menu de nueva partida\n", opcion11);
										break;
									
									case 3: //Combinación avanzada.
										break;
								
									case 4: //Regresa al menú "Nueva Partida".
										printf( "Ha seleccionado %d por lo que va a regresesar al menu de nueva partida\n\n", opcion11);
										break;
									default:
										printf("Opcion no valida\n");
										break;
								}
							}while ( (opcion11 < 1 ) || (opcion11 > 4 ) );
							break;
						
						case 2: // Seleccionar combinación.
							printf( "Ha seleccionado %d por lo que va a elegir una combinacion guardada de fichas\n", opcion1);
							break;
					
						case 3: //Regresa al menú principal.
							printf ("Ha seleccionado %d por lo que va a regresar al menu principal\n\n", opcion1);
							opcion11 = 0;
							break;
						
						default:
							printf("Opcion no valida\n");
							break;						
					}
				
				}while ((opcion1 < 1 ) || (opcion1 > 3 ) || (opcion11 == 4));
				break;
			
			case 2: // Continuar partida. 
				printf( "Ha seleccionado la opcion %d por lo que va a continuar una partida guardada\n", opcion);
				//*rCicloJuego = 1;
				break;
			
			case 3: // Ver estadisticas.
				printf("Ha seleccionado la opcion %d por lo que va a ver las estadisticas\n", opcion);
				*rCicloJuego = 0;
				break;
			
			case 4: //Salir del juego. 
				*rCicloJuego = 0;
				*rSalir = 1;
				opcion1 = 0;
				break;
			
			default:

				printf("Opcion no valida\n");
				break;
		}	
	}while((opcion < 1) || (opcion > 4) || opcion1 == 3);	
	
}
