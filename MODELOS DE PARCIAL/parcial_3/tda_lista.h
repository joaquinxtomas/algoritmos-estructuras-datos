#ifndef TDA_LISTA_H_INCLUDED
#define TDA_LISTA_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MINIMO(x,y) ((x) < (y) ? (x):(y))

typedef struct sNodo{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* lista);
int insertarAlFinal(tLista* lista, void* dato, unsigned tam);
int sacarDelFinal(tLista* lista, void* dato, unsigned tam);
void vaciarLista(tLista* lista);
int ordenarLista (tLista* lista, unsigned tam, int(*cmp)(const void*, const void*));
int insertarOrdenado(tLista* lista, const void* dato, unsigned tam, int(*cmp)(const void*, const void*));
void invertirLista(tLista* lista, unsigned tam);
int insertarAlInicio(tLista* lista,void* dato,unsigned tam);
int sacarDelInicio(tLista* lista, void* dato, unsigned tam);
void vaciarLista(tLista* lista);

#endif // TDA_LISTA_H_INCLUDED
