#include "tda_lista.h"

void crearLista(tLista* lista){
    *lista = NULL;
}

int insertarAlFinal(tLista* lista, void* dato, unsigned tam){
    while(*lista){
        lista = &(*lista)->sig;
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

    nuevo->sig = NULL;
    *lista = nuevo;

    return 1; //TODO OK
}


int sacarDelFinal(tLista* lista, void* dato, unsigned tam){
    if(!*lista){
        return 0; //lista vacia
    }

    while((*lista)->sig){
        lista = &(*lista)->sig;
    }

    tNodo* eliminar = *lista;

    memcpy(dato, eliminar->info, MINIMO(eliminar->tamInfo, tam));

    *lista = NULL;
    free(eliminar->info);
    free(eliminar);
    return 1; //TODO OK
}

//flujo ordenamiento de lista simplemente enlazada
//usar lista simplemente enlazada auxiliar
//sacar de lista original
//insertar ordenadamente en lista auxiliar
//si se busca ordenar in-situ realizar *lista = lista_aux

//insertar el primero
//si el proximo (sig) es menor al que ya está, reemplazarlo (sacarprimero, insertar al inicio el nuevo)
//luego el primero que quedo en un auxiliar, insertarlo al final.
//while (lista) --mientras la lista original tenga elementos
//realizar el proceso


int ordenarLista (tLista* lista, unsigned tam, int(*cmp)(const void*, const void*)){
    tLista lista_aux;
    crearLista(&lista_aux); //lista vacia auxiliar

    if(!*lista){
        return 0; //nada que ordenar
    }

    tNodo* actual = *lista;

    while(actual){
        insertarOrdenado(&lista_aux, actual->info, tam, cmp);
        actual = actual->sig;
    }

    vaciarLista(lista);

    *lista = lista_aux;
    return 1; //lista ordenada;
}


int insertarOrdenado(tLista* lista, const void* dato, unsigned tam, int(*cmp)(const void*, const void*)){
    while(*lista && cmp((*lista)->info, dato) < 0){
        lista = &(*lista)->sig;
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
    return 1;
}

void invertirLista(tLista* lista, unsigned tam){
    tNodo* actual = *lista;

    tLista lista_aux;
    crearLista(&lista_aux);

    void* dato = malloc(tam);

    while(*lista){
        sacarDelInicio(lista, dato, tam);
        insertarAlInicio(&lista_aux, dato, tam);
    }
    free(dato);
    *lista = lista_aux;
}

int insertarAlInicio(tLista* lista,void* dato,unsigned tam){
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
        tNodo* eliminar = *lista;
        *lista = eliminar->sig;
        free(eliminar->info);
        free(eliminar);
    }
}
