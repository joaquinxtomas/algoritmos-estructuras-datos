#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct sNodo{
    void* info;
    unsigned tamInfo;
    struct sNodo* izq, *der;
}tNodo;

typedef tNodo* tArbol;

void crearArbol(tArbol* arbol);
int insertarEnArbol(tArbol* arbol, void* dato, unsigned tam, int(*cmp)(const void*, const void*));
int eliminarNodo(tArbol* arbol, void* dato, unsigned tam, int(*cmp)(const void*, const void*));
int eliminarRaiz(tArbol* arbol);
int alturaArbol(tArbol* arbol);
int menorNodoArbol(tArbol* arbol);
int mayorNodoArbol(tArbol* arbol);

int grabarArbolEnBin(tArbol* arbol, const char* filename, unsigned tam);
int vaciarArbol(tArbol* arbol);

tNodo** buscarNodoArbol(tArbol* arbol, void* clave, int(*cmp)(const void*, const void*));

void recorrerInOrden(tArbol* arbol, void* params, unsigned n, void(*accion)(void*, unsigned, void*));

#endif // ARBOL_H_INCLUDED
