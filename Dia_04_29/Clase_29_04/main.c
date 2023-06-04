#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TAM_VEC 100

void ordenarVectorBurbujeo(int* v, int ce);
void ordenarVectorSeleccion(int* v, int ce);
void ordenarVectorInsercion(int* v, int ce);
int buscarMenorEnVector(int* v,int ini,int fin);
void mostrarVector(int* v, int ce);
void intercambiar(int* x, int* y);
void cargarVectorRandom(int* vector, int ce, int semilla);

int main()
{
    int vector[TAM_VEC] = {6, 5, 9, 2, 8, 3, 4, 7, 10, 1};
    int ce = TAM_VEC; // ojo no siempre es TAM_VEC
    int segIni, segFin;
    int semilla = time(NULL);

    cargarVectorRandom(vector, ce, semilla);
    segIni = time(NULL);
    ordenarVectorBurbujeo(vector, ce);
    segFin = time(NULL);
    printf("Tiempo de ejecucion burbujeo: %d\n", segFin - segIni);

    cargarVectorRandom(vector, ce, semilla);
    segIni = time(NULL);
    ordenarVectorSeleccion(vector, ce);
    segFin = time(NULL);
    printf("Tiempo de ejecucion burbujeo: %d\n", segFin - segIni);

    cargarVectorRandom(vector, ce, semilla);
    segIni = time(NULL);
    ordenarVectorInsercion(vector, ce);
    segFin = time(NULL);
    printf("Tiempo de ejecucion burbujeo: %d\n", segFin - segIni);

    mostrarVector(vector, TAM_VEC);

    return 0;
}

void ordenarVectorBurbujeo(int* v, int ce)
{
    bool huboIntercambio = true;

    for(int i = 0; i < ce && huboIntercambio; i++)
    {

        huboIntercambio = false;

        for(int j = 0; j < ce - i; j++)
        {
        if(v[j] > v[j + 1]) // if(*j > *(j+1))
            {
            intercambiar(&v[j], &v[j + 1]);
            huboIntercambio = true;
            }

        }
    }
}

void ordenarVectorSeleccion(int* v, int ce)
{
    int ult = ce - 1, m;
    for(int i = 0; i < ult; i++)
    {
        m = buscarMenorEnVector(v, i, ult);

        if(i != m)
            intercambiar(&v[i], &v[m]);

    }
}

void ordenarVectorInsercion(int* v, int ce)
{
    int aInsertar;
    int j;

    for(int i = 1; i < ce; i++)
    {
        aInsertar = v[i];
        for(j = i - 1; j >= 0 && aInsertar < v[j]; j--)
            v[j + 1] = v[j];

        v[j + 1] = aInsertar;
    }
}

void mostrarVector(int* v, int ce)
{
    for(int i = 0; i < ce; i++)
        {
            printf("%d", v[i]);
        }
    printf("\n");
}

void intercambiar(int* x, int* y)
{
    printf("Antes Int.: x: %d, y: %d\n", *x, *y);

    int xTemp = *x; //xTemp = a;
    *x = *y; //a = b;
    *y = xTemp; //b = xTemp;

    printf("Despues Int.: x: %d, y: %d\n", *x, *y);
}

int buscarMenorEnVector(int* v,int ini,int fin) // devolvemos posición en int
{
    int m = ini;

    for(int j = ini + 1; j <= fin; j++)
    {
        if(v[j] < v[m])
            m = j;
    }

    return m;
}

void cargarVectorRandom(int* vector, int ce, int semilla)
{
    srand(semilla);

    for(int i = 0; i < ce; i++)
    {
        vector[i] = rand();
    }
}
