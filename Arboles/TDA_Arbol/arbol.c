#include "arbol.h"

/** PRIMITIVAS DE UN ARBOL **/
//CREAR ARBOL
void crearArbol(tArbol *arbol){
    *arbol = NULL;
}

//INSERTAR ELEMENTO
int insertarRecArbolBinBusqueda(tArbol* arbol, const void* dato, unsigned tam, int(*cmp)(const void*, const void*)){
    tNodoArbol *nue;
    int rc;

    if(*arbol){
        if((rc = cmp(dato, (*arbol)->info)) < 0){
            return insertarRecArbolBinBusqueda(&(*arbol)->izq, dato, tam, cmp);
        }
        if(rc > 0){
            return insertarRecArbolBinBusqueda(&(*arbol)->der, dato, tam, cmp);
        }
        return DUPLICADO;
    }

    if(!reservarMemoriaNodo(nue, sizeof(tNodoArbol), nue->info, tam)){
        return SIN_MEMORIA;
    }
    nue->tamInfo = tam;
    memcpy(nue->info, dato, tam);
    nue->der = NULL;
    nue->izq = NULL;
    *arbol = nue; //apunta a la raiz
    return TODO_OK;
}

//BUSQUEDA
int buscarEnArbol(const tArbol* arbol, void* dato, unsigned tam, int(*cmp)(const void*, const void*)){
    if(!*arbol){
        return 0;
    }

    int comp = cmp(dato, (*arbol)->info);

    if(comp == 0){
        memcpy(dato, (*arbol)->info, tam);
        return 1;
    }

    if(comp < 0){
        return buscarEnArbol(&(*arbol)->izq, dato, tam, cmp);
    } else {
        return buscarEnArbol(&(*arbol)->der, dato, tam, cmp);
    }

}

//EN ORDEN
void recorrerEnOrdenRecArbolBinBusqueda(const tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*)){
    if(!*arbol){
        return;
    }

    recorrerEnOrdenRecArbolBinBusqueda(&(*arbol)->izq, n+1,params, accion);
    accion((*arbol)->info, (*arbol)->tamInfo, n, params);
    recorrerEnOrdenRecArbolBinBusqueda(&(*arbol)->der, n+1, params, accion);
}

//PRE ORDEN
void recorrerPreOrdenRecArbolBinBusqueda(const tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*)){
    if(!*arbol){
        return;
    }

    accion((*arbol)->info, (*arbol)->tamInfo, n, params);
    recorrerPreOrdenRecArbolBinBusqueda(&(*arbol)->izq, n+1, params, accion);
    recorrerPreOrdenRecArbolBinBusqueda(&(*arbol)->der, n+1, params, accion);
}

//POS ORDEN
void recorrerPosOrdenRecArbolBinBusqueda(const tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*)){
    if(!*arbol){
        return;
    }
    recorrerPosOrdenRecArbolBinBusqueda(&(*arbol)->izq, n+1, params, accion);
    recorrerPosOrdenRecArbolBinBusqueda(&(*arbol)->der, n+1, params, accion);
    accion((*arbol)->info, (*arbol)->tamInfo, n, params);
}

//ELIMINAR ARBOL
void eliminarArbol(tArbol *arbol){
    if(*arbol){
        eliminarArbol(&(*arbol)->izq);
        eliminarArbol(&(*arbol)->der);
        free((*arbol)->info);
        free(*arbol);
        *arbol = NULL;
    }
}

