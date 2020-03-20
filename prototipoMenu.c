//Prototipo de menu.

//Distribucion:
//	
//	Menu principal:
//		1 Nueva Partida:
//			1.1 Nueva Combinacion:
//				1.1.1 Combinacion Basica.
//				1.1.2 Combinacion Media:
//					1.1.2.1 Normal.
//					1.1.2.2 Vista.
//					1.1.2.3 Aleatoria.
//				1.1.3 Combinacion Avanzada.
//			1.2 Combinacion Guardada.
//		2 Continuar Partida.
//		3 Ver Estadisticas.
//		4 Salir.
					
		
#include <stdio.h>


void menuPrincipal(int);
void menuNuevaPartida(int);
void combinacionBasica(int);
void menuCombinacionMedia(int);
void mediaNormal(int n);
void mediaVista(int n);
void mediaAleatoria(int n);
void combinacionAvanzada(int);
void continuarPartida(int);
void verEstadisticas(int);
void salir(int);
void menuCombinacionNueva(int);
void combinacionGuardada(int);

int main(){
	
	menuPrincipal(0);
		
	return 0;
}

void menuPrincipal ( int n ){
	
	void(*fm[4])(int) = { menuNuevaPartida, continuarPartida, verEstadisticas, salir };
	
	int opcion;
	
	//Imprime en pantalla las opciones del menu principal.
	
	printf ("Menu Principal:\n\n");
	printf ("\t1-Nueva Partida.\n");
	printf ("\t2-Continuar Partida.\n");
	printf ("\t3-Estadisticas.\n");
	printf ("\t4-Salir.\n\n\n");
	
	do {
		
		printf ("Seleccione una opcion.");
		scanf ("%d",&opcion);
	}while ( (opcion < 1 ) || (opcion > 4 ) );
	
	(*fm[opcion - 1])(opcion);	
	
	
}

void menuNuevaPartida(int n){
	
	printf("Ha saleccionado %d por lo que se va a crear una nueva partida.\n\n", n);
	
	void(*fm[3])(int) = { menuCombinacionNueva, combinacionGuardada, menuPrincipal };
	
	int opcion;
	
	//Imprime en pantalla las opciones del menu nueva partida.
	
	printf ("Nueva partida:\n\n");
	printf ("\t1-Nueva combinacion.\n");
	printf ("\t2-Seleccionar combinacion.\n");
	printf ("\t3-Atras.\n\n\n");
	
	do {
		
		printf ("Seleccione una opcion.");
		scanf ("%d",&opcion);
	}while ( (opcion < 1 ) || (opcion > 3 ) );
	
	 (*fm[opcion - 1])(opcion);
}


void menuCombinacionNueva(int n){
	
	printf("Ha saleccionado %d por lo que se va a crear una combinacion nueva\n\n", n);
	
	void(*fm[4])(int) = { combinacionBasica, menuCombinacionMedia, combinacionAvanzada, menuNuevaPartida };
	
	int opcion;
	
	//Imprime en pantalla las opciones del menu combinacion nueva.
	
	printf ("Menu crear combinacion:\n\n");
	printf ("\t1-Combinacion basica.\n");
	printf ("\t2-Combinacion media.\n");
	printf ("\t3-Combinacion avanzada.\n");
	printf ("\t4-Atras.\n\n\n");
	
	do {
		
		printf ("Seleccione una opcion.");
		scanf ("%d",&opcion);
	}while ( (opcion < 1 ) || (opcion > 4 ) );
	
	(*fm[opcion - 1])(opcion);		
	
}

void combinacionBasica(int n){
	
	printf("Ha saleccionado %d por lo que se va a crear una combinacion de peones.\n\n", n);
		
}
void menuCombinacionMedia(int n){
	
	printf("Ha saleccionado %d por lo que se va a crear una combinacion de 4 peones y 4 figuras.\n\n", n);
	
	void(*fm[4])(int) = { mediaNormal, mediaVista, mediaAleatoria, menuCombinacionNueva };
	
	int opcion;
	
	//Imprime en pantalla las opciones del menu combinacion nueva.
	
	printf ("Menu combinacion media:\n\n");
	printf ("\t1-Seleccion normal.\n");
	printf ("\t2-Seleccion por turnos.\n");
	printf ("\t3-Seleccion Aleatoria.\n");
	printf ("\t4-Atras.\n\n\n");
	
	do {
		
		printf ("Seleccione una opcion.");
		scanf ("%d",&opcion);
	}while ( (opcion < 1 ) || (opcion > 4 ) );
	
	(*fm[opcion - 1])(opcion);		
		
	
}

void mediaNormal(int n){
	
	printf("Ha saleccionado %d por lo que se va a seleccionar 4 figuras en su turno.\n\n", n);
}

void mediaVista(int n){
	
	printf("Ha saleccionado %d por lo que se va a seleccionar 4 figuras de una en una.\n\n", n);
}

void mediaAleatoria(int n){
	
	printf("Ha saleccionado %d por lo que se va a crear una combinacion de 4 figuras de forma aleatoria.\n\n", n);
}

void combinacionAvanzada(int n){
	
	printf("Ha saleccionado %d por lo que se va a crear una combinacion de 8 figuras.\n\n", n);
}

void continuarPartida(int n){
	
	printf("Ha saleccionado %d por lo que se va a continuar una partida.\n\n", n);
}

void verEstadisticas(int n){
	
	printf("Ha saleccionado %d por lo que se va a ver las estadisticas\n\n", n);
}

void salir(int n){
	
	printf("Ha saleccionado %d por lo que se va a salir del juego\n", n);
}

void combinacionGuardada(int n){
	
	printf("Ha saleccionado %d por lo que se va a seleccionar una combinacion guardada\n", n);
}

