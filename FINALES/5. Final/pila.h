#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void vaciarPila(tPila* pila);
int verTope(tPila* pila, void* dato, unsigned tam);
int esPilaVacia(tPila* pila);


#endif // PILA_H_INCLUDED
