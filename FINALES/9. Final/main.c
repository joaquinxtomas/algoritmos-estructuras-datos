#include "productos.h"
int main()
{
    const char* filename = "pruebas.txt";

    crearLote(filename);

    FILE* archivo = fopen(filename, "r");
    if(!archivo) return 0;

    char linea[200];
    tProducto producto;

    tLista lista_prod;
    crearLista(&lista_prod);

    tNodo* ultimo = NULL;

    while(fgets(linea, sizeof(linea), archivo)){
        sscanf(linea, "%8[^;];%30[^;];%u;%f;%d/%d/%d", producto.cod_producto, producto.descripcion, &producto.stock, &producto.precio,
               &producto.fecha_ultima_actualizacion.dia, &producto.fecha_ultima_actualizacion.mes, &producto.fecha_ultima_actualizacion.anio);

        if(!ultimo){
            insertarUltimo(&lista_prod, &ultimo, &producto, sizeof(tProducto));
            ultimo = lista_prod;
        } else {
            insertarUltimo(&lista_prod,&ultimo, &producto, sizeof(tProducto));
        }
    }

    //primer parte
    eliminarDuplicados(&lista_prod, comparaCodigos, agruparProductos);

    printf("ELIMINAR DUPLICADOS, RESULTADO DE LISTA:\n");
    recorrerLista(&lista_prod, mostrarProducto);
    printf("\n\n");

    float resultado=0;
    reduce(&lista_prod, &resultado, ingresosBrutosPotenciales);
    printf("\nINGRESOS BRUTOS POTENCIALES: %.2f\n\n", resultado);


    tLista lista_superan_monto;
    crearLista(&lista_superan_monto);
    tContexto contexto;

    contexto.resultado = lista_superan_monto;
    printf("Ingrese el importe: ");
    scanf("%f", &contexto.precio_tope);

    reduce(&lista_prod, &contexto, superaImporte);
    printf("LISTA CON PRODUCTOS QUE SUPERAN EL MONTO: \n");
    recorrerLista(&contexto.resultado, mostrarProducto);

    fclose(archivo);
    vaciarLista(&lista_prod);
    vaciarLista(&lista_superan_monto);
}
