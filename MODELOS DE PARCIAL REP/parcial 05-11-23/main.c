#include "funciones.h"
#include "lista.h"

int main()
{
    const char* filename = "stock.dat";
    const char* filename_prod = "prod_a_vencer.txt";

    FILE* archivo_stock = fopen(filename, "rb");
    if(!archivo_stock){
        printf("ERROR ARCHIVO.\n");
        return 0;
    }

    FILE* archivo_prod = fopen(filename_prod, "w");
    if(!archivo_prod){
        fclose(archivo_stock);
        printf("ERROR ARCHIVO.\n");
        return 0;
    }

    //generarLote(filename);
    //mostrarArchivoBin(filename, sizeof(tProducto), mostrarProducto);

    tLista lista_top;
    int cont = 1;

    crearLista(&lista_top);

    tProducto prod;

    fseek(archivo_stock, 0, SEEK_END);
    rewind(archivo_stock);

    t_fecha fecha_actual;
    printf("Ingresar fecha actual (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &fecha_actual.dia, &fecha_actual.mes, &fecha_actual.anio);

    int n;
    printf("Ingrese el maximo del top: ");
    scanf("%d", &n);

    fread(&prod, sizeof(tProducto), 1, archivo_stock);
    while(!feof(archivo_stock)){
        if(fechaEsAnterior(fecha_actual, prod.fVto)){
            insertarEnPodio(&lista_top, &prod, sizeof(tProducto), comparaFechasYCant, n);
        }
        fread(&prod, sizeof(tProducto), 1, archivo_stock);
    }

    fclose(archivo_stock);

    while(cont <= n){
        tProducto prod_aux;
        sacarDelInicio(&lista_top, &prod_aux, sizeof(tProducto));
        if(cont == 1){
            printf("PRODUCTO PROXIMO A VENCER: %s - %d/%d/%d.\n", prod_aux.codProd, prod_aux.fVto.dia, prod_aux.fVto.mes, prod_aux.fVto.anio);
        }
        fprintf(archivo_prod, "%6s|%d/%d/%d|%10d - pos: %d\n", prod_aux.codProd, prod_aux.fVto.dia, prod_aux.fVto.mes, prod_aux.fVto.anio, prod_aux.cant, cont);
        cont++;
    }

    fclose(archivo_prod);
}
