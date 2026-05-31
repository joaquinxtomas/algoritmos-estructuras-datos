#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <string.h>

//estructura tda vector
typedef struct{
    void *vec;
    int cap;
    int ce;
    size_t tam;
}Vector;

//estructura ejercicio 4
typedef struct{
    char nombre[20];
    char apellido[20];
    int edad;
}tPersona;

int crearVector(Vector *vec, int ce, size_t tam);
int vectorLleno(Vector *vec);
int vectorVacio(Vector *vec);
int cantElem(Vector *vec);
int insertarEnOrden(Vector *vec, void* elem, int(*cmp)(const void*, const void*));
void destruirVector(Vector *vec);
int eliminarElemento(Vector* vec, int idx);
void recorrerVec(Vector* vec, void(*accion)(const void*));
void mostrarVecInt(const void* elemento);

float calcular (float operando1, float operando2, float(*operacion)(float, float));
float division(float operando1, float operando2);
float multiplicacion(float operando1, float operando2);
float suma(float operando1, float operando2);
float resta(float operando1, float operando2);

void proceso(const char* filename);

void mostrarVecPersona(const void *elemento);
int leerLinea(FILE* archivo, tPersona* persona);
void procesoPersona(const char* filename);

void procesoGenericoTexto(const char* filename, size_t tam, int(*leerDato)(FILE*,void*), void(*mostrarDato)(const void*));

#endif // FUNCIONES_H_INCLUDED
