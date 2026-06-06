#include "funciones.h"

int main()
{
    const char* filename = "empleados.bin";

    tArbol* arbol;
    crearArbol(arbol);

    cargarArbolDesdeArchivo(filename, arbol);
    recorrerEnOrdenRecArbolBinBusqueda(arbol, 0, NULL, mostrarEmpleado);

    int altura = obtenerAltura(arbol);
    int cantNodos = contarNodos(arbol);
    printf("ALTURA: %d - CANT. NODOS: %d\n", altura, cantNodos);

    //int completo = esCompleto(arbol);
    //completo ? printf("Es completo") : printf("No es completo");

    int balanceado = esBalanceado(arbol);
    balanceado ? printf("Es balanceado") : printf("No es balanceado");
}
