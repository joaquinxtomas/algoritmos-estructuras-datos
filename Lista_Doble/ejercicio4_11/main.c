#include "funciones.h"

int main()
{

    tLista lista;
    crearLista(&lista);

    insertarNumLista(&lista, insertarAlComienzo);

    printf("LISTA ANTES DE REDUCE\n");
    mostrarDeDerIzq(&lista, mostrarNumero);

    printf("\nLISTA NUEVA DESPUES DE REDUCE\n");
    tLista listaReducida = reduce(&lista, sizeof(int), sumar);
    mostrarDeDerIzq(&listaReducida, mostrarNumero);

    printf("\nLISTA ORIGINAL LUEGO DE REDUCE\n");
    mostrarDeDerIzq(&lista, mostrarNumero);

}
