#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MINIMO(x,y) ((x) < (y) ? (x) : (y))

typedef struct sNodo{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* lista);
int insertarAlInicio(tLista* lista, void* dato, unsigned tam);
int sacarDelInicio(tLista* lista, void* dato, unsigned tam);
void vaciarLista(tLista* lista);

#endif // LISTA_H_INCLUDED
