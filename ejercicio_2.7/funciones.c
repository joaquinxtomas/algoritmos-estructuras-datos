#include "pila.h"

void proceso(const char* filename, size_t tam, int (*cmp)(const void*,const void*)){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        printf("Error al abrir el archivo para su lectura.");
        return;
    }

    FILE* archivoOrdenado = fopen("ordenado.bin", "wb");
    if(!archivoOrdenado){
        printf("Error al abrir el archivo para su escritura.");
        fclose(archivo);
        return;
    }

    tPila pila1;
    tPila pila2;

    //creacion ambas pilas
    crearPila(&pila1);
    crearPila(&pila2);

    void* elemento = malloc(tam);

    if(!elemento){
        fclose(archivo);
        fclose(archivoOrdenado);
        printf("SIN MEMORIA");
        return;
    }
    //comenzar a leer archivo
    fread(elemento, tam, 1, archivo);
    while(!feof(archivo)){

        //cargar pila 1, pila 2 dejar vacia
        insertarEnPila(&pila1, elemento, tam);

        fread(elemento, tam, 1, archivo);
    }

    fclose(archivo);

    ordenarPila(&pila1, &pila2, tam, cmp);

    if(pilaVacia(&pila1)){
        printf("Error al ordenar la pila, no posee elementos.");
    }

    while(!pilaVacia(&pila1)){
        sacarDePila(&pila1, elemento, tam);
        fwrite(elemento, tam, 1, archivoOrdenado);
    }

    fclose(archivoOrdenado);
    free(elemento);
}

void ordenarPila(tPila* pila1, tPila* pila2, size_t tam, int (*cmp)(const void*,const void*)){
    void* temp = malloc(tam);
    void* elemento = malloc(tam);

    while(!pilaVacia(pila1)){
        sacarDePila(pila1, temp, tam);

        int posEncontrada = 0;

        while(!pilaVacia(pila2)){
            verTope(pila2, elemento, tam);

            if(cmp(temp, elemento) > 0){
                sacarDePila(pila2, elemento, tam);
                insertarEnPila(pila1, elemento, tam);
            }else {
                break;
            }
        }
        insertarEnPila(pila2, temp, tam);
    }

    while(!pilaVacia(pila2)){
        sacarDePila(pila2, elemento, tam);
        insertarEnPila(pila1, elemento, tam);
    }

    free(temp);
    free(elemento);
}

void crearArchivo(const char* filename){
    FILE* archivo = fopen(filename, "wb");
    if(!archivo){
        printf("Error al abrir el archivo para su escritura.");
        return;
    }

    tPersona personas[5] = {
        {"Roberto", "Gomez", 43457272},
        {"Joaquin", "Palacios", 12332857},
        {"Mirta", "Palacios", 92342857},
        {"Vero", "Palacios", 42632857},
        {"Anabella", "Amado", 32332857},
    };

    fwrite(personas, sizeof(tPersona), 5, archivo);

    fclose(archivo);
}

int compararDni(const void* elemento1, const void* elemento2){
    tPersona* persona1 = (tPersona*)elemento1;
    tPersona* persona2 = (tPersona*)elemento2;

    return (int)(persona1->dni - persona2->dni);
}

void mostrarArchivo(const char* filename, size_t tam, void(*mostrar)(const void*)){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        printf("Error al abrir el archivo para su lectura.");
        return;
    }

    void* elemento = malloc(tam);
    if(!elemento){
        fclose(archivo);
        return;
    }

    fread(elemento, tam, 1, archivo);
    while(!feof(archivo)){
        mostrar(elemento);
        fread(elemento, tam, 1, archivo);
    }
    free(elemento);
    fclose(archivo);
}

void mostrarPersona(const void* elemento){
    tPersona* persona = (tPersona*)elemento;

    printf("%20s - %20s - %10d\n", persona->nombre, persona->apellido, persona->dni);
}

