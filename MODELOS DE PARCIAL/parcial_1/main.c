#include "funciones.h"

int main()
{

    char* cadena_test = "{[]}[[]]";

    int res = parentesisValido2(cadena_test);

    if(res == 1 ){
        printf("Esta bien parentizado.\n");
    }else {
        printf("Esta mal parentizado.\n");
    }

}
