//Cabecera de Control.
//
//Distintas funciones para determinar acciones y reglas del juego.


#include "tablero_elementos.h"


int nDistMov(pieza*, pieza*, pieza*, coord);
_Bool checkMovimiento( _Bool [][DIMTAB_REL], _Bool [][DIMTAB_REL], int , int , coord, int);
void iniTrack( _Bool [][DIMTAB_REL]);
void setDirecciones(coord, coord, int*, int*);
_Bool checkPiezaMeta(pieza*, pieza*, pieza*, coord*);
