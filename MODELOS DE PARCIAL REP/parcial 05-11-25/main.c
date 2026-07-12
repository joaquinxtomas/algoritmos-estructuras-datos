#include "pila.h"
int main()
{
    const char* filename = "claves.txt";
    const char* temp = "temp.txt";

    FILE* archivo = fopen(filename, "r");
    if(!archivo){
        printf("ERROR ARCHIVO.\n");
        return 0;
    }

    FILE* archivo_temp = fopen(temp, "w");
    if(!archivo_temp){
        printf("ERROR ARCHIVO.\n");
        fclose(archivo);
        return 0;
    }

    tPila pila;
    crearPila(&pila);

    char aux, eliminado;

    char linea[55];

    while(fgets(linea, sizeof(linea), archivo)){
        char* actual = linea;

        while(*actual){

            if(!pilaVacia(&pila)){
                verTope(&pila, &aux, sizeof(char));
                if(tolower(*actual) == tolower(aux)){
                    sacarDePila(&pila, &eliminado, sizeof(char));
                }else{
                    insertarEnPila(&pila, actual, sizeof(char));
                }
            } else {
                insertarEnPila(&pila, actual, sizeof(char));
            }
            actual++;

        }

        if(!pilaVacia(&pila)){
            invertirPila(&pila, sizeof(char));
        }

        while(!pilaVacia(&pila)){
            sacarDePila(&pila, &aux, sizeof(char));
            fprintf(archivo_temp, "%c", aux);
        }

        fprintf(archivo_temp, "\n");
    }

    fclose(archivo);
    fclose(archivo_temp);
}
