#include "funciones.h"

int main()
{
    const char* filename_indice = "productos.idx";
    const char* filename_productos = "productos.dat";
    const char* filename_pedidos = "pedidos.txt";

    //leerArchivoBin(filename_productos, sizeof(tProducto), mostrarProducto);
    //leerArchivoBin(filename_indice, sizeof(tIndice), mostrarIndice);

    //tArbol arbol;
    //crearArbol(&arbol);

    //grabarArbolIndice(&arbol, filename_indice);
    //recorrerEnOrden(&arbol, NULL, NULL, mostrarIndice);

    leerArchivoTxt(filename_pedidos);
}
