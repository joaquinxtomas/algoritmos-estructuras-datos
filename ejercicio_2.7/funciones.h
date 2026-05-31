#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct {
    char nombre[20];
    char apellido[20];
    int dni;
}tPersona;

void mostrarPersona(const void* elemento);
int compararDni(const void* elemento1, const void* elemento2);
void proceso(const char* filename, size_t tam, int (*cmp)(const void*,const void*));
#endif // FUNCIONES_H_INCLUDED
