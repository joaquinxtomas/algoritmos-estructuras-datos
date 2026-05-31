#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "cola_dinamica.h"

int main()
{
    const char* filename = "archivo.bin";
    //cargarArchivo(filename);

    //recorrerArchivo(filename, sizeof(Producto), mostrarProducto);

    Cola cola;
    crearCola(&cola);
    cargarColaArchivo(&cola, sizeof(Producto), filename);

    char* mensaje = "1 - Cargar producto\n2 - Ver frente de la cola\n3 - Sacar de la cola\n4 - Ver fondo de la cola\n5 - Salir\nElija una opcion: ";

    int opc = menu(mensaje, 1, 5);

    while(opc != 5){
        switch (opc) {
        case 1: {
            Producto prod;
            ingresarProducto(&prod);
            insertarEnCola(&cola, &prod, sizeof(Producto));
            printf("Elemento insertado en la cola.");
            break;
        }
        case 2: {
            Producto prod;
            verFrenteCola(&cola, &prod, sizeof(Producto));
            mostrarProducto(&prod);
            break;
        }
        case 3: {
            Producto prod;
            sacarDeCola(&cola, &prod, sizeof(Producto));
            printf("Elemento eliminado de la cola.\n");
            mostrarProducto(&prod);
            break;
        }
        case 4: {
            Producto prod;
            verFondoCola(&cola, &prod, sizeof(Producto));
            mostrarProducto(&prod);
            break;
        }
    }

        opc = menu(mensaje, 1, 5);
    }

    if(colaVacia(&cola)){
        remove(filename);
    } else {
        cargarArchivoCola(filename, &cola);
    }

    recorrerArchivo(filename, sizeof(Producto), mostrarProducto);


}
