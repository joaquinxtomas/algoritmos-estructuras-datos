#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../TDA_Arbol/arbol.h"

#define reservarMemoriaNodo(ptrNodo,tamNodo,ptrInfo,tamInfo)(\
        ((ptrNodo) = (typeof(ptrNodo))malloc(tamNodo)) == NULL ||\
        ((ptrInfo) = malloc(tamInfo)) == NULL?\
        free(ptrNodo), 0:1)

#define DUPLICADO 0
#define SIN_MEMORIA 0
#define TODO_OK 1

/**
GRAFICO DE EJEMPLO PARA PODER SABER SI SE ESTA IMPLEMENTANDO BIEN EL EJERCICIO 6.1
              LEG-005
             /       \
        LEG-002     LEG-008
        /     \     /     \
   LEG-001 LEG-003 LEG-007 LEG-009
               \    /        \
           LEG-004 LEG-006  LEG-010
**/

typedef struct sNodoArbol{
    void *info;
    unsigned tamInfo;
    struct sNodoArbol *izq, *der;
}tNodoArbol;
typedef tNodoArbol* tArbol;

typedef struct{
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

void crearArbol(tArbol* arbol);
int insertarRecArbolBinBusqueda(tArbol* arbol, const void* dato, unsigned tam, int(*cmp)(const void*, const void*));

void recorrerEnOrdenRecArbolBinBusqueda(const tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*));
void recorrerPreOrdenRecArbolBinBusqueda(const tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*));
void recorrerPosOrdenRecArbolBinBusqueda(const tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*));

int buscarEnArbol(const tArbol* arbol, void* dato, unsigned tam, int(*cmp)(const void*, const void*));

void eliminarArbol(tArbol *arbol);

/** GUIA DE EJERCICIOS **/
//ejercicio 6.1
//implementar la función que determina la altura del árbol.
void obtenerAltura(void* info, unsigned tam, unsigned n, void* params); //de esta manera se puede enviar en "accion" en la recorrida generica
int alturaArbolBin(const tArbol* arbol); //esta es la correcta para cualquier arbol

//implementar la función que imprime solo las hojas
void mostrarHojas(tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*));

//implementar la función que imprime solo las no-hojas
void mostrarNoHojas(tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*));

//implementar la función que imprime nodos que solo tienen hijo por izquierda
void mostrarHijosIzq(tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*));

//implementar la función que imprime nodos que tienen hijo por izquierda.
void mostrarHijosIzqOpc(tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*));

//implementar la función que 'poda' un arbol de modo que no se supere una altura determinada
void podarArbolAltura(tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*));

//implementar la función que 'poda' las ramas de un arbol de una altura determinada o inferior
void podarArbolAlturaInferior(tArbol* arbol, void* params);

//crear archivo con la información del arbol
void generarArchivoArbol(void* info, unsigned tam, unsigned n, void* params);

/**funciones que no son originarias de arboles*/
int compararLegajo(const void* dato1, const void* dato2);
void mostrarEmpleado(void* info, unsigned tam, unsigned nivel, void* params);
void mostrarArchivo(char* filename, unsigned tam, void(*accion)(void*, unsigned, unsigned, void*));
#endif // FUNCIONES_H_INCLUDED
