#include "productos.h"
#include "cola.h"

int main()
{
    const char* filename_productos = "productos.dat";
    const char* filename_indice = "productos.idx";
    const char* filename_pedidos = "pedidos.txt";

    const char* pedidos_realizados = "pedidos_realizados.txt";
    const char* pedidos_faltantes = "pedidos_faltantes.txt";

    FILE* archivo_productos = fopen(filename_productos, "r+b");
    if(!archivo_productos){
        printf("Error al abrir el archivo de productos.\n");
        return 0;
    }

    FILE* archivo_indice = fopen(filename_indice, "rb");
    if(!archivo_indice){
        fclose(archivo_productos);
        printf("Error al abrir el archivo de indices.\n");
        return 0;
    }

    FILE* archivo_pedidos = fopen(filename_pedidos, "r");
    if(!archivo_pedidos){
        fclose(archivo_productos);
        fclose(archivo_indice);
        printf("Error al abrir el archivo de pedidos.\n");
        return 0;
    }

    FILE* archivo_pedidos_realizados = fopen(pedidos_realizados, "w");
    if(!archivo_pedidos_realizados){
        fclose(archivo_productos);
        fclose(archivo_indice);
        fclose(archivo_pedidos);
        printf("Error al abrir el archivo de pedidos realizados.\n");
        return 0;
    }

    FILE* archivo_pedidos_faltantes = fopen(pedidos_faltantes, "w");
    if(!archivo_pedidos_faltantes){
        fclose(archivo_productos);
        fclose(archivo_indice);
        fclose(archivo_pedidos);
        fclose(archivo_pedidos_realizados);
        printf("Error al abrir el archivo de pedidos realizados.\n");
        return 0;
    }

    int pedido_actual;
    int pedido_valido = 1;
    float total = 0.0;

    tPedido pedido;
    tPedido pedidoCola;
    tIndice indice;
    char linea[50];

    tProducto producto;

    tArbol arbol;
    crearArbol(&arbol);
    cargarIndiceArbol(filename_indice, &arbol);

    tCola cola;
    crearCola(&cola);

    if(fgets(linea, sizeof(linea), archivo_pedidos)){
        leerPedido(linea, &pedido);
        pedido_actual = pedido.cod_ped;
    }

    while(!feof(archivo_pedidos)){
        if(pedido.cod_ped != pedido_actual){
            if(pedido_valido == 1){
                while(!colaVacia(&cola)){
                    sacarDeCola(&cola, &pedidoCola, sizeof(tPedido));
                    strcpy(indice.cod, pedidoCola.cod_prod);
                    buscarPorClave(&arbol, &indice, sizeof(tIndice), comparaIndice);
                    fseek(archivo_productos, sizeof(tProducto)*(indice.nroReg - 1), SEEK_SET);

                    fread(&producto, sizeof(tProducto), 1, archivo_productos);
                    producto.stock -= pedidoCola.cantidad;
                    total += pedidoCola.cantidad * producto.precio;

                    fseek(archivo_productos, -sizeof(tProducto), SEEK_CUR);
                    fwrite(&producto, sizeof(tProducto), 1, archivo_productos);
                }
                fprintf(archivo_pedidos_realizados, "PEDIDO: %u REALIZADO CORRECTAMENTE | TOTAL: %.2f\n", pedido_actual, total);
            } else {
                vaciarCola(&cola);
            }
            pedido_actual = pedido.cod_ped;
            pedido_valido = 1;
            total = 0.0;
        }

        strcpy(indice.cod, pedido.cod_prod);
        buscarPorClave(&arbol, &indice, sizeof(tIndice), comparaIndice);
        fseek(archivo_productos, sizeof(tProducto) * (indice.nroReg - 1), SEEK_SET);
        fread(&producto, sizeof(tProducto), 1 ,archivo_productos);

        if(pedido.cantidad <= producto.stock){
            ponerEnCola(&cola, &pedido, sizeof(tPedido));
        }else{
            fprintf(archivo_pedidos_faltantes, "PRODUCTO: %s | STOCK FALTANTE\n", producto.cod);
            pedido_valido = 0;
        }

        if(fgets(linea, sizeof(linea), archivo_pedidos)){
            leerPedido(linea, &pedido);
        }
    }

    if(pedido_valido == 1 && !colaVacia(&cola)){
            while(!colaVacia(&cola)){
                sacarDeCola(&cola, &pedidoCola, sizeof(tPedido));
                strcpy(indice.cod, pedidoCola.cod_prod);
                buscarPorClave(&arbol, &indice, sizeof(tIndice), comparaIndice);
                fseek(archivo_productos, sizeof(tProducto)*(indice.nroReg - 1), SEEK_SET);

                fread(&producto, sizeof(tProducto), 1, archivo_productos);
                producto.stock -= pedidoCola.cantidad;
                total += pedidoCola.cantidad * producto.precio;

                fseek(archivo_productos, -sizeof(tProducto), SEEK_CUR);
                fwrite(&producto, sizeof(tProducto), 1, archivo_productos);
            }
            fprintf(archivo_pedidos_realizados, "PEDIDO: %u REALIZADO CORRECTAMENTE | TOTAL: %.2f\n", pedido_actual, total);
    } else{
        vaciarCola(&cola);
    }

    fclose(archivo_indice);
    fclose(archivo_pedidos);
    fclose(archivo_productos);
    fclose(archivo_pedidos_faltantes);
    fclose(archivo_pedidos_realizados);
}
