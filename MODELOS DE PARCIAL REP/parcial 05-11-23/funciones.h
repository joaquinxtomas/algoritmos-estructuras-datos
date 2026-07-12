#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    int dia;
    int mes;
    int anio;
}t_fecha;

typedef struct{
    char codProd[6];
    char descripcion[25];
    unsigned lote;
    t_fecha fVto;
    unsigned cant;
}tProducto;

void generarLote(const char* filename);
void mostrarArchivoBin(const char* filename, unsigned tam, void(*accion)(const void*));
void mostrarProducto(const void* dato);
int comparaFechasYCant(const void* dato1, const void* dato2);
int fechaEsAnterior(t_fecha f1, t_fecha f2);


#endif // FUNCIONES_H_INCLUDED
