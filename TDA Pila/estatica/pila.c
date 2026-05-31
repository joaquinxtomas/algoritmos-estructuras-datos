#include "pila.h"

void crearPila(PilaEst* pila){
    pila->tope = TAM;
}

int insertarElemento(PilaEst* pila, void* elemento, size_t tamElemento){
    if(pila->tope < tamElemento + sizeof(size_t)){
        return PILA_LLENA; //definir si es un 1 o un 0
    }

    //reducir tope
    pila->tope -= tamElemento;

    //el destino es el ultimo elemento (el que esta en el tope)
    //se copia el elemento
    //la cantidad de bytes es la que viene por parametro
    memcpy(pila->vec + pila->tope, elemento, tamElemento);

    //ahora se resta el tamaño del elemento que designa esa posicion
    pila->tope -= sizeof(size_t);

    //ahora copiar el valor que nos dice cuantos bytes ocupa el elemento
    memcpy(pila->vec + pila->tope, &tamElemento, sizeof(size_t));

    return TODO_OK;
}

int eliminarElemento(PilaEst* pila, void* elemento, size_t tamElemento){
    size_t tamDatoPila;

    if(pila->tope == TAM){
        return PILA_VACIA;
    }

    memcpy(&tamDatoPila, pila->vec + pila->tope, sizeof(size_t));
    pila->tope += sizeof(size_t);

    memcpy(elemento, pila->vec + pila->tope, MINIMO(tamElemento, tamDatoPila));
    pila->tope += tamDatoPila;

    return TODO_OK;
}

int verElementoTope(PilaEst* pila, void* elemento, size_t tamElemento){
    size_t tamDatoPila;

    if(pila->tope == TAM){
        return PILA_VACIA;
    }

    memcpy(&tamDatoPila, pila->vec + pila->tope, sizeof(size_t));
    memcpy(elemento, pila->vec + pila->tope + sizeof(size_t), MINIMO(tamElemento, tamDatoPila));
    return TODO_OK;
}

int estaLlena(PilaEst* pila, size_t tamElemento){
    if(pila->tope < tamElemento + sizeof(size_t)){
        return PILA_LLENA;
    }
    return TODO_OK;
}

int estaVacia(PilaEst* pila, size_t tamElemento){
    if(pila->tope == TAM){
        return PILA_VACIA;
    }
    return TODO_OK;
}

void vaciarPila(PilaEst* pila){
    pila->tope = TAM;
}

void verPila(PilaEst* pila, void(*mostrar)(const void*)){
    size_t cursor = pila->tope;
    size_t tamElemento;

    printf("\n TOPE DE PILA \n\n");
    while(cursor < TAM){
        memcpy(&tamElemento, pila->vec + cursor, sizeof(size_t));
        cursor += sizeof(size_t);

        mostrar((const void*)(pila->vec + cursor));

        cursor += tamElemento;
    }

    printf("\n BASE DE PILA \n");
}

void cargarArchivoPila(const char* filename, PilaEst* pila){
    FILE* archivo = fopen(filename, "wb");
    if(!archivo){
        printf("Error al abrir el archivo para su escritura.");
        return;
    }

    size_t tamElemento;
    size_t cursor = pila->tope;

    while(cursor < TAM){
        memcpy(&tamElemento, pila->vec + cursor, sizeof(size_t));
        cursor += sizeof(size_t);

        fwrite(pila->vec + cursor, tamElemento, 1, archivo);
        cursor += tamElemento;
    }

    fclose(archivo);
}

void ordenarPila(PilaEst* pila, size_t tamElemento){
    //se crea una pila auxiliar
    PilaEst pila_auxiliar;
    crearPila(&pila_auxiliar);

    void* elementoAuxiliar;

    /*
    logica planteada:
    1. la pila original esta vacia, retorna, no se puede ordenar.
    2. verificacion si la pila auxiliar esta vacia o si el elemento es menor (o mayor) al de la variable auxiliar
    3. eliminar el elemento de la pila de entrada y colocarlo en la variable auxiliar
    4. si la pila auxiliar esta vacia, el auxiliar va al tope.
    5. sacar siguiente elemento de la pila original a la variable auxiliar y comparar nuevamente
    6. cuando se de que la comparacion es falsa, se debe sacar el elemento de la pila temporal y devolver a la pila de entrada,
       para seguir comparando o realizar el intercambio con la variable auxiliar correspondiente.
    7. Así hasta que la pila de entrada esté vacía.
    */

}
