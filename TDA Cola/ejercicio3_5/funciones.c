#include "funciones.h"
void proceso(){
    srand(time(NULL));

    int arribos[] = {1,5,9};
    int atenciones[] = {1,3,5};

    unsigned tiempoActual = 0;
    unsigned proximoArribo = 0;
    unsigned finAtencion = 0;
    int atendiendo = 0;
    int vecesVacia = 0;
    int idCliente = 1;

    tCola cola;
    crearCola(&cola);

    while(vecesVacia < 5){

        if(tiempoActual == proximoArribo){
            insertarAlFinal(&cola, &idCliente, sizeof(idCliente));
            //printf("Min %u: llega cliente #%d\n", tiempoActual, idCliente);
            idCliente++;
            proximoArribo = tiempoActual + arribos[rand()%3];
        }

        if(atendiendo && tiempoActual == finAtencion){
            int saliendo;
            sacarAlComienzo(&cola, &saliendo, sizeof(saliendo));
            printf("Min %u: termina cliente #%d\n", tiempoActual, saliendo);
            atendiendo = 0;
            if(esColaVacia(&cola)){
                vecesVacia++;
                //printf("  >> cola vacía (%d/5)\n", vecesVacia);
            }
        }

        if(!atendiendo && !esColaVacia(&cola)){
            int atender;
            verPrimero(&cola, &atender, sizeof(atender));
            finAtencion = tiempoActual + atenciones[rand()%3];
            atendiendo = 1;
            //printf("Min %u: empieza a atender a #%d\n", tiempoActual, atender);
        }

        printf("\n--- Estado al minuto %u ---\n", tiempoActual);
        mostrarCola(&cola, mostrarNum);
        printf("\n\n");

        tiempoActual++;
        sleep(2);

    }

    vaciarCola(&cola);

}

/*
void proceso(){
    srand(time(NULL));

    unsigned tiempoActual = 0;
    unsigned proximoArribo = 0;
    unsigned finAtencion = 0;
    int atendiendo = 0;
    int vecesVacia = 0;
    int idCliente = 1;

    int arribos[] = {1,5,9};
    int atenciones[] = {1,3,5};

    tCola cola;
    crearCola(&cola);

    while(vecesVacia < 5){

        if(!atendiendo || proximoArribo <= finAtencion){
            tiempoActual = proximoArribo;
            insertarAlFinal(&cola, &idCliente, sizeof(idCliente));
            printf("Min %u: llega cliente #%d\n", tiempoActual, idCliente);
            idCliente++;

            proximoArribo = tiempoActual + arribos[rand() % 3];

            if(!atendiendo){
                int aAtender;
                verPrimero(&cola, &aAtender, sizeof(aAtender));
                finAtencion = tiempoActual + atenciones[rand()%3];
                atendiendo = 1;
                printf("Min %u: atendiendo cliente #%d\n", tiempoActual, aAtender);
            }

        }else {
            tiempoActual = finAtencion;
            int saliendo;
            sacarAlComienzo(&cola,&saliendo, sizeof(saliendo));
            printf("Min %u: termina cliente #%d\n", tiempoActual, saliendo);
            if(esColaVacia(&cola)){
                vecesVacia++;
                atendiendo = 0;
                printf("  >> cola vacía (%d/5)\n", vecesVacia);
            } else {
                int siguiente;
                verPrimero(&cola, &siguiente, sizeof(siguiente));
                finAtencion = tiempoActual + atenciones[rand() % 3];
                printf("Min %u: atendiendo cliente #%d\n", tiempoActual, siguiente);
            }
        }

    }

}*/

void mostrarCola(const tCola* cola, void(*mostrar)(const void*)){
    tNodo* aux = cola->primero;
    while(aux){
        mostrar(aux->info);
        aux = aux->sig;
    }
}

void mostrarNumSale(const void* dato){
    int numero = *(int*)dato;
    printf("Numero termino atención: %d", numero);
}

void mostrarNumLlega(const void* dato){
    int numero = *(int*)dato;
    printf("Numero llegando: %d", numero);
}

void mostrarNum(const void* dato){
    int numero = *(int*)dato;
    printf("Numero: %d\n", numero);
}
