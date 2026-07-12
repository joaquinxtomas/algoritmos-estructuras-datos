#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINIMO(x,y) ((x) < (y) ? (x) : (y))

typedef struct sNodo{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* lista);
int insertarEnPodio(tLista* lista, void* dato, unsigned tam, int(*cmp)(const void*, const void*), int limite);
int insertarAlFinal(tLista* lista, void* dato, unsigned tam);
int sacarDelFinal(tLista* lista, void* dato, unsigned tam);
int sacarDelInicio(tLista* lista, void* dato, unsigned tam);

#endif // LISTA_H_INCLUDED
