#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "tda_arbol.h"

typedef struct{
    int dia;
    int mes;
    int anio;
}tFecha;

typedef struct {
    char patente[8];
    int nroCuota;
    char apellidoNombre[26];
    int dni;
    tFecha vto;
    float importe;
}tRegistro;

void generarLote(const char* filename);
void mostrarArchivoBin(const char* filename);
void insertarArbolArchivoBin(tArbol* arbol, const char* filename, int(*cmp)(const void*, const void*));
void escribirArchivoTxtArbol(tArbol* arbol, const char* filename, void(*accion)(const void*, unsigned, const void*));
void escribirDni(const void* info, unsigned tam, const void* params);
void escribirDniYPatente(const void* info, unsigned tam, const void* params);
int comparaDni(const void* dato1, const void* dato2);
int comparaDniYPatente(const void* dato1, const void* dato2);
char menu(const char* msj, const char* opc);
void sumarTotal(const void* info, unsigned tam, const void* params);

#endif // FUNCIONES_H_INCLUDED
