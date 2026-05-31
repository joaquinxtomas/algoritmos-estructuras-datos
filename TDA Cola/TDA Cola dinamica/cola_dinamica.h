#ifndef COLA_DINAMICA_H_INCLUDED
#define COLA_DINAMICA_H_INCLUDED
#define TODO_OK 0
#define SIN_MEMORIA 1
#define COLA_VACIA 1
#define COLA_LLENA 1
#define MINIMO(x,y) (((x) < (y) ? (x) : (y)))

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct sNodo {
    void* info;
    size_t tamInfo;
    struct sNodo* siguiente;
} tNodo;

typedef struct {
   struct sNodo* ptrInicio;
   struct sNodo* ptrFin;
} Cola;

void crearCola(Cola* cola);
int insertarEnCola(Cola* cola, const void* elemento, size_t tamElemento);
int sacarDeCola(Cola* cola, void* elemento, size_t tamElemento);
void vaciarCola(Cola* cola);
int colaVacia(const Cola* cola);
int colaLlena(const Cola* cola, size_t tamElemento);
int verFrenteCola(const Cola* cola, const void* elemento, size_t tamElemento);
int verFondoCola(const Cola* cola, const void* elemento, size_t tamElemento);

void imprimirCola(const Cola* cola, void (*mostrar)(void*));

#endif // COLA_DINAMICA_H_INCLUDED
