#include "cola.h"

void crearCola(tCola* cola){
    cola->primero = cola->ultimo = NULL;
}

int ponerEnCola(tCola* cola, void* dato, unsigned tam){
    tNodoCola* nuevo = (tNodoCola*)malloc(sizeof(tNodoCola));
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

    nuevo->sig = NULL;
    if(!cola->primero){
        cola->primero = nuevo;
    }else{
        cola->ultimo->sig = nuevo;
    }
    cola->ultimo = nuevo;

    return 1;
}

int sacarDeCola(tCola* cola, void* dato, unsigned tam){
    if(!cola->primero){
        printf("COLA VACIA.\n");
        return 0;
    }

    tNodoCola* eliminar = cola->primero;

    memcpy(dato, eliminar->info, tam);
    cola->primero = eliminar->sig;
    if(!cola->primero){
        cola->ultimo = NULL;
    }
    free(eliminar->info);
    free(eliminar);

    return 1;
}

int verPrimero(tCola* cola, void* dato, unsigned tam){
    if(!cola->primero){
        printf("COLA VACIA.\n");
        return 0;
    }

    memcpy(dato, cola->primero->info, tam);

    return 1;
}

int colaLlena(tCola* cola, unsigned tam){
    tNodoCola* aux = (tNodoCola*)malloc(sizeof(tNodoCola));
    void* info = malloc(tam);
    free(aux);
    free(info);
    return !aux || !info;
}

int colaVacia(tCola* cola){
    return cola->primero == NULL;
}

void vaciarCola(tCola* cola){
    while(cola->primero){
        tNodoCola* eliminar = cola->primero;
        cola->primero = eliminar->sig;
        free(eliminar->info);
        free(eliminar);
    }
}


