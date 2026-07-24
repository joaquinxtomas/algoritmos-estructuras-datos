#include "arbol.h"

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
            return 0; //DUPLICADO
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

    *arbol = nuevo;
    nuevo->der = nuevo->izq = NULL;

    return 1;
}

void recorrerInOrden(tArbol* arbol, void* params, unsigned n, unsigned tam, void(*accion)(void*, unsigned , unsigned, void*)){
    if(!*arbol){
        return;
    }

    recorrerInOrden(&(*arbol)->izq, params, n + 1, tam, accion);
    accion((*arbol)->info, n, tam, params);
    recorrerInOrden(&(*arbol)->der, params, n + 1,tam, accion);
}

void cargarDesdeBin(tArbol* arbol, const char* filename, unsigned tam, int(*cmp)(const void*, const void*)){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        return;
    }

    void* info = malloc(tam);
    fread(info, tam, 1, archivo);
    while(!feof(archivo)){
        insertarEnArbol(arbol, info, tam, cmp);
        fread(info, tam, 1, archivo);
    }

    free(info);
    fclose(archivo);
}

void cargarArchivo(tArbol* arbol, const char* filename, unsigned tam){
    FILE* archivo = fopen(filename, "wb");
    if(!archivo) return;
    recorrerInOrden(arbol, archivo, 0, tam, escribirBin);
}

void escribirBin(void* info, unsigned n, unsigned tam, void* params){
    FILE* archivo = (FILE*)params;
    fwrite(info, tam, 1, archivo);
}

void mostrarArbolGrafico(tArbol* arbol, unsigned nivel, unsigned tam, void(*accion)(void*, unsigned, unsigned, void*)){
    if(!*arbol){
        return;
    }

    mostrarArbolGrafico(&(*arbol)->der, nivel + 1,tam, accion);

    for(unsigned i = 0; i < nivel; i++){
        printf("    ");
    }
    accion((*arbol)->info, nivel, tam, NULL);

    mostrarArbolGrafico(&(*arbol)->izq, nivel + 1, tam, accion);

}
