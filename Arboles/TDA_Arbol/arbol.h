#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define reservarMemoriaNodo(ptrNodo,tamNodo,ptrInfo,tamInfo)(\
        ((ptrNodo) = (typeof(ptrNodo))malloc(tamNodo)) == NULL ||\
        ((ptrInfo) = malloc(tamInfo)) == NULL?\
        free(ptrNodo), 0:1)

#define DUPLICADO 0
#define SIN_MEMORIA 0
#define TODO_OK 1

typedef struct sNodoArbol{
    void *info;
    unsigned tamInfo;
    struct sNodoArbol *izq, *der;
}tNodoArbol;
typedef tNodoArbol* tArbol;


void crearArbol(tArbol* arbol);
int insertarRecArbolBinBusqueda(tArbol* arbol, const void* dato, unsigned tam, int(*cmp)(const void*, const void*));

void recorrerEnOrdenRecArbolBinBusqueda(const tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*));
void recorrerPreOrdenRecArbolBinBusqueda(const tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*));
void recorrerPosOrdenRecArbolBinBusqueda(const tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*));

int buscarEnArbol(const tArbol* arbol, void* dato, unsigned tam, int(*cmp)(const void*, const void*));

void eliminarArbol(tArbol *arbol);

#endif // ARBOL_H_INCLUDED

