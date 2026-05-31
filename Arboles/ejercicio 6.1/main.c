#include "funciones.h"

int main()
{
    char* filename = "empleados.bin";
    FILE* archivo = fopen(filename, "wb");
    if(!archivo){
        printf("Error al abrir el archivo");
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

    int cantPersonas = sizeof(empleados)/sizeof(tEmpleado);

    tArbol arbol;
    crearArbol(&arbol);

    for(int i = 0; i < cantPersonas; i++){
        insertarRecArbolBinBusqueda(&arbol, &empleados[i], sizeof(tEmpleado), compararLegajo);
    }

    int altura = 1;
    /*recorrerEnOrdenRecArbolBinBusqueda(&arbol, 0, &altura, obtenerAltura);*/
    //int altura = alturaArbolBin(&arbol);
    //printf("%d", altura);

    //mostrarHojas(&arbol, 0 , NULL, mostrarEmpleado);

    //mostrarNoHojas(&arbol, 0, NULL, mostrarEmpleado);

    //mostrarHijosIzq(&arbol, 0, NULL, mostrarEmpleado);
    //mostrarHijosIzqOpc(&arbol, 0, NULL, mostrarEmpleado);

    //recorrerEnOrdenRecArbolBinBusqueda(&arbol, 0, NULL, mostrarEmpleado);
    //printf("-----------------------------------------------------------\n");
    //podarArbolAlturaInferior(&arbol, &altura);
    //printf("-----------------------------------------------------------\n");
    //recorrerEnOrdenRecArbolBinBusqueda(&arbol, 0, NULL, mostrarEmpleado);

    recorrerPreOrdenRecArbolBinBusqueda(&arbol, 0, archivo, generarArchivoArbol);
    fclose(archivo);
    mostrarArchivo(filename, sizeof(tEmpleado), mostrarEmpleado);
}
