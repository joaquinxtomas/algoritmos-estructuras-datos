#include "funciones.h"
#include "tda_lista.h"

int main()
{
    const char* filename = "prueba.txt";
    generarLote(filename);

    tLista lista;
    crearLista(&lista);

    grabarListaDesdeArch(&lista, filename);

    //lista normal
    recorrerLista(&lista, mostrarDniPromedio);

    //lista invertida
    /*invertirLista(&lista, sizeof(t_alumno));

    printf("\n");
    recorrerLista(&lista, mostrarDni);*/

    //lista ordenada por mejores promedios
    printf("\n");
    ordenarLista(&lista, sizeof(t_alumno), comparaPromedios);
    recorrerLista(&lista, mostrarDniPromedio);


}
