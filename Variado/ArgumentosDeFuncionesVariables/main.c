#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef int (*Suma)(int n, ...);

void mostrarSuma(Suma sum);
int sumarNnumeros(int n, ...);

int main()
{
    mostrarSuma(sumarNnumeros);

    return 0;
}

int sumarNnumeros(int n, ...)
{
    int acum = 0;
    va_list argumentos;

    va_start(argumentos, n);

    for(int i = 0; i < n; i++)
        acum += va_arg(argumentos, int);

    va_end(argumentos);
    return acum;
}

void mostrarSuma(Suma sum)
{
    printf("%d", sum(6, 1, 2, 3, 4, 5, 6));
}
