#include "funciones.h"

//flujo
//se lee pedido
//colocar todo en la cola
//leer cola
//sacar de cola de a 1, mientras el pedido sea el mismo que ver primero (proximo a salir)
//procesar
//una vez termine de procesar todo ese pedido y verificar que el stock es suficiente, pasar a siguiente
int proceso(const char* filename_pedidos, const char* filename_productos, const char* filename_indice){
    FILE* archivo_pedidos = fopen(filename_pedidos, "r");
    if(!archivo_pedidos){
        printf("Error al abrir el archivo de pedidos");
        return 0; //error al abrir el archivo;
    }

    FILE* archivo_productos = fopen(filename_productos, "r+b");
    if(!archivo_productos){
        fclose(archivo_pedidos);
        return 0;
    }

    FILE* archivo_indice = fopen(filename_indice, "rb");
    if(!archivo_indice){
        fclose(archivo_pedidos);
        fclose(archivo_productos);
        return 0;
    }

    FILE* archivo_pedidos_faltantes = fopen("pedidos_faltantes.txt", "w");
    if(!archivo_pedidos_faltantes){
        fclose(archivo_pedidos);
        fclose(archivo_productos);
        fclose(archivo_indice);
        return 0;
    }

    FILE* archivo_pedidos_realizados = fopen("pedidos_realizados.txt", "w");
    if(!archivo_pedidos_realizados){
        fclose(archivo_pedidos);
        fclose(archivo_productos);
        fclose(archivo_indice);
        fclose(archivo_pedidos_faltantes);
        return 0;
    }

    char linea[50];
    float total = 0.0;
    tPedido pedido;
    tIndice indice;
    tProducto producto;

    tCola cola;
    crearCola(&cola);

    int pedido_actual;
    int pedido_valido = 1;

    tArbol arbol;
    crearArbol(&arbol);
    grabarArbolIndice(&arbol, filename_indice);

    if(fgets(linea, sizeof(linea), archivo_pedidos)){
        trozarCampos(linea, &pedido);
        pedido_actual = pedido.cod_pedido;
    }

    while(!feof(archivo_pedidos)){
        if(pedido.cod_pedido != pedido_actual){
            if(pedido_valido == 1){
                while(desencolar(&cola, &pedido, sizeof(tPedido))){
                    indice.clave = pedido.cod_prod;
                    buscarPorClave(&arbol, &indice, sizeof(tIndice), comparaIndices);
                    fseek(archivo_productos, sizeof(tProducto)* (indice.nro_reg - 1), SEEK_SET);

                    fread(&producto, sizeof(tProducto), 1, archivo_productos);
                    producto.stock -= pedido.cantidad;
                    total += pedido.cantidad * producto.precio;

                    fseek(archivo_productos, -sizeof(tProducto), SEEK_CUR);
                    fwrite(&producto, sizeof(tProducto), 1, archivo_productos);
                }
                fprintf(archivo_pedidos_realizados, "%d|%.2f\n", pedido_actual, total);
            } else{
                vaciarCola(&cola);
            }
            pedido_actual = pedido.cod_pedido;
            pedido_valido = 1;
            total = 0.0;
        }

        indice.clave = pedido.cod_prod;
        buscarPorClave(&arbol, &indice, sizeof(tIndice), comparaIndices);
        fseek(archivo_productos, sizeof(tProducto)*(indice.nro_reg - 1), SEEK_SET);
        fread(&producto, sizeof(tProducto), 1, archivo_productos);

        if(pedido.cantidad <= producto.stock){
            encolar(&cola, &pedido, sizeof(tPedido));
        } else {
            fprintf(archivo_pedidos_faltantes, "%d|%s|%d\n", pedido.cod_pedido, pedido.cod_prod, pedido.cantidad);
            pedido_valido = 0;
        }

        if(fgets(linea, sizeof(linea), archivo_pedidos)){
            trozarCampos(linea, &pedido);
        }
    }

    if (pedido_valido == 1 && !colaVacia(&cola)) {
        while (desencolar(&cola, &pedido, sizeof(tPedido))) {
                indice.clave = pedido.cod_prod;
                buscarPorClave(&arbol, &indice, sizeof(tIndice), comparaIndices);
                fseek(archivo_productos, sizeof(tProducto)* (indice.nro_reg - 1), SEEK_SET);

                fread(&producto, sizeof(tProducto), 1, archivo_productos);
                producto.stock -= pedido.cantidad;
                total += pedido.cantidad * producto.precio;

                fseek(archivo_productos, -sizeof(tProducto), SEEK_CUR);
                fwrite(&producto, sizeof(tProducto), 1, archivo_productos);
        }
        fprintf(archivo_pedidos_realizados, "%d|%.2f\n", pedido_actual, total);
    } else {
        vaciarCola(&cola);
    }

    fclose(archivo_pedidos);
    fclose(archivo_indice);
    fclose(archivo_productos);
    fclose(archivo_pedidos_faltantes);
    fclose(archivo_pedidos_realizados);
    return 1; //todo_ok
}

void leerArchivoBin(const char* filename, unsigned tam, void(*accion)(const void*)){
    FILE* archivo = fopen(filename, "rb");
    if(!archivo){
        return;
    }

    void* dato = malloc(tam);
    fread(dato, tam, 1, archivo);
    while(!feof(archivo)){
        accion(dato);
        fread(dato,tam,1, archivo);
    }

    free(dato);
    fclose(archivo);
}

void leerArchivoTxt(const char* filename){
    FILE* archivo = fopen(filename, "r");
    if(!archivo){
        return;
    }

    char linea[50];
    tPedido pedido;

    while(fgets(linea, sizeof(linea), archivo)){
        trozarCampos(&linea, &pedido);
        printf("%d - %s - %d\n", pedido.cod_pedido, pedido.cod_prod, pedido.cantidad);
    }

    fclose(archivo);
}

/*
void trozarCampos(char* linea, tPedido* pedido){
    unsigned tam_linea = 19, tam_cantidad = 3, tam_cod = 10, tam_cod_pedido = 6;

    char* aux = linea + tam_linea;
    *aux = '\0';

    aux -= tam_cantidad;
    sscanf(aux, "%d", &pedido->cantidad);
    *aux = '\0';

    aux -= tam_cod;
    strncpy(pedido->cod_prod, aux, 10);
    pedido->cod_prod[10] = '\0';
    *aux = '\0';

    aux -= tam_cod_pedido;
    sscanf(aux, "%d", &pedido->cod_pedido);
}*/

void trozarCampos(char* linea, tPedido* pedido){
    char* nueva = strchr(linea,'\n');
    if(nueva){
        *nueva = '\0';
    }

    sscanf(linea, "%d %9s %d", &pedido->cod_pedido, pedido->cod_prod, &pedido->cantidad);
}

void mostrarIndice(const void* dato, unsigned n, const void* params){
    tIndice* indice = (tIndice*)dato;

    printf("%s - %d\n", indice->clave.codigo, indice->nro_reg);
}

void mostrarProducto(const void* dato, unsigned n, const void* params){
    tProducto* producto = (tProducto*)dato;

    printf("%s - %s - %u - %.2f\n", producto->cod, producto->descripcion, producto->stock, producto->precio);
}
