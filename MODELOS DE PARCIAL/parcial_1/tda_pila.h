#ifndef TDA_PILA_H_INCLUDED
#define TDA_PILA_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MINIMO(x,y) ((x) < (y) ? (x) : (y))

typedef struct sNodo {
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tPila;

void crearPila(tPila* pila);
int ponerEnPila(tPila* pila, void* dato, unsigned tam);
int sacarDePila(tPila* pila, void* dato, unsigned tam);
int pilaLlena(tPila* pila, unsigned tam);
int pilaVacia(tPila* pila);

#endif // TDA_PILA_H_INCLUDED
