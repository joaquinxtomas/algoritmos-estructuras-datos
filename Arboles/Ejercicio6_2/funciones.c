#include "funciones.h"

/** FUNCIONES DE ARBOLES **/
void cargarArbolArchivo(tArbol* arbol, const char* filename){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        printf("Error al abrir el archivo para su lectura.\n");
        return;
    }

    tEmpleado empleado;
    tIndice indice;
    int contador = 0;

    fread(&empleado, sizeof(tEmpleado), 1, archivo);
    while(!feof(archivo)){

        strcpy(indice.legajo, empleado.legajo);
        indice.nroRegistro = contador;

        contador++;

        insertarRecArbolBinBusqueda(arbol, &indice, sizeof(tIndice), compararLegajos);
        fread(&empleado, sizeof(tEmpleado),1, archivo);
    }
    fclose(archivo);
}

int compararLegajos(const void* dato1, const void* dato2){
    return strcmp(((tIndice*)dato1)->legajo, ((tIndice*)dato2)->legajo);
}

void mostrarIndiceEmpleadoArbol(void* info, unsigned tam, unsigned n, void* params){
    tIndice* indice = (tIndice*)info;
    printf("Nivel %d: [%s] | %d\n", n, indice->legajo, indice->nroRegistro);
}

//agregar registros
void agregarRegistro(const char* filename, tArbol* arbol, int(*cmp)(const void*, const void*)){
    FILE* archivo = fopen(filename, "r+b");
    if(!archivo){
        printf("Error al abrir el archivo para agregar un registro.\n");
        return;
    }

    tEmpleado nuevoEmp;

    printf("Ingrese el legajo del empleado: ");
    scanf("%s", &nuevoEmp.legajo);

    printf("Ingrese el apellido y nombre del empleado: ");
    scanf("%s", &nuevoEmp.apellidoNombre);

    printf("Ingrese el cargo del empleado: ");
    scanf("%s", &nuevoEmp.cargo);

    printf("Ingrese la fecha de alta del empleado: ");
    scanf("%d/%d/%d", &nuevoEmp.fechaAlta.dia, &nuevoEmp.fechaAlta.mes, &nuevoEmp.fechaAlta.anio);

    printf("Ingrese la fecha de baja del empleado: ");
    scanf("%d/%d/%d", &nuevoEmp.fechaBaja.dia, &nuevoEmp.fechaBaja.mes, &nuevoEmp.fechaBaja.anio);

    fseek(archivo, 0, SEEK_END);
    long tamTotal = ftell(archivo);
    long cantidadRegistros = tamTotal / sizeof(tEmpleado);

    //en arbol esta el indice, no el dato completo
    tIndice indiceBuscar;
    strcpy(indiceBuscar.legajo, nuevoEmp.legajo);
    indiceBuscar.nroRegistro = cantidadRegistros;

    int buscarIndice = buscarEnArbol(arbol, &indiceBuscar, sizeof(tIndice), cmp);

    if(!buscarIndice){
        fwrite(&nuevoEmp, sizeof(tEmpleado), 1, archivo);
        insertarRecArbolBinBusqueda(arbol, &indiceBuscar, sizeof(tIndice), cmp);
    } else {
        printf("El elemento ya esta en el arbol, no admite duplicados.");
    }

    fclose(archivo);
}

/*- Ingresar la clave, para buscarla en el árbol y con el número de registro muestre la
información del archivo.*/
void buscarElemento(const char* filename, tArbol* arbol, int(*cmp)(const void*, const void*)){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        printf("Error al abrir el archivo para su lectura.\n");
        return;
    }

    tIndice indice;
    tEmpleado empleado;

    do{
        printf("Ingrese la clave(legajo) a buscar: ");
        scanf("%s", &indice.legajo);
        int hallar = buscarEnArbol(arbol, &indice, sizeof(tIndice), cmp);

        if(hallar == 1){
            fseek(archivo, sizeof(tEmpleado) * (indice.nroRegistro), SEEK_SET);
            fread(&empleado, sizeof(tEmpleado), 1, archivo);
            printf("Empleado encontrado:\n");
            mostrarEmpleadoArchivo(&empleado);
        } else {
            printf("La clave (legajo) no existe en el archivo.");
        }

    }while(strcmp(indice.legajo, "0") != 0);

    fclose(archivo);
}

void mostrarInformacionArchivoArbol(
                               const char* filename,
                               tArbol* arbol,
                               void(*recorrer)(const tArbol*, unsigned, void*,
                                               void(*accion)(void*, unsigned, unsigned, void*))){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo)
    {
        printf("Error al abrir el archivo para su lectura.\n");
        return;
    }

    //para recorrer se llama a mostrarInformacionEnOrden
    recorrer(arbol, 0, archivo, mostrarDesdeArchivoArbol);

    fclose(archivo);
}

