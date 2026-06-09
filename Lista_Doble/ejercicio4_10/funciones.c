#include "funciones.h"

/*
Diseñar y desarrollar una funcion denominada filter, la cual recibe como argumento un puntero a funcion y una lista, la funcion pasada como argumento
sera la encargada de producir el filtrado.
*/
tLista filter(const tLista* lista, unsigned tam, int(*funcion)(void*)){
    tLista listaFiltrada;
    crearLista(&listaFiltrada);

    tNodo* actual = *lista;

    if(!actual){
        return NULL; //lista vacia
    }

    while(actual->ant){
        actual = actual->ant;
    }

    while(actual){

        if(funcion(actual->info)){
            insertarAlComienzo(&listaFiltrada, actual->info, tam);
        }

        actual = actual->sig;
    }

    return listaFiltrada;
}

int alturaMayor(void* dato){
    tPersona* persona = (tPersona*)dato;
    if(persona->altura > 1.70){
        return 1; //debe incluirse en la lista nueva
    }
    return 0; //si es 0, no debe estar incluido
}


void insertarPersonasLista(tLista* lista, int(*insertar)(tLista*, void*, unsigned)){
    tPersona personas[] = {
        {3, "Carlos",  1.75},
        {1, "Ana",     1.62},
        {5, "Elena",   1.80},
        {2, "Bruno",   1.70},
        {4, "Diana",   1.58}
    };

    int cantPersonas = sizeof(personas) / sizeof(tPersona);
    int i;
    for(i = 0; i < cantPersonas; i++){
        insertar(lista, &personas[i], sizeof(tPersona));
    }
}

void mostrarPersona(const void* dato){
    tPersona* persona = (tPersona*)dato;

    printf("%d - %s - %.2f\n", persona->dni, persona->nombre, persona->altura);
}
