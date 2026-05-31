#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#define MENSAJE_MENU "ELIJA UNA OPCION\n1 - Cargar elemento a la pila\n2 - Ver información del tope de la pila\n3 - Eliminar de la pila\n4 - Salir\n"

void proceso(const char *filename, PilaEst* pila);

//definiciones de menu
char menuSinErr(const char* msj, const char* opc);

#endif // FUNCIONES_H_INCLUDED