void mostrarDesdeArchivoArbol(void* info, unsigned tam, unsigned n, void* params){
    tIndice* indice = (tIndice*)info;
    FILE* archivo = (FILE*)params;
    tEmpleado empleado;

    fseek(archivo, sizeof(tEmpleado) * indice->nroRegistro, SEEK_SET);
    fread(&empleado, sizeof(tEmpleado), 1, archivo);
    mostrarEmpleadoArchivo(&empleado);
}

void asignarFechaBaja(const char* filename, tArbol* arbol){
    FILE* archivo = fopen(filename, "r+b");
    if(!archivo){
        printf("Error al abrir el archivo para su actualización.");
        return;
    }

    tIndice indice;
    tEmpleado empleado;

    //arbol ya tiene los indices
    printf("Ingrese el legajo del empleado a actualizar: ");
    scanf("%s", &indice.legajo);

    int hallar = buscarEnArbol(arbol, &indice, sizeof(tIndice), compararLegajos);
    if(hallar){
        fseek(archivo, sizeof(tEmpleado) * indice.nroRegistro, SEEK_SET);
        fread(&empleado, sizeof(tEmpleado), 1, archivo);
        printf("Empleado hallado: \n");
        mostrarEmpleadoArchivo(&empleado);

        if(empleado.fechaBaja.dia == 0 && empleado.fechaBaja.mes == 0 && empleado.fechaBaja.anio == 0)
        {
            printf("\nIngrese la fecha de baja (dd/mm/aaaa): ");
            scanf("%d/%d/%d", &empleado.fechaBaja.dia, &empleado.fechaBaja.mes, &empleado.fechaBaja.anio);
            fseek(archivo, sizeof(tEmpleado) * indice.nroRegistro, SEEK_SET);
            fwrite(&empleado, sizeof(tEmpleado), 1, archivo);
        } else {
            printf("El empleado ya tiene una fecha de baja asignada.\n");
            return;
        }
    }else{
        printf("El legajo no existe en el archivo.\n");
        return;
    }
    fclose(archivo);

}

/** FUNCIONES DE ARCHIVOS **/
void crearArchivo(char* filename){
    FILE* archivo = fopen(filename, "wb");

    if(!archivo){
        printf("Error al abrir el archivo para su escritura.\n");
        return;
    }

    tEmpleado empleados[] = {
        { "LEG-005", "Fernandez, Lucia",      "Analista",      { 15,  3, 2020 }, {  0,  0,    0 } },
        { "LEG-002", "Lopez, Martin",         "Gerente",       { 10,  1, 2018 }, {  0,  0,    0 } },
        { "LEG-008", "Rodriguez, Camila",     "Desarrollador", {  5,  6, 2021 }, {  0,  0,    0 } },
        { "LEG-001", "Garcia, Tomas",         "Director",      {  1,  2, 2015 }, {  0,  0,    0 } },
        { "LEG-003", "Diaz, Valentina",       "Analista",      { 20, 11, 2019 }, { 15,  8, 2023 } },
        { "LEG-007", "Martinez, Mateo",       "Soporte",       { 12,  7, 2022 }, {  0,  0,    0 } },
        { "LEG-009", "Gomez, Sofia",          "Tester",        {  8,  4, 2021 }, { 30,  6, 2024 } },
        { "LEG-004", "Perez, Joaquin",        "Desarrollador", { 25,  9, 2020 }, {  0,  0,    0 } },
        { "LEG-006", "Sanchez, Martina",      "Analista",      {  3,  5, 2019 }, {  0,  0,    0 } },
        { "LEG-010", "Ruiz, Nicolas",         "Soporte",       { 18, 12, 2023 }, {  0,  0,    0 } }
    };

    fwrite(empleados, sizeof(tEmpleado), 10, archivo);
    fclose(archivo);
}

void mostrarArchivo(char* filename, unsigned tam, void(*accion)(const void*)){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        printf("Error al abrir el archivo para su lectura\n");
        return;
    }

    void* dato = malloc(tam);
    fread(dato, tam, 1, archivo);
    while(!feof(archivo)){
        accion(dato);
        fread(dato,tam, 1, archivo);
    }
    fclose(archivo);
}

void mostrarEmpleadoArchivo(const void* dato){
    tEmpleado* empleado = (tEmpleado*)dato;
    printf("%s | %s | %s | %d/%d/%d | %d/%d/%d\n", empleado->legajo, empleado->apellidoNombre, empleado->cargo,
           empleado->fechaAlta.dia, empleado->fechaAlta.mes, empleado->fechaAlta.anio,
           empleado->fechaBaja.dia, empleado->fechaBaja.mes, empleado->fechaBaja.anio
    );
}
