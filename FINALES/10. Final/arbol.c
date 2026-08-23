#include "arbol.h"

void crearArbol(tArbol* arbol){
    *arbol = NULL;
}

int insertarEnArbol(tArbol* arbol, void* dato, unsigned tam, int(*cmp)(const void*, const void*)){
    int res;
    while(*arbol){
        if(res = cmp((*arbol)->info, dato) > 0){
            arbol = &(*arbol)->izq;
        } else if(res < 0){
            arbol = &(*arbol)->der;
        } else {
            return 0; //DUPLICADO
        }
    }

    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(!nuevo) return 0;

    nuevo->info = malloc(tam);
    if(!nuevo->info){
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, dato, tam);
    nuevo->tamInfo = tam;

    *arbol = nuevo;
    nuevo->izq = nuevo->der = NULL;

    return 1;
}

void cargarBalanceadoRec(FILE* archivo, tArbol* arbol, int inicio, int fin, unsigned tam, int(*cmp)(const void*, const void*)){
    if(inicio > fin){
        return;
    }

    int medio = (inicio + fin) / 2;

    void* buffer = malloc(tam);
    if(!buffer) return;

    fseek(archivo, medio * tam, SEEK_SET);
    fread(buffer, tam, 1, archivo);
    insertarEnArbol(&arbol, buffer, tam, cmp);
    free(buffer);

    cargarBalanceadoRec(archivo, arbol, inicio, medio - 1, tam, cmp);
    cargarBalanceadoRec(archivo, arbol, medio + 1, fin, tam, cmp);
}

int buscarPorCampo(tArbol* arbol, void* datoBusqueda ,int(*cmp)(const void*, const void*), void* dato, unsigned tam, tArbol* subArbol){

   if(!*arbol) return 0;

    if(cmp((*arbol)->info, datoBusqueda) == 0){
        memcpy(dato, (*arbol)->info, tam);
        copiarArbol(subArbol, arbol);
        return 1;
    }

    encontrado = buscarPorCampo(&(*arbol)->izq, datoBusqueda, cmp, dato, tam, subArbol);

    if(encontrado){
        return 1;
    }

    return buscarPorCampo(&(*arbol)->der, datoBusqueda, cmp, dato, tam ,subArbol);
}

int copiarArbol(tArbol* destino, tArbol* origen){
    if(!*origen){
        *destino =NULL;
        return 1;
    }

    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(!nuevo) return 0;

    nuevo->info = malloc((*origen)->tamInfo);
    if(!nuevo->info){
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, (*origen)->info, (*origen)->tamInfo);
    nuevo->tamInfo = (*origen)->tamInfo;
    nuevo->izq = NULL;
    nuevo->der = NULL;

    *destino = nuevo;

    copiarArbol(&nuevo->izq, &(*origen)->izq);
    copiarArbol(&nuevo->der, &(*origen)->der);

    return 1;
}
