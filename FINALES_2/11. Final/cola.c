#include "cola.h"

void crearCola(tCola* cola){
    cola->primero = cola->ultimo = NULL;
}

int ponerEnCola(tCola* cola, void* elemento, unsigned tam){
    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(!nuevo){
        return 0; //error de memoria
    }

    nuevo->info = malloc(tam);
    if(!nuevo->info){
        free(nuevo);
        return 0; //error de memoria
    }

    memcpy(nuevo->info, elemento, tam);
    nuevo->tamInfo = tam;
    nuevo->sig = NULL;

    if(cola->ultimo){
        cola->ultimo->sig = nuevo;
    } else {
        cola->primero = nuevo;
    }
    cola->ultimo = nuevo;

    return 1;
}

int sacarDeCola(tCola* cola, void* elemento, unsigned tam){
    if(!cola->primero){
        return 0; //cola vacia
    }

    tNodo* eliminar = cola->primero;
    memcpy(elemento, eliminar->info, MINIMO(eliminar->tamInfo, tam));

    cola->primero = eliminar->sig;

    if(!cola->primero){
        cola->ultimo = NULL;
    }

    free(eliminar->info);
    free(eliminar);

    return 1;
}

int colaLlena(tCola* cola, unsigned tam){
    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));
    void* info = malloc(tam);
    free(aux);
    free(info);

    return !aux || !info;
}

int colaVacia(tCola* cola){
    return cola->primero == NULL;
}

int verPrimero(tCola* cola, void* elemento, unsigned tam){
    if(!cola->primero){
        return 0; //cola vacia
    }

    tNodo* ver = cola->primero;
    memcpy(elemento, ver->info, MINIMO(ver->tamInfo, tam));

    return 1;
}
