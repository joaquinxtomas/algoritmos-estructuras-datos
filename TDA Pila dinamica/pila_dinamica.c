#include "pila_dinamica.h"

void crearPila(Pila* pila){
    *pila = NULL;
}

int insertarEnPila(Pila* pila, void* elemento, size_t tamElemento){
    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));

    if(!nuevo){
        return SIN_MEMORIA;
    }

    nuevo->info = malloc(tamElemento);
    if(!nuevo->info){
        free(nuevo);
        return SIN_MEMORIA;
    }

    nuevo->tamInfo = tamElemento;
    memcpy(nuevo->info, elemento, tamElemento);

    nuevo->siguiente = *pila;
    *pila = nuevo;

    return TODO_OK;
}

int sacarDePila(Pila* pila, void* elemento, size_t tamElemento){
    tNodo* eliminar = *pila;
    if(!*pila){
        return PILA_VACIA;
    }

    memcpy(elemento, eliminar->info, MINIMO(tamElemento, eliminar->tamInfo));

    *pila = eliminar->siguiente;

    free(eliminar->info);
    free(eliminar);

    return TODO_OK;
}

int pilaVacia(Pila* pila){
    if(!*pila){
        return PILA_VACIA;
    }
    return TODO_OK;
}

void vaciarPila(Pila* pila){
    while(*pila){
        tNodo* eliminar = *pila;
        *pila = eliminar->siguiente;
        free(eliminar->info);
        free(eliminar);
    }
}

void mostrarPila(Pila* pila, void(*mostrar)(void*)){

    if(pilaVacia(&pila)){
        printf("La pila esta vacía");
        return;
    }

    Pila nodoActual = *pila;

    while(nodoActual != NULL){
        mostrar(nodoActual->info);
        nodoActual = nodoActual->siguiente;
    }
}
