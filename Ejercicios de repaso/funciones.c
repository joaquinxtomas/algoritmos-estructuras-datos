#include "funciones.h"

/** EJERCICIO 1 **/
int crearVector(Vector* vec, int ce, size_t tam){
    vec->vec = malloc(ce * tam);
    if(!vec->vec){
        printf("Error al reservar memoria.\n");
        return 0;
    }
    vec->ce = 0;
    vec->cap = ce;
    vec->tam = tam;
    return 1;
}

int vectorLleno(Vector *vec){
    if(vec->cap == vec->ce){
        return 1; //lleno
    }
    return 0;
}

int vectorVacio(Vector *vec){
    if(vec->ce == 0){
        return 1; //vacio
    }
    return 0;
}

int cantElem(Vector* vec){
    return vec->ce;
}

int insertarEnOrden(Vector *vec, void* elem, int(*cmp)(const void*, const void*)){
    if(vectorLleno(vec)){
        return 1; //no se puede insertar
    }

    char* inicio = (char*) vec->vec;
    char* fin = inicio + (vec->ce * vec->tam);
    while(inicio < fin && cmp(elem, inicio) > 0){
        inicio += vec->tam;
    }

    memmove(inicio + vec->tam, inicio, fin - inicio);
    memcpy(inicio, elem, vec->tam);
    vec->ce++;
    return 0; //todo ok
}

int insertarElemento(Vector *vec, void* elem){
    if(vectorLleno(vec)){
        return 1; //no se puede insertar
    }

    char* ultimo = (char*) vec->vec + (vec->ce * vec->tam);

    memcpy(ultimo, elem, vec->tam);
    vec->ce++;

    return 0;
}

int eliminarElemento(Vector* vec, int idx){
    if(idx < 0 || idx >= vec->ce){
        return 1; //indice fuera de rango
    }

    char *inicio = (char*)vec->vec + (idx * vec->tam);


    if(idx < vec->ce - 1){
        char *siguiente = inicio + vec->tam;
        size_t bytes = (vec->ce - idx - 1) * vec->tam;

        memmove(inicio, siguiente, bytes);
    }

    vec->ce--;

    return 0;
}

void destruirVector(Vector *vec){
    if(vec->ce != NULL) {
        free(vec->vec);
    }
    vec->vec = NULL;
    vec->ce = 0;
    vec->cap = 0;
    vec->tam = 0;
}

void recorrerVec(Vector* vec, void(*accion)(const void*)){
    char* inicio = (char*) vec->vec;
    char* fin = inicio + vec->ce * vec->tam;

    while(inicio < fin){
        accion(inicio);
        inicio += vec->tam;
    }
}

void mostrarVecInt(const void* elemento){
    printf("%d ", *(int*)elemento);
}

/** EJERCICIO 2 **/

float calcular (float operando1, float operando2, float(*operacion)(float, float)){
    return operacion(operando1, operando2);
}

float division(float operando1, float operando2){

    if(operando2 == 0){
        printf("No se puede dividir por cero.\n");
        return 0.0f;
    }
    return operando1 / operando2;

}

float multiplicacion(float operando1, float operando2){
    return operando1 * operando2;
}

float suma(float operando1, float operando2){
    return operando1 + operando2;
}

float resta(float operando1, float operando2){
    return operando1 - operando2;
}

/** EJERCICIO 3 **/

void proceso(const char* filename){
    int num, cantidadElementos, contador = 0, contadorErrores = 0;

    FILE* archivo = fopen(filename, "r");
    if(!archivo){
        printf("Error al leer el archivo de texto.\n");
        return;
    }

    Vector vec;

    if(fscanf(archivo, "%d", &cantidadElementos) == 1){
        printf("Cantidad elementos: %d\n", cantidadElementos);

        crearVector(&vec, cantidadElementos, sizeof(int));

        while(fscanf(archivo, "%d", &num) == 1){
            contador++;
            int insertado = insertarElemento(&vec, &num);
            if(insertado == 1){
                contadorErrores++;
            }
        }

        if(contador > cantidadElementos){
            printf("\n\nLa cantidad de elementos es mayor a la cantidad dada en la primer linea.");
        } else if(contador < cantidadElementos){
            printf("\nLa cantidad de elementos es menor a la cantidad dada en la primer linea.");
        }

        if(contadorErrores != 0){
            printf("\n\nVector lleno, se intentaron insertar %d elementos y no hubo exito.\n", contadorErrores);
        }
    }

    printf(" \nElementos insertados exitosamente: ");
    recorrerVec(&vec, mostrarVecInt);
    destruirVector(&vec);

    fclose(archivo);
}

/** EJERCICIO 4 **/

//necesito ahora trozar el texto
//formato supuesto: Joaquin;Palacios;23

void procesoPersona(const char* filename){
    int cantidadElementos, contador = 0, contadorErrores = 0;

    FILE* archivo = fopen(filename, "r");
    if(!archivo){
        printf("Error al abrir el archivo para su lectura.\n");
        return;
    }

    Vector vec;
    tPersona persona;

    if(fscanf(archivo, "%d", &cantidadElementos) == 1){
        printf("Cantidad de elementos: %d", cantidadElementos);

        fgetc(archivo);

        crearVector(&vec, cantidadElementos, sizeof(tPersona));

        while(leerLinea(archivo, &persona) == 1){
            contador++;
            int insertado = insertarElemento(&vec, &persona);
            if(insertado == 1){
                contadorErrores++;
            }
        }

        if(contador > cantidadElementos){
            printf("\n\nLa cantidad de elementos es mayor a la cantidad dada en la primer linea.");
        } else if(contador < cantidadElementos){
            printf("\nLa cantidad de elementos es menor a la cantidad dada en la primer linea.");
        }

        if(contadorErrores != 0){
            printf("\n\nVector lleno, se intentaron insertar %d elementos y no hubo exito.\n", contadorErrores);
        }
    }

    printf("\nElementos insertados exitosamente: ");
    recorrerVec(&vec, mostrarVecPersona);
    destruirVector(&vec);

    fclose(archivo);
}

