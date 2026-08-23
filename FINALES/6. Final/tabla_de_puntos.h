#ifndef TABLA_DE_PUNTOS_H_INCLUDED
#define TABLA_DE_PUNTOS_H_INCLUDED
#include "lista.h"

typedef struct{
    char iniciales[4];
    unsigned puntaje;
}t_puntaje;

typedef struct {
    tLista tabla;
    unsigned tam;
}t_tabla_puntos;

void crear_tabla_puntos(t_tabla_puntos* p, unsigned tam);
int agregar_puntaje(t_tabla_puntos* p, const t_puntaje* dato);
void imprimir_tabla_puntos(t_tabla_puntos* p);
void vaciar_tabla_puntos(t_tabla_puntos* p);

int procesar_top(const char* filename);
int comparaPuntajes(const void* dato1, const void* dato2);

int procesar_podio(const char* filename);
int agregar_puntaje_podio(t_tabla_puntos *p, const t_puntaje* dato);


#endif // TABLA_DE_PUNTOS_H_INCLUDED
