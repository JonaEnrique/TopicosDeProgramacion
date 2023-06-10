#include <stdio.h>
#include <stdlib.h>

/*  Imprime la tabla de Fahrenheit-Celsius
    para fahr = 0, 20, ..., 300*/

int main()
{
    float fahr;

    for(fahr = 300; fahr >= 0; fahr -= 20){
        printf("%3.0f %6.1f\n", fahr, (5.0/9.0) * (fahr-32.0));
    }

    /*float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("Tabla Faherenheit-Celsius\niolpñ");

    fahr = lower;
    while(fahr <= upper){
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr += step;
    } */

    return 0;
}

/*  El punto decimal en una constante indice que está en punto flotante, por lo que 5.0/9.0
    no se trunca debido a que es una relacióm de dos valores de punto flotante*/
