#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "lista.h"

typedef struct{
    int horas;
    int minutos;
    int segundos;
}tTiempo;

typedef struct{
    int dni;
    char nombreApellido[30];
    tTiempo tiempo;
}tPersona;

void generarLote(const char* filename);
void mostrarPersona(const void* dato);
int comparaTiempos(const void* dato1, const void* dato2);
#endif // FUNCIONES_H_INCLUDED
