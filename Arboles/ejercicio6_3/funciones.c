#include "funciones.h"

int estaOrdenado(const char* filename, unsigned tam, int (*cmp)(const void*, const void*)){

    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        printf("Error al abrir el archivo para su lectura.");
        return;
    }

    void* anterior = malloc(tam);
    void* actual = malloc(tam);

    fread(anterior, tam, 1, archivo);

    while(!feof(archivo)){
        fread(actual, tam, 1, archivo);
        memcpy(anterior, actual, tam);
        if(cmp(anterior, actual) > 0){
            return 0; //NO ESTÁ ORDENADO
        }
    }

    free(anterior);
    free(actual);
    fclose(archivo);
    return 1; //ESTÁ ORDENADO
}

int comparaLegajos(const void* dato1, const void* dato2){
    return strcmp(((tEmpleado*)dato1)->legajo, ((tEmpleado*)dato2)->legajo);
}
