#include "funciones.h"

int main()
{

    tLista lista;
    crearLista(&lista);

    //insertarPersonasLista(&lista, insertarAlComienzo);
    insertarPersonasOrdenadas(&lista, comparaDni);

    mostrarDeIzqDer(&lista, mostrarPersona);


}
