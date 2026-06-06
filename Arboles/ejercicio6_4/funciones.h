#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../TDA_Arbol/arbol.h"

#define MAX(x,y)((x) > (y) ? (x) : (y))
#define MIN(x,y)((x) < (y) ? (x) : (y))

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

void cargarArbolDesdeArchivo(const char* filename, tArbol* arbol);
int comparaLegajos(const void* dato1, const void* dato2);
void mostrarEmpleado(const void* dato, unsigned tam, unsigned n, void* params);

int esCompleto(const tArbol* arbol);
int obtenerAltura(const tArbol* arbol);
int contarNodos(const tArbol* arbol);

int esBalanceado(const tArbol* arbol);
int contarNodosHastaAltura(const tArbol* arbol, int n, int altura);
#endif // FUNCIONES_H_INCLUDED
