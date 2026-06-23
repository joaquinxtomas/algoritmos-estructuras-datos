#ifndef TDA_ARBOL_H_INCLUDED
#define TDA_ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo {
    void* info;
    unsigned tamInfo;
    struct sNodo* izq, *der;
}tNodo;

typedef tNodo* tArbol;

void crearArbol(tArbol* arbol);
void recorrerEnOrden(tArbol* arbol, void* params, void(*accion)(const void*, unsigned, const void*));
int insertarEnArbol(tArbol* arbol, void* dato, unsigned tam, int(*cmp)(const void*, const void*));
void vaciarArbol(tArbol* arbol); //por si se pide otro campo, volver al flujo inicial


#endif // TDA_ARBOL_H_INCLUDED
