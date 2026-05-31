#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dia;
    int mes;
    int anio;
}tFecha;

typedef struct{
    char codigo_producto[7];
    char descripcion[15];
    char proveedor[15];
    tFecha fecha_compra;
    tFecha fecha_vencimiento;
    int cant;
    float precio_compra;
    float precio_venta;
}Producto;

void cargarArchivoProductos(const char* filename);
void mostrarProducto(const void* elemento);
void ingresarProducto(Producto* prod);

#endif // PRODUCTO_H_INCLUDED
