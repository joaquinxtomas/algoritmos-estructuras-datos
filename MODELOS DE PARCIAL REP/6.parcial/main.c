#include "arbol.h"

char menu(const char* mensaje, const char* opciones){
    char opc;
    do{
        printf("%s\nIngrese una opcion: ", mensaje);
        scanf(" %c", &opc);
        if(strchr(opciones, opc) == NULL){
            printf("Opcion invalida. Intente nuevamente: ");
        }
    }while(strchr(opciones, opc) == NULL);
    return opc;
}

int main()
{
    const char* filename_alumnos = "alumnos.dat";
    const char* filename_indice = "alumnos.idx";

    tArbol arbol;
    crearArbol(&arbol);
    cargarArbol(&arbol, filename_indice);

    char opcion;
    do{
        opcion = menu("1. Baja de alumno\n2.Grabar indice\n3. VaciarArbol\n 4.Salir\n", "1234");

        switch(opcion){
        case '1':
            baja_alumno(&arbol, filename_alumnos, filename_indice);
            break;
        case '2':
            grabarArbolEnBin(&arbol, filename_indice, sizeof(tIndice));
            break;
        case '3':
            vaciarArbol(&arbol);
        }
    }while(opcion != '4');
}
