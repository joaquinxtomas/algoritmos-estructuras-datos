#include "funciones.h"

int main()
{
    tLista lista;
    crearLista(&lista);

    insertarPersonasLista(&lista, insertarAlComienzo);

    printf("\n-LISTA ORIGINAL\n");
    mostrarDeDerIzq(&lista, mostrarPersona);

    //map2(&lista, &listaMapeada, sizeof(tPersona), sumaDni);
    tLista listaMapeada = map2(&lista, sizeof(tPersona), sumaDni);
    printf("\n-------------------------------------------\n");
    printf("\n-LISTA MAPEADA\n");
    mostrarDeDerIzq(&listaMapeada, mostrarPersona);

    printf("\n-LISTA ORIGINAL DESPUES DE MAPEAR\n");
    mostrarDeDerIzq(&lista, mostrarPersona);
}
