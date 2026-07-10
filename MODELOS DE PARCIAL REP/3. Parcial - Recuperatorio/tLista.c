#include "tLista.h"

void crearLista(tLista* lista){
    *lista = NULL;
}

int insertarAlFinal(tLista* lista, void* dato, unsigned tam){

    while(*lista){
        lista = &(*lista)->sig; //se ubica al final
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

    *lista = nuevo;
    nuevo->sig = NULL;

    return 1; //exito
}

int sacarDelFinal(tLista* lista, void* dato, unsigned tam){
    if(*lista == NULL){
        printf("LISTA VACIA.\n");
        return 0;
    }

    while((*lista)->sig){
        lista = &(*lista)->sig;
    }

    tNodo* eliminar = *lista;
    memcpy(dato, eliminar->info, tam);

    free(eliminar->info);
    free(eliminar);

    *lista = NULL; //no convence

    return 1;
}

int insertarOrdenado(tLista* lista, void* dato, unsigned tam, int(*cmp)(const void*, const void*)){
    while(*lista && cmp((*lista)->info, dato) < 0){
        lista = &(*lista)->sig;
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

    nuevo->sig = *lista;
    *lista = nuevo;

    return 1; //exito
}

int insertarAlPrincipio(tLista* lista, void* dato, unsigned tam){
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

    nuevo->sig = *lista;
    *lista = nuevo;

    return 1;
}

int sacarDelPrincipio(tLista* lista, void* dato, unsigned tam){
    if(*lista == NULL){
        printf("LISTA VACIA.\n");
        return 0;
    }

    tNodo* eliminar = *lista;

    memcpy(dato, eliminar->info, tam);
    *lista = eliminar->sig;

    free(eliminar->info);
    free(eliminar);

    return 1;
}

int invertirLista(tLista* lista, unsigned tam){
    if(*lista == NULL){
        printf("LISTA VACIA.\n");
        return 0;
    }

    tLista listaAux;
    crearLista(&listaAux);

    while(*lista){
        void* aux = malloc(tam);
        sacarDelPrincipio(lista, aux, tam);
        insertarAlPrincipio(&listaAux, aux, tam);
        free(aux);
    }

    *lista = listaAux;

    return 1;
}

void recorrerLista(tLista* lista, void(*accion)(const void*)){
    if(*lista == NULL){
        printf("LISTA VACIA.\n");
        return;
    }

    while(*lista){
        accion((*lista)->info);
        lista = &(*lista)->sig;
    }
}

int listaVacia(tLista* lista){
    return *lista == NULL;
}

int listaLlena(tLista* lista, unsigned tam){
    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));
    void* info = malloc(tam);

    free(info);
    free(aux);

    return !aux || !info;
}

void vaciarLista(tLista* lista, unsigned tam){
    while(*lista){
        tNodo* eliminar = *lista;
        *lista = eliminar->sig;
        free(eliminar->info);
        free(eliminar);
    }
}

int ordenarLista(tLista* lista, unsigned tam, int(*cmp)(const void*, const void*)){
    tLista listaAux;
    crearLista(&listaAux);

    tNodo* rec = *lista;

    while(rec){
        insertarOrdenado(&listaAux, rec->info, tam, cmp);
        rec = rec->sig;
    }

    vaciarLista(lista, tam);
    *lista = listaAux;
    return 1;
}


