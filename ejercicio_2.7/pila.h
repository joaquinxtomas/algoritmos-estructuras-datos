#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#define MINIMO(x,y) (((x) < (y)) ? (x) : (y))
#define SIN_MEMORIA 1
#define PILA_LLENA 1
#define PILA_VACIA 1
#define TODO_OK 0
#include "funciones.h"

typedef struct sNodo{
    void* info;
    size_t tamInfo;
    struct sNodo* siguiente;
}tNodo;

typedef tNodo* tPila;

void crearPila(tPila* pila);
int insertarEnPila(tPila* pila, void* elemento, size_t tamElemento);
int sacarDePila(tPila* pila, void* elemento, size_t tamElemento);
int verTope(tPila* pila, void* elemento, size_t tamElemento);
void vaciarPila(tPila* pila);
int pilaVacia(const tPila* pila);
int pilaLlena(const tPila* pila, size_t tamElemento);
#endif // PILA_H_INCLUDED
