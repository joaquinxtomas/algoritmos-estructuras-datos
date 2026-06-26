#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tda_arbol.h"

typedef struct{
    char cod[10];
    char descripcion[20];
    unsigned stock;
    float precio;
}tProducto;

typedef struct{
    int cod_pedido; //6
    char cod_prod[10];
    int cantidad; //3
}tPedido;

void leerArchivoBin(const char* filename, unsigned tam, void(*accion)(const void*));
void mostrarIndice(const void* dato, unsigned n, const void* params);
void mostrarProducto(const void* dato, unsigned n, const void* params);
void leerArchivoTxt(const char* filename);
void trozarCampos(char* linea, tPedido* pedido);

#endif // FUNCIONES_H_INCLUDED
