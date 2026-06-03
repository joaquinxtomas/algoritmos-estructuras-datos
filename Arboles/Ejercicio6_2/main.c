#include "funciones.h"

/*
Ejercicio 6.2
Valiéndose de un árbol en el que sólo almacena la clave y el número de registro que le corresponde
en el archivo, escriba un programa que intente abrir un archivo, y si lo puede abrir, haga la carga del
árbol. La información a tratar es la del ejercicio anterior. A continuación, haciendo uso de un menú,
implemente las funciones necesarias que permitan:
- Agregar nuevos registros de información (siempre que la clave no exista en el árbol),
agregando el registro al final del archivo y su clave y número de registro en el árbol.
- Ingresar la clave, para buscarla en el árbol y con el número de registro muestre la
información del archivo.
- Recorriendo el árbol, muestre la información de los registros del archivo en orden.
- Ídem en preorden.
- Ídem en posorden.
- Ingresar la clave, para buscarla en el árbol y con el número de registro asignar la fecha de
baja.
Al terminar el programa, debe generar un nuevo archivo ordenado por la clave
*/

int main()
{
    const char* filename = "empleados.bin";
    crearArchivo(filename);
    printf("ARCHIVO\n");
    mostrarArchivo(filename, sizeof(tEmpleado), mostrarEmpleadoArchivo);
    printf("---------------------------------------------------------\n");
    tArbol arbol;
    crearArbol(&arbol);
    cargarArbolArchivo(&arbol, filename);

    printf("\nARBOL SIN AGREGAR NADA\n");
    recorrerPreOrdenRecArbolBinBusqueda(&arbol, 0, NULL, mostrarIndiceEmpleadoArbol);
    printf("----------------------------------------------------------------------\n");
    /*agregarRegistro(filename, &arbol,  compararLegajos);
    printf("\nARBOL CON UN REGISTRO MÁS\n");
    recorrerPreOrdenRecArbolBinBusqueda(&arbol, 0 , NULL, mostrarIndiceEmpleadoArbol);
    */

    //buscarElemento(filename, &arbol, compararLegajos);

    //mostrarInformacionArchivoArbol(filename, &arbol, recorrerEnOrdenRecArbolBinBusqueda);
    //mostrarInformacionArchivoArbol(filename, &arbol, recorrerPreOrdenRecArbolBinBusqueda);
    //mostrarInformacionArchivoArbol(filename, &arbol, recorrerPosOrdenRecArbolBinBusqueda);

    asignarFechaBaja(filename, &arbol);
    mostrarArchivo(filename, sizeof(tEmpleado), mostrarEmpleadoArchivo);
    printf("---------------------------------------------------------\n");
    printf("\nARBOL SIN AGREGAR NADA\n");
    recorrerPreOrdenRecArbolBinBusqueda(&arbol, 0, NULL, mostrarIndiceEmpleadoArbol);

}
