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
            return 0;
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
    nuevo->izq = nuevo->der = NULL;

    return 1;
}

int cargarDesdeTxt(tArbol* arbol, const char* filename, unsigned tam, int(*cmp)(const void*, const void*), int(*parsear)(const char*, void*)){
    FILE* archivo = fopen(filename, "r");
    if(!archivo){
        return 0;
    }

    char linea[10];
    void* info = malloc(tam);

    while(fgets(linea, sizeof(linea), archivo)){
        if(parsear(linea,info)){
            insertarEnArbol(arbol, info, tam, cmp);
        }
    }

    free(info);
    fclose(archivo);
    return 1;
}

void recorrerArbolInOrden(tArbol* arbol, void* params, unsigned n, void(*accion)(void*, unsigned, void*)){
    if(!*arbol){
        return; //arbol vacio
    }

    recorrerArbolInOrden(&(*arbol)->izq, params, n + 1, accion);
    accion((*arbol)->info, n, params);
    recorrerArbolInOrden(&(*arbol)->der, params, n + 1, accion);
}

void recorrerArbolPreOrden(tArbol* arbol, void* params, unsigned n, void(*accion)(void*, unsigned, void*)){
    if(!*arbol){
        return; //arbol vacio
    }

    accion((*arbol)->info, n, params);
    recorrerArbolPreOrden(&(*arbol)->izq, params, n + 1, accion);
    recorrerArbolPreOrden(&(*arbol)->der, params, n + 1, accion);
}

void esNivelCompleto(const tArbol* arbol, int n){
    if(n < 0){
        return;
    }

    int cantidadReal = contarNodosNivel(arbol, n);
    int cantidadEsperada = potencia(n);

    if(cantidadReal == cantidadEsperada){
        printf("El nivel esta completo.\n");
    } else {
        int diferencia = cantidadEsperada - cantidadReal;
        printf("El nivel esta incompleto, faltan %d nodos.\n", diferencia);
    }
}

int potencia(int n){
    int res = 1;
    for(int i = 0;i < n; i++){
        res *= 2;
    }
    return res;
}

int contarNodosNivel(const tArbol* arbol, int nivel){
    if(!*arbol){
        return 0;
    }

    if(nivel == 0){
        return 1;
    }

    return contarNodosNivel(&(*arbol)->izq, nivel - 1) + contarNodosNivel((&(*arbol)->der, nivel - 1));
}

int cantNodosPorNivel(tArbol* arbol, int nivel){
    return cantNodosHastaNivel(arbol, nivel) - cantNodosHastaNivel(arbol, nivel - 1);
}

int cantNodosHastaNivel(tArbol* arbol, int nivel){
    if(!*arbol){
        return 0;
    }
    if(n == 0){
        return 1;
    }

    return (cantNodosHastaNivel(&(*arbol)->izq, nivel - 1) + cantNodosHastaNivel(&(*arbol)->der, nivel - 1) + 1)
}



