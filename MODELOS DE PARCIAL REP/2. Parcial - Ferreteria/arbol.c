#include "arbol.h"

void crearArbol(tArbol* arbol){
    *arbol = NULL; //o izq y der null?
}

int insertarEnArbol(tArbol* arbol, void* dato, unsigned tam, int(*cmp)(const void*, const void*)){
    while(*arbol){
        if(cmp((*arbol)->info, dato) > 0){
            arbol = &(*arbol)->izq;
        } else if (cmp((*arbol)->info, dato) < 0){
            arbol = &(*arbol)->der;
        } else {
            printf("REGISTRO DUPLICADO.\n");
            return 0;
        }
    }

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

    nuevo->der = nuevo->izq = NULL;
    *arbol = nuevo;

    return 1;
}

void recorrerInOrden(tArbol* arbol, void* params, unsigned n, unsigned tam, void(*accion)(void*, unsigned, void*)){
    if(!*arbol){
        return;
    }

    recorrerInOrden(&(*arbol)->izq, params, n + 1, tam, accion);
    accion((*arbol)->info, n, params);
    recorrerInOrden(&(*arbol)->der, params, n + 1, tam, accion);
}

int buscarPorClave(tArbol* arbol, void* clave, unsigned tam, int(*cmp)(const void*, const void*)){
    if(!*arbol){
        return 0;
    }

    while(*arbol){
        if(cmp((*arbol)->info, clave) > 0){
            arbol = &(*arbol)->izq;
        } else if (cmp((*arbol)->info, clave) < 0){
            arbol = &(*arbol)->der;
        } else {
            memcpy(clave, (*arbol)->info, tam);
            return 1;
        }
    }
    return 0;
}
