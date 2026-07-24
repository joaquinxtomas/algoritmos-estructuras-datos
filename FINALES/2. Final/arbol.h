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
int cargarDesdeTxt(tArbol* arbol, const char* filename, unsigned tam, int(*cmp)(const void*, const void*), int(*parsear)(const char*, void*));
void recorrerArbolPreOrden(tArbol* arbol, void* params, unsigned n, void(*accion)(void*, unsigned, void*));
void recorrerArbolInOrden(tArbol* arbol, void* params, unsigned n, void(*accion)(void*, unsigned, void*));
void esNivelCompleto(const tArbol* arbol, int n);
int potencia(int n);
int contarNodosNivel(const tArbol* arbol, int nivel);
int cantNodosPorNivel(tArbol* arbol, int nivel);
int cantNodosHastaNivel(tArbol* arbol, int nivel);
#endif // ARBOL_H_INCLUDED
