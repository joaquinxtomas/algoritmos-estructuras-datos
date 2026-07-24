#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED
#include "arbol.h"

typedef struct{
    char cod[5];
    char tipo;
    int cant;
}tProducto;

typedef struct{
    char cod[5];
    char tipo;
}tClave;

typedef struct{
    tClave clave;
    int nroReg;
}tIndice;

void generarLote(const char* filename);
void cargarIndice(const char* filename, tArbol* arbol);
int comparaClaves(const void*, const void*);
void mostrarIndice(void* info, unsigned n, unsigned tam, void* params);


#endif // PRODUCTOS_H_INCLUDED
