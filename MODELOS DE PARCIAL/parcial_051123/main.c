#include "tda_arbol.h" //incluye librerias principales
#include "funciones.h"

int main()
{
    const char* filename = "impuestosVencidos.dat";
    generarLote(filename);
    mostrarArchivoBin(filename);

    const char* filename_txt = "deudas.txt";

    //en cada opcion del menu
    //1. comparar por dni y escribir (insertar en arbol con cmp dni unicamente) y escribir en archivo el arbol
    //2. comparar por dni y patente y escribir en archivo el arbol
    tArbol arbol;
    crearArbol(&arbol);

    char opcion;
    do{
        opcion = menu("1 - dni\n"
                      "2 - dni y patente\n"
                      "3 - salir\n", "123");

        switch(opcion){
        case '1':
            insertarArbolArchivoBin(&arbol, filename, comparaDni);
            escribirArchivoTxtArbol(&arbol, filename_txt, escribirDni);
            vaciarArbol(&arbol);
            break;
        case '2':
            insertarArbolArchivoBin(&arbol, filename, comparaDniYPatente);
            escribirArchivoTxtArbol(&arbol, filename_txt, escribirDniYPatente);
            vaciarArbol(&arbol);
            break;
        }
    }while(opcion != '3');
}
