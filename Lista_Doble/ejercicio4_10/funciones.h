#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../TDA_Lista/ListaDoble.h"

typedef struct {
    int dni;
    char nombre[20];
    float altura;
}tPersona;

void insertarPersonasLista(tLista* lista, int(*insertar)(tLista*, void*, unsigned));
void mostrarPersona(const void* dato);

tLista filter(const tLista* lista, unsigned tam, int(*funcion)(void*));
int alturaMayor(void* dato);

#endif // FUNCIONES_H_INCLUDED
