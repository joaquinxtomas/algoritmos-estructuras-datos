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
