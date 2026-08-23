#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct sNodo{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef struct{
    tNodo* primero;
    tNodo* ultimo;
}tCola;
#endif // COLA_H_INCLUDED
