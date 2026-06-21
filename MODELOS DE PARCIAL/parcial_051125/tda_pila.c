#include "tda_pila.h"

void crearPila(tPila* pila){
    *pila = NULL;
}

void vaciarPila(tPila* pila){
    while(*pila){
        tNodo* aux = *pila;
        *pila = aux->sig;
        free(aux->info);
        free(aux);
    }
}

int pilaVacia(tPila* pila){
    return *pila == NULL;
}

int pilaLlena(tPila* pila, unsigned tam){
    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));
    void* info = malloc(tam);
    free(aux);
    free(info);

    return aux == NULL || info == NULL;
}

int ponerEnPila(tPila* pila, void* dato, unsigned tam){
    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));
    if(!aux){
        return 0; //SIN MEMORIA
    }

    aux->info = malloc(tam);
    if(!aux->info){
        free(aux);
        return 0; //error sin memoria
    }

    memcpy(aux->info, dato, tam);
    aux->tam = tam;

    aux->sig = *pila; //el siguiente es el que esta apilado abajo
    *pila = aux; //actualizo tope

    return 1; //TODO OK
}

int sacarDePila(tPila* pila, void* dato, unsigned tam){
    if(!*pila){
        return 0; //pila vacia
    }

    tNodo* elim = *pila; //te paras en el tope

    if(dato){
        memcpy(dato, elim->info, MINIMO(elim->tam, tam));
    }

    *pila = elim->sig;

    free(elim->info);
    free(elim);

    return 1; //hecho
}

int verTope(tPila* pila, void*dato, unsigned tam){
    if(!*pila){
        return 0;
    }

    tNodo* ver = *pila;
    memcpy(dato, ver->info, MINIMO(ver->tam, tam));

    return 1;
}

