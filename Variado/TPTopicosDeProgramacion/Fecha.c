#include "Fecha.h"

Fecha ingresarFecha()
{
    Fecha fecha;

//    puts("Ingrese la fecha en formato dd/mm/aaaa");
//    fflush(stdin);
    scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);

    while(!esFechaValida(fecha))
    {
        puts("Fecha invalida, ingrese la fecha en formato dd/mm/aaaa");
        scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
    }

    return fecha;
}

int esFechaValida(Fecha f)
{
    if(f.anio >= ANIO_BASE)
        if(f.mes >= 1 && f.mes <= 12)
            if(f.dia >= 1 && f.dia <= cantDiasDelMes(f.mes, f.anio))
                return 1;

    return 0;
}

int cantDiasDelMes(int mes, int anio)
{
    int cdm[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(mes == 2 && esBisiesto(anio))
        return 29;
    else
        return cdm[mes];
}

