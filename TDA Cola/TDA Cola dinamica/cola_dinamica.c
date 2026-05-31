#include "cola_dinamica.h"

void crearCola(Cola* cola){
    cola->ptrInicio = cola->ptrFin = NULL;
}

int insertarEnCola(Cola* cola, const void* elemento, size_t tamElemento){

    tNodo* nuevo = (tNodo*)malloc(tamElemento);

    if(!nuevo){
        return SIN_MEMORIA;
    }

    nuevo->info = malloc(tamElemento);
    if(!nuevo->info){
        free(nuevo);
        return SIN_MEMORIA;
    }

    nuevo->tamInfo = malloc(tamElemento);
    memcpy(nuevo->info, elemento, tamElemento);

    nuevo->siguiente = NULL;
    if(cola->ptrFin){
        cola->ptrFin->siguiente = nuevo;
    } else {
        cola->ptrInicio = nuevo;
    }

    cola->ptrFin = nuevo;

    return TODO_OK;

}

int sacarDeCola(Cola* cola, void* elemento, size_t tamElemento){
    tNodo* eliminar = cola->ptrInicio;

    if(!eliminar){
        return COLA_VACIA;
    }

    //no se si es necesario asignar el tamaño
    memcpy(elemento, eliminar->info, MINIMO(tamElemento, eliminar->tamInfo));
    cola->ptrInicio = eliminar->siguiente;

    if(!cola->ptrInicio){
        cola->ptrFin = NULL;
    }

    free(eliminar->info);
    free(eliminar);

    return TODO_OK;
}

int verFrenteCola(const Cola* cola, const void* elemento, size_t tamElemento){
    if(!cola->ptrInicio){
        return COLA_VACIA;
    }

    memcpy(elemento, cola->ptrInicio->info, MINIMO(tamElemento, cola->ptrInicio->tamInfo));

    return TODO_OK;
}

int verFondoCola(const Cola* cola, const void* elemento, size_t tamElemento){
    if(!cola->ptrInicio){
        return COLA_VACIA;
    }

    memcpy(elemento, cola->ptrFin->info, MINIMO(tamElemento, cola->ptrFin->tamInfo));

    return TODO_OK;
}

void vaciarCola(Cola* cola){
    while(cola->ptrInicio){
        tNodo* eliminar = cola->ptrInicio;
        cola->ptrInicio = eliminar->siguiente;
        free(eliminar->info);
        free(eliminar);
    }
}

int colaLlena(const Cola* cola, size_t tamElemento){
    void* nodo = malloc(sizeof(tNodo));
    void* info = malloc(tamElemento);

    free(nodo);
    free(info);

    return !nodo || !info;
}

int colaVacia(const Cola* cola){
    return !cola->ptrInicio;
}

void imprimirCola(const Cola* cola, void (*mostrar)(void*)){
    if(colaVacia(cola)){
        printf("La cola esta vacia.");
        return;
    }

    tNodo* aux = cola->ptrInicio;

    while(aux){
        mostrar(aux->info);
        aux = aux->siguiente;
    }
    printf("\n\n");
}

