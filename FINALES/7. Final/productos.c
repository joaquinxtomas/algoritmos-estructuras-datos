#include "productos.h"

void generarLote(const char* filename){
    FILE* archivo = fopen(filename, "wb");
    if(!archivo){
        return;
    }

    tProducto productos[10] = {
            {"P003", 'A', 50},
            {"P001", 'B', 120},
            {"P006", 'C', 30},
            {"P004", 'A', 85},
            {"P002", 'B', 40},
            {"P009", 'A', 200},
            {"P010", 'C', 15},
            {"P011", 'B', 60},
            {"P015", 'A', 110},
            {"P005", 'C', 75}
    };

    fwrite(productos, sizeof(tProducto), 10, archivo);

    fclose(archivo);
}

void cargarIndice(const char* filename, tArbol* arbol){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        return;
    }

    tProducto producto;
    tIndice indice;
    int cont = 1;

    fread(&producto, sizeof(tProducto), 1, archivo);
    while(!feof(archivo)){
        strcpy(indice.clave.cod,producto.cod);
        indice.clave.tipo = producto.tipo;
        indice.nroReg = cont;

        insertarEnArbol(arbol, &indice, sizeof(tIndice), comparaClaves);
        cont++;
        fread(&producto, sizeof(tProducto), 1, archivo);
    }

    fclose(archivo);
}

int comparaClaves(const void* dato1, const void* dato2){
    tIndice* indice1 = (tIndice*)dato1;
    tIndice* indice2 = (tIndice*)dato2;

    if (indice1->clave.tipo - indice2->clave.tipo != 0){
        return indice1->clave.tipo - indice2->clave.tipo;
    }

    return strcmp(indice1->clave.cod, indice2->clave.cod);
}

void mostrarIndice(void* info, unsigned n, unsigned tam, void* params){
    tIndice* indice = (tIndice*)info;
    printf("%s - %c - %d\n", indice->clave.cod, indice->clave.tipo, indice->nroReg);
}
