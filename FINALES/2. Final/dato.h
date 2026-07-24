#ifndef DATO_H_INCLUDED
#define DATO_H_INCLUDED
#include "arbol.h"

typedef struct{
    char clave[5];
    int dato;
}tDato;


int parsearDato(const char*, void*);
void mostrarDato(const void*);
int comparaDato(const void*, const void*);

#endif // DATO_H_INCLUDED
