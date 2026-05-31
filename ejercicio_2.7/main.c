#include "funciones.h"

int main()
{
    const char* filename = "binario.dat";
    crearArchivo(filename);

    printf("ARCHIVO SIN ORDENAR\n");
    mostrarArchivo(filename, sizeof(tPersona), mostrarPersona);

    printf("ARCHIVO ORDENADO\n");
    proceso(filename, sizeof(tPersona), compararDni);

    mostrarArchivo("ordenado.bin", sizeof(tPersona), mostrarPersona);
}
