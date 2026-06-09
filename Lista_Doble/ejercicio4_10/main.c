#include "funciones.h"

int main()
{
    tLista lista;
    crearLista(&lista);
    insertarPersonasLista(&lista, insertarAlComienzo);

    printf("LISTA ORIGINAL\n");
    mostrarDeDerIzq(&lista, mostrarPersona);

    printf("LISTA FILTRADA\n");
    tLista listaFiltrada = filter(&lista, sizeof(tPersona), alturaMayor);
    mostrarDeDerIzq(&listaFiltrada, mostrarPersona);

    printf("LISTA ORIGINAL DESPUES DE FILTER\n");
    mostrarDeDerIzq(&lista, mostrarPersona);
}
