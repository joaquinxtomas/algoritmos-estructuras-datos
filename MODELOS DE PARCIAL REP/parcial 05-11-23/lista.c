#include "lista.h"

void crearLista(tLista* lista){
    *lista = NULL;
}

int insertarAlFinal(tLista* lista, void* dato, unsigned tam){
    while(*lista){
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

    nuevo->sig = NULL;
    *lista = nuevo;

    return 1;
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

    memcpy(dato, eliminar->info, MINIMO(eliminar->tamInfo, tam));

    *lista = NULL;
    free(eliminar->info);
    free(eliminar);

    return 1;
}

int sacarDelInicio(tLista* lista, void* dato, unsigned tam){
    if(*lista == NULL){
        printf("LISTA VACIA.\n");
        return 0;
    }

    tNodo* eliminar = *lista;
    memcpy(dato, eliminar->info, MINIMO(eliminar->tamInfo, tam));

    *lista = eliminar->sig;
    free(eliminar->info);
    free(eliminar);

    return 1;
}

/*
int insertarEnPodio(tLista* lista, void* dato, unsigned tam, int(*cmp)(const void*, const void*), int limite){
    int pos = 0;
    tNodo* nodoLimite, *nuevo;

    if(limite <= 0){
        return 0;
    }

    while(*lista && cmp((*lista)->info, dato) >= 0){
        lista = &(*lista)->sig;
        pos++;
    }

    if(pos >= limite && (!*lista || cmp((*lista)->info, dato) != 0)){
        return 0;
    }

    nuevo = malloc(sizeof(tNodo));
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

    lista = &(*lista)->sig;
    pos += 2;

    while(*lista && pos < limite){
        pos++;
        lista = &(*lista)->sig;
    }

    nodoLimite = *lista;
    if(pos <= limite){
        while(*lista && cmp((*lista)->info, nodoLimite->info) == 0){
            lista = &(*lista)->sig;
        }
    }

    while(*lista){
        tNodo* eliminar = *lista;
        *lista = eliminar->sig;
        free(eliminar->info);
        free(eliminar);
    }

    return 1;
}
*/
int insertarEnPodio(tLista* lista, void* dato, unsigned tam, int(*cmp)(const void*, const void*), int n){
    if(n <= 0){
        return 0;
    }

    if(!insertarOrdenado(lista, dato, tam, cmp)){
        return 0;
    }

    recortarPodio(lista, n, cmp);
    return 1;
}

void recortarPodio(tLista* lista, int n, int(*cmp)(const void*, const void*)){
    int contador = 0;

    while(*lista && contador <= n){
        lista = &(*lista)->sig;
        contador++;
    }

    if(!*lista){
        return;
    }

    tNodo* limite = *lista;

    while(*lista && cmp((*lista)->info, limite->info) == 0){
        lista = &(*lista)->sig;
    }

    while(*lista){
        tNodo* eliminar = *lista;
        *lista = eliminar->sig;
        free(eliminar->info);
        free(eliminar);
    }
}

int insertarOrdenado(tLista* lista, void* dato, unsigned tam, int(*cmp)(const void*, const void*)){
    while(*lista && cmp((*lista)->info, dato) >= 0){
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

    return 1;
}
