#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct sNodo{
    void* info;
    unsigned tamInfo;
    struct sNodo* izq, *der;
}tNodo;

typedef tNodo* tArbol;

void crearArbol(tArbol* arbol);
void vaciarArbol(tArbol* arbol);
int insertarEnArbol(tArbol* arbol, void* dato, unsigned tam, int(*cmp)(const void*, const void*));
void recorrerInOrden(tArbol* arbol, void* params, unsigned n, unsigned tam, void(*accion)(void*, unsigned, void*));
int buscarPorClave(tArbol* arbol, void* clave, unsigned tam, int(*cmp)(const void*, const void*));


#endif // ARBOL_H_INCLUDED
