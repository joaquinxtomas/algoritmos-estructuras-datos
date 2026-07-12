#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED
#include "arbol.h"

typedef struct {
    char cod[10];
    char descripcion[20];
    unsigned stock;
    float precio;
}tProducto;

typedef struct{
    char cod[11];
    unsigned nroReg;
}tIndice;

typedef struct{
    unsigned cod_ped;
    char cod_prod[10];
    unsigned cantidad;
}tPedido;

void cargarIndiceArbol(const char* filename, tArbol* arbol);
void verArchivoBin(const char* filename, unsigned tam, void(*accion)(const void*));
int comparaIndice(const void* dato1, const void* dato2);

void mostrarProducto(const void* dato);
void mostrarIndice(const void* dato);
void mostrarIndiceArbol(void* dato, unsigned n, void* params);

int leerPedido(char* linea, tPedido* pedido);

#endif // PRODUCTOS_H_INCLUDED
