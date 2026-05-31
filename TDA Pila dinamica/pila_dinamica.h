#ifndef PILA_DINAMICA_H_INCLUDED
#define PILA_DINAMICA_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIN_MEMORIA 1
#define TODO_OK 0
#define PILA_VACIA 1

#define MINIMO(x,y) (((x) < (y)) ? (x):(y))


typedef struct sNodo {
    void* info;
    size_t tamInfo;
    struct sNodo* siguiente;
}tNodo;

typedef tNodo* Pila;

void crearPila(Pila* pila);
int insertarEnPila(Pila* pila, void* elemento, size_t tamElemento);
int sacarDePila(Pila* pila, void* elemento, size_t tamElemento);
void mostrarPila(Pila* pila, void (*mostrar)(void*));
int pilaVacia(Pila* pila);
void vaciarPila(Pila* pila);


#endif // PILA_DINAMICA_H_INCLUDED
