#include "arbol.h"

void crearArbol(tArbol* arbol){
    *arbol = NULL;
}

int insertarEnArbol(tArbol* arbol, void* dato, unsigned tam, int(*cmp)(const void*, const void*)){
    while(*arbol){
        if(cmp((*arbol)->info, dato) > 0){
            arbol = &(*arbol)->izq;
        } else if(cmp((*arbol)->info, dato) < 0){
            arbol = &(*arbol)->der;
        } else {
            printf("DUPLICADO\n");
            return 0;
        }
    }

    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(!nuevo){
        printf("SIN MEMORIA.\n");
        return 0;
    }

    nuevo->info = malloc(tam);
    if(!nuevo->info){
        printf("SIN MEMORIA.\n");
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, dato, tam);
    nuevo->tamInfo = tam;

    nuevo->izq = nuevo->der = NULL;
    *arbol = nuevo;

    return 1;
}

int eliminarNodo(tArbol* arbol, void* dato, unsigned tam, int(*cmp)(const void*, const void*)){
    tNodo** res = buscarNodoArbol(arbol, dato, cmp);
    if(!res){
        printf("NODO NO ENCONTRADO.\n");
        return 0;
    }
    memcpy(dato, (*res)->info, MINIMO((*res)->tamInfo, tam));
    return eliminarRaiz(res);
}

int eliminarRaiz(tArbol* arbol){
    tNodo** reemp, *elim;
    if(!*arbol){
        return 0;
    }

    if(!(*arbol)->izq && !(*arbol)->der)){
        free((*arbol)->info);
        free(*arbol);
        *arbol = NULL;
        return 1;
    }

    reemp = alturaArbol(&(*arbol)->izq) > alturaArbol(&(*arbol)->der) ? mayorNodoArbol(&(*arbol)->izq) : menorNodoArbol(&(*arbol)->der);

    elim = *reemp;
    free((*arbol)->info);
    (*arbol)->info = elim->info;
    (*arbol)->tamInfo = elim->tamInfo;

    *reemp = elim->izq ? elim->izq : elim->der;
    free(elim);

    return 1;
}

int alturaArbol(tArbol* arbol){
    if(!*arbol){
        return 0;
    }

    int hi = alturaArbol(&(*arbol)->izq);
    int hd = alturaArbol(&(*arbol)->der);

    return (hi > hd ? hi : hd) + 1;
}

tNodo** menorNodoArbol(tArbol* arbol){
    if(!*arbol){
        return NULL;
    }

    while((*arbol)->izq){
        arbol = &(*arbol)->izq;
    }

    return arbol;
}

tNodo** mayorNodoArbol(tArbol* arbol){
    if(!*arbol){
        return NULL;
    }

    while((*arbol)->der){
        arbol = &(*arbol)->der;
    }

    return arbol;
}

int vaciarArbol(tArbol* arbol){
    if(!*arbol){
        return 0;
    }

    vaciarArbol(&(*arbol)->izq);
    vaciarArbol(&(*arbol)->der);
    free((*arbol)->info);
    free(*arbol);
    *arbol = NULL;
    return 1;
}

tNodo** buscarNodoArbol(tArbol* arbol, void* clave, int(*cmp)(const void*, const void*)){
    while(*arbol){
        if(cmp((*arbol)->info, clave) > 0){
            arbol = &(*arbol)->izq;
        } else if(cmp((*arbol)->info, clave) < 0){
            arbol = &(*arbol)->der;
        } else {
            return arbol;
        }
    }
}

int grabarArbolEnBin(tArbol* arbol, const char* filename, unsigned tam){
    FILE* archivo = fopen(filename, "wb");
    if(!archivo){
        printf("ERROR ARCHIVO.\n");
        return 0;
    }

    recorrerInOrden(arbol, archivo, 0, tam, escribirBinario);

    fclose(archivo);
    return 1;
}

void escribirBinario(void* info, unsigned n, unsigned tam, void* params){
    FILE* archivo = (FILE*)params;

    fwrite(info, tam, 1, archivo);
}

void recorrerInOrden(tArbol* arbol, void* params, unsigned n, unsigned tam, void(*accion)(void*, unsigned, unsigned, void*)){
    if(!*arbol){
        return;
    }

    recorrerInOrden(&(*arbol)->izq, params, n + 1, tam, accion);
    accion((*arbol)->info, n, tam, params);
    recorrerInOrden(&(*arbol)->der, params, n + 1, tam, accion);
}
