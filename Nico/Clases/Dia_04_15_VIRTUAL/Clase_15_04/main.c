#include <stdio.h>
#include <stdlib.h>

void intercambiar(int* x, int* y);

int main()
{
    int a = 5;
    int b = 8;
    int* p = &a;

    printf("Antes Int.: a: %d, b: %d\n", a, b);

    intercambiar(p, &b);

    printf("Despues Int.: a: %d, b: %d\n", a, b);

    return 0;
}

void intercambiar(int* x, int* y)
{
    printf("Antes Int.: x: %d, y: %d\n", *x, *y);

    int xTemp = *x; //xTemp = a;
    *x = *y; //a = b;
    *y = xTemp; //b = xTemp;

    printf("Despues Int.: x: %d, y: %d\n", *x, *y);

}


