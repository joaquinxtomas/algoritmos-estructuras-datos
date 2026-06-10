#include "funciones.h"

/*
Desarrollar funcion reduce, debe aplicar la funcion y retornar una nueva lista con el resultado
*/
tLista reduce(tLista* lista, unsigned tam, void*(*funcion)(void*, void*)){
    tNodo* actual = *lista;

    tLista listaNueva;
    crearLista(&listaNueva);

    if(!actual){
        return NULL; //nada que hacer
    }

    while(actual->ant){
        actual = actual->ant;
    }

    void* acumulado = malloc(tam);
    memcpy(acumulado, actual->info, tam);
    actual = actual->sig;

    while(actual){
        funcion(acumulado, actual->info);

        actual = actual->sig;
    }

    insertarAlComienzo(&listaNueva, acumulado, tam);
    free(acumulado);

    return listaNueva;
}

void* sumar(void* acumulado, void* actual){
    *(int*)acumulado += *(int*)actual;
}

void insertarNumLista(tLista* lista, int(*insertar)(tLista*, void*, unsigned)){
    int numeros[] = {1,2,3,4,5};

    int cantNums = sizeof(numeros) / sizeof(int);
    int i;
    for(i = 0; i < cantNums; i++){
        insertar(lista, &numeros[i], sizeof(int));
    }
}

void mostrarNumero(const void* dato){
    int numero = *(int*)dato;

    printf("%d -", numero);
}

