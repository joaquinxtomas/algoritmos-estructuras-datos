#include "funciones.h"

void proceso(const char* filename){
    FILE* archivo = fopen(filename, "r");
    if(!archivo){
        return;
    }

    FILE* archivo_incompleto = fopen("despachos_ineficientes.txt", "w");
    if(!archivo_incompleto){
        fclose(archivo);
        return;
    }

    FILE* archivo_pendientes = fopen("pendientes.txt", "w");
    if(!archivo_pendientes){
        fclose(archivo);
        fclose(archivo_incompleto);
        return;
    }

    char linea[200];
    char codigo_ing[4];
    int tam_vec_colas, capacidad_maxima;

    fgets(linea, sizeof(linea), archivo); //leer capacidad maxima y tamaño vec
    sscanf(linea, "%d,%d", &capacidad_maxima, &tam_vec_colas);

    tCola lista_colas[capacidad_maxima];

    for(int i = 0; i < capacidad_maxima; i++){
        crearCola(lista_colas[i]);
    }

    while(fgets(linea, sizeof(linea), archivo)){
        strncpy(codigo_ing, linea, 3);

        if(strcmp(codigo_ing, "DES")){
            //SACAR DE COLA Y ESCRIBIR SEGUN CORRESPONDA
            int destino;
            sscanf(linea, "|%d", &destino);
            int cant_paquetes = 0;
            while(!colaVacia(lista_colas[destino - 1]){
                tPaquete paquete_aux;
                sacarDeCola(lista_colas[destino - 1], &paquete_aux, sizeof(tPaquete));
                cant_paquetes++;
            }

            if(cant_paquetes < capacidad_maxima){
                fprintf(archivo_incompleto, "%s|%d|%s|%d|%d\n",
                    "DES", destino, "INCOMPLETO", capacidad_maxima, cant_paquetes);
            } else {
                //imprimir destino OK (vacio no hay mas paquetes para ese destino)
                fprintf(archivo_incompleto, "%s|%d|%s\n",
                    "DES", destino, "VACIO");
            }
        } else if(strcmp(codigo_ing, "ING")){
            //PONER EN COLA Y CONTAR PAQUETES
            //leer linea a estructura
            tPaquete paquete;
            sscanf(linea, "%s|%d|%c", paquete.codigo, &paquete.destino, paquete.tipo);

            ponerEnCola(&lista_colas[paquete.destino - 1], &paquete, sizeof(tPaquete));

        }
    }

    for(i = 0; i < capacidad_maxima; i++){
        if(!colaVacia(lista_colas[i])){
            //sacar de cola y escribir pendientes
            tPaquete paquete_aux;
            sacarDeCola(lista_colas[i], &paquete_aux, sizeof(tPaquete));
            //escribir archivo
            fprintf(archivo_pendientes, "%s|%d|%c\n",
                    paquete_aux.codigo, paquete_aux.destino, paquete_aux.tipo);
        }
    }

}
