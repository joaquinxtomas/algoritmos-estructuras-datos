#include "ListaDoble.h"

void crearLista(tLista* lista){
    *lista = NULL;
}

void vaciarLista(tLista* lista){
    tNodo* actual = *lista;

    if(actual){

        while(actual->ant){
            actual = actual->ant;
        }

        while(actual){
            tNodo* aux = actual->sig;
            free(actual->info);
            free(actual);
            actual = aux;
        }
        *lista = NULL;
    }

}

int listaVacia(const tLista* lista){
    return *lista == NULL;
}

int listaLlena(const tLista* lista, unsigned tam){
    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    void *aux = malloc(tam);

    free(nuevo);
    free(aux);
    return aux == NULL || nuevo == NULL;
}

int insertarAlFinal(tLista* lista, void* dato, unsigned tam){
    tNodo* actual = *lista, *nuevo;

    if(actual){
        while(actual->sig){
            actual = actual->sig;
        }
    }

    if((nuevo = (tNodo*)malloc(sizeof(tNodo))) == NULL ||
       (nuevo->info = malloc(tam)) == NULL){

        free(nuevo);
        return 0;
       }

    memcpy(nuevo->info, dato, tam);
    nuevo->tam = tam;
    nuevo->sig = NULL;
    nuevo->ant = actual;
    if(actual){
        actual->sig = nuevo;
    }

    *lista = nuevo;
    return 1;
}

int insertarAlComienzo(tLista* lista, const void* dato, unsigned tam){
    tNodo* actual = *lista, *nuevo;
    if(actual){
        while(actual->ant){
            actual = actual->ant;
        }
    }

    if( (nuevo = malloc(sizeof(tNodo))) == NULL || (nuevo->info = malloc(tam)) == NULL ){
        free(nuevo);
        return 0; //NO MEMORIA
    }

    memcpy(nuevo->info, dato, tam);
    nuevo->tam = tam;

    nuevo->ant = NULL;
    nuevo->sig = actual;
    if(actual){
        actual->ant = nuevo;
    }
    *lista = nuevo; //siempre apunta al ultimo nodo insertado
    return 1;
}

void mostrarDeDerIzq(const tLista* lista, void(*mostrar)(const void* dato)){
    tNodo* actual = *lista;
    if(actual){
        while(actual->sig){
            actual = actual->sig;
        }

        while(actual){
            mostrar(actual->info);
            actual = actual->ant;
        }
    }
}

void mostrarDeIzqDer(const tLista* lista, void(*mostrar)(const void* dato)){
    tNodo* actual = *lista;
    if(actual){
        while(actual->ant){
            actual = actual->ant;
        }

        while(actual){
            mostrar(actual->info);
            actual = actual->sig;
        }
    }
}