int leerLinea(FILE* archivo, tPersona* persona){
    char linea[300];

    if(fgets(linea, sizeof(linea), archivo) == NULL){
        return 0;
    }

    char* actual = strrchr(linea, ';');
    if(!actual) return 0;
    *actual = '\0';
    actual++;

    sscanf(actual, "%d", &persona->edad);

    actual = strrchr(linea, ';');
    if(!actual) return 0;
    *actual = '\0';
    actual++;

    strcpy(persona->apellido, actual);

    strcpy(persona->nombre, linea);

    return 1; //exitoso
}

void mostrarVecPersona(const void *elemento){
    tPersona* persona = (tPersona*)elemento;

    printf("%s - %s - %d\n", persona->nombre, persona->apellido, persona->edad);
}

/** EJERCICIO 5 **/

void procesoGenericoTexto(const char* filename, size_t tam, int(*leerDato)(FILE*,void*), void(*mostrarDato)(const void*)){
    //si, necesito el tamaño del elemento que va a tener el archivo.
    int cantidadElementos, contador = 0, contadorErrores = 0;

    FILE* archivo = fopen(filename, "r");
    if(!archivo){
        printf("Error al abrir el archivo para su lectura.\n");
        return;
    }

    Vector vec;
    void* elemento;

    if(fscanf(archivo, "%d", &cantidadElementos) == 1){
        printf("Cantidad de elementos: %d", cantidadElementos);

        crearVector(&vec, cantidadElementos, tam);

        while(leerDato(archivo, &elemento) == 1){
            contador++;
            int insertado = insertarElemento(&vec, &elemento);
            if(insertado == 1){
                contadorErrores++;
            }
        }

        if(contador > cantidadElementos){
            printf("\n\nLa cantidad de elementos es mayor a la cantidad dada en la primer linea.");
        } else if(contador < cantidadElementos){
            printf("\n\nLa cantidad de elementos es menor a la cantidad dada en la primer linea.");
        }

        if(contadorErrores != 0){
            printf("\n\nVector lleno, se intentaron insertar %d elementos y no hubo exito.\n", contadorErrores);
        }
    }

    printf("\nElementos insertados exitosamente: ");
    recorrerVec(&vec, mostrarDato);
    destruirVector(&vec);
}


/** EJERCICIO 6 **/
void procesoGenericoBinario(const char* filename, size_t tam, void(*mostrarDato)(const void*)){
    int cantidadElementos, contador = 0, contadorErrores = 0;

    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        printf("Error al abrir el archivo para su lectura.\n");
        return;
    }

    /*fseek(archivo, 0 , SEEK_END);
    long tamArchivo = ftell(archivo);
    cantidadElementos = tamArchivo/tam; //representa cantidad real que posee el archivo
    rewind(archivo);*/

    Vector vec;

    fread(&cantidadElementos, sizeof(int), 1, archivo); // representa el numero de la primer fila (cantidad elementos supuesta)

    void* elemento = malloc(tam);

    crearVector(&vec, cantidadElementos, tam);

    fread(elemento, tam, 1, archivo);
    while(!feof(archivo)){
        contador++;

        int insertado = insertarElemento(&vec, elemento);

        if(insertado == 1){
            contadorErrores++;
        }

        fread(elemento, tam, 1, archivo);
    }

    if(contador > cantidadElementos){
        printf("\n\nLa cantidad de elementos es mayor a la cantidad dada en la primer linea.");
    } else if(contador < cantidadElementos){
        printf("\n\nLa cantidad de elementos es menor a la cantidad dada en la primer linea.");
    }

    if(contadorErrores != 0){
        printf("\n\nVector lleno, se intentaron insertar %d elementos y no hubo exito.\n", contadorErrores);
    }

    free(elemento);

    printf("\nCantidad de elementos supuesta (primer linea): %d\n" ,cantidadElementos);
    printf("\nElementos insertados exitosamente: ");
    recorrerVec(&vec, mostrarDato);
    destruirVector(&vec);
    fclose(archivo);
}

void crearArchivoBin(const char* filename){
    FILE* archivo = fopen(filename, "wb");
    if(!archivo){
        printf("Error al abrir el archivo para su escritura.\n");
        return;
    }

    int numero = 5;

    fwrite(&numero, sizeof(int), 1, archivo);

    tPersona personas[]={
        {"Joaquin", "Palacios", 23},
        {"Mirta", "Guzman", 56},
        {"Alfredo", "Palacios", 65},
        {"Barbara", "Palacios", 42}
    };

    fwrite(personas, sizeof(tPersona), 4, archivo);

    fclose(archivo);
}

void leerArchivoBinario(const char* filename){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        printf("Error al abrir el archivo para su lectura.\n");
        return;
    }

    int numero;
    fread(&numero, sizeof(int), 1, archivo);

    printf("Numero inicial: %d\n", numero);

    tPersona persona;

    fread(&persona, sizeof(tPersona), 1, archivo);
    while(!feof(archivo)){
        printf("%20s - %20s - %5d\n", persona.nombre, persona.apellido, persona.edad);
        fread(&persona, sizeof(tPersona), 1, archivo);
    }
    fclose(archivo);
}




