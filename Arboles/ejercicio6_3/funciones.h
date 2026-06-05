#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../TDA_Arbol/arbol.h"

typedef struct {
    int dia;
    int mes;
    int anio;
}tFecha;

typedef struct {
    char legajo[10];
    char apellidoNombre[35];
    char cargo[15];
    tFecha fechaAlta;
    tFecha fechaBaja;
}tEmpleado;

typedef struct {
    char legajo[11]; //clave
    int nroRegistro; //posicion en el archivo
}tIndice;

int estaOrdenado(const char* filename, unsigned tam, int (*cmp)(const void*, const void*));
int comparaLegajos(const void* dato1, const void* dato2);


#endif // FUNCIONES_H_INCLUDED
