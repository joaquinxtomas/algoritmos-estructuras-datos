#include "tda_pila.h"

void crearPila(tPila* pila){
    *pila = NULL;
}

int ponerEnPila(tPila* pila, void* dato, unsigned tam){
    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(!nuevo){
        return 0;
    }

    nuevo->info = malloc(tam);
    if(!nuevo->info){
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, dato,tam);
    nuevo->tamInfo = tam;

    nuevo->sig = *pila;
    *pila = nuevo;

    return 1; //todo bien
}

int sacarDePila(tPila* pila, void* dato, unsigned tam){
    if(!*pila){
        return 0;
    }

    tNodo* eliminar = *pila;

    memcpy(dato, eliminar->info, MINIMO(eliminar->tamInfo, tam));

    *pila = eliminar->sig;
    free(eliminar->info);
    free(eliminar);

    return 1; //todo_ok
}

void verTope(tPila* pila, void* dato, unsigned tam){
    if(!*pila){
        return;
    }

    tNodo* ver = *pila;
    memcpy(dato, ver->info, MINIMO(ver->tamInfo, tam));
}

int pilaLlena(tPila* pila, unsigned tam){
    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));

    if(!aux){
        return 1; //pila llena
    }

    aux->info = malloc(tam);
    if(!aux->info){
        free(aux);
        return 1;
    }
    free(aux->info);
    free(aux);
    return 0; //pila vacia
}

int pilaVacia(tPila* pila){
    return *pila == NULL;
}
