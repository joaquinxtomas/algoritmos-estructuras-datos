#include "funciones.h"

int main()
{

    tLista lista;
    crearLista(&lista);

    insertarPersonasLista(&lista, insertarAlComienzo);
    //insertarPersonasOrdenadas(&lista, comparaDni);
    //mostrarDeIzqDer(&lista, mostrarPersona);

    //ordenarLista(&lista, comparaDni);

    //mostrarDeIzqDer(&lista, mostrarPersona);

    tPersona persona;
    persona.dni = 4;

    buscar(&lista, &persona, sizeof(tPersona), comparaDni);

    mostrarPersona(&persona);

}
