#include "tda_arbol.h"

void crearArbol(tArbol* arbol){
    *arbol = NULL;
}

int insertarEnArbol(tArbol* arbol, void* dato, unsigned tam, int(*cmp)(const void*, const void*)){
    int res;

    while(*arbol){
        if((res = cmp((*arbol)->info, dato)) > 0){
            arbol = &(*arbol)->izq;
        } else if(res < 0){
            arbol = &(*arbol)->der;
        } else {
            return 0; //duplicado
        }
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

    nuevo->izq = nuevo->der = NULL;
    *arbol = nuevo;

    return 1; //insertado correctamente
}

int buscarPorClave(tArbol* arbol, void* clave, unsigned tam, int(*cmp)(const void*, const void*)){
    while(*arbol){
        if(cmp((*arbol)->info, clave) == 0){
            //copia data
            memcpy(clave, (*arbol)->info, tam);
            return 1; //encontrado
        } else if(cmp((*arbol)->info, clave) < 0){
            arbol = &(*arbol)->der;
        } else {
            arbol = &(*arbol)->izq;
        }
    }
    return 0; //no encontrado
}

void grabarArbolIndice(tArbol* arbol, const char* filename){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        return;
    }

    tIndice indice;

    fread(&indice, sizeof(tIndice), 1, archivo);
    while(!feof(archivo)){
        insertarEnArbol(arbol, &indice, sizeof(tIndice), comparaIndices);
        fread(&indice, sizeof(tIndice), 1, archivo);
    }
    fclose(archivo);
}

void recorrerEnOrden(tArbol* arbol, unsigned n, void* params, void(*accion)(const void*, unsigned, const void*)){
    if(!*arbol){
        return;
    }

    recorrerEnOrden(&(*arbol)->izq, n + 1, params, accion);
    accion((*arbol)->info, n, params);
    recorrerEnOrden(&(*arbol)->der, n + 1, params, accion);
}

int comparaIndices(const void* dato1, const void* dato2){
    tIndice* indice1 = (tIndice*)dato1;
    tIndice* indice2 = (tIndice*)dato2;

    return strcmp(indice1->clave.codigo, indice2->clave.codigo);
}
