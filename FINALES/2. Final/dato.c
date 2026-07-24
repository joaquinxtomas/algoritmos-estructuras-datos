#include "dato.h"

int parsearDato(const char* linea, void* dato){
    tDato* d = (tDato*)dato;

    return sscanf(linea, "%5[^-]-%d", d->clave, &d->dato) == 2;
}

void mostrarDato(const void* dato){
    tDato* d = (tDato*)dato;

    printf("%s - %d\n", d->clave, d->dato);
}

int comparaDato(const void* dato1, const void* dato2){
    tDato* d1 = (tDato*)dato1;
    tDato* d2 = (tDato*)dato2;

    return strcmp(d1->clave, d2->clave);
}
