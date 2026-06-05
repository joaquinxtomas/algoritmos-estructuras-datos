#include "funciones.h"

int main()
{

    const char* filename = "empleados.bin";
    const char* filenameOrdenado = "empleados_ordenados.bin";

    int ordenado = estaOrdenado(filenameOrdenado, sizeof(tEmpleado), comparaLegajos);

    if(ordenado == 1){
        printf("El archivo está correctamente ordenado.");
    } else {
        printf("El archivo está desordenado.");
    }
}
