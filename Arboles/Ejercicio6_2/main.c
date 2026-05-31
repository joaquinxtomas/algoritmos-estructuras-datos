#include "funciones.h"

int main()
{
    const char* filename = "empleados.bin";
    //crearArchivo(filename);
    mostrarArchivo(filename, sizeof(tEmpleado), mostrarEmpleadoArchivo);
    printf("---------------------------------------------------------\n");
    tArbol arbol;
    crearArbol(&arbol);
    cargarArbolArchivo(&arbol, filename);
    recorrerPreOrdenRecArbolBinBusqueda(&arbol, 0, NULL, mostrarIndiceEmpleadoArbol);
}
