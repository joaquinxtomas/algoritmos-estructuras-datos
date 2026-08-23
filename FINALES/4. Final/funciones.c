#include "funciones.h"

void generarLote(const char* filename){
    FILE* archivo = fopen(filename, "w");
    if(!archivo) return;

    tPersona corredores[] = {
        {30125478, "Garcia Manuel",          {4, 12, 35}},
        {28934561, "Lopez Maria",            {3, 45, 18}},
        {35672190, "Rodriguez Pablo",        {5, 1,  42}},
        {41258903, "Fernandez Laura",        {3, 45, 18}},
        {33789012, "Martinez Juan",          {4, 33, 51}},
        {27456389, "Gonzalez Ana",           {3, 22, 14}},
        {38901245, "Perez Santiago",         {4, 12, 35}},
        {42567834, "Diaz Romina",            {5, 15, 3}},
        {31234567, "Sanchez Carlos",         {3, 22, 14}},
        {36890123, "Torres Valentina",       {4, 33, 51}},
        {29345678, "Ramirez Diego",          {3, 45, 18}},
        {40123456, "Herrera Camila",         {4, 28, 11}},
    };
    int cantCorredores = sizeof(corredores) / sizeof(tPersona);

    for(int i = 0; i < cantCorredores; i++){
        fprintf(archivo, "%8d-%30s-%d:%d:%d\n", corredores[i].dni, corredores[i].nombreApellido, corredores[i].tiempo.horas,corredores[i].tiempo.minutos,corredores[i].tiempo.segundos);
    }

    fclose(archivo);
}

void mostrarPersona(const void* dato){
    tPersona* persona = (tPersona*)dato;

    printf("%d %30s %d:%d:%d\n", persona->dni, persona->nombreApellido, persona->tiempo.horas, persona->tiempo.minutos, persona->tiempo.segundos);
}

int comparaTiempos(const void* dato1, const void* dato2){
    tPersona* persona1 = (tPersona*)dato1;
    tPersona* persona2 = (tPersona*)dato2;

    if((persona1->tiempo.horas - persona2->tiempo.horas) != 0){
        return persona1->tiempo.horas - persona2->tiempo.horas;
    }

    if((persona1->tiempo.minutos- persona2->tiempo.minutos) != 0){
        return persona1->tiempo.minutos - persona2->tiempo.minutos;
    }

    return persona1->tiempo.segundos - persona2->tiempo.segundos;
}
