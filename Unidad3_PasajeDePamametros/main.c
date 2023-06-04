#include <stdio.h>
#include <stdlib.h>

#define TAM_VEC 10

typedef struct
{
    int dni;
    char apellido[20];
    char nombres[30];
    float peso;
}Persona;

int compararEntero(const void* arg1, const void* arg2);
int compararPersona(const void* arg1, const void* arg2);
void mostrarVecEntero(int* vec, int ce);

int main()
{
    int vec[TAM_VEC] = {2, 1, 3, 5, 6, 8, 9, 10, 7, 4};

    qsort(vec, TAM_VEC, sizeof(vec[0]), compararEntero);

    mostrarVecEntero(vec, TAM_VEC);

    return 0;
}

int compararEntero(const void* arg1, const void* arg2)
{
    return -1 * (*(int*)arg1 - *(int*)arg2);
}

void mostrarVecEntero(int* vec, int ce)
{
    int* finVec = vec + ce;

    for(int* i = vec; i < finVec; i++){
        printf("%d ", *i);
    }

    printf("\n");
}

int compararPersona(const void* arg1, const void* arg2)
{
    return ((Persona*)arg1)->dni - ((Persona*)arg2)->dni;
}
