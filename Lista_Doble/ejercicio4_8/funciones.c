#include "funciones.h"

//Resuelva la inserción al comienzo, al final y en orden por una clave.
//al comienzo y al final están definidas en las primitivas. Aquí se resolverá en orden por una clave.
int insertarEnOrden(tLista* lista, const void* dato, unsigned tam, int(*cmp)(const void*, const void*)){
    tNodo* actual = *lista, *nuevo;

    if(actual){
        while(actual->ant){
            actual = actual->ant;
        }
    }

    if( (nuevo = malloc(sizeof(tNodo))) == NULL || (nuevo->info = malloc(tam)) == NULL ){
        free(nuevo);
        return 0; //SIN MEMORIA
    }

    memcpy(nuevo->info, dato, tam);
    nuevo->tam = tam;

    //lista vacia
    if(!actual){
        nuevo->sig = NULL;
        nuevo->ant = NULL;
        *lista = nuevo;
        return 1;
    }

    //insertar antes del primero
    if(cmp(actual->info, nuevo->info) > 0){
        nuevo->ant = NULL;
        nuevo->sig = actual;
        actual->ant = nuevo;
        *lista = nuevo;
        return 1;
    }

    //insertar donde corresponda
    while(actual->sig && cmp(actual->sig->info, nuevo->info) < 0){
        actual = actual->sig;
    }

    nuevo->sig = actual->sig;
    nuevo->ant = actual;

    if(actual->sig){
        actual->sig->ant = nuevo;
    }

    actual->sig = nuevo;
    *lista = nuevo;
    return 1; //EXITO
}

//Resuelva el ordenamiento de la lista
void ordenarLista(tLista* lista, int(*cmp)(const void*, const void*)){
    tNodo* actual = *lista;
    int ordenado = 0; //flag para ver si esta ordenado

    if(!actual) return;

    while(actual->ant){
        actual = actual->ant;
    }

    while(!ordenado){
        ordenado = 1;
        tNodo* aux = actual;

        while(aux->sig){
            if(cmp(aux->info, aux->sig->info) > 0){
                void* tmpInfo = aux->info;
                unsigned tmpTam = aux->tam;

                aux->info = aux->sig->info;
                aux->tam = aux->sig->tam;
                aux->sig->info = tmpInfo;
                aux->sig->tam = tmpTam;
                ordenado = 0;
            }
            aux = aux->sig;
        }
    }
}

/*
Resuelva la busqueda por la clave, con eliminacion o no del nodo, recuperando la informacion en caso de encontrarse la clave
*/
int buscar(tLista* lista, void* dato, unsigned tam, int(*cmp)(const void*, const void*)){
    tNodo* actual = *lista;
    if(!actual){
        return 0; //no hay nada que buscar
    }

    while(actual->ant){
        actual = actual->ant;
    }

    while(actual){
        if(cmp(actual->info, dato) == 0){
            memcpy(dato, actual->info, tam);
            return 1; //encontrado
        }
        actual = actual->sig;
    }

    return 0; //no encontrado

}

//Funciones extra - se utilizan para la resolución de las consignas pero no son la función principal.
void insertarPersonasOrdenadas(tLista* lista, int(*cmp)(const void*, const void*)){
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
        insertarEnOrden(lista, &personas[i], sizeof(tPersona), comparaDni);
    }
}

int comparaDni(const void* dato1, const void* dato2){
    return ((tPersona*)dato1)->dni - ((tPersona*)dato2)->dni;
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
