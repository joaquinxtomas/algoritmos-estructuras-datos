#include "productos.h"

void agruparProductos(const void* dato1, const void* dato2){
    tProducto* producto1 = (tProducto*)dato1;
    tProducto* producto2 = (tProducto*)dato2;

    producto1->stock += producto2->stock;

    if(comparaFechas(producto1->fecha_ultima_actualizacion, producto2->fecha_ultima_actualizacion) < 0){
        producto1->fecha_ultima_actualizacion = producto2->fecha_ultima_actualizacion;

        producto1->precio = producto2->precio;
        strcpy(producto1->descripcion, producto2->descripcion);
    }
}

int comparaFechas(tFecha fecha1, tFecha fecha2){
    if(fecha1.anio != fecha2.anio) return (fecha1.anio > fecha2.anio) ? 1  : -1;
    if(fecha1.mes != fecha2.mes) return (fecha1.mes > fecha2.mes) ? 1  : -1;
    if(fecha1.dia != fecha2.dia) return (fecha1.dia > fecha2.dia) ? 1  : -1;

    return 0;
}

int comparaCodigos(const void* dato1, const void* dato2){
    tProducto* prod1 = (tProducto*)dato1;
    tProducto* prod2 = (tProducto*)dato2;

    return strcmp(prod1->cod_producto, prod2->cod_producto);
}

void ingresosBrutosPotenciales(const void* info, void* res){
    float* resultado = (float*) res;
    tProducto* producto = (tProducto*)info;
    float total = producto->stock * producto->precio;
    *resultado += total;
}

void superaImporte(const void* info, void* res){
    tContexto* contexto = (tContexto*)res;
    tProducto* producto = (tProducto*)info;

    if(producto->precio > contexto->precio_tope){
        insertarAlInicio(&contexto->resultado, producto, sizeof(tProducto));
    }
}

void mostrarProducto(const void* dato1){
    tProducto* prod = (tProducto*)dato1;

    printf("%8s - %30s - %5d - %8.2f - %d/%d/%d\n", prod->cod_producto, prod->descripcion, prod->stock, prod->precio,
           prod->fecha_ultima_actualizacion.dia, prod->fecha_ultima_actualizacion.mes, prod->fecha_ultima_actualizacion.anio);
}

void crearLote(const char* filename){
    FILE* archivo = fopen(filename, "w");
    if(!archivo ) return;

    tProducto productos[] = {
        {"PRD001", "Arroz largo fino",          50, 1250.00, {15, 3, 2026}},
        {"PRD008", "Aceite girasol",            30, 2100.50, {10, 1, 2026}},
        {"PRD003", "Fideos spaghetti",          80, 890.00,  {22, 5, 2026}},
        {"PRD012", "Leche entera",              45, 1100.75, {1,  7, 2026}},
        {"PRD001", "Arroz largo fino",          25, 1300.00, {20, 4, 2026}},
        {"PRD005", "Harina 000",               100, 750.00,  {5,  2, 2026}},
        {"PRD019", "Sal fina",                  60, 450.00,  {18, 6, 2026}},
        {"PRD003", "Fideos spaghetti",          35, 920.00,  {11, 6, 2026}},
        {"PRD010", "Azucar",                    70, 980.50,  {3,  4, 2026}},
        {"PRD015", "Galletitas crackers",       40, 1650.00, {27, 3, 2026}},
        {"PRD008", "Aceite girasol",            20, 2200.00, {14, 5, 2026}},
        {"PRD021", "Yerba mate 1kg",            55, 3200.00, {9,  7, 2026}},
        {"PRD005", "Harina 000",               40,  780.00, {19, 4, 2026}},
        {"PRD017", "Mermelada durazno",         15, 1800.25, {6,  1, 2026}},
        {"PRD012", "Leche entera",              60, 1150.00, {25, 6, 2026}},
        {"PRD002", "Cafe molido",               25, 4500.00, {12, 5, 2026}},
        {"PRD019", "Sal fina",                  30, 480.00,  {2,  7, 2026}},
        {"PRD006", "Atun en lata",              90, 1400.00, {8,  3, 2026}},
        {"PRD010", "Azucar",                    45, 1020.00, {21, 6, 2026}},
        {"PRD001", "Arroz largo fino",          10, 1350.00, {7,  7, 2026}},
        {"PRD023", "Dulce de leche",            35, 2800.00, {16, 2, 2026}},
        {"PRD008", "Aceite girasol",            15, 2150.00, {30, 6, 2026}},
    };

    int cantProd = sizeof(productos) / sizeof(tProducto);

    for(int i = 0; i < cantProd; i++){
        fprintf(archivo, "%s;%s;%d;%f;%d/%d/%d\n", productos[i].cod_producto, productos[i].descripcion, productos[i].stock, productos[i].precio,
                productos[i].fecha_ultima_actualizacion.dia, productos[i].fecha_ultima_actualizacion.mes, productos[i].fecha_ultima_actualizacion.anio);
    }

    fclose(archivo);
}
