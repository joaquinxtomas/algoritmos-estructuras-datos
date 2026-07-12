#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct sNodoCola{
    void* info;
    unsigned tamInfo;
    struct sNodoCola* sig;
}tNodoCola;

typedef struct{
    tNodoCola* primero;
    tNodoCola* ultimo;
}tCola;

void crearCola(tCola* cola);
int ponerEnCola(tCola* cola, void* dato, unsigned tam);
int sacarDeCola(tCola* cola, void* dato, unsigned tam);
int colaLlena(tCola* cola, unsigned tam);
int colaVacia(tCola* cola);
int verPrimero(tCola* cola, void* dato, unsigned tam);
void vaciarCola(tCola* cola);

#endif // COLA_H_INCLUDED
