//#include "lista.h"
#include "productos.h"

typedef struct{
    int dni;
    char nombre[30];
    int edad;
}tPersona;

void mostrarPersona(const void* dato){
    tPersona* persona = (tPersona*)dato;

    printf("%d - %s - %d\n", persona->dni, persona->nombre, persona->edad);
}

int menoresA18(const void* dato){
    tPersona* persona = (tPersona*)dato;

    if(persona->edad < 18){
        return 1;
    }

    return 0;
}

int main()
{
    /**item A**/
    /*tPersona personas[10] = {
            {434567272, "Joaquin",20},
            {39123456, "Sofia",19},
            {40987654, "Mateo",10},
            {38555444, "Valentina",5},
            {41222333, "Lucas",46},
            {37888999, "Martina",40},
            {42111000, "Santiago",35},
            {36777888, "Camila",60},
            {44555666, "Alejandro",6},
            {35444333, "Lucia",9}
    };

    tLista lista;
    crearLista(&lista);

    for(int i = 0; i < 10; i++){
        insertarAlInicio(&lista, &personas[i], sizeof(tPersona));
    }

    mostrarInverso(&lista, mostrarPersona, menoresA18);*/

    /**item B**/
    const char* filename_productos = "productos.dat";
    const char* filename_indice = "prodTC.idx";

    tArbol arbol;
    crearArbol(&arbol);

    generarLote(filename_productos);
    cargarIndice(filename_productos, &arbol);
    cargarArchivo(&arbol, filename_indice, sizeof(tIndice));
    //recorrerInOrden(&arbol, NULL,0 , sizeof(tIndice), mostrarIndice);
    mostrarArbolGrafico(&arbol, 0, sizeof(tIndice), mostrarIndice);
}
