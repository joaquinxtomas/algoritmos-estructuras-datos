#include "lista.h"

void crearLista(tLista* lista){
    *lista = NULL;
}

int insertarUltimo(tLista* lista, tNodo** ultimo, void* dato, unsigned tam){
    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(!nuevo) return 0;

    nuevo->info = malloc(tam);
    if(!nuevo->info){
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, dato, tam);
    nuevo->tamInfo = tam;

    nuevo->sig = NULL;
    nuevo->ant = *ultimo;

    if(*ultimo){
        (*ultimo)->sig = nuevo;
    } else {
        *lista = nuevo;
    }

    *ultimo = nuevo;
    return 1;
}

int insertarAlInicio(tLista* lista, void* dato, unsigned tam){

    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(!nuevo) return 0;

    nuevo->info = malloc(tam);
    if(!nuevo->info){
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, dato, tam);
    nuevo->tamInfo = tam;

    nuevo->sig = *lista;
    if(*lista){
        (*lista)->ant = nuevo;
    }
    *lista = nuevo;

    return 1;
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

void vaciarLista(tLista* lista){
    if(!*lista) return;
    while((*lista)->ant){
        lista = &(*lista)->ant;
    }

    while(*lista){
        tNodo* aux = *lista;
        *lista = aux->sig;
        free(aux->info);
        free(aux);
    }
}

void eliminarDuplicados(tLista* lista, int(*cmp)(const void*, const void*), void(*accion)(const void*, const void*)){

    while(*lista){
        tNodo** aux = &(*lista)->sig;
        while(*aux){
            if(cmp((*lista)->info, (*aux)->info) == 0){
                accion((*lista)->info, (*aux)->info);

                tNodo* eliminar = *aux;
                *aux = eliminar->sig;
                if(*aux){
                    (*aux)->ant = eliminar->ant;
                }
                free(eliminar->info);
                free(eliminar);
            } else {
                aux = &(*aux)->sig;
            }
        }
        lista = &(*lista)->sig;
    }
}

void reduce(tLista* lista, void* res, void(*accion)(const void*, void*)){
    tNodo** aux = lista;
    while(*aux){
        accion((*aux)->info, res);
        aux = &(*aux)->sig;
    }
}


