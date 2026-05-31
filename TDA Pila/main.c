#include "pila.h"
#include "producto.h"
#include "funciones.h"

void mostrarArchivo(const char* filename, size_t tam, void(*mostrar)(void*)){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        printf("Error al abrir el archivo para su lectura.");
        return;
    }

    void* elemento = malloc(tam);
    if(!elemento){
        fclose(archivo);
        return;
    }

    fread(elemento, tam, 1, archivo);
    while(!feof(archivo)){
        mostrar(elemento);
        fread(elemento, tam, 1, archivo);
    }
    free(elemento);
    fclose(archivo);
}

int main()
{
    const char* filename = "productos.dat";
    char opcion;
    cargarArchivoProductos(filename);
    //mostrarArchivo(filename, sizeof(Producto), mostrarProducto);

    PilaEst pila;
    crearPila(&pila);

    proceso(filename, &pila);

    //verPila(&pila, mostrarProducto);

    do{
        opcion = menuSinErr(MENSAJE_MENU, "123456789");

        switch(opcion){
            case '1': {
                Producto prod;
                ingresarProducto(&prod);
                insertarElemento(&pila, &prod, sizeof(Producto));
                mostrarProducto(&pila);

                printf("\nPresione Enter para continuar...");
                getchar();
                break;
            }
            case '2': {
                Producto prod;
                verElementoTope(&pila, &prod, sizeof(Producto));
                mostrarProducto(&prod);

                printf("\nPresione Enter para continuar...");
                getchar();
                break;
            }
            case '3': {
                Producto prod;
                eliminarElemento(&pila, &prod, sizeof(Producto));
                printf("ELEMENTO ELIMINADO:\n");
                mostrarProducto(&prod);

                printf("\nPresione Enter para continuar...");
                getchar();
                break;
            }
            case '4': {
                verPila(&pila, mostrarProducto);
                cargarArchivoPila(filename, &pila);

                printf("\nPresione Enter para cerrar el programa...");
                getchar();
                break;
            }
        }
    }while(opcion != '4');

}
