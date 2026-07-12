#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MINIMO(x,y) ((x) < (y) ? (x) : (y))

typedef struct sNodo{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tPila;

void crearPila(tPila* pila);
int insertarEnPila(tPila* pila, void* dato, unsigned tam);
int sacarDePila(tPila* pila, void* dato, unsigned tam);
int pilaLlena(tPila* pila, unsigned tam);
int pilaVacia(tPila* pila);
void vaciarPila(tPila* pila);
int verTope(tPila* pila, void* dato, unsigned tam);
int invertirPila(tPila* pila, unsigned tam);
#endif // PILA_H_INCLUDED
