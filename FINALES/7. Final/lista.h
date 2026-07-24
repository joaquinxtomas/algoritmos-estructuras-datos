#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct sNodo{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* lista);
int insertarAlInicio(tLista* lista, void* dato, unsigned tam);
//void invertirLista(tLista* lista);
void mostrarInverso(tLista* lista, void(*accion)(const void*), int(*condicion)(const void*));

#endif // LISTA_H_INCLUDED
