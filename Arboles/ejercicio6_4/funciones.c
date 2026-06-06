#include "funciones.h"

/*
ARBOL COMPLETO: posee la cantidad de nodos que le corresponde a su altura. Formula -> cantNodos = 2^altura - 1. Si coincide, es completo.*/
int esCompleto(const tArbol* arbol){
    int altura = obtenerAltura(arbol);
    int cantNodos = contarNodos(arbol);

    if((potencia(2, altura) - 1) == cantNodos){
        return 1; //ES COMPLETO
    } else {
        return 0; //NO ES COMPLETO
    }

}

int potencia(int num, int elevar){
    int i, res = 1;
    for(i = 0; i < elevar; i++){
        res *= num;
    }
    return res;
}

/*
ARBOL BALANCEADO: es un arbol casi completo, el ultimo nivel puede o no estar completo, pero hasta el penultimo debe estarlo.
Entonces, se debe verificar solo hatsta altura - 2 que posea el nivel correspondiente.
AL MENOS Debe alcanzar 2^(altura - 1) == cantNodos
*/
int esBalanceado(const tArbol* arbol){
    int altura = obtenerAltura(arbol);
    int cantNodos = contarNodosHastaAltura(arbol, 0, altura - 1);

    if(potencia(2, altura - 1) - 1 == cantNodos){
        return 1; //ES BALANCEADO
    } else {
        return 0; //NO ES BALANCEADO
    }
}


/*
ARBOL AVL: no se verifica que este completo o balanceado, si no que los subarboles no se extiendan mas de 1 nodo hacia un lado.
Se determina por la diferencia de altura entre dos subarboles.
Si el subarbol izquierdo tiene altura 3 y el subarbol derecho tiene altura 1, no es AVL, ya que esta seria una diferencia de 2,
y la misma no puede superar el valor de 1.
*/
int esAVL(const tArbol* arbol){
    if(!*arbol){
        return 1;
    }

    int alturaIzq = obtenerAltura(&(*arbol)->izq);
    int alturaDer = obtenerAltura(&(*arbol)->der);

    int mayor = MAX(alturaIzq, alturaDer);
    int menor = MIN(alturaIzq, alturaDer);

    int izqAVL = esAVL(&(*arbol)->izq);
    int derAVL = esAVL(&(*arbol)->der);

    if((mayor - menor) > 1){
        return 0;
    }

    return izqAVL && derAVL;
}


int obtenerAltura(const tArbol* arbol){
    if(!*arbol){
        return 0;
    }

    int alturaIzq = obtenerAltura(&(*arbol)->izq);
    int alturaDer = obtenerAltura(&(*arbol)->der);

    return MAX(alturaIzq, alturaDer) + 1;
}

int contarNodos(const tArbol* arbol){
    if(!*arbol){
        return 0;
    }

    return contarNodos(&(*arbol)->izq) + contarNodos(&(*arbol)->der) + 1;
}

int contarNodosHastaAltura(const tArbol* arbol, int n, int altura){
    if(!*arbol){
        return 0;
    }

    if(n >= altura){
        return 0;
    }

    int nodosIzq = contarNodosHastaAltura(&(*arbol)->izq, n + 1, altura);
    int nodosDer = contarNodosHastaAltura(&(*arbol)->der, n + 1, altura);

    return 1 + nodosIzq + nodosDer;
}

void cargarArbolDesdeArchivo(const char* filename, tArbol* arbol){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        printf("Error al abrir el archivo para su lectura.");
        return;
    }

    tEmpleado empleado;
    fread(&empleado, sizeof(tEmpleado), 1, archivo);
    while(!feof(archivo)){
        insertarRecArbolBinBusqueda(arbol, &empleado, sizeof(tEmpleado), comparaLegajos);
        fread(&empleado, sizeof(tEmpleado), 1, archivo);
    }

    fclose(archivo);
}

int comparaLegajos(const void* dato1, const void* dato2){
    return strcmp( ((tEmpleado*)dato1)->legajo, ((tEmpleado*)dato2)->legajo);
}

void mostrarEmpleado(const void* dato, unsigned tam, unsigned n, void* params){
    tEmpleado* empleado = (tEmpleado*)dato;
    printf("NIVEL:%d | %s - %s - %s - %d/%d/%d - %d/%d/%d\n", n,
           empleado->legajo, empleado->apellidoNombre, empleado->cargo,
           empleado->fechaAlta.dia, empleado->fechaAlta.mes, empleado->fechaAlta.anio,
           empleado->fechaBaja.dia, empleado->fechaBaja.mes, empleado->fechaBaja.anio);
}

