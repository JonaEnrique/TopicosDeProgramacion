#include <stdio.h>
#include <stdlib.h>

/* Notacion y aritmetica de punteros clase 06/05*/

// * -> desreferencia en más eficiente porque no hace la cuenta para obetener la direccion del elemento
// como en el caso del corchete

void ordenarSeleccion(int* vec, int ce);
int* buscarMenor(int* ini, int* fin);
void intercambiar(int* a, int* b);

int main()
{
    int vec[10] = {1, 2, 3, 4, 5, 6};
    int ce = 6;
    int* fin = vec + ce -1; // Así no lo hace todo el tiempo en el for, lo declaro antes

    for(int* i = vec; i <= fin; i++)
        printf("%d", *i); // No hacer *(vec + i)

    return 0;
}

void ordenarSeleccion(int* vec, int ce)
{
    int* n, *ult = vec + ce - 1;

    for(int i = 0; i < ult; i++) {
        n = buscarMenor(i, ult);

        if(n != i)
            intercambiar(i, n);
    }
}

int* buscarMenor(int* ini, int* fin)
{
    int* menor = ini;

    for(int* i = ini + 1; i <= fin; i++)
        if(*i < *menor)
            menor = i;

    return menor;
}

void intercambiar(int* a, int* b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}