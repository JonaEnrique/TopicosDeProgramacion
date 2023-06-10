#include <stdio.h>
#include <stdlib.h>

float euler(const int x);

int main()
{
    printf("Euler: %f", euler(1));

    return 0;
}

float euler(const int x)
{
    float   termino = 1, // Se van guardando los terminos, inicia en 1 por la formula (numerador/denominador)
            numerador = (float)x, // Se van guardando los numeradores
            denominador = 1, // Se van guardando los denominadores
            resultado = 1, // Se va acumulando los terminos
            n = 1,
            TOL = 0.000001;

    while(termino > TOL)
    {
        termino = numerador/denominador;

        resultado += termino;

        numerador *= x;
        n++;
        denominador *= n;
    }

    return resultado;
}
