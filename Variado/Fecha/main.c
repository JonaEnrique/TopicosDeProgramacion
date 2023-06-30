#include <stdio.h>
#include <stdlib.h>

#include "Fecha.h"

int main()
{
    Fecha fecha;

    printf("Ingrese fecha: ");
    scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);

    printf("La fecha %s es valida\n", esFechaValida(&fecha) ? "si" : "no");

    int dias = 30;
    Fecha tempFecha = sumarDiasAFecha(&fecha, dias);

    printf("La fecha sumada %d dias es %d/%d/%d\n", dias, tempFecha.dia, tempFecha.mes, tempFecha.anio);

    return 0;
}
