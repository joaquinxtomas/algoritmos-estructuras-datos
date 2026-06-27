#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "tda_pila.h"

int parentesisValido(char* linea);
int esCierre(const char caracter);
int esApertura(const char caracter);
int resultadoEsperado(const char caracter, const char esperado);
#endif // FUNCIONES_H_INCLUDED
