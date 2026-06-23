#include "funciones.h"

int baja(tArbol* arbol, const char* filenameAlumnos){
    int dni;
    tRegInd regInd;
    tRegInd clave;
    tAlumno alumno;

    printf("Escriba el DNI del alumno a dar de baja: ");
    scanf("%d", &dni);

    clave.dni = dni;
    clave.nro_reg = 0;

    tNodo** encontrado;
    encontrado = buscarNodoArbol(arbol, &clave, comparaDni);

    if(encontrado == NULL || *encontrado == NULL || (*encontrado)->info == NULL){
        return NO_EXISTE;
    }

    memcpy(&regInd, (*encontrado)->info, sizeof(tRegInd));

    FILE* archivo = fopen(filenameAlumnos, "r+b"); // alumnos
    if(!archivo){
        return 0;
    }

    fseek(archivo, sizeof(tAlumno) * regInd.nro_reg, SEEK_SET);

    fread(&alumno, sizeof(tAlumno),1, archivo);
    alumno.estado = 'B';

    fseek(archivo, -sizeof(tAlumno), SEEK_CUR);
    fwrite(&alumno, sizeof(tAlumno), 1, archivo);

    fclose(archivo);

    tArbol* arbolAux = arbol;
    eliminarNodo(&arbolAux, &regInd.dni, comparaDni);

    const char* filenamev2 = "alumnosv2.idx";
    grabarArbolArchivoBin(arbol, filenamev2, comparaDni);

    return TODO_OK;
}

int eliminarNodo(tArbol* arbol, void* clave, int(*cmp)(const void*, const void*)){
    if(!(arbol = buscarNodoArbol(arbol, clave, cmp))){
        return NO_EXISTE;
    }

    return eliminarRaiz(arbol);
}

int eliminarRaiz(tArbol* arbol){
    if(!*arbol){
        return NO_EXISTE;
    }

    free((*arbol)->info);

    if(!(*arbol)->izq && !(*arbol)->der){
        free(*arbol);
        *arbol = NULL; //consultar esto
        return TODO_OK;
    }

    tArbol* reemplazo, eliminar;

    reemplazo = alturaArbol(&(*arbol)->izq) > alturaArbol(&(*arbol)->der)
                ? mayorNodoArbol(&(*arbol)->izq)
                : menorNodoArbol(&(*arbol)->der);

    eliminar = *reemplazo;

    (*arbol)->info = eliminar->info;
    (*arbol)->tamInfo = eliminar->tamInfo;

    *reemplazo = eliminar->izq ? eliminar->izq : eliminar->der;

    free(eliminar);
    return TODO_OK;
}

int alturaArbol(tArbol* arbol){
    int hi,hd;
    if(!*arbol){
        return 0;
    }

    hi = alturaArbol(&(*arbol)->izq);
    hd = alturaArbol(&(*arbol)->der);
    return (hi < hd ? hd : hi) + 1;
}

tNodo** buscarNodoArbol(tArbol* arbol, void* clave, int(*cmp)(const void*, const void*)){
    if(!*arbol){
        return NULL;
    }

    int res = cmp((*arbol)->info, clave);

    if(res == 0){
        return (tNodo**)arbol;
    }

    if(res > 0){
        return buscarNodoArbol(&(*arbol)->izq, clave, cmp);
    } else if(res < 0){
        return buscarNodoArbol(&(*arbol)->der, clave, cmp);
    }
    return NULL;
}

tNodo** mayorNodoArbol(tArbol* arbol){
    if(!*arbol){
        return 0;
    }
    while((*arbol)->der){
        arbol = &(*arbol)->der;
    }
    return (tNodo**)arbol;
}

tNodo** menorNodoArbol(tArbol* arbol){
    if(!*arbol){
        return 0;
    }

    while((*arbol)->izq){
        arbol = &(*arbol)->izq;
    }
    return(tNodo**)arbol;
}

void grabarArbolArchivoBin(tArbol* arbol, const char* filename, void(*accion)(const void*, unsigned, const void*)){ //GRABA DEL ARBOL AL ARCHIVO
    FILE* archivo = fopen(filename, "wb");
    if(!archivo){
        return;
    }

    recorrerEnPosOrden(arbol, NULL, archivo, accion);

    fclose(archivo);
}

void grabarArchivoBinArbol(tArbol* arbol, const char* filename, unsigned tam, int(*cmp)(const void*, const void*)){ //GRABA DEL ARCHIVO AL ARBOL
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        return;
    }

    void* dato = malloc(tam);
    fread(dato, tam, 1, archivo);
    while(!feof(archivo)){
        insertarEnArbol(arbol, dato, tam, cmp);
        fread(dato,tam,1,archivo);
    }

    free(dato);
    fclose(archivo);
}

void mostrarArchivo(const char* filename, unsigned tam, void(*accion)(const void*)){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        printf("Error al abrir el archivo para su lectura.\n");
        return;
    }

    void* data = malloc(tam);

    fread(data, tam, 1, archivo);
    while(!feof(archivo)){
        accion(data);
        fread(data, tam, 1, archivo);
    }

    free(data);
    fclose(archivo);
}

void escribirRegIndiceBinario(const void* info, unsigned n, const void* params){
    FILE* archivo = (FILE*)params;

    tRegInd* regInd = (tRegInd*)info;

    fwrite(regInd, sizeof(tRegInd), 1, archivo);
}

void mostrarAlumno(const void* dato){
    tAlumno* alumno = (tAlumno*)dato;
    printf("%d - %s - %d - %.2f - %c\n", alumno->dni, alumno->apellidoNombre, alumno->cant_materias, alumno->promedio, alumno->estado);
}

void mostrarRegIndice(const void* dato){
    tRegInd* regInd = (tRegInd*)dato;
    printf("%d - %d\n", regInd->dni, regInd->nro_reg);
}

int comparaDni(const void* a, const void* b){
    return ((tRegInd*)a)->dni - ((tRegInd*)b)->dni;
}

void mostrarRegIndiceArbol(const void* info, unsigned tam, const void* params){
    tRegInd* reg = (tRegInd*)info;
    printf("%d - %d\n", reg->dni, reg->nro_reg);
}

