#include "funciones.h"

/*
Se solicita que diseñe y desarrolle una funcion denominada map, la cual aplica la funcion recibida como puntero a uno de los elementos de la lista y
retorna una nueva lista con los resultados de la transformación realizada
*/

//version 1
tLista map2(tLista* lista, unsigned tam, void(*funcion)(void*)){
    //debe recorrer toda la lista, aplicar los cambios y devolver otra
    tLista listaNueva;
    crearLista(&listaNueva);

    tNodo* actual = *lista;

    if(!actual){
        return NULL; //lista vacia
    }

    while(actual->ant){
        actual = actual->ant;
    }

    while(actual){
        insertarAlComienzo(&listaNueva, actual->info, tam);

        funcion(listaNueva->info);

        actual = actual->sig;
    }

    return listaNueva;
}

//version 2
/*
void map2(tLista* lista, tLista* listaNueva, unsigned tam, void(*funcion)(void*)){
    //debe recorrer toda la lista, aplicar los cambios y devolver otra

    tNodo* actual = *lista;
    if(!actual){
        return;//lista vacia
    }

    while(actual->ant){
        actual = actual->ant;
    }

    while(actual){
        void* nuevo = malloc(tam);
        memcpy(nuevo, actual->info, tam);
        funcion(nuevo);

        insertarAlComienzo(listaNueva, nuevo, tam);
        free(nuevo);
        actual = actual->sig;
    }
}*/

void sumaDni(void* dato){
    tPersona* persona = (tPersona*)dato;
    persona->dni = persona->dni + 2;
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
