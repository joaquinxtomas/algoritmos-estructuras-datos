#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tda_arbol.h"

#define TODO_OK 1
#define SIN_MEMORIA 0
#define DUPLICADO 0
#define NO_EXISTE 0

typedef struct{
    int dni;
    char apellidoNombre[40];
    int cant_materias;
    float promedio;
    char estado; //A - activo y B - baja
}tAlumno;

typedef struct
{
    int dni;
    int nro_reg;
}tRegInd;

void mostrarArchivo(const char* filename, unsigned tam, void(*accion)(const void*));
void mostrarAlumno(const void* dato);
void mostrarRegIndice(const void* dato);
int baja(tArbol* arbol, const char* filenameAlumnos);
int eliminarNodo(tArbol* arbol, void* clave, int(*cmp)(const void*, const void*));
int eliminarRaiz(tArbol* arbol);
int alturaArbol(tArbol* arbol);
tNodo** buscarNodoArbol(tArbol* arbol, void* clave, int(*cmp)(const void*, const void*));
tNodo** mayorNodoArbol(tArbol* arbol);
tNodo** menorNodoArbol(tArbol* arbol);
void grabarArbolArchivoBin(tArbol* arbol, const char* filename, void(*accion)(const void*, unsigned, const void*));
void grabarArchivoBinArbol(tArbol* arbol, const char* filename, unsigned tam, int(*cmp)(const void*, const void*));
void escribirRegIndiceBinario(const void* info, unsigned n, const void* params);
int comparaDni(const void* a, const void* b);

void mostrarRegIndiceArbol(const void* info, unsigned tam, const void* params);

#endif // FUNCIONES_H_INCLUDED
