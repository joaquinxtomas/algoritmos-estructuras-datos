#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "string.h"

typedef struct sNodo{
    void* info;
    size_t tamInfo;
    struct sNodo* sig;
}tNodo;

typedef struct tNodo* tLista;

#endif // LISTA_H_INCLUDED
