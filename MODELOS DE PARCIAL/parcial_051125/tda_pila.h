#ifndef TDA_PILA_H_INCLUDED
#define TDA_PILA_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MINIMO(x,y) ((x) < (y) ? (x) : (y))

typedef struct sNodo{
    void* info;
    unsigned tam;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tPila;

void crearPila(tPila* pila);
void vaciarPila(tPila* pila);
int pilaVacia(tPila* pila);
int pilaLlena(tPila* pila, unsigned tam);
int ponerEnPila(tPila* pila, void* dato, unsigned tam);
int sacarDePila(tPila* pila, void* dato, unsigned tam);
int verTope(tPila* pila, void* dato, unsigned tam);
void escribirArchivoDesdePila(tPila* pila, FILE* file, unsigned tam);


#endif // TDA_PILA_H_INCLUDED
