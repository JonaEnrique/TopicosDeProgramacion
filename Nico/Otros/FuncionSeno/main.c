#include <stdio.h>
#include <stdlib.h>

int factorial(int numero);
double potencia (int num, int exp);
double mi_modulo (double num);
double seno (double num, double tol);

int main()
{
    printf("Seno: %lf", seno(5.0, 0.001));

    return 0;
}

/// EJERCICIO 1
int factorial(int num)
{
    int resul = 1;

    if (num == 0)
    return 1;

    while(num > 0)
    {
        resul*= num;
        num--;
    }

    return resul;
}

/// EJERCICIO 3
double potencia (int num, int exp)
{
    int resul = 1;
    for(int i=1; i <= exp; i++)
    {
        resul*=num;
    }
    return resul;
}

/// EJERCICIO 6
/// REVISAR PORQUE NO DA RESULTADO CORRECTO

double mi_modulo (double num)
{
    if(num < 0)
        return num*=-1;
    return num;
}

double seno (double num, double tol)
{
    double res = num, resAnte = 0, resActu = 0, tolBase = 1;
    int exponente = 3;

    for(int i = 1; tolBase > tol; i++)
    {
        if(i%2 == 0) // par idad
            res = (res + (potencia(num, exponente)/factorial(exponente)));
        else
        {
            res = (res - (potencia(num, exponente)/factorial(exponente)));
        }

        exponente+=2;
        resActu = mi_modulo(res);

        if(i > 1)
        {
            tolBase = (mi_modulo(resAnte - resActu)); // evito usar variable resulAnterior como paso en Ejercicio 4
        }

        resAnte = mi_modulo(res);
    }

    return res;

}

double sen(double x)
{
    double res = x, numerador = , denominador

    return  res;
}

