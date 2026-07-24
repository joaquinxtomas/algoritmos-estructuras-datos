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
int insertarEnArbol(tArbol* arbol, void* dato, unsigned tam, int(*cmp)(const void*, const void*));
void recorrerInOrden(tArbol* arbol, void* params, unsigned n, unsigned tam, void(*accion)(void*, unsigned,unsigned, void*));
void cargarDesdeBin(tArbol* arbol, const char* filename, unsigned tam, int(*cmp)(const void*, const void*));
void escribirBin(void* info, unsigned n, unsigned tam, void* params);
void cargarArchivo(tArbol* arbol, const char* filename, unsigned tam);
void mostrarArbolGrafico(tArbol* arbol, unsigned nivel, unsigned tam, void(*accion)(void*, unsigned, unsigned, void*));
#endif // ARBOL_H_INCLUDED
