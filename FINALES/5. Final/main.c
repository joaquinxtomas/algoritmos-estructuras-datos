#include "pila.h"

int validar_xml(const char* filename){

    tPila pila;
    crearPila(&pila);

    int esApertura = 0;
    int esCierre = 0;

    char etiqueta[30];
    char* p_etiqueta = etiqueta;

    char buffer[30];

    FILE* archivo = fopen(filename, "r");
    if(!archivo) return 0;

    char linea[200];
    while(fgets(linea, sizeof(linea), archivo)){
        char* actual = linea;

        while(*actual){

            if(*actual == '<'){
                esApertura = 1;
            }else if(*actual == '/'){
                esCierre = 1;
                esApertura = 0;
            }else if(*actual == '>'){
                //apilo
                *p_etiqueta = '\0';
                if(esApertura){
                    insertarEnPila(&pila, etiqueta, sizeof(etiqueta));
                } else if(esCierre){
                    verTope(&pila, buffer, sizeof(buffer));

                    if(strcmp(buffer, etiqueta) == 0){
                        sacarDePila(&pila, buffer, sizeof(buffer));
                    }
                }

                p_etiqueta = etiqueta;
                esApertura = 0;
                esCierre = 0;
            } else if (esApertura || esCierre){
                *p_etiqueta = *actual;
                p_etiqueta++;
            }

            actual++;
        }
    }

    if(!esPilaVacia(&pila)){
        vaciarPila(&pila);
        fclose(archivo);
        return 0;
    }

    fclose(archivo);
    return 1;
}

int main()
{
    const char* filename = "archivo.xml";
    if(validar_xml(filename) == 1){
        printf("XML VALIDO");
    }else {
        printf("XML INVALIDO");
    }
    return 1;
}
