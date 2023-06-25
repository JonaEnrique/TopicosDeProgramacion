#include "Fecha.h"

Fecha ingresarFecha()
{
    Fecha fecha;

    puts("Ingrese la fecha en formato dd/mm/aaaa");
    scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);

    while(!esFechaValida(fecha))
    {
        puts("Fecha invalida, ingrese la fecha en formato dd/mm/aaaa");
        scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
    }

    return fecha;
}
int esFechaValida(Fecha f);

