#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "cola_dinamica.h"

typedef struct{
    int dia;
    int mes;
    int anio;
} tFecha;

typedef struct {
    char cod_producto[7];
    char descripcion[15];
    char proveedor[15];
    tFecha fecha_compra;
    tFecha fecha_venta;
    int cantidad;
    float precio_compra;
    float precio_venta;
}Producto;

void proceso(const char* filename, Cola* cola);

void cargarArchivo(const char* filename);
void recorrerArchivo(const char* filename, size_t tam, void(*mostrar)(void*));
void mostrarProducto(void* elemento);
void cargarColaArchivo(Cola* cola, size_t tam, const char* filename);
void ingresarProducto(Producto* prod);


#endif // FUNCIONES_H_INCLUDED
