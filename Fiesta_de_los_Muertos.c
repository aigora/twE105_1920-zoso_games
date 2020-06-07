//Fiesta de los muertos.
					
#include "menuFMvsc.h"

int main(){
	
	tab tablero;	//Estructura del tablero.
	pieza J1[DIM_PIEZASJ];	//Vector de piezas del jugador 1.
	pieza J2[DIM_PIEZASJ];	//Vector de piezas del jugador 2.
	
	_Bool cicloJuego = 0, salir = 0, load = 0; // Se encarga de determinar si vamos a jugar. salir se engarga de romper el primer bucle. load de cargar preparar variables continuando la partida 
	_Bool track [DIMTAB_REL][DIMTAB_REL]; // nueva variable para determinar checkMovimiento de una forma más optima. 
	
	coord cNJ[24] = {	//Vector de coordenadas de las casillas no jugables.(*MEJOR UTILIZAR UN FICHERO*).
					{A1_X,A1_Y}, {A2_X,A2_Y},{A8_X,A8_Y}, {A9_X,A9_Y},{A10_X,A10_Y},
					{B1_X,B1_Y}, {B9_X,B9_Y},{B10_X,B10_Y},
					{H1_X,H1_Y}, {H9_X,H9_Y},{H10_X,H10_Y},
					{I1_X,I1_Y}, {I2_X,I2_Y},{I8_X,I8_Y}, {I9_X,I9_Y},{I10_X,I10_Y},
					{J1_X,J1_Y}, {J2_X,J2_Y},{J8_X,J8_Y}, {J9_X,J9_Y},{J10_X,J10_Y},
					{CENTRO_X, CENTRO_Y}, {EX1_X, EX1_Y}, {EX2_X, EX2_Y}
					};

	int turno;
	int  nFicha, nMov;
	int nPiezasJ1 = DIM_PIEZASJ, nPiezasJ2 = DIM_PIEZASJ; 
	int *pnPiezasJ; // Apunta al numero de piezas del jugador que este en su turno.
	char mInfoJ1[] = "Jugador 1";
	char mInfoJ2[] = "Jugador 2";
	char mSelectP[] = "pieza que quiere jugar";
	char mSelectC[] = "casilla a la que quiere mover la pieza";
	coord temp, tempRel;	
	char *mInfoJ, *mSelect, aux; //Punteros que apuntaran a las cadenas de jugadores y acciones respectivamente;
	
	pieza *pJ, *pNJ; //Punteros que apuntaran a los vectores de piezas cuando sea su turno.

	_Bool continuar = 0; // Se encarga de comprobar que una pieza puede llegar a su destino debido a los obsatáculos.
	
	//Ejecución del programa.
 	
	while (!salir){
		
		menuPrincipalSC(0, &tablero, J1, J2, &cicloJuego, &salir, &load, &turno, &nPiezasJ1, &nPiezasJ2);
		
		
		if ( load ){
			
			if ( turno ==  1){
				pJ = J1;
				pNJ = J2;
				mInfoJ = mInfoJ1;
				pnPiezasJ = &nPiezasJ1; 
			}else if ( turno ==2){
				pJ = J2;
				pNJ = J1;
				mInfoJ = mInfoJ2;
				pnPiezasJ = &nPiezasJ2; 
	
			}			
		}else {
		//Establecemos que el primer turno es del jugador 1.
		
			pJ = J1;
			pNJ = J2;
			mInfoJ = mInfoJ1;
			pnPiezasJ = &nPiezasJ1; 				
		}
		
		//Lógica del juego:
		
		while(cicloJuego){
			
				imprimir(tablero.coordAbsolutas);
			
			do{
 
				do{	
				
					continuar = 0;	
					mSelect = mSelectP;	
				
					do{
						temp = getCoordInput(mInfoJ, mSelect);

					}while(!checkCoordP(pJ, pNJ, temp, &nFicha));
	
					nMov = nDistMov(pJ, J1, J2, temp);
					mSelect = mSelectC; // Cambiamos el mensaje ya que ahora queremos que nos den la casilla;
				
					do{
					
						temp = getCoordInput(mInfoJ, mSelect);		 	
					
					}while(!checkCoordC(pJ, pNJ, J1, J2, temp, cNJ));
					
					//Pasamos las coordenadas a relativas.

					tempRel = toRel(temp);					
					pJ[nFicha].relativas = toRel( pJ[nFicha].cActual);
					
					//Comprobamos si esta demasiado lejos de primeras para evitar llamar a checkMovimiento innecesariamente.	
					if (checknMov(pJ[nFicha].cActual, temp, nMov)){
			 			 
						//Calculamos el movimiento:
						iniTrack(track);
						tablero.coordRelativas[pJ[nFicha].relativas.x][pJ[nFicha].relativas.y] = 0;
						continuar =  (checkMovimiento(tablero.coordRelativas, track, pJ[nFicha].relativas.x, pJ[nFicha].relativas.y, tempRel, nMov));
						if (!continuar) printf("No puede mover la pieza seleccionada a esa casilla.\n");
						
					}else continuar = 0;
							
				}while (!continuar);

				borrarTablero( tablero.coordAbsolutas, pJ[nFicha].cActual.x, pJ[nFicha].cActual.y);
			
				if (checkPiezaMeta(pJ, J1, J2, &tempRel)){
				
					*pnPiezasJ -= 1;
					printf("%s ha alcanzado su meta con la pieza seleccionada. Le quedan %d piezas.\n", mInfoJ, *pnPiezasJ);
					pJ[nFicha].cActual.x = -1;
					pJ[nFicha].cActual.y = -1;	
							
				}
				else {
					setTablero( &tablero, pJ[nFicha].dFigura, temp.x, temp.y);				
					pJ[nFicha].cActual = temp;		
				}
							
//				system("cls");
				imprimir(tablero.coordAbsolutas);
//				cambioTurno( &pJ, &pNJ, J1, J2,&mInfoJ, mInfoJ1, mInfoJ2);

				//El jugador actual ha ganado?
				if ( *pnPiezasJ == 0){
				
					printf("Enhorabuena %s ha ganado la partida!!!\n", mInfoJ);
					continuar = 0;
					cicloJuego = 0;
				}
				
				else{
					
				// Cambiamos de turno.
					pieza *auxJugador;
					char *auxMensaje;
		
					auxJugador = pJ;
					pJ = pNJ;
					pNJ = auxJugador;
		
					if ( mInfoJ == mInfoJ1) mInfoJ = mInfoJ2;
					else mInfoJ = mInfoJ1;
			
					if (pnPiezasJ == &nPiezasJ1) pnPiezasJ = &nPiezasJ2;
					else pnPiezasJ = &nPiezasJ1; 
									
				
					//Fin de turno y guardar la partida.
					if ( finTurno() == 0 ){
					
						continuar = 0;
						cicloJuego = 0;
	
						do {
		
							printf ( "Desea guardar la partida?(s/n)\n");
							fflush(stdin);
							scanf("%c",&aux);
							if ( aux == 's') saveGame(pJ, pNJ, J1, J2, nPiezasJ1, nPiezasJ2);
							else if ( aux != 'n') printf("Opcion no valida\n");
		
						}while ( aux != 's' && aux != 'n' );
					}				
				}	
				
			}while (continuar);
		}
	}	
	
	return 0;
}
