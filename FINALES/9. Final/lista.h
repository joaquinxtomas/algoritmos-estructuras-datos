#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct sNodo{
    void* info;
    unsigned tamInfo;
    struct sNodo*sig, *ant;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* lista);
int insertarUltimo(tLista* lista, tNodo** ultimo, void* dato, unsigned tam);
int insertarAlInicio(tLista* lista, void* dato, unsigned tam);
void recorrerLista(tLista* lista, void (*accion)(const void*));
void vaciarLista(tLista* lista);

void eliminarDuplicados(tLista* lista, int(*cmp)(const void*, const void*), void(*accion)(const void*, const void*));
void reduce(tLista* lista, void* res, void(*accion)(const void*, void*));

#endif // LISTA_H_INCLUDED
