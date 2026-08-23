#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED

#include "lista.h"

typedef struct{
    int dia;
    int mes;
    int anio;
}tFecha;

typedef struct {
    char cod_producto[9];
    char descripcion[31];
    unsigned stock;
    float precio;
    tFecha fecha_ultima_actualizacion;
}tProducto;

typedef struct{
    tLista resultado;
    float precio_tope;
}tContexto;

void agruparProductos(const void*, const void*);
void ingresosBrutosPotenciales(const void*, void*);
void superaImporte(const void* info, void* res);
void mostrarProducto(const void* dato1);

int comparaFechas(tFecha fecha1, tFecha fecha2);
int comparaCodigos(const void* dato1, const void* dato2);

void crearLote(const char* filename);

#endif // PRODUCTOS_H_INCLUDED
