#ifndef TDA_ARBOL_H_INCLUDED
#define TDA_ARBOL_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct sNodo{
    void* info;
    unsigned tamInfo;
    struct sNodo *izq, *der;
}tNodo;

typedef tNodo* tArbol;

typedef struct{
    char codigo[10];
}tClave;

typedef struct{
    tClave clave;
    int nro_reg;
}tIndice;

void crearArbol(tArbol* arbol);
int insertarEnArbol(tArbol* arbol, void* dato, unsigned tam, int(*cmp)(const void*, const void*));
int buscarPorClave(tArbol* arbol, void* clave, unsigned tam, int(*cmp)(const void*, const void*));
void recorrerEnOrden(tArbol* arbol, unsigned n, void* params, void(*accion)(const void*, unsigned, const void*));
int comparaIndices(const void* dato1, const void* dato2);

#endif // TDA_ARBOL_H_INCLUDED
