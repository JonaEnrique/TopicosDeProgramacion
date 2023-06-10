#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Meotodos de ordenamiento Clase 29/04 */

/*  Burbujeo -> Comparacion por pares e intercamibo
    Seleccion -> Busca el menor y lo coloca al principio */

#define TAM_VEC 10

void intercambiar(int* a, int* b);
void ordenarVectorBurbujeo(int* v, int ce);
void ordenarVectorSeleccion(int* v, int ce);
void mostrarVector(int* v, int ce);

int main()
{
    int vec[TAM_VEC] = {2, 3, 6, 8, 1, 9, 5, 4, 7, 10};
    int ce = 10;

    ordenarVectorBurbujeo(vec, ce);
    mostrarVector(vec, ce);

    return 0;
}

void ordenarVectorBurbujeo(int* v, int ce)
{
    bool huboIntercambio = true;

    for(int i = 1; i < ce && huboIntercambio; i++)
    {
        huboIntercambio = false;

        for(int j = 0; j < ce - i; j++)
        {
            if(v[j] > v[j + 1])
            {
                intercambiar(&v[j], &v[j + 1]);

                huboIntercambio = true;
            }
        }
    }
}

void ordenarVectorSeleccion(int* v, int ce)
{
    int ult = ce - 1, m; // Hacemos esta varible para que me haga la resta solo una vez

    for(int i = 0; i < ult; i++) // En este caso si tengo que usar i en 0 para poder manipular el vector
    {
        m = buscarMenorEnVector(v, i, ult);
    }
}

void intercambiar(int* a, int* b)
{
    int aTemp = *a;
    *a = *b;
    *b = aTemp;
}

void mostrarVector(int* v, int ce)
{
    for(int i = 0; i < ce; i++)
        printf("%d ", v[i]);
}

// Hola hola hola hola
