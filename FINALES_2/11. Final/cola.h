#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MINIMO(x,y) ((x) < (y) ? (x) : (y))

typedef struct sNodo{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef struct{
    tNodo* primero;
    tNodo* ultimo;
}tCola;

void crearCola(tCola* cola);
int ponerEnCola(tCola* cola, void* elemento, unsigned tam);
int sacarDeCola(tCola* cola, void* elemento, unsigned tam);
int colaVacia(tCola* cola);
int colaLlena(tCola* cola, unsigned tam);
void vaciarCola(tCola* cola);
int verPrimero(tCola* cola, void* elemento, unsigned tam);
#endif // COLA_H_INCLUDED
