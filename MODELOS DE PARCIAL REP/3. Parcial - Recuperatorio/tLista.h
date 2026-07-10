#ifndef TLISTA_H_INCLUDED
#define TLISTA_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct sNodo{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* lista);
int insertarAlFinal(tLista* lista, void* dato, unsigned tam);
int sacarDelFinal(tLista* lista, void* dato, unsigned tam);
int insertarAlPrincipio(tLista* lista, void* dato, unsigned tam);
int sacarDelPrincipio(tLista* lista, void* dato, unsigned tam);
void recorrerLista(tLista* lista, void(*accion)(const void*));
int ordenarLista(tLista* lista, unsigned tam, int(*cmp)(const void*, const void*));
int invertirLista(tLista* lista, unsigned tam);
void vaciarLista(tLista* lista, unsigned tam);
int listaVacia(tLista* lista);
int listaLlena(tLista* lista, unsigned tam);
int insertarOrdenado(tLista* lista, void* dato, unsigned tam, int(*cmp)(const void*, const void*));

#endif // TLISTA_H_INCLUDED
