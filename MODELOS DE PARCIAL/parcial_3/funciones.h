#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "tda_lista.h"

typedef struct{
    int cod_materia;
    char cod_cursada[7];
    int nota_final;
}t_materia;

typedef struct{
    t_materia materias[50];
    int cant_materias;
}t_materias;

typedef struct {
    int dni;
    char apellido[21];
    char nombres[21];
    char cod_carrera[4];
    t_materias materias;
}t_alumno;

void generarLote(const char* filename);
int comparaDni(const void* dato1, const void* dato2);
int comparaApellidoNombreDni(const void* dato1, const void* dato2);
int comparaCarreraApNomDni(const void* dato1, const void* dato2);
int comparaPromedios(const void* dato1, const void* dato2);
void grabarListaDesdeArch(tLista* lista, const char* filename);
void trozarAlumno(char* linea, t_alumno* alumno);
void trozarMaterias(char* linea, t_materia* materia);
void recorrerLista(tLista* lista, void(*accion)(const void*));
void mostrarDni(const void* dato);
void mostrarDniPromedio(const void* dato);

#endif // FUNCIONES_H_INCLUDED
