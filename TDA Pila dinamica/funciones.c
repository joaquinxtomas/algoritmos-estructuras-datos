#include "funciones.h"
#include "pila_dinamica.h"

void sumaMuchosDigitos(char* numero1, char* numero2){
    int num1temp, num2temp;

    Pila pilaA;
    Pila pilaB;
    Pila pilaC; //temporal

    crearPila(&pilaA);
    crearPila(&pilaB);
    crearPila(&pilaC);

    while(*numero1){
        //castear el numero
        num1temp = *numero1 - '0'; //resto caracter 0 para obtener numero correcto
        insertarEnPila(&pilaA, &num1temp, sizeof(int));
        //avanzar numero a numero
        numero1++;
    }

    while(*numero2){
        num2temp = *numero2 - '0';
        insertarEnPila(&pilaB, &num2temp, sizeof(int));
        numero2++;
    }

    int num1, num2, carry = 0;

    while(!pilaVacia(&pilaA) || !pilaVacia(&pilaB) || carry > 0){
        num1 = 0;
        num2 = 0;
        //usar sacarDePila para obtener el dato y sumarlo
        sacarDePila(&pilaA, &num1, sizeof(int));

        sacarDePila(&pilaB, &num2, sizeof(int));

        int resultado = num1 + num2 + carry;

        int ultimoDigito = resultado % 10;
        carry = resultado / 10;

        insertarEnPila(&pilaC, &ultimoDigito, sizeof(int));
    }

    mostrarPila(&pilaC, mostrarEntero);

    vaciarPila(&pilaC);
}

void mostrarEntero(void* elemento){
    int num = *(int*)elemento;
    printf("%d", num);
}


