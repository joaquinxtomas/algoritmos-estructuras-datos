#include "funciones.h"

void cargarArchivo(const char* filename){

    FILE* archivo = fopen(filename, "wb");
    if(!archivo){
        printf("Error al abrir el archivo para su escritura.\n");
        return;
    }

    Producto productos[15] = {
        {"P00001", "Teclado USB",   "Logitech",  {10, 1, 2026}, {15, 1, 2026}, 54, 12.50,  25.00},
        {"P00002", "Mouse Inalamb", "Logitech",  {12, 1, 2026}, {20, 1, 2026}, 20,  8.00,  15.50},
        {"P00003", "Monitor 24",    "Samsung",   {15, 1, 2026}, { 2, 2, 2026},10, 120.00, 180.00},
        {"P00004", "Auriculares",   "Sony",      {20, 1, 2026}, { 5, 2, 2026},35,  35.00,  60.00},
        {"P00005", "Cable HDMI 2m", "Genius",    {22, 1, 2026}, {10, 2, 2026},5,   4.50,   9.99},
        {"P00006", "Pendrive 64GB", "Kingston",  { 1, 2, 2026}, {12, 2, 2026},54,   7.20,  14.00},
        {"P00007", "Disco SSD 1TB", "Western Dig", { 5, 2, 2026}, {18, 2, 2026},76,  55.00,  85.00},
        {"P00008", "Gabinete ATX",  "Corsair",   {10, 2, 2026}, {22, 2, 2026},88,  45.00,  75.00},
        {"P00009", "Fuente 600W",   "Corsair",   {10, 2, 2026}, {25, 2, 2026},12,  60.00,  95.00},
        {"P00010", "Memoria RAM 8G", "Kingston", {15, 2, 2026}, { 1, 3, 2026},1,  22.00,  40.00},
        {"P00011", "Motherboard",   "Gigabyte",  {20, 2, 2026}, { 5, 3, 2026},90,  85.00, 130.00},
        {"P00012", "Procesador i5", "Intel",     {20, 2, 2026}, {10, 3, 2026},10, 150.00, 210.00},
        {"P00013", "Cooler CPU",    "CoolerMast", {25, 2, 2026}, {15, 3, 2026},32,  18.00,  30.00},
        {"P00014", "Pasta Termica", "Arctic",    { 1, 3, 2026}, {20, 3, 2026},3,   5.50,  12.00},
        {"P00015", "Webcam 1080p",  "Logitech",  { 5, 3, 2026}, {25, 3, 2026},6,  28.00,  50.00}
    };

    fwrite(productos, sizeof(Producto), 15, archivo);

    fclose(archivo);
}

void recorrerArchivo(const char* filename, size_t tam, void(*mostrar)(void*)){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        printf("Error al abrir el archivo para su lectura.");
        return;
    }

    void* elemento = malloc(tam);

    fread(elemento, tam, 1, archivo);
    while(!feof(archivo)){
        mostrar(elemento);

        fread(elemento, tam, 1, archivo);
    }

    fclose(archivo);
}

void mostrarProducto(void* elemento){
    Producto* prod = (Producto*)elemento;

    printf("%7s | %15s | %15s | %d/%d/%d | %d/%d/%d | %d | %.2f | %.2f\n",
           prod->cod_producto, prod->descripcion, prod->proveedor,
           prod->fecha_compra.dia, prod->fecha_compra.mes, prod->fecha_compra.anio,
           prod->fecha_venta.dia, prod->fecha_venta.mes, prod->fecha_venta.anio,
           prod->cantidad, prod->precio_compra, prod->precio_venta);
}

void cargarColaArchivo(Cola* cola, size_t tam, const char* filename){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        printf("Error al abrir el archivo para su lectura.");
        return;
    }

    void* elemento = malloc(tam);

    fread(elemento, tam, 1, archivo);
    while(!feof(archivo)){
        insertarEnCola(cola, elemento, tam);

        fread(elemento, tam, 1, archivo);
    }
    free(elemento);
    fclose(archivo);
}

void cargarArchivoCola(const char* filename, Cola* cola){
    FILE* archivo = fopen(filename, "wb");
    if(!archivo){
        printf("Error al abrir el archivo para su lectura.");
        return;
    }

    Producto prod;

    while(!colaVacia(cola)){
        sacarDeCola(cola, &prod, sizeof(Producto));
        fwrite(&prod, sizeof(Producto), 1, archivo);
    }

    fclose(archivo);
}


void ingresarProducto(Producto* prod){
    printf("Ingrese el codigo del producto: ");
    scanf("%s", prod->cod_producto);

    printf("Ingrese la descripcion del producto: ");
    scanf("%s", prod->descripcion);

    printf("Ingrese el proveedor del producto: ");
    scanf("%s", prod->proveedor);

    printf("Ingrese la fecha de compra en formato DD/MM/AAAA: ");
    scanf("%d/%d/%d", &prod->fecha_compra.dia, &prod->fecha_compra.mes, &prod->fecha_compra.anio);

    printf("Ingrese la fecha de vencimiento en formato DD/MM/AAAA: ");
    scanf("%d/%d/%d", &prod->fecha_venta.dia, &prod->fecha_venta.mes, &prod->fecha_venta.anio);

    printf("Ingrese la cantidad: ");
    scanf("%d", &prod->cantidad);

    printf("Ingrese el precio de compra: ");
    scanf("%f", &prod->precio_compra);

    printf("Ingrese el precio de venta: ");
    scanf("%f", &prod->precio_venta);
}

/** MENU **/

int menu(const char* mensaje, int min, int max){
    int op;
    do{
        printf("%s\n", mensaje);
        fflush(stdin);
        scanf("%d", &op);
    }while(op < min || op > max);
    return op;
}
