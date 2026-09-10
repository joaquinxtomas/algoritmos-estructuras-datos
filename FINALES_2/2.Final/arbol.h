#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define pow(x) ((x)*(x))

typedef struct sNodo{
    void* info;
    unsigned tamInfo;
    struct sNodo* izq, *der;
}tNodo;

typedef tNodo* tArbol;

void crearArbol(tArbol* arbol);
int insertarEnArbol(tArbol* arbol, void* elemento, unsigned tam, int(*cmp)(void*, void*));
void vaciarArbol(tArbol* arbol);
int insertarBalanceado(tArbol* arbol, void* elemento, unsigned tam, int(*cmp)(void*, void*), int li, int ls);
void recorrerArbolPreOrden(tArbol* arbol, unsigned tam, int n, void* params, void(*accion)(void*, int, void*));
int cantNodosNivel(tArbol* arbol, int nivel);
int nivelCompleto(tArbol* arbol, int nivel);
int cantNodosHastaNivel(tArbol* arbol, int nivel);

#endif // ARBOL_H_INCLUDED
