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
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, dato, tam);
    nuevo->tamInfo = tam;

    nuevo->sig = *lista;
    *lista = nuevo;

    return 1;
}

void mostrarInverso(tLista* lista, void(*accion)(const void*), int(*condicion)(const void*)){
    if(!*lista){
        return;
    }
    mostrarInverso(&(*lista)->sig, accion, condicion);
    if(condicion((*lista)->info)){
        accion((*lista)->info);
    }
}
