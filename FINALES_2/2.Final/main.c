#include "funciones.h"
int main()
{
    const char* filename = "datos.txt";
    tArbol arbol;
    crearArbol(&arbol);

    cargarDesdeTxt(filename, &arbol);
    recorrerArbolPreOrden(&arbol, sizeof(Dato), 0, NULL, mostrarDato);

    int nivelCant = 3;
    int nivelComp = 3;
    int cantNodos = cantNodosNivel(&arbol, nivelCant);
    int esNivelComp = nivelCompleto(&arbol, nivelComp);

    printf("cantidad de nodos (nivel %d): %d - es nivel completo (nivel %d): %d", nivelCant, cantNodos, nivelComp, esNivelComp);
}
