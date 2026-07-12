#include "funciones.h"

void generarLote(const char* filename){
    FILE* archivo = fopen(filename, "wb");
    if(!archivo){
        printf("ERROR ARCHIVO.\n");
        return;
    }

    tProducto productos[7]= {
        {"prod1", "descripcion1", 123, {25,7,2026}, 50},
        {"prod2", "descripcion2", 126, {21,7,2026}, 10},
        {"prod3", "descripcion3", 132, {19,6,2026}, 22},
        {"prod4", "descripcion4", 154, {18,7,2026}, 21},
        {"prod5", "descripcion5", 156, {16,2,2026}, 37},
        {"prod6", "descripcion6", 176, {17,9,2026}, 42},
        {"prod7", "descripcion7", 125, {26,7,2026}, 20}
    };

    fwrite(productos, sizeof(tProducto), 7, archivo);

    fclose(archivo);
}

void mostrarArchivoBin(const char* filename, unsigned tam, void(*accion)(const void*)){
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

    fclose(archivo);
}

void mostrarProducto(const void* dato){
    tProducto* prod = (tProducto*)dato;

    printf("%s|%s|%u|%d/%d/%d|%u\n", prod->codProd, prod->descripcion, prod->lote, prod->fVto.dia, prod->fVto.mes, prod->fVto.dia, prod->cant);
}

int comparaFechasYCant(const void* dato1, const void* dato2){
    tProducto* prod1 = (tProducto*)dato1;
    tProducto* prod2 = (tProducto*)dato2;

    if((prod1->fVto.anio - prod2->fVto.anio) != 0) {
        return prod2->fVto.anio - prod1->fVto.anio;
    }

    if((prod1->fVto.mes - prod2->fVto.mes) != 0) {
        return prod2->fVto.mes - prod1->fVto.mes;
    }

    if((prod1->fVto.dia - prod2->fVto.dia) != 0) {
        return prod2->fVto.dia - prod1->fVto.dia;
    }

    return prod1->cant > prod2->cant ? 1 : prod2->cant > prod1->cant ? -1 : 0;
}

int fechaEsAnterior(t_fecha f1, t_fecha f2){
    if(f1.anio != f2.anio) return f1.anio < f2.anio;
    if(f1.mes  != f2.mes)  return f1.mes  < f2.mes;
    return f1.dia < f2.dia;
}
