#include "tLista.h"
#include "alumno.h"

int main()
{
    const char* filename = "alumnos.txt";
    tLista lista;
    crearLista(&lista);

    crearLote(filename);
    cargarLista(filename, &lista);
    char opcion;
    do{
        opcion = menu("1. Ordenar alumnos por DNI\n2. Ordenar alumnos por apellido, nombre y DNI\n3. Ordenar alumnos por carrera, apellido, nombre y DNI\n"
                      "4. Ordenar alumnos por promedio\n5. Ordenar alumnos por carrera y promedio sin contar aplazos \n6. Invertir lista y mostrar.\n7. Salir", "1234567");
        switch(opcion){
        case '1':
            ordenarLista(&lista, sizeof(t_alumno), comparaDni);
            recorrerLista(&lista, mostrarAlumnoSinMaterias);
            break;
        case '2':
            ordenarLista(&lista, sizeof(t_alumno), comparaApNomDni);
            recorrerLista(&lista, mostrarAlumnoSinMaterias);
            break;
        case '3':
            ordenarLista(&lista, sizeof(t_alumno), comparaCarApNomDni);
            recorrerLista(&lista, mostrarAlumnoSinMaterias);
            break;
        case '4':
            ordenarLista(&lista, sizeof(t_alumno), comparaProm);
            recorrerLista(&lista, mostrarAlumnoPromedio);
            break;
        case '5':
            ordenarLista(&lista, sizeof(t_alumno), comparaCarProm);
            recorrerLista(&lista, mostrarAlumnoPromedio);
            break;
        case '6':
            invertirLista(&lista, sizeof(t_alumno));
            recorrerLista(&lista, mostrarAlumno);
            break;
        }
    }while(opcion != '7');
}
