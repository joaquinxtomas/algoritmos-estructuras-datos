#include "TDA_Cola.h"

void crearCola(tCola* cola){
    cola->primero = NULL;
    cola->ultimo = NULL;
}

int insertarAlFinal(tCola* cola, void* dato, unsigned tam){
    tNodo* aux = malloc(sizeof(tNodo));

    if(!aux){
        return 0; //COLA LLENA
    }

    aux->info = malloc(tam);

    if(!aux->info){
        free(aux);
        return 0;
    }

    memcpy(aux->info, dato, tam);
    aux->tamInfo = tam;
    aux->sig = NULL;

    if(cola->primero == NULL){
        cola->primero = aux;
    } else {
        cola->ultimo->sig = aux;
    }
    cola->ultimo = aux;

    return 1; //EXITO
}

int sacarAlComienzo(tCola* cola, void* dato, unsigned tam){
    tNodo* elim = cola->primero;

    if(!elim){
        return 0; //COLA VACIA
    }

    cola->primero = elim->sig;

    memcpy(dato, elim->info, MINIMO(elim->tamInfo, tam));

    free(elim->info);
    free(elim);

    if(cola->primero == NULL){
        cola->ultimo = NULL;
    }

    return 1;
}

int esColaLlena(const tCola* cola, unsigned tam){
    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));
    void* info = malloc(tam);

    free(aux);
    free(info);

    return !aux || !info;
}

int esColaVacia(const tCola* cola){
    return cola->primero == NULL;
}

void verPrimero(const tCola* cola, void* dato, unsigned tam){
    if(!cola->primero){
        return; //COLA VACIA
    }

    memcpy(dato, cola->primero->info, MINIMO(cola->primero->tamInfo, tam));
}

void vaciarCola(tCola* cola){
    while(cola->primero){
        tNodo* elim = cola->primero;
        cola->primero = elim->sig;
        free(elim->info);
        free(elim);
    }
    cola->ultimo = NULL;
}

