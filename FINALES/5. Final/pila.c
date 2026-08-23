#include "pila.h"

void crearPila(tPila* pila){
    *pila = NULL;
}

int insertarEnPila(tPila* pila, void* dato, unsigned tam){
    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(!nuevo){
        return 0;
    }

    nuevo->info = malloc(tam);
    if(!nuevo->info){
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, dato, tam);
    nuevo->tamInfo = tam;

    nuevo->sig = *pila;
    *pila = nuevo;

    return 1;
}


int sacarDePila(tPila* pila, void* dato, unsigned tam){
    if(!*pila){
        return 0;
    }

    tNodo* elim = *pila;

    memcpy(dato, elim->info, MINIMO(elim->tamInfo, tam));

    *pila = elim->sig;
    free(elim->info);
    free(elim);

    return 1;
}

int verTope(tPila* pila, void* dato, unsigned tam){
    if(!*pila){
        return 0;
    }

    memcpy(dato, (*pila)->info, MINIMO((*pila)->info, tam));
    return 1;
}

void vaciarPila(tPila* pila){
    while(*pila){
        tNodo* aux = *pila;
        *pila = aux->sig;
        free(aux->info);
        free(aux);
    }
}

int esPilaVacia(tPila* pila){
    return *pila == NULL;
}
