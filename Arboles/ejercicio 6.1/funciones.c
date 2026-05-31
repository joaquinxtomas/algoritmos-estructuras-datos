#include "funciones.h"

/** GUIA DE EJERCICIOS **/
//ejercicio 6.1
//Implementar la función que determina la altura del árbol.
void obtenerAltura(void* info, unsigned tam, unsigned n, void* params){
    int max = *(int*)params; // max es igual a 0
    if(n + 1 > max){ // si el n que llega es mayor a max, significa que se alcanzó un nuevo nivel, se coloca + 1 porque buscamos la altura, que es el nivel + 1
        max = n + 1; //guardamos el maximo hasta el momento
    }
    *(int*)params = max; //modificamos los parametros (que es la altura como variable)
}

int alturaArbolBin(const tArbol* arbol){
    int alturaIzq, alturaDer;
    if(!*arbol){
        return 0;
    }

    alturaIzq = alturaArbolBin(&(*arbol)->izq);
    alturaDer = alturaArbolBin(&(*arbol)->der);

    return (alturaIzq > alturaDer? alturaIzq: alturaDer) + 1;
}

//Implementar la función que muestra los nodos hoja.
void mostrarHojas(tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*)){
    if(!*arbol){
        return;
    }

    if(((*arbol)->izq == NULL) && ((*arbol)->der == NULL)){
        accion((*arbol)->info, (*arbol)->tamInfo, n, params);
    }
    mostrarHojas(&(*arbol)->izq, n + 1, params, accion);
    mostrarHojas(&(*arbol)->der, n + 1, params, accion);
}

//Implementar la función que muestra los nodos no-hoja
void mostrarNoHojas(tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*)){
    if(!*arbol){
        return;
    }

    if((*arbol)->izq != NULL || (*arbol)->der != NULL){
        accion((*arbol)->info, (*arbol)->tamInfo, n, params);
    }
    mostrarNoHojas(&(*arbol)->izq, n + 1, params, accion);
    mostrarNoHojas(&(*arbol)->der, n + 1, params, accion);
}

//Implementar la función que muestra los nodos que solo tienen hijo por izquierda (POR IZQUIERDA SI, POR DERECHA NO)
void mostrarHijosIzq(tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*)){
    if(!*arbol){
        return;
    }

    if((*arbol)->izq != NULL && (*arbol)->der == NULL){
        accion((*arbol)->info, (*arbol)->tamInfo, n, params);
    }
    mostrarHijosIzq(&(*arbol)->izq, n + 1, params, accion);
    mostrarHijosIzq(&(*arbol)->der, n + 1, params, accion);
}

//Implementar la funcion que muestra los nodos que tienen hijo por izquierda (PUEDEN TENER O NO POR DERECHA)
void mostrarHijosIzqOpc(tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*)){
    if(!*arbol){
        return;
    }

    if((*arbol)->izq != NULL){
        accion((*arbol)->info, (*arbol)->tamInfo, n, params);
    }
    mostrarHijosIzqOpc(&(*arbol)->izq, n + 1, params, accion);
    mostrarHijosIzqOpc(&(*arbol)->der, n + 1, params, accion);
}

//Implementar la función que "pode" las ramas de un arbol de modo que no supere una altura determinada
void podarArbolAltura(tArbol* arbol, unsigned n, void* params, void(*accion)(void*, unsigned, unsigned, void*)){ //params va a poseer la altura hasta la que deseamos podar
    if(!*arbol){
        return;
    }

    if(n <= *(int*)params){
        podarArbolAltura(&(*arbol)->izq, n + 1, params, accion);
        accion((*arbol)->info, (*arbol)->tamInfo, n, params);
        podarArbolAltura(&(*arbol)->der, n + 1,params, accion);
    } else {
        eliminarArbol(arbol);
    }
}

//Implementar la funcion que "pode" las ramas de un arbol de una altura determinada o inferior
void podarArbolAlturaInferior(tArbol* arbol, void* params){
    if(!*arbol){
        return;
    }

    int alturaIzq, alturaDer;
    alturaIzq = alturaArbolBin(&(*arbol)->izq);
    alturaDer = alturaArbolBin(&(*arbol)->der);

    if((alturaIzq <= *(int*)params) ){
        eliminarArbol(&(*arbol)->izq);
    }else{
        podarArbolAlturaInferior(&(*arbol)->izq, params);
    }

    if((alturaDer <= *(int*)params)){
        eliminarArbol(&(*arbol)->der);
    }else{
        podarArbolAlturaInferior(&(*arbol)->der, params);
    }

}

//función que genera archivo con la información del arbol
void generarArchivoArbol(void* info, unsigned tam, unsigned n, void* params){
    FILE* archivo = (FILE*)params;
    void* dato = malloc(tam);
    memcpy(dato, info, tam);

    fwrite(dato, tam, 1, archivo);
}

/** funciones que no son basicas de arbol **/
//compararDNI
int compararLegajo(const void* dato1, const void* dato2){
    return strcmp(((tEmpleado*)dato1)->legajo,((tEmpleado*)dato2)->legajo);
}

void mostrarEmpleado(void* info, unsigned tam, unsigned nivel, void* params){
    tEmpleado* empleado = (tEmpleado*)info;
    printf("Nivel %d: [%s] %s %s (%d/%d/%d) (%d/%d/%d)\n",nivel, empleado->legajo, empleado->apellidoNombre, empleado->cargo,
           empleado->fechaAlta.dia, empleado->fechaAlta.mes, empleado->fechaAlta.anio,
           empleado->fechaBaja.dia, empleado->fechaBaja.mes, empleado->fechaBaja.anio);
}

void mostrarArchivo(char* filename, unsigned tam, void(*accion)(void*, unsigned, unsigned, void*)){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        printf("Error al abrir el archivo");
        return;
    }

    void* dato = malloc(tam);

    fread(dato, tam, 1, archivo);
    while(!feof(archivo)){
        accion(dato, tam, 0, NULL);
        fread(dato,tam,1,archivo);
    }

    fclose(archivo);
}
