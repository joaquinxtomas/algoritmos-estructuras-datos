#include "funciones.h"

/*
formato txt

ABCDE6
ABBBD79
ABNND9
*/

void cargarDesdeTxt(const char* filename, tArbol* arbol){
    FILE* archivo = fopen(filename, "r");
    if(!archivo){
        return;
    }

    char linea[200];

    Dato dato;

    while(fgets(linea, sizeof(linea), archivo)){
        sscanf(linea, "%5[A-Za-z]%d", dato.clave, &dato.dato);
        insertarEnArbol(arbol, &dato, sizeof(Dato), comparaDato);
    }

    fclose(archivo);
}

int comparaDato(void* dato1, void* dato2){
    Dato* d1 = (Dato*)dato1;
    Dato* d2 = (Dato*)dato2;

    return strcmp(d1->clave, d2->clave);
}

void mostrarDato(void* info, int n, void* params){
    Dato* dato = (Dato*)info;
    printf("%s - %d\n", dato->clave, dato->dato);
}
