//Fiesta de los muertos.
					
#include "menuFMvsc.h"


int main(){
	
	tab tablero;			//Variable del tablero.
	
	pieza J1[DIM_PIEZASJ];	//Vector de piezas del jugador 1.
	pieza J2[DIM_PIEZASJ];	//Vector de piezas del jugador 2.
	pieza *pJ, *pNJ; 		//Punteros que apuntaran a los vectores de piezas cuando sea su turno.	
	
	_Bool cicloJuego = 0, salir = 0; 		// Se encarga de determinar si vamos a jugar. salir se engarga de romper el primer bucle.
	_Bool track [DIMTAB_REL][DIMTAB_REL];	// Variable para determinar checkMovimiento de una forma más optima. 
	_Bool continuar = 0; 					// Se encarga de comprobar que una pieza puede llegar a su destino debido a los obsatáculos.
	
	int  nFicha, nMov;										//nFicha se encarga de alamacenar la posicion de una pieza en el vector de piezas.// nMov la cantidad de movimiento.
	int nPiezasJ1 = DIM_PIEZASJ, nPiezasJ2 = DIM_PIEZASJ; 	//Variables que alamacenan el numero de piezas que tiene el jugador.
	int *pnPiezasJ; 										// Apunta al numero de piezas del jugador que este en su turno.
	
	char mInfoJ1[] = "Jugador 1";
	char mInfoJ2[] = "Jugador 2";
	char mSelectP[] = "pieza que quiere jugar.\n";
	char mSelectC[] = "casilla a la que quiere mover la pieza.\n";
	char *mInfoJ, *mSelect;		//Punteros que apuntaran a las cadenas de jugadores y acciones respectivament.
	
	coord temp, tempRel;		//variable auxiliares para almacenar coordenadas.	
	
	//Establecemos que el primer turno es del jugador 1.
	pJ = J1;
	pNJ = J2;
	mInfoJ = mInfoJ1;
	pnPiezasJ = &nPiezasJ1;  
	
	//Ejecución del programa.
 	
	while (!salir){

		menuPrincipalSC(0, &tablero, J1, J2, &cicloJuego, &salir);
		
		//Lógica del juego:
		
//		while(cicloJuego){
//
//			//
//		}
	}	
	
	return 0;
}
