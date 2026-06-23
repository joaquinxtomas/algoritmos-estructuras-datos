#include "funciones.h"

void generarLote(const char *filename){
    FILE* archivo = fopen(filename, "wb");
    if(!archivo){
        return;
    }

    tRegistro registros[10] = {
        {"AB123CD", 2, "Carlos Rodriguez", 43457272, {2021,5,23}, 40000},
        {"BF124DD", 1, "Enrique Pauper", 46372637, {2021,8,23}, 30000},
        {"GF223FD", 5, "Anastasio Giralt", 48263637, {2024,5,3}, 10000},
        {"AS123HH", 4, "Leonardo Messi", 48273625, {2019,10,2}, 8000},
        {"AG125FG", 3, "Robertino Perez", 3473621, {2022,5,6}, 13000},
        {"AB143JH", 6, "Roland Garros", 58746251, {2022,1,6}, 80000},
        {"AS125CV", 2, "Ronald McDonald", 1234234, {2020,12,4}, 20000},
        {"QW123FG", 1, "Alberto Fer", 47362512, {2020,12,3}, 23000},
        {"XC153AS", 2, "Luis Rodriguez", 47263527, {2021,5,2}, 12000},
        {"AA123HJ", 6, "Juan Delafuente", 84725152, {2022,11,2}, 1000}
    };

    fwrite(registros, sizeof(tRegistro),10, archivo);

    fclose(archivo);
}

void mostrarArchivoBin(const char* filename){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        return;
    }

    tRegistro registro;

    fread(&registro, sizeof(tRegistro), 1, archivo);
    while(!feof(archivo)){
        printf("%10s - %d - %26s - %10d - %d/%d/%d - %.2f\n",
               registro.patente, registro.nroCuota, registro.apellidoNombre,registro.dni,
               registro.vto.anio, registro.vto.mes, registro.vto.dia, registro.importe);

        fread(&registro, sizeof(tRegistro), 1, archivo);
    }
    fclose(archivo);
}

void insertarArbolArchivoBin(tArbol* arbol, const char* filename, int(*cmp)(const void*, const void*)){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        return;
    }

    tRegistro registro;

    fread(&registro, sizeof(tRegistro), 1, archivo);
    while(!feof(archivo)){
        insertarEnArbol(arbol, &registro, sizeof(tRegistro), cmp);
        fread(&registro, sizeof(tRegistro), 1, archivo);
    }

    fclose(archivo);
}

void escribirArchivoTxtArbol(tArbol* arbol, const char* filename, void(*accion)(const void*, unsigned, const void*)){
    FILE* archivo = fopen(filename, "w");
    if(!archivo){
        return;
    }

    float total = 0;

    recorrerEnOrden(arbol,archivo, accion);
    recorrerEnOrden(arbol, &total, sumarTotal);
    fprintf(archivo, "TOTAL:\t\t %.2f", total);

    fclose(archivo);
}

void sumarTotal(const void* info, unsigned tam, const void* params){
    tRegistro* registro = (tRegistro*)info;
    *(float*)params += registro->importe;
}

void escribirDni(const void* info, unsigned tam, const void* params){
    tRegistro* registro = (tRegistro*)info;
    FILE* archivo = (FILE*)params;
    fprintf(archivo, "%d|%f\n", registro->dni, registro->importe);
}

void escribirDniYPatente(const void* info, unsigned tam, const void* params){
    tRegistro* registro = (tRegistro*)info;
    FILE* archivo = (FILE*)params;
    fprintf(archivo, "%d|%s|%f\n", registro->dni, registro->patente, registro->importe);
}

char menu(const char* msj, const char* opc){
    char opta;
    do{
        printf("%s", msj);
        scanf(" %c", &opta);
    }while(!strchr(opc, opta));
    return opta;
}

int comparaDni(const void* dato1, const void* dato2){
    tRegistro* registro1 = (tRegistro*)dato1;
    tRegistro* registro2 = (tRegistro*)dato2;

    return registro1->dni - registro2->dni;
}

int comparaDniYPatente(const void* dato1, const void* dato2){
    tRegistro* registro1 = (tRegistro*)dato1;
    tRegistro* registro2 = (tRegistro*)dato2;

    if((registro1->dni - registro2->dni) != 0){
        return registro1->dni - registro2->dni;
    }

    return strcmp(registro1->patente, registro2->patente);
}
