#include "pila.h"

void crearPila(tPila* pila){
    *pila = NULL;
}

int insertarEnPila(tPila* pila, void* dato, unsigned tam){
    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(!nuevo){
        printf("SIN MEMORIA.\n");
        return 0;
    }

    nuevo->info = malloc(tam);
    if(!nuevo->info){
        free(nuevo);
        printf("SIN MEMORIA.\n");
        return 0;
    }

    memcpy(nuevo->info, dato, tam);
    nuevo->tamInfo = tam;

    nuevo->sig = *pila;
    *pila = nuevo;

    return 1;
}

int sacarDePila(tPila* pila, void* dato, unsigned tam){
    if(*pila == NULL){
        printf("PILA VACIA.\n");
        return 0;
    }

    tNodo* eliminar = *pila;
    memcpy(dato, eliminar->info, MINIMO(eliminar->tamInfo, tam));
    *pila = eliminar->sig;

    free(eliminar->info);
    free(eliminar);

    return 1;
}

int verTope(tPila* pila, void* dato, unsigned tam){
    if(*pila == NULL){
        printf("PILA VACIA.\n");
        return 0;
    }

    memcpy(dato, (*pila)->info, MINIMO((*pila)->tamInfo, tam));

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

int pilaLlena(tPila* pila, unsigned tam){
    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));
    void* info = malloc(tam);

    free(aux);
    free(info);
    return !aux || !info;
}

int pilaVacia(tPila* pila){
    return *pila == NULL;
}

int invertirPila(tPila* pila, unsigned tam){
    tPila pila_aux;
    crearPila(&pila_aux);

    while(*pila){
        void* dato = malloc(tam);
        sacarDePila(pila, dato, tam);
        insertarEnPila(&pila_aux, dato, tam);
        free(dato);
    }

    *pila = pila_aux;
}
