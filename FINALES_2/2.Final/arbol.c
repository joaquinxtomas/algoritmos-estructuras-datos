#include "arbol.h"

void crearArbol(tArbol* arbol){
    *arbol = NULL;
}

int insertarEnArbol(tArbol* arbol, void* elemento, unsigned tam, int(*cmp)(void*,void*)){
    while(*arbol){
        if(cmp((*arbol)->info, elemento) > 0){
            arbol = &(*arbol)->izq;
        } else if(cmp((*arbol)->info, elemento) < 0){
            arbol = &(*arbol)->der;
        } else {
            return 0; //elemento duplicado
        }
    }

    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(!nuevo){
        return 0; //sin memoria
    }

    nuevo->info = malloc(tam);
    if(!nuevo->info){
        free(nuevo);
        return 0; //sin memoria
    }

    memcpy(nuevo->info, elemento, tam);
    nuevo->tamInfo = tam;

    nuevo->izq = nuevo->der = NULL;
    *arbol = nuevo;

    return 1; //exitoso
}

void recorrerArbolPreOrden(tArbol* arbol, unsigned tam, int n, void* params, void(*accion)(void*, int, void*)){
    if(!*arbol){
        return; //arbol vacio
    }

    recorrerArbolPreOrden(&(*arbol)->izq, tam, n + 1, params, accion);
    accion((*arbol)->info, n, params);
    recorrerArbolPreOrden(&(*arbol)->der, tam, n+1, params, accion);
}

void vaciarArbol(tArbol* arbol){
    while(*arbol){
        free(&(*arbol)->der);
        free(&(*arbol)->izq);
        free(arbol);
    }
}

int cantNodosHastaNivel(tArbol* arbol, int nivel){
    if(!*arbol || nivel < 0){
        return 0;
    }

    if(nivel == 0){
        return 1;
    }

    return cantNodosHastaNivel(&(*arbol)->izq, nivel - 1) +
            cantNodosHastaNivel(&(*arbol)->der, nivel - 1) + 1;
}

int cantNodosNivel(tArbol* arbol, int nivel){
    return cantNodosHastaNivel(arbol, nivel) - cantNodosHastaNivel(arbol, nivel - 1);
}

int nivelCompleto(tArbol* arbol, int nivel){
    if (cantNodosNivel(arbol, nivel) == pow(nivel)){
        return 1;
    }
    return 0;
}

