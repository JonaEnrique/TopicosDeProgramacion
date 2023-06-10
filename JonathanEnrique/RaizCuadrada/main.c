#include <stdio.h>
#include <stdlib.h>

double raizCuadrada(const int n);

int main()
{
    printf("Raiz cuadrada: %f", raizCuadrada(10));
    return 0;
}

double raizCuadrada(const int n)
{
    double  rAnterior = 1,
            rActual = ((rAnterior + ((double)n / rAnterior)))/2,
            cota = 0.001,
            dif;

    while ((dif = rActual - rAnterior) >= cota)
    {
        rAnterior = rActual;
        rActual = ((rAnterior + ((double)n / rAnterior)))/2;
    }

    return rActual;
}
