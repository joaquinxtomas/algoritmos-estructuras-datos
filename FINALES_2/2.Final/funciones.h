#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED


#include "arbol.h"

typedef struct {
    char clave[6];
    int dato;
}Dato;

void cargarDesdeTxt(const char* filename, tArbol* arbol);
int comparaDato(void* dato1, void* dato2);
void mostrarDato(void* info, int n, void* params);

#endif // FUNCIONES_H_INCLUDED
