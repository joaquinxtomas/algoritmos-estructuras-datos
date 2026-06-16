#ifndef TDA_COLA_H_INCLUDED
#define TDA_COLA_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MINIMO(x,y) ((x) < (y) ? (x) : (y))

typedef struct sNodo {
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef struct{
    tNodo* primero, *ultimo;
}tCola;

void crearCola(tCola* cola);
void vaciarCola(tCola* cola);
int esColaVacia(const tCola* cola);
int esColaLlena(const tCola* cola, unsigned tam);
int insertarAlFinal(tCola* cola, void* dato, unsigned tam);
int sacarAlComienzo(tCola* cola, void* dato, unsigned tam);
void verPrimero(const tCola* cola, void* dato, unsigned tam);


#endif // TDA_COLA_H_INCLUDED
