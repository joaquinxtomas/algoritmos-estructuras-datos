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
int cargarBalanceado(const char* filename, tArbol* arbol, int inicio, int fin, unsigned tam, int(*cmp)(const void*, const void*));
int insertarEnArbol(tArbol* arbol, void* dato, unsigned tam, int(*cmp)(const void*, const void*));
void vaciarArbol(tArbol* arbol);


#endif // ARBOL_H_INCLUDED
