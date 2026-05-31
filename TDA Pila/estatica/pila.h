#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#define MINIMO(x,y) (((x) < (y)) ? (x) : (y))
#define TAM 4096
#define PILA_LLENA 1
#define PILA_VACIA 1
#define TODO_OK 0



typedef struct {
    char vec[TAM]; //tamaño en bytes, no en cantidad numerica
    unsigned int tope;
}PilaEst;

//primitivas (crear, verTope, insertarElemento, sacarElemento, vaciar, estaLlena, estaVacia)
void vaciarPila(PilaEst* pila);
void vaciarPila(PilaEst* pila);
int insertarElemento(PilaEst* pila, void* elemento, size_t tamElemento);
int sacarElemento(PilaEst* pila, void* elemento, size_t tamElemento);
int estaLlena(PilaEst* pila, size_t tamElemento);
int estaVacia(PilaEst* pila, size_t tamElemento);
int verElementoTope(PilaEst* pila, void* elemento, size_t tamElemento);

//ver una pila completa
void verPila(PilaEst* pila, void(*mostrar)(const void*));
//cargar un archivo desde una pila
void cargarArchivoPila(const char* filename, PilaEst* pila);

#endif // FUNCIONES_H_INCLUDED
