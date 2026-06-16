#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "../TDA_Cola/TDA_Cola.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void proceso();
void mostrarCola(const tCola* cola, void(*mostrar)(const void*));
void mostrarNumSale(const void* dato);
void mostrarNumLlega(const void* dato);
void mostrarNum(const void* dato);

#endif // FUNCIONES_H_INCLUDED
