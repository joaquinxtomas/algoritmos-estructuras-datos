#include "funciones.h"

int main()
{
    const char* filename = "corredores.txt";
    generarLote(filename);

    FILE* archivo = fopen(filename, "r");
    if(!archivo) return -1;

    tPersona persona;
    char linea[200];

    tLista lista;
    crearLista(&lista);

    while(fgets(linea, sizeof(linea), archivo)){
        sscanf(linea, "%d-%30[^-]-%d:%d:%d", &persona.dni, persona.nombreApellido, &persona.tiempo.horas, &persona.tiempo.minutos, &persona.tiempo.segundos);
        insertarEnTop(&lista, &persona, sizeof(tPersona), comparaTiempos, 3);
    }

    recorrerLista(&lista, mostrarPersona);

    vaciarLista(&lista);

    fclose(archivo);
}
