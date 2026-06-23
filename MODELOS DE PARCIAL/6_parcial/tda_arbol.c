#include "tda_arbol.h"

void crearArbol(tArbol* arbol){
    *arbol = NULL;
}

void vaciarArbol(tArbol* arbol){
    if(!*arbol){
        return;
    }

    vaciarArbol(&(*arbol)->izq);
    vaciarArbol(&(*arbol)->der);
    free((*arbol)->info);
    free(*arbol);
}

void recorrerEnPosOrden(tArbol* arbol, unsigned n, void* params,void(*accion)(const void*, unsigned, const void*)){
    if(!*arbol){
        return;
    }

    recorrerEnPosOrden(&(*arbol)->izq, n+1, params, accion);
    recorrerEnPosOrden(&(*arbol)->der, n+1, params, accion);
    accion((*arbol)->info, n, params);
}

void recorrerEnOrden(tArbol* arbol, unsigned n, void* params,void(*accion)(const void*, unsigned, const void*)){
    if(!*arbol){
        return;
    }

    recorrerEnOrden(&(*arbol)->izq, n+1, params, accion);
    accion((*arbol)->info, n, params);
    recorrerEnOrden(&(*arbol)->der, n+1, params, accion);
}

int insertarEnArbol(tArbol* arbol, void* dato, unsigned tam, int(*cmp)(const void*, const void*)){
    int res;

    while(*arbol){
        if((res = cmp(dato, (*arbol)->info)) < 0){
            arbol = &(*arbol)->izq;
        } else if(res > 0){
            arbol = &(*arbol)->der;
        } else {
            return DUPLICADO;
        }
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
    nuevo->der = nuevo->izq = NULL;
    *arbol = nuevo;
    return TODO_OK;
}


