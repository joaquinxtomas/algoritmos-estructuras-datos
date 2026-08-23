#include "lista.h"

int insertarEnTop(tLista* lista, void* dato, unsigned tam, int(*cmp)(const void*, const void*), unsigned n){
    int ce = 0;

    while(*lista && (cmp((*lista)->info, dato)) <= 0){
            lista = &(*lista)->sig;
            ce++;
    }

    if(ce >= n){
        return 0;
    }

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

    while(*lista && ce != n){
        lista = &(*lista)->sig;
        ce++;
    }

    if(ce == n){
        while(*lista){
            tNodo* aux = *lista;
            *lista = aux->sig;
            free(aux->info);
            free(aux);
        }
    }

    return 1;
}

void crearLista(tLista* lista){
    *lista = NULL;
}

void vaciarLista(tLista* lista){
    while(*lista){
        tNodo* aux = *lista;
        *lista = aux->sig;
        free(aux->info);
        free(aux);
    }
}

void recorrerLista(tLista* lista, void(*accion)(const void*)){
    if(!*lista){
        return;
    }
    while(*lista){
        accion((*lista)->info);
        lista = &(*lista)->sig;
    }
}
