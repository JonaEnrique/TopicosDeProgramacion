#include <stdio.h>
#include <stdlib.h>

#include "funciones.h"

#define TAM_VEC 10

int main()
{
    int vector[TAM_VEC]={1,3,5,7,9,11,13,15,17};
    int ce = 9;
//    cargarVector(vector,TAM_VEC);
    int elem = 8;
    int ret = insertarEnVectorOrd(vector, &ce, TAM_VEC, elem);
    mostrarVector(vector,ce);
    return ret;
}
