#include "lista.h"

void crearLista (tLista* lista){
    *lista = NULL;
}

int listaVacia(tLista* lista){
    return *lista == NULL;
}

int listaLlena(tLista* lista, size_t tam){
    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));
    void* info_aux = malloc(tam);

    free(aux);
    free(info_aux);

    return aux == NULL || info_aux == NULL;
}

void vaciarLista(tLista* lista){
    while(*lista){
        tNodo* elim = *lista;
        *p = elim->sig;
        free(elim);
        free(elim->info);
    }
}

int ponerAlComienzo(tLista* lista, void* elemento, size_t tam){
    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(!nuevo){
        return SIN_MEMORIA;
    }

    nuevo->info = malloc(tam);

    if(!nuevo->info){
        free(nuevo);
        return SIN_MEMORIA;
    }

    memcpy(nuevo->info, elemento, tam);
    nuevo->tamInfo = tam;
    nuevo->sig = *lista;
    *lista = nuevo;

    return TODO_OK;
}

int sacarPrimero(tLista* lista, void* elemento, size_t tam){
    tNodo* elim = *lista;

    if(*elim == NULL){
        return LISTA_VACIA;
    }

    memcpy(elemento, elim->info, MINIMO(elim->tamInfo, tam));
    *lista = elim->sig;

    free(elim->info);
    free(elim);

    return TODO_OK;
}

int verPrimero(tLista* lista, void* elemento, size_t tam){
    tNodo* elim = *lista;
    if(*elim == NULL){
        return LISTA_VACIA;
    }

    memcpy(elemento, elim->info, MINIMO(elim->tamInfo, tam));

    return TODO_OK;
}

int ponerAlFinal(tLista* lista, void* elemento, size_t tam){

    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));

    while(*lista){
        lista = &(*lista)->sig;
    }


    if(!nuevo){
        return SIN_MEMORIA;
    }

    nuevo->info = malloc(tam);
    if(!nuevo->info){
        free(nuevo);
        return SIN_MEMORIA;
    }

    memcpy(nuevo->info, elemento, tam);
    nuevo->tamInfo = tam;
    nuevo->sig = NULL;

    *lista->sig = nuevo;
}

int sacarUltimo(tLista* lista, void* elemento, size_t tam){

    if(*lista == NULL){
        return LISTA_VACIA;
    }

    while((*lista)->sig){
        lista = &(*lista)->sig;
    }

    tNodo* ult = *lista;
    memcpy(elemento, ult->info, MINIMO(ult->tamInfo, tam));

    free(ult->info);
    free(ult);

    *lista = NULL;

    return TODO_OK;
}

int verUltimo(const tLista* lista, void* elemento, size_t tam){
    if(*lista == NULL){
        return LISTA_VACIA;
    }

    while((*lista)->sig){
        lista = &(*lista)->sig;
    }

    tNodo* ult = *lista;
    memcpy(elemento, ult->info, MINIMO(ult->tamInfo, tam));

    return TODO_OK;
}

int ponerEnOrden(tLista* lista, void* elemento, size_t tam, int(*cmp)(void*, void*)){
    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(!nuevo){
        return SIN_MEMORIA;
    }

    nuevo->info = malloc(tam);
    if(!nuevo->info){
        free(nuevo);
        return SIN_MEMORIA;
    }

    while(*lista  && cmp((*lista)->info, nuevo->info) < 0){
        lista = &(*lista)->sig; // ejemplo para comprender: si tenemos una lista con [1,2,3,4,5,6,8] y buscamos insertar un 7, lista en este punto queda apuntando al SIGUIENTE del 6.
    }

    memcpy(nuevo->info, elemento, tam);
    nuevo->tamInfo = tam;

    nuevo->sig = *lista; // SIGUIENTE del 7 apunta al 8.
    *lista = nuevo; // SIGUIENTE del 6 apunta al 7.

    return TODO_OK;
}

int ordenar(tLista* lista, int(*cmp)(void*,void*)){
    tLista* primero = lista; //apunta al primero de la lista (al inicio absoluto)

    if(*lista == NULL){
        return LISTA_VACIA; // si esta vacia, salir, no se puede ordenar nada.
    }

    while((*lista)->sig){ //continuar mientras haya un siguiente, si no hay uno, no se puede modificar más nada.
        if(cmp((*lista)->info, (*lista)->sig->info) > 0){ //comparar entre la info del nodo ACTUAL y la del nodo SIGUIENTE
            tLista *q = pri; //genera una lista que apunta al primero?
            tNodo* aux = (*lista)->sig; //nodo auxiliar que apunta al siguiente del nodo actual.

            (*lista)->sig = aux->sig; //

            while(cmp((*q)->info, aux->info) > 0){
                q = &(*q)->sig;
            }
            aux->sig = *q;
            *q = aux;
        } else {
            p = &(*p)->sig;
        }
    }


}


