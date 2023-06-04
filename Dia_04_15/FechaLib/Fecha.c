#include <stdbool.h>
#include "fecha.h"

#define ANIO_BASE 1601

#define esBisiesto(anio) (((anio) % 4 == 0 && (anio) % 100 != 0) || anio % 400 == 0)

int cantDiasMes(int mes, int anio);

Fecha ingresarFecha()
{
    Fecha fecha;
    puts("Ingrese la fecha en el formato dd/mm/aaaa");
    scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
    while(!esFechaValida(&fecha))
    {
        puts("Fecha invalida. Ingrese la fecha en el formato dd/mm/aaaa");
        scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
    }

    return fecha;
}


bool esFechaValida(const Fecha* f)
{
    if(f->anio >= ANIO_BASE)
        if(f->mes >= 1 && f->mes <= 12)
            if(f->dia >= 1 && f->dia <= cantDiasMes(f->mes, f->anio))
                return true;
    return false;
}

Fecha sumarDiasAFecha(const Fecha* fecha, int dias)
{
    Fecha fSuma = *fecha;
    fSuma.dia += dias;
    int cdm;

    while(fSuma.dia > (cdm = cantDiasMes(fSuma.mes, fSuma.anio)))
    {
        fSuma.dia -= cdm;
        fSuma.anio += fSuma.mes / 12;
        fSuma.mes = fSuma.mes % 12 + 1;

    // if(fSuma.mes > 12)
    // {
    //      fSuma.mes = 1;
    //      fSuma.anio++;
    // }

    }

    return fSuma;
}

int cantDiasMes(int mes, int anio)
{
    int cdm[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(mes == 2 && esBisiesto(anio))
        return 29;
    else
        return cdm[mes];
}
