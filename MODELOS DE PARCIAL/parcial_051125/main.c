#include "tda_pila.h"

int main()
{
    proceso();
}

void proceso(){

    tPila pila;
    crearPila(&pila);

    //flujo de resolucion
    //leer caracter a caracter
    //apilar uno a uno
    //utilizar "verTope" y guardar en una variable
    //apilar el siguiente y comparar el tope con el tope anterior
    //en el momento en el que coincidan, desapilar dos veces (el enunciado solo habla de pares)
    //nunca dejar de apilar, ya que lo que posea la pila al final va a ser lo que se escriba en el nuevo archivo de texto
    //una vez recorrida toda la linea, escribir en el nuevo archivo lo que posee la pila
    //desapilar y comenzar de nuevo con la siguiente linea

    const char* filename = "claves.txt";
    const char* filename2 = "claves2.txt";
    FILE* archivo = fopen(filename, "r");
    if(!archivo){
        printf("Error al intentar leer el archivo.\n");
        return;
    }

    FILE* archivo2 = fopen(filename2, "w");
    if(!archivo2){
        fclose(archivo);
        printf("Error al abrir el archivo para su escritura.\n");
        return;
    }

    char linea[55];
    //lee una linea

    while(fgets(linea, sizeof(linea), archivo)){
        char* p = linea;
        while(*p != '\0'){
            char tope;
            if(verTope(&pila, &tope, sizeof(char)) && tolower(tope) == tolower(*p)){ //verTope es el anterior, *p es el actual
                sacarDePila(&pila, &tope, sizeof(char));
            }else{
                ponerEnPila(&pila, p, sizeof(char));
            }
            p++;
        }
        escribirArchivoDesdePila(&pila, archivo2, sizeof(char));
        vaciarPila(&pila);
    }

    fclose(archivo);
    fclose(archivo2);

}

void escribirArchivoDesdePila(tPila* pila, FILE* file, unsigned tam){
    tPila pilaAux;
    crearPila(&pilaAux);

    while(*pila){
        void* aux = malloc(tam);
        sacarDePila(pila, aux, tam);
        ponerEnPila(&pilaAux, aux, tam);
        free(aux);
    }

    while(pilaAux){
        void* aux = malloc(tam);
        sacarDePila(&pilaAux, aux, tam);

        fprintf(file, "%c", *(char*)aux);
        free(aux);
    }

}
