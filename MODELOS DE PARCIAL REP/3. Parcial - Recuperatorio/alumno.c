#include "alumno.h"

void crearLote(const char* filename){
    FILE* archivo = fopen(filename, "w");
    if(!archivo){
        printf("Error al abrir el archivo.\n");
        return;
    }

    srand((unsigned)time(NULL));


    char nombres[20][20] = {"Joaquin", "Federico", "Juan", "Roberto", "Brian", "Anabella","Luz","Soledad", "Alberto", "Lionel", "Camilo", "Juana", "Maximiliano",
                            "Leandro", "Emiliano", "Nicolas", "Alfredo","Mirta", "Mauro", "Gilberto"};
    char apellidos[20][20] = {"Apellido1", "Apellido2", "Apellido3", "Apellido4", "Apellido5", "Apellido6", "Apellido7", "Apellido8", "Apellido9", "Apellido10",
                                "Apellido11", "Apellido12", "Apellido13", "Apellido14", "Apellido15", "Apellido16", "Apellido17", "Apellido18", "Apellido19", "Apellido20"};
    char cod_carrera[5][4] = {"INF", "ELE","IND","MED","ABO"};
    char cod_cursada[4][7] = {"20231C", "20232C","20241C","20242C"};

    t_alumno alumno;

    for(int i = 0; i < 20; i++){ //cant alumnos
        strcpy(alumno.apellido, apellidos[i]);
        strcpy(alumno.nombre, nombres[i]);
        strcpy(alumno.cod_carrera, cod_carrera[rand() % 5]);
        alumno.dni = rand() % 30000000;
        alumno.materias.cant_materias = 1 + rand() % 50;
        fprintf(archivo, "%u|%s|%s|%s|%u\n",alumno.dni, alumno.apellido, alumno.nombre, alumno.cod_carrera, alumno.materias.cant_materias);
        for(int j = 0; j < alumno.materias.cant_materias; j++){
            alumno.materias.materias[j].cod_materia = 1000 + rand() % 9000;
            alumno.materias.materias[j].nota_final =1 + rand() % 10;
            strcpy(alumno.materias.materias[j].cod_cursada, cod_cursada[rand() % 4]);
            fprintf(archivo,"%u|%s|%u\n", alumno.materias.materias[j].cod_materia, alumno.materias.materias[j].cod_cursada, alumno.materias.materias[j].nota_final);
        }
    }

    fclose(archivo);
}

void cargarLista(const char* filename, tLista* lista){
    FILE* archivo = fopen(filename, "r");
    if(!archivo){
        printf("Error al abrir el archivo.\n");
        return;
    }

    t_alumno alumno;
    t_materia materia;

    char linea[100];
    while(fgets(linea, sizeof(linea), archivo)){
        trozarCabecera(&alumno, linea);

        for(int i = 0 ; i < alumno.materias.cant_materias; i++){
            if(!fgets(linea, sizeof(linea), archivo)){
                return;
            }
            trozarMateria(&materia, linea);

            alumno.materias.materias[i] = materia;
        }

        insertarAlPrincipio(lista, &alumno, sizeof(t_alumno));
    }

    fclose(archivo);
}

int trozarCabecera(t_alumno* alumno, char* linea){
    char* tok = strtok(linea, "|");
    if(!tok){
        return 0;
    }
    sscanf(tok, "%u", &alumno->dni);

    tok = strtok(NULL, "|");
    strcpy(alumno->apellido, tok);

    tok = strtok(NULL, "|");
    strcpy(alumno->nombre, tok);

    tok = strtok(NULL, "|");
    strcpy(alumno->cod_carrera, tok);

    tok = strtok(NULL, "\n");
    sscanf(tok, "%u", &alumno->materias.cant_materias);

    return 1;
}

int trozarMateria(t_materia* materia, char* linea){
    char* tok = strtok(linea, "|");
    if(!tok){
        return 0;
    }
    sscanf(tok, "%u", &materia->cod_materia);

    tok = strtok(NULL, "|");
    strcpy(materia->cod_cursada, tok);

    tok = strtok(NULL, "\n");
    sscanf(tok, "%u", &materia->nota_final);

    return 1;
}

