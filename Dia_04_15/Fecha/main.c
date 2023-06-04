//#include "fecha.h"

#include "../FechaLib/fecha.h"

/// OJO RECORDAR POR SI NO ENCUENTRA DEFINE Y FUINCIONES
/// boton derecho sobre proyecto Fecha
/// abrir build option
/// ir a linker setting
/// agregar la libreria que usamos (esta en big/debug)
/// mantener como path  relative

int ingresarEnteroPositivo(const char* mensaje);


int main()
{
    Fecha fIngr = ingresarFecha();

    printf("Dir fIngr: %p\n", &fIngr);

    printf("La fecha ingresada es: %d/%d/%d", fIngr.dia, fIngr.mes, fIngr.anio);



    int dias = ingresarEnteroPositivo("Ingrese la cantidad de dias a sumar: ");

    Fecha fSuma = sumarDiasAFecha(&fIngr, dias);

    printf("La fecha resultante es: %d/%d/%d\n", fSuma.dia, fSuma.mes, fSuma.anio);

    return 0;
}

int ingresarEnteroPositivo(const char* mensaje)
{

    printf("Cad en pos 3: %c\n", mensaje [3]);

    int n;
    puts(mensaje);
    scanf("%d", &n);
    while(n <= 0)
    {
        printf("Error. %s", mensaje);
        scanf("%d", &n);
    }

    return n;
}


