#include "funciones.h"

int parentesisValido(char* linea){
    char* aux = linea;
    char caracter_aux;


    tPila pila;
    crearPila(&pila);

    while(*aux){
        if(esApertura(*aux)){
            ponerEnPila(&pila, aux, sizeof(char));
        }
        else if(esCierre(*aux)){
            char buffer[3];
            buffer[0] = '\0';

            verTope(&pila, &caracter_aux, sizeof(char));

            char strTope[2] = {caracter_aux,'\0'};
            char strActual[2] = {*aux, '\0'};

            strcat(buffer, strTope);
            strcat(buffer, strActual);

            if(strcmp(buffer, "{}") == 0 || strcmp(buffer, "[]") == 0 || strcmp(buffer, "()") == 0){
                sacarDePila(&pila, &caracter_aux, sizeof(char));
            } else {
                return 0; //no es valido
            }
        }
        aux++;
    }
    return 1; //salieron del while, están bien parentizados
}

int esCierre(const char caracter){
    char* cierres = ")}]";
    while(*cierres){
        if(*cierres == caracter){
            return 1;
        }
        cierres++;
    }
    return 0;
}

int esApertura(const char caracter){
    char* aperturas = "([{";
    while(*aperturas){
        if(*aperturas == caracter){
            return 1;
        }
        aperturas++;
    }
    return 0;
}

/**VERSION 2**/
int parentesisValido2(const char* linea){
    char* aux = linea;
    char car;

    tPila pila;
    crearPila(&pila);

    while(*aux){
        if(esApertura(*aux)){
            ponerEnPila(&pila, aux, sizeof(char));
        } else if (esCierre(*aux)){
            verTope(&pila, &car, sizeof(char));
            if(resultadoEsperado(car, *aux)){
                sacarDePila(&pila, &car, sizeof(char));
            } else {
                return 0; //no es el esperado entonces esta mal
            }
        }
        aux++;
    }
    return 1;
}

int resultadoEsperado(const char caracter, const char esperado){
    if((caracter == '{' && esperado == '}') ||
       (caracter == '[' && esperado == ']') ||
       (caracter == '(' && esperado == ')')){
        return 1;
    }
    return 0;
}

