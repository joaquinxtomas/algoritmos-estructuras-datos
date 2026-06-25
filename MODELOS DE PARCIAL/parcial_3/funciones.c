#include "funciones.h"

void generarLote(const char* filename){
    srand((unsigned)time(NULL));

    t_alumno alumno;
    t_materia vecMaterias[50];

    FILE* archivo = fopen(filename, "w");
    if(!archivo){
        return;
    }

    char nombres[20][21] = {"nombre1", "nombre2", "nombre3", "nombre4", "nombre5", "nombre6", "nombre7", "nombre8", "nombre9", "nombre10", "nombre11", "nombre12", "nombre13", "nombre14",
                            "nombre15", "nombre16", "nombre17", "nombre18", "nombre19", "nombre20"};

    char apellidos[20][21] = {"apellido1", "apellido2", "apellido3","apellido4","apellido5","apellido6","apellido7","apellido8","apellido9","apellido10","apellido11","apellido12","apellido13",
                            "apellido14","apellido15","apellido16","apellido17","apellido18","apellido19","apellido20"};

    char codigosCarrera[5][4] = {"INF", "ELE", "IND","MED","ABO"};

    char codigosMateria[4][7] = {"20231C", "20232C", "20241C", "20242C"};

    for(int i = 0; i< 20; i++){
        strcpy(alumno.nombres, nombres[i]);
        strcpy(alumno.apellido, apellidos[i]);
        strcpy(alumno.cod_carrera, codigosCarrera[i % 5]);
        alumno.dni = 40000 + i;
        alumno.materias.cant_materias = 50;

        fprintf(archivo, "%d|%s|%s|%s|%d\n", alumno.dni, alumno.apellido, alumno.nombres, alumno.cod_carrera, 50);

        for(int j = 0; j < 50; j++){
            vecMaterias[j].cod_materia = 1000 + i;
            strcpy(vecMaterias[j].cod_cursada, codigosMateria[i % 4]);
            vecMaterias[j].nota_final = (rand() % 10) + 1;

            fprintf(archivo, "%d|%s|%d\n", vecMaterias[j].cod_materia, vecMaterias[j].cod_cursada, vecMaterias[j].nota_final);
        }

    }
    fclose(archivo);
}

int comparaDni(const void* dato1, const void* dato2){
    t_alumno* alumno1 = (t_alumno*)dato1;
    t_alumno* alumno2 = (t_alumno*)dato2;

    return (alumno1->dni - alumno2->dni);
}

int comparaApellidoNombreDni(const void* dato1, const void* dato2){
    t_alumno* alumno1 = (t_alumno*)dato1;
    t_alumno* alumno2 = (t_alumno*)dato2;

    if(strcmp(alumno1->apellido, alumno2->apellido) != 0){
        return strcmp(alumno1->apellido, alumno2->apellido);
    }

    if(strcmp(alumno1->nombres, alumno2->nombres) != 0){
        return strcmp(alumno1->nombres, alumno2->nombres);
    }

    return alumno1->dni - alumno2->dni;
}

int comparaCarreraApNomDni(const void* dato1, const void* dato2){
    t_alumno* alumno1 = (t_alumno*)dato1;
    t_alumno* alumno2 = (t_alumno*)dato2;

    if(strcmp(alumno1->cod_carrera, alumno2->cod_carrera) != 0){
        return strcmp(alumno1->cod_carrera, alumno2->cod_carrera);
    }

    if(strcmp(alumno1->apellido, alumno2->apellido) != 0){
        return strcmp(alumno1->apellido, alumno2->apellido);
    }

    if(strcmp(alumno1->nombres, alumno2->nombres) != 0){
        return strcmp(alumno1->nombres, alumno2->nombres);
    }

    return alumno1->dni - alumno2->dni;
}

int comparaPromedios(const void* dato1, const void* dato2){
    t_alumno* alumno1 = (t_alumno*)dato1;
    t_alumno* alumno2 = (t_alumno*)dato2;

    int cant_1 = alumno1->materias.cant_materias;
    float total_1 = 0.0;
    int cant_2 = alumno2->materias.cant_materias;
    float total_2 = 0.0;

    for(int i = 0; i < cant_1; i++){
        total_1 += alumno1->materias.materias[i].nota_final;
    }

    for(int j = 0;j < cant_2;j++){
        total_2 += alumno2->materias.materias[j].nota_final;
    }

    float prom_1 = cant_1 > 0 ? (total_1 / cant_1) : 0.0;
    float prom_2 = cant_2 > 0 ? (total_2 / cant_2) : 0.0;

    return prom_1 < prom_2 ? 1 : prom_2 < prom_1 ? -1 : 0;

}

void grabarListaDesdeArch(tLista* lista, const char* filename){
    FILE* archivo = fopen(filename, "r");
    if(!archivo){
        return;
    }

    char linea[255];

    t_alumno alumno;

    int i;

    while(fgets(linea, sizeof(linea), archivo)){

        trozarAlumno(linea, &alumno);

        for(i = 0; i < alumno.materias.cant_materias; i++){
            fgets(linea, sizeof(linea), archivo);
            trozarMaterias(linea, &alumno.materias.materias[i]); //materias es ARRAY
        }

        insertarAlFinal(lista, &alumno, sizeof(t_alumno));
    }

    fclose(archivo);
}

void trozarAlumno(char* linea, t_alumno* alumno){
    char* tok;

    tok = strtok(linea, "|");
    sscanf(tok, "%d", &alumno->dni);

    tok = strtok(NULL, "|");
    strcpy(alumno->apellido, tok);

    tok = strtok(NULL, "|");
    strcpy(alumno->nombres, tok);

    tok = strtok(NULL, "|");
    strcpy(alumno->cod_carrera, tok);

    tok = strtok(NULL, "|\n");
    sscanf(tok, "%d", &alumno->materias.cant_materias);

}

void trozarMaterias(char* linea, t_materia* materia){
    char* tok;

    tok = strtok(linea, "|");
    sscanf(tok, "%d", &materia->cod_materia);

    tok = strtok(NULL,"|");
    strcpy(materia->cod_cursada, tok);

    tok = strtok(NULL, "|\n");
    sscanf(tok, "%d", &materia->nota_final);
}

void recorrerLista(tLista* lista, void(*accion)(const void*)){
    if(!*lista){
        return;
    }

    tNodo* actual = *lista;

    while(actual){
        accion(actual->info);
        actual = actual->sig;
    }
}

void mostrarDni(const void* dato){
    t_alumno* alumno = (t_alumno*)dato;

    printf("%d\n", alumno->dni);
}


void mostrarDniPromedio(const void* dato){
    t_alumno* alumno = (t_alumno*)dato;

    int cant_1 = alumno->materias.cant_materias;
    float total_1 = 0.0;
    for(int i = 0; i < cant_1; i++){
        total_1 += alumno->materias.materias[i].nota_final;
    }
    float prom_1 = cant_1 > 0 ? (total_1 / cant_1) : 0.0;
    printf("%d - %.2f\n ", alumno->dni, prom_1);
}

