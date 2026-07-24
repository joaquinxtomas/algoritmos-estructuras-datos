#include "dato.h"

int main()
{

    const char* filename = "datos.txt";

    tArbol arbol;
    crearArbol(&arbol);

    cargarDesdeTxt(&arbol, filename, sizeof(tDato), comparaDato, parsearDato);
    recorrerArbolPreOrden(&arbol, NULL, 0, mostrarDato);

}
