#ifndef TDA_ARBOL_H_INCLUDED
#define TDA_ARBOL_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TODO_OK 1
#define SIN_MEMORIA 0
#define DUPLICADO 0
#define NO_EXISTE 0

typedef struct sNodo {
    void* info;
    unsigned tamInfo;
    struct sNodo* izq, *der;
}tNodo;

typedef tNodo* tArbol;


void vaciarArbol(tArbol* arbol);
void recorrerEnPosOrden(tArbol* arbol, unsigned n, void* params,void(*accion)(const void*, unsigned, const void*));
void recorrerEnOrden(tArbol* arbol, unsigned n, void* params,void(*accion)(const void*, unsigned, const void*));
void crearArbol(tArbol* arbol);

#endif // TDA_ARBOL_H_INCLUDED
