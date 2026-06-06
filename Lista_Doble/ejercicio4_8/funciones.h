#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../TDA_Lista/ListaDoble.h"

typedef struct {
    int dni;
    char nombre[20];
    float altura;
}tPersona;


void mostrarPersona(const void* dato);
int comparaDni(const void* dato1, const void* dato2);
int insertarEnOrden(tLista* lista, const void* dato, unsigned tam, int(*cmp)(const void*, const void*));
void insertarPersonasLista(tLista* lista, int(*insertar)(tLista*, void*, unsigned));
#endif // FUNCIONES_H_INCLUDED
