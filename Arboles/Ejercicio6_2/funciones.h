#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
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

void crearArchivo(char* filename);
void mostrarArchivo(char* filename, unsigned tam, void(*accion)(const void*));
void mostrarEmpleadoArchivo(const void* dato);

void cargarArbolArchivo(tArbol* arbol, const char* filename);
int compararLegajos(const void* dato1, const void* dato2);
void mostrarIndiceEmpleadoArbol(void* info, unsigned tam, unsigned n, void* params);

#endif // FUNCIONES_H_INCLUDED
