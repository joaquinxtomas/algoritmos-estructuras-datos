#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>

typedef struct sNodo {
    void* info;
    unsigned tam;
    struct sNodo* ant;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* lista);
void vaciarLista(tLista* lista);
int listaVacia(const tLista* lista);
int listaLlena(const tLista* lista, unsigned tam);
int insertarAlFinal(tLista* lista, void* dato, unsigned tam);
int insertarAlComienzo(tLista* lista, const void* dato, unsigned tam);
void mostrarDeIzqDer(const tLista* lista, void(*mostrar)(const void*));
void mostrarDeDerIzq(const tLista* lista, void(*mostrar)(const void*));


#endif // LISTADOBLE_H_INCLUDED
