#include "funciones.h"

//PARA PARTE A
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

    tCola lista_colas[tam_vec_colas];

    for(int i = 0; i < tam_vec_colas; i++){
        crearCola(&lista_colas[i]);
    }

    while(fgets(linea, sizeof(linea), archivo)){
        strncpy(codigo_ing, linea, 3);
        codigo_ing[3] = '\0';

        if(strcmp(codigo_ing, "DES") == 0){
            //SACAR DE COLA Y ESCRIBIR SEGUN CORRESPONDA
            int destino;
            sscanf(linea, "%*[^|]|%*[^|]|%d", &destino);
            int cant_paquetes = 0;
            while(!colaVacia(&lista_colas[destino - 1]) && cant_paquetes < capacidad_maxima){
                tPaquete paquete_aux;
                sacarDeCola(&lista_colas[destino - 1], &paquete_aux, sizeof(tPaquete));
                cant_paquetes++;
            }

            if(cant_paquetes == 0) {
                //imprimir destino OK (vacio no hay mas paquetes para ese destino)
                fprintf(archivo_incompleto, "%s|%d|%s\n",
                    "DES", destino, "VACIO");
            }
            else if(cant_paquetes < capacidad_maxima){
                fprintf(archivo_incompleto, "%s|%d|%s|%d|%d\n",
                    "DES", destino, "INCOMPLETO", capacidad_maxima, cant_paquetes);
            }
        } else if(strcmp(codigo_ing, "ING") == 0){
            //PONER EN COLA Y CONTAR PAQUETES
            //leer linea a estructura
            tPaquete paquete;
            sscanf(linea, "%*[^|]|%10[^|]|%d|%c", paquete.codigo, &paquete.destino, &paquete.tipo);
            int esUrgente = 0;

            ponerEnCola(&lista_colas[paquete.destino - 1], &paquete, sizeof(tPaquete));

        }
    }

    for(int i = 0; i < tam_vec_colas; i++){
        while(!colaVacia(&lista_colas[i])){
            //sacar de cola y escribir pendientes
            tPaquete paquete_aux;
            sacarDeCola(&lista_colas[i], &paquete_aux, sizeof(tPaquete));
            //escribir archivo
            fprintf(archivo_pendientes, "ING|%s|%d|%c\n",
                    paquete_aux.codigo, paquete_aux.destino, paquete_aux.tipo);
        }
    }

    fclose(archivo);
    fclose(archivo_incompleto);
    fclose(archivo_pendientes);

}

//PARA PARTE B
void proceso2(const char* filename){
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

    fgets(linea, sizeof(linea), archivo);
    sscanf(linea, "%d,%d", &capacidad_maxima, &tam_vec_colas);

    tDestino lista_colas[tam_vec_colas];

    for(int i = 0; i < tam_vec_colas; i++){
        crearCola(&lista_colas[i].normales);
        crearCola(&lista_colas[i].urgentes);
        lista_colas[i].contador = 0;
    }

    while(fgets(linea, sizeof(linea), archivo)){
        strncpy(codigo_ing, linea, 3);
        codigo_ing[3] = '\0';

        if(strcmp(codigo_ing, "DES") == 0){
            int destino;
            sscanf(linea, "%*[^|]|%*[^|]|%d", &destino);

            int cargados = 0;
            while(!colaVacia(&lista_colas[destino - 1].urgentes) && cargados < capacidad_maxima){
                tPaquete paquete_aux;
                sacarDeCola(&lista_colas[destino - 1].urgentes, &paquete_aux, sizeof(tPaquete));
                cargados++;
            }

            //while 2
            while(!colaVacia(&lista_colas[destino - 1].normales) && cargados < capacidad_maxima){
                tPaquete paquete_aux;
                sacarDeCola(&lista_colas[destino - 1].normales, &paquete_aux, sizeof(tPaquete));
                cargados++;
            }

            //escritura 2
            if(cargados == 0) {
                //imprimir destino OK (vacio no hay mas paquetes para ese destino)
                fprintf(archivo_incompleto, "%s|%d|%s\n",
                    "DES", destino, "VACIO");
            }
            else if(cargados < capacidad_maxima){
                fprintf(archivo_incompleto, "%s|%d|%s|%d|%d\n",
                    "DES", destino, "INCOMPLETO", capacidad_maxima, lista_colas[destino - 1].contador);
            }

            lista_colas[destino - 1].contador += cargados;

        } else if(strcmp(codigo_ing, "ING") == 0){

            tPaquete paquete;
            sscanf(linea, "%*[^|]|%10[^|]|%d|%c", paquete.codigo, &paquete.destino, &paquete.tipo);

            if(paquete.tipo == 'U'){
                ponerEnCola(&lista_colas[paquete.destino - 1].urgentes, &paquete, sizeof(tPaquete));
            } else if(paquete.tipo == 'N'){
                ponerEnCola(&lista_colas[paquete.destino - 1].normales, &paquete, sizeof(tPaquete));
            }
        }
    }

    for(int i = 0; i < tam_vec_colas; i++){
        while(!colaVacia(&lista_colas[i].urgentes)){
            //sacar de cola y escribir pendientes
            tPaquete paquete_aux;
            sacarDeCola(&lista_colas[i].urgentes, &paquete_aux, sizeof(tPaquete));
            //escribir archivo
            fprintf(archivo_pendientes, "ING|%s|%d|%c\n",
                    paquete_aux.codigo, paquete_aux.destino, paquete_aux.tipo);
        }

        while(!colaVacia(&lista_colas[i].normales)){
            //sacar de cola y escribir pendientes
            tPaquete paquete_aux;
            sacarDeCola(&lista_colas[i].normales, &paquete_aux, sizeof(tPaquete));
            //escribir archivo
            fprintf(archivo_pendientes, "ING|%s|%d|%c\n",
                    paquete_aux.codigo, paquete_aux.destino, paquete_aux.tipo);
        }

        printf("Destino %d: %d\n", i+1, lista_colas[i].contador);
    }

    fclose(archivo);
    fclose(archivo_incompleto);
    fclose(archivo_pendientes);


}
