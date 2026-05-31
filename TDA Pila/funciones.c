#include "funciones.h"
#include "pila.h"
#include "producto.h"

void proceso(const char *filename, PilaEst* pila){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        printf("Error al abrir el archivo para su lectura.\n");
        return;
    }

    Producto prod;

    fread(&prod, sizeof(Producto), 1, archivo);
    while(!feof(archivo)){
        insertarElemento(pila, &prod, sizeof(Producto));
        fread(&prod, sizeof(Producto), 1, archivo);
    }

    fclose(archivo);
}

/** FUNCIONES DE MENÚ **/
char menuSinErr(const char* msj, const char* opc){
    char opta;
    do{
        printf("%s", msj);
        fflush(stdin);
        scanf("%c", &opta);
        system("clear");
    }while(strchr(opc, opta) == NULL);
    return opta;
}