void mostrarAlumno(const void* dato){
    t_alumno* alumno = (t_alumno*)dato;

    printf("%u | %s | %s | %s | %u: \n", alumno->dni, alumno->apellido, alumno->nombre, alumno->cod_carrera, alumno->materias.cant_materias);
    for(int i = 0; i < alumno->materias.cant_materias; i++){
        printf("%u | %s | %u\n", alumno->materias.materias[i].cod_materia, alumno->materias.materias[i].cod_cursada, alumno->materias.materias[i].nota_final);
    }
}

void mostrarAlumnoSinMaterias(const void* dato){
    t_alumno* alumno = (t_alumno*)dato;

    printf("%u | %s | %s | %s\n", alumno->dni, alumno->apellido, alumno->nombre, alumno->cod_carrera);
}

void mostrarAlumnoPromedio(const void* dato){
    t_alumno* alumno = (t_alumno*)dato;

    float prom = calculaPromedio(alumno);
    printf("%u | %s | %s | %s | %.2f \n", alumno->dni, alumno->apellido, alumno->nombre, alumno->cod_carrera, prom);

}

char menu(const char* mensaje, const char* opciones){
    char opc;
    do{
        printf("%s\nIngrese su opcion: ", mensaje);
        scanf(" %c", &opc);

        opc = toupper(opc);
        if(strchr(opciones, opc) == NULL){
            printf("Opcion invalida. Intente nuevamente.\n");
        }
    }while(strchr(opciones, opc) == NULL);
    return opc;
}

/*FUNCIONES DE COMPARACION PARA ORDENAR*/

int comparaDni(const void* dato1, const void* dato2){
    t_alumno* alumno1 = (t_alumno*)dato1;
    t_alumno* alumno2 = (t_alumno*)dato2;

    return alumno1->dni - alumno2->dni;
}

int comparaApNomDni(const void* dato1, const void* dato2){
    t_alumno* alumno1 = (t_alumno*)dato1;
    t_alumno* alumno2 = (t_alumno*)dato2;

    if(strcmp(alumno1->apellido, alumno2->apellido) != 0){
        return strcmp(alumno1->apellido, alumno2->apellido);
    }

    if(strcmp(alumno1->nombre, alumno2->nombre) != 0){
        return strcmp(alumno1->nombre, alumno2->nombre);
    }

    return alumno1->dni - alumno2->dni;
}

int comparaCarApNomDni(const void* dato1, const void* dato2){
    t_alumno* alumno1 = (t_alumno*)dato1;
    t_alumno* alumno2 = (t_alumno*)dato2;

    if(strcmp(alumno1->cod_carrera, alumno2->cod_carrera) != 0){
        return strcmp(alumno1->cod_carrera, alumno2->cod_carrera);
    }

    if(strcmp(alumno1->apellido, alumno2->apellido) != 0){
        return strcmp(alumno1->apellido, alumno2->apellido);
    }

    if(strcmp(alumno1->nombre, alumno2->nombre) != 0){
        return strcmp(alumno1->nombre, alumno2->nombre);
    }

    return alumno1->dni - alumno2->dni;
}

int comparaProm(const void* dato1, const void* dato2){
    t_alumno* alumno1 = (t_alumno*)dato1;
    t_alumno* alumno2 = (t_alumno*)dato2;

    float prom1 = calculaPromedio(alumno1);
    float prom2 = calculaPromedio(alumno2);

    return prom1 > prom2 ? 1 : prom2 > prom1 ? -1: 0;
}

float calculaPromedio(t_alumno* alumno){
    float total = 0.0;
    for(int i = 0; i < alumno->materias.cant_materias; i++){
        total += alumno->materias.materias[i].nota_final;
    }

    return total / alumno->materias.cant_materias;
}

float calculaPromedioSinAplazo(t_alumno* alumno){
    float total = 0.0;
    for(int i = 0; i < alumno->materias.cant_materias; i++){
        if(alumno->materias.materias[i].nota_final > 2){
            total += alumno->materias.materias[i].nota_final;
        }
    }

    return total / alumno->materias.cant_materias;
}

int comparaCarProm(const void* dato1, const void* dato2){
    t_alumno* alumno1 = (t_alumno*)dato1;
    t_alumno* alumno2 = (t_alumno*)dato2;

    if(strcmp(alumno1->cod_carrera, alumno2->cod_carrera) != 0){
        return strcmp(alumno1->cod_carrera, alumno2->cod_carrera);
    }

    float prom1 = calculaPromedio(alumno1);
    float prom2 = calculaPromedio(alumno2);

    return prom1 > prom2 ? 1 : prom2 > prom1 ? -1: 0;
}
