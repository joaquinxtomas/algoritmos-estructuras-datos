#include "funciones.h"
#include "tda_arbol.h"



int main(){
    const char* filenameAlumnos = "alumnos.dat";
    const char* filenameIndice = "alumnos.idx";

    printf("=== ARCHIVO ALUMNOS ===\n");
    mostrarArchivo(filenameAlumnos, sizeof(tAlumno), mostrarAlumno);

    // Cargar indice desde archivo binario de indice
    tArbol arbol;
    crearArbol(&arbol);
    grabarArchivoBinArbol(&arbol, filenameIndice, sizeof(tRegInd), comparaDni);

    printf("\n=== INDICE EN ORDEN ===\n");
    recorrerEnOrden(&arbol, 0, NULL, mostrarRegIndiceArbol);

    // Probar BAJA
    printf("\n=== BAJA ===\n");
    baja(&arbol, filenameAlumnos);

    printf("\n=== ARCHIVO DESPUES DE BAJA ===\n");
    mostrarArchivo(filenameAlumnos, sizeof(tAlumno), mostrarAlumno);

    printf("\n=== INDICE DESPUES DE BAJA ===\n");
    recorrerEnOrden(&arbol, 0, NULL, mostrarRegIndiceArbol);

    // Grabar arbol actualizado en archivo de indice
    printf("\n=== GRABAR ARBOL EN ARCHIVO ===\n");
    grabarArbolArchivoBin(&arbol, filenameIndice, escribirRegIndiceBinario);
    printf("Archivo de indice grabado.\n");

    printf("\n=== VERIFICAR ARCHIVO INDICE ===\n");
    mostrarArchivo(filenameIndice, sizeof(tRegInd), mostrarRegIndice);

    // Vaciar arbol
    printf("\n=== VACIAR ARBOL ===\n");
    vaciarArbol(&arbol);
    printf("Arbol vaciado.\n");

    return 0;
}
