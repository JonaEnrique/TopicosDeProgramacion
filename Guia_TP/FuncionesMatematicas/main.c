#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h> // para usar bool en Ejercicio 13

#define ES_PERFECTO 1
#define ES_DEFICIENTE 2
#define ES_ABUDANTE 3
#define ERROR 12
#define ES_PRIMO 6
#define NO_ES_PRIMO 5

int factorial(int numero);
long calcular_factorial(long num);
int combinatorio(int num1, int num2);
double potencia (int num, int exp);
double eulerExponencial(int num, float tol);
double raizCuadrada(int num, float tol);
int serieFinobacci(int num);
double mi_modulo (double num);
double seno (double num, double tol);
int numeroPerfecto(int num);
int productoPorSumas(int num1, int num2);
int cociente(int num1, int num2);
int sumaNumerosNaturales(int num);
int sumaNumerosNaturalesPares(int num);
int sumaNumerosNaturalesParesMenores(int num);
int numeroPrimo(int num);

int main()
{
    /// TODAS LAS PRUEBAS CON DEBUG Y WATCHER
    int num = 5;
    int numu = 4;

    int resulFactorial = factorial(3);
    long resulFactorialMejor = calcular_factorial(num);
    int resulCombinatorio = combinatorio(5, -4);
    int resulPotencia = potencia(4, 3);
    double resulExponencial =  eulerExponencial(2, 0.5); // Tolerancia debe ser entre 1 y 0 (excluyendo extremos)
    double resulRaizCuadrada = raizCuadrada(48, 0.5);
    int resulSEriesFinobacci = serieFinobacci(56);
    double resulSeno = seno(5, 0.05);
    int resulNumeroPerfecto = numeroPerfecto(10);
    int resulProductoPorSumas = productoPorSumas(8, 6);
    int resulCociente = cociente(0, 5);
    int resulsumaNumerosNaturales = sumaNumerosNaturales(8);
    int resulsumaNumerosNaturalesPares = sumaNumerosNaturalesPares(6);
    int resulsumaNumerosNaturalesParesMenores = sumaNumerosNaturalesParesMenores(10);
    int resulnumeroPrimo = numeroPrimo(113);

    puts("Para Debug.");


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

/// EJERCICIO 1 MEJORADO
long calcular_factorial(long num)
{
    if(num != 0)
    {
            return calcular_factorial(num - 1) * num;
    }
    return 1;
}

/// EJERCICIO 2
int combinatorio(int m, int n)
{
    int resul;

    if(m >= n)
    {
        if(n >= 0)
        {
            return resul = factorial(m)/(factorial(n)*factorial(m - n));
        }
        puts("segundo valor menor a 0");
        return 0;
    }
    puts("primer valor menor a segundo valor");
    return 0;
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

/// EJERCICIO 3
double eulerExponencial(int num, float tol)
{
    double tol_base = 1;
    double exponencial = 1;

    /*
    if(num == 0)
        return exponencial;
    */ /// este codigo esta de mas pq se contempla en el for

    for(int i = 1; tol_base > tol; i++)
        {
            tol_base = fabs(potencia(num, i) / factorial(i)); /// Se puede hacer funcion fabs propia (es modulo)
            exponencial += tol_base;
        }
    return exponencial;
}

/// EJERCICIO 4
/// COMO APLICAR TOLERANCIA?
double raizCuadrada(int num, float tol)
{
    double resul = 1;
    double resulAnte = 1;
    double tol_base = 1;

    if(num <= 0)
    {
        puts("No calculamos numeros inferiores o iguales a 0");
        return 0;
    }

    for(int i = 1; tol_base > tol; i++)
    {
    resul = ((resul + (num/resul))/2); // es lo mismo usar resul y resulAnte para el calculo.
    if(i>1)
    {
    tol_base = resulAnte - resul;
    }
    resulAnte = resul;
    }
    return resul;

}

/// EJERCICIO 5
int serieFinobacci(int num)
{
    int res = 1, auxiliar = 1, resAnterior = 1;

    for(int i = 0; res != num; i++)
    {
        auxiliar = res;
        res += resAnterior;
        resAnterior = auxiliar;
        if(res > num)
            return 0;
    }
    return 1;
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

/// EJERCICIO 7
int numeroPerfecto(int num)
{
    int numActual = 1, sumatoria = 0;

    for(int i = 0; numActual < num; i++)
    {
        if (num % numActual == 0)
        {
            sumatoria += numActual;
        }
        numActual++;
    }

    if(sumatoria>num)
        return ES_ABUDANTE;
    if(sumatoria==num)
        return ES_PERFECTO;
    return ES_DEFICIENTE;
}

/// EJERCICIO 8
int productoPorSumas(int num1, int num2)
{
    int res = num1;

    if(num1 == 0 && num2 == 0)
    {
       return 0;
    }

    for(int i = 1; i < num2; i++)
    {
        res += num1;
    }

    return res;
}

/// EJERCICIO 9
int cociente(int num1, int num2)
{
    int aux = num1, res = 0;
    if(num2 == 0)
    {
        puts("Divisor no puede ser 0\n");
        return ERROR;
    }
    if(num1 == 0)
    {
        printf("El coeficiente entero es: %d\n", num1);
        printf("El resto es: % d\n", num1);
        return 1;
    }
    while(aux > 0)
    {
        aux = aux - num2;
        res = res + 1;
    }
    if(aux < 0)
    {
        printf("El coeficiente entero es: %d\n", (res - 1));
        printf("El resto es: % d\n", (aux + num2));
        return 1;
    }
    printf("El coeficiente entero es: %d\n", (res));
    printf("El resto es: % d\n", (aux));
    return 1;
}

/// EJERCICIO 10
int sumaNumerosNaturales(int num)
{
    int res = 0, contador = 0;

    for(int i = 0; i < num; i++)
    {
        res = res + contador;
        contador++;
    }

    return res;
}

/// EJERCICIO 11
int sumaNumerosNaturalesPares(int num)
{
    // se suman los primeros numeros naturales pares
    int res = 0, contadorPar = 0, contador =0;

    for(int i = 0; contadorPar < num; i++)
    {
        if(i%2 == 0)
        {
            res = res + contador;
            contadorPar++;
        }
        contador++;

    }

    return res;
}

/// EJERCICIO 12
int sumaNumerosNaturalesParesMenores(int num)
{
    int res = 0, contadorPar = 0, contador =0;

    for(int i = 0; contador < num; i++)
    {
        if(i%2 == 0)
        {
            res = res + contador;
            contadorPar++;
        }
        contador++;

    }

    return res;
}

/// EJERCICIO 13
int numeroPrimo(int num)
{
    int contadorPrimo = 0;

    if (num == 0)
        return ERROR;

    for(int i = 1; i <= num && contadorPrimo < 3; i++)
    {
    if (num%i == 0)
        contadorPrimo++;
    }
    if(contadorPrimo > 2)
        return NO_ES_PRIMO;

    return ES_PRIMO;
}
