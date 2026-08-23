#include "lista.h"

void crearLista(tLista* lista){
    *lista = NULL;
}

int insertarAlInicio(tLista* lista, void* dato, unsigned tam){
    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(!nuevo){
        return 0;
    }

    nuevo->info = malloc(tam);
    if(!nuevo->info){
        return 0;
    }

    memcpy(nuevo->info, dato, tam);
    nuevo->tamInfo = tam;

    nuevo->sig = *lista;
    *lista = nuevo;

    return 1;
}

int sacarDelInicio(tLista* lista, void* dato, unsigned tam){
    if(!*lista){
        return 0;
    }

    tNodo* eliminar = *lista;

    memcpy(dato, eliminar->info, MINIMO(eliminar->tamInfo, tam));

    *lista = eliminar->sig;
    free(eliminar->info);
    free(eliminar);

    return 1;
}

void vaciarLista(tLista* lista){
    while(*lista){
        tNodo* aux = *lista;
        *lista = aux->sig;
        free(aux->info);
        free(aux);
    }
}

