#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main()
{
    char* filename = "archivo.bin";

    crearArchivoBin(filename);
    leerArchivoBinario(filename);

    procesoGenericoBinario(filename, sizeof(tPersona), mostrarVecPersona);
}
