#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo {
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* lista);
int insertarEnTop(tLista* lista, void* dato, unsigned tam, int(*cmp)(const void*, const void*), unsigned n);
void recorrerLista(tLista* lista, void(*accion)(const void*));
void vaciarLista(tLista* lista);

#endif // LISTA_H_INCLUDED
