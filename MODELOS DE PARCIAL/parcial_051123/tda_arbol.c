#include "tda_arbol.h"
void crearArbol(tArbol* arbol){
    *arbol = NULL;
}

int insertarEnArbol(tArbol* arbol, void* dato, unsigned tam, int(*cmp)(const void*, const void*)){
    tNodo *nuevo;

    while(*arbol){
        if(cmp(dato, (*arbol)->info) < 0){
            //va por izq
            arbol = &(*arbol)->izq;
        } else if (cmp(dato,(*arbol)->info) > 0) {
            //va por der
            arbol = &(*arbol)->der;
        } else {
            printf("La clave ya existe en el arbol.");
            return 0; // clave duplicada
        }
    }

    nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(!nuevo)
    {
        printf("Sin memoria.\n");
        return 0;
    }

    nuevo->info = malloc(tam);
    if(!nuevo->info){
        free(nuevo);
        printf("Sin memoria.\n");
        return 0;
    }

    nuevo->tamInfo = tam;
    memcpy(nuevo->info, dato, tam);

    nuevo->der = nuevo->izq = NULL;
    *arbol = nuevo;
    return 1; //OK
}

void recorrerEnOrden(tArbol* arbol, void* params, void(*accion)(const void*, unsigned, const void*)){
    if(!*arbol){
        return; //arbol vacio
    }

    recorrerEnOrden(&(*arbol)->izq, params, accion);
    accion((*arbol)->info, (*arbol)->tamInfo, params);
    recorrerEnOrden(&(*arbol)->der, params, accion);
}

void vaciarArbol(tArbol* arbol){
    if(!*arbol){
        return;
    }

    vaciarArbol(&(*arbol)->izq);
    vaciarArbol(&(*arbol)->der);
    free((*arbol)->info);
    free(*arbol);
    *arbol = NULL;
}
