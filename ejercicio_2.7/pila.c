#include "pila.h"

void crearPila(tPila* pila){
    *pila = NULL;
}

int insertarEnPila(tPila* pila, void* elemento, size_t tamElemento){
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

int sacarDePila(tPila* pila, void* elemento, size_t tamElemento){
    tNodo* eliminado = *pila;

    if(*pila == NULL){ //pila vacia
        return PILA_VACIA;
    }

    eliminado->tamInfo = tamElemento;
    memcpy(elemento, eliminado->info, MINIMO(eliminado->tamInfo, tamElemento));
    *pila = eliminado->siguiente;
    return TODO_OK;
}

int verTope(tPila* pila, void* elemento, size_t tamElemento){
    tNodo* elim = *pila;

    if(pila == NULL){
        return PILA_VACIA;
    }

    elim->tamInfo = tamElemento;
    memcpy(elemento, elim->info, MINIMO(elim->tamInfo, tamElemento));

    return TODO_OK;
}

int pilaVacia(const tPila* pila){
    return *pila == NULL;
}

int pilaLlena(const tPila* pila, size_t tamElemento){
    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));
    aux->info = malloc(tamElemento);

    free(aux->info);
    free(aux);

    return aux == NULL || aux->info == NULL;
}

void vaciarPila(tPila* pila){
    while(*pila){
        tNodo* elim = *pila;
        *pila = elim->siguiente;
        free(elim->info);
        free(elim);
    }
}

void ordenarPila(tPila* pila1, tPila* pila2, size_t tam, int (*cmp)(const void*,const void*));

