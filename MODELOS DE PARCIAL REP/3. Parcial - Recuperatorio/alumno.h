#ifndef ALUMNO_H_INCLUDED
#define ALUMNO_H_INCLUDED
#include "tLista.h"
#include <time.h>
#include <ctype.h>

typedef struct{
    unsigned cod_materia;
    char cod_cursada[7];
    unsigned nota_final;
}t_materia;

typedef struct{
    t_materia materias[50];
    unsigned cant_materias;
}t_materias;

typedef struct{
    unsigned dni;
    char apellido[21];
    char nombre[21];
    char cod_carrera[4];
    t_materias materias;
}t_alumno;

void crearLote(const char* filename);
void cargarLista(const char* filename, tLista* lista);
int trozarCabecera(t_alumno* alumno, char* linea);
int trozarMateria(t_materia* materia, char* linea);
void mostrarAlumno(const void* dato);
float calculaPromedio(t_alumno* alumno);
int comparaCarProm(const void* dato1, const void* dato2);
int comparaProm(const void* dato1, const void* dato2);
int comparaCarApNomDni(const void* dato1, const void* dato2);
int comparaApNomDni(const void* dato1, const void* dato2);
int comparaDni(const void* dato1, const void* dato2);
void mostrarAlumnoSinMaterias(const void* dato);
void mostrarAlumnoPromedio(const void* dato);
char menu(const char* mensaje, const char* opciones);

#endif // ALUMNO_H_INCLUDED
