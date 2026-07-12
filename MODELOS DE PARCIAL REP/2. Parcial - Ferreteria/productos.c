#include "productos.h"

void verArchivoBin(const char* filename, unsigned tam, void(*accion)(const void*)){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        printf("ERROR ARCHIVO.\n");
        return;
    }

    void* dato = malloc(tam);
    fread(dato, tam, 1, archivo);
    while(!feof(archivo)){
        accion(dato);
        fread(dato, tam, 1, archivo);
    }
    free(dato);

    fclose(archivo);
}

void cargarIndiceArbol(const char* filename, tArbol* arbol){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        printf("ERROR ARCHIVO.\n");
        return;
    }

    tIndice indice;
    fread(&indice, sizeof(tIndice), 1, archivo);
    while(!feof(archivo)){
        insertarEnArbol(arbol, &indice, sizeof(tIndice), comparaIndice);
        fread(&indice, sizeof(tIndice),1, archivo);
    }

    fclose(archivo);
}

void mostrarPedidos(const char* filename){
    FILE* archivo = fopen(filename, "r");
    if(!archivo){
        printf("ERROR ARCHIVO.\n");
        return;
    }

    char linea[50];
    tPedido pedido;
    while(fgets(linea, sizeof(linea), archivo)){
        leerPedido(linea, &pedido);
        printf("%6u|%10s|%3u\n", pedido.cod_ped, pedido.cod_prod, pedido.cantidad);
    }

    fclose(archivo);
}

int leerPedido(char* linea, tPedido* pedido){
    sscanf(linea,"%6u%10s%3u", &pedido->cod_ped, pedido->cod_prod, &pedido->cantidad);
}

int comparaIndice(const void* dato1, const void* dato2){
    tIndice* indice1 = (tIndice*)dato1;
    tIndice* indice2 = (tIndice*)dato2;

    return strcmp(indice1->cod, indice2->cod);
}

void mostrarProducto(const void* dato){
    tProducto* producto = (tProducto*)dato;

    printf("%11s|%21s|%5u|%10.2f\n", producto->cod, producto->descripcion, producto->stock, producto->precio);
}

void mostrarIndice(const void* dato){
    tIndice* indice = (tIndice*)dato;
    printf("%11s|%u\n", indice->cod, indice->nroReg);
}

void mostrarIndiceArbol(void* dato, unsigned n, void* params){
    tIndice* indice = (tIndice*)dato;
    printf("%11s|%u\n", indice->cod, indice->nroReg);
}
