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

void insertarNumLista(tLista* lista, int(*insertar)(tLista*, void*, unsigned));
void mostrarNumero(const void* dato);

void* sumar(void* acumulado, void* actual);
tLista reduce(tLista* lista, unsigned tam, void*(*funcion)(void*, void*));

#endif // FUNCIONES_H_INCLUDED
