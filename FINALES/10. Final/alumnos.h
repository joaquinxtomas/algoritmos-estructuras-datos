#ifndef ALUMNOS_H_INCLUDED
#define ALUMNOS_H_INCLUDED

typedef struct{
    int dni;
    char apellido[20];
    char nombre[20];
    int carrera;
    float promedio;
}tAlumno;

int comparaAlumno(const void*, const void*) //por clave

#endif // ALUMNOS_H_INCLUDED
