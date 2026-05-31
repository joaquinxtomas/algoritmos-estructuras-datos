#include "producto.h"

void cargarArchivoProductos(const char* filename){
    FILE* archivo = fopen(filename, "wb");
    if(!archivo){
        printf("Error al abrir el archivo para su escritura.\n");
        return;
    }

    Producto productos[15] = {
        {"ALM001", "Harina 000",    "Blancaflor",  {10, 2, 2026}, {15, 8, 2026},  50,  800.00, 1200.00},
        {"ALM002", "Fideos Moño",   "Matarazzo",   {5, 3, 2026}, {20, 12, 2026}, 40,  950.00, 1400.00},
        {"BEB001", "Coca Cola 2L",  "Coca-Cola",   {1, 4, 2026}, {1, 10, 2026}, 24, 1500.00, 2200.00},
        {"BEB002", "Agua Mineral",  "Villavicencio",{12, 4, 2026}, {12, 4, 2027},  60,  600.00,  900.00},
        {"LAC001", "Leche Entera",  "La Serenis.", {8, 4, 2026}, {20, 4, 2026},  30, 1100.00, 1450.00},
        {"LAC002", "Yogurt Frut.",  "Yogs",        {9, 4, 2026}, {25, 4, 2026},  20,  750.00, 1100.00},
        {"LIM001", "Lavandina 1L",  "Ayudin",      {15, 1, 2026}, {15, 1, 2028},  15, 1200.00, 1800.00},
        {"LIM002", "Detergente",    "Magistral",   {20, 2, 2026}, {20, 2, 2028},  25, 1800.00, 2500.00},
        {"GAL001", "Gallet. Oreo",  "Nabisco",     {10, 3, 2026}, {15, 9, 2026},  45,  900.00, 1350.00},
        {"GAL002", "Pepitos",       "Nabisco",     {11, 3, 2026}, {20, 9, 2026},  35,  850.00, 1300.00},
        {"ALM003", "Arroz Largo",   "Lucchetti",   {5, 2, 2026}, {5, 2, 2027},  55, 1000.00, 1500.00},
        {"ALM004", "Aceite Giras.", "Natura",      {14, 4, 2026}, {14, 4, 2027},  12, 2500.00, 3200.00},
        {"BEB003", "Cerveza Lata",  "Quilmes",     {2, 4, 2026}, {2, 12, 2026}, 48,  800.00, 1400.00},
        {"LAC003", "Manteca 200g",  "Sancor",      {10, 4, 2026}, {10, 5, 2026},  18, 1600.00, 2100.00},
        {"LIM003", "Jabón Liquido", "Skip",        {1, 3, 2026}, {1, 3, 2028},  10, 4500.00, 6200.00}
    };

    fwrite(productos, sizeof(Producto), 15, archivo);

    fclose(archivo);
}

void ingresarProducto(Producto* prod){
    printf("Ingrese el codigo del producto: ");
    scanf("%s", prod->codigo_producto);

    printf("Ingrese la descripcion del producto: ");
    scanf("%s", prod->descripcion);

    printf("Ingrese el proveedor del producto: ");
    scanf("%s", prod->proveedor);

    printf("Ingrese la fecha de compra en formato DD/MM/AAAA: ");
    scanf("%d/%d/%d", &prod->fecha_compra.dia, &prod->fecha_compra.mes, &prod->fecha_compra.anio);

    printf("Ingrese la fecha de vencimiento en formato DD/MM/AAAA: ");
    scanf("%d/%d/%d", &prod->fecha_vencimiento.dia, &prod->fecha_vencimiento.mes, &prod->fecha_vencimiento.anio);

    printf("Ingrese la cantidad: ");
    scanf("%d", &prod->cant);

    printf("Ingrese el precio de compra: ");
    scanf("%f", &prod->precio_compra);

    printf("Ingrese el precio de venta: ");
    scanf("%f", &prod->precio_venta);
}

void mostrarProducto(const void* elemento){
    Producto* prod = (Producto*)elemento;
    printf("%7s | %15s | %15s | %2d-%2d-%4d | %2d-%2d-%4d | %3d | %.4f | %.4f\n",
           prod->codigo_producto, prod->descripcion, prod->proveedor, prod->fecha_compra.dia, prod->fecha_compra.mes, prod->fecha_compra.anio,
           prod->fecha_vencimiento.dia, prod->fecha_vencimiento.mes, prod->fecha_vencimiento.anio, prod->cant, prod->precio_compra, prod->precio_venta);
}




