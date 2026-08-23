#include "tabla_de_puntos.h"

//FUNCION INICIAL
int procesar_top(const char* filename){
    FILE* archivo = fopen(filename, "r");
    if(!archivo) return 0;

    char linea[200];
    unsigned tam;
    fgets(linea, sizeof(linea), archivo);
    sscanf(linea, "%d", &tam);

    t_tabla_puntos tabla_puntos;
    crear_tabla_puntos(&tabla_puntos, tam);

    t_puntaje puntaje;

    while(fgets(linea, sizeof(linea), archivo)){
        sscanf(linea, "%4s %d", puntaje.iniciales, &puntaje.puntaje);

        agregar_puntaje(&tabla_puntos, &puntaje);
    }

    imprimir_tabla_puntos(&tabla_puntos);

    vaciar_tabla_puntos(&tabla_puntos);

    fclose(archivo);

    return 1;
}

void crear_tabla_puntos(t_tabla_puntos *p, unsigned tam){
    crearLista(&p->tabla);
    p->tam = tam;
}

int agregar_puntaje(t_tabla_puntos *p, const t_puntaje* dato){
    int ce = 0;
    tNodo** aux = &p->tabla;

    if(p->tam <= 0){
        return 0;
    }

    while(*aux && comparaPuntajes((*aux)->info, dato) > 0 && ce < p->tam){
        ce++;
        aux = &(*aux)->sig;
    }

    if(ce == p->tam){
        return 0; //no puede insertarse
    }

    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(!nuevo) return 0;

    nuevo->info = malloc(sizeof(t_puntaje));
    if(!nuevo->info){
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, dato, sizeof(t_puntaje));
    nuevo->tamInfo = sizeof(t_puntaje);

    nuevo->sig = *aux;
    *aux = nuevo;

    ce++;

    while(*aux && ce < p->tam){
        ce++;
        aux = &(*aux)->sig;
    }

    if(*aux){
        tNodo* resto = (*aux)->sig;
        (*aux)->sig = NULL;
        vaciarLista(&resto);
    }

    return 1;
}

void imprimir_tabla_puntos(t_tabla_puntos *p){
    while(p->tabla){
        t_puntaje* puntaje = (t_puntaje*)p->tabla->info;
        printf("%s ... %d\n", puntaje->iniciales, puntaje->puntaje);
        p->tabla = p->tabla->sig;
    }
}

void vaciar_tabla_puntos(t_tabla_puntos *p){
    while(p->tabla){
        tNodo* aux = p->tabla;
        p->tabla = aux->sig;
        free(aux->info);
        free(aux);
    }

    p->tam = 0;
}

int comparaPuntajes(const void* dato1, const void* dato2){
    t_puntaje* puntaje1 = (t_puntaje*)dato1;
    t_puntaje* puntaje2 = (t_puntaje*)dato2;

    return puntaje1->puntaje - puntaje2->puntaje;
}

int agregar_puntaje_podio(t_tabla_puntos *p, const t_puntaje* dato){
    int ce = 0;
    tNodo** aux = &p->tabla;

    if(p->tam <= 0){
        return 0;
    }

    const void* anterior = NULL;
    while(*aux && comparaPuntajes((*aux)->info, dato) > 0 && ce < p->tam){
        if(!anterior || comparaPuntajes((*aux)->info, anterior) != 0){
            ce++;
        }
        anterior = (*aux)->info;
        aux = &(*aux)->sig;
    }

    if(ce == p->tam){
        return 0; //no puede insertarse
    }

    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(!nuevo) return 0;

    nuevo->info = malloc(sizeof(t_puntaje));
    if(!nuevo->info){
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->info, dato, sizeof(t_puntaje));
    nuevo->tamInfo = sizeof(t_puntaje);

    nuevo->sig = *aux;
    *aux = nuevo;

    ce++;

    anterior = (*aux)->info;
    aux = &(*aux)->sig;
    while(*aux && ce < p->tam){
        if(comparaPuntajes((*aux)->info, anterior) != 0){
            ce++;
        }
        anterior = (*aux)->info;
        if(ce < p->tam){
            aux = &(*aux)->sig;
        }

    }

    if(*aux){
        tNodo* resto = (*aux)->sig;
        (*aux)->sig = NULL;
        vaciarLista(&resto);
    }

    return 1;
}


int procesar_podio(const char* filename){
    FILE* archivo = fopen(filename, "r");
    if(!archivo) return 0;

    char linea[200];
    unsigned tam;
    fgets(linea, sizeof(linea), archivo);
    sscanf(linea, "%d", &tam);

    t_tabla_puntos tabla_puntos;
    crear_tabla_puntos(&tabla_puntos, tam);

    t_puntaje puntaje;

    while(fgets(linea, sizeof(linea), archivo)){
        sscanf(linea, "%4s %d", puntaje.iniciales, &puntaje.puntaje);

        agregar_puntaje_podio(&tabla_puntos, &puntaje);
    }

    imprimir_tabla_puntos(&tabla_puntos);

    vaciar_tabla_puntos(&tabla_puntos);

    fclose(archivo);

    return 1;
}

