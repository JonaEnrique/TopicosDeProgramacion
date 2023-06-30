#include "Fecha.h"

int esFechaValida(const Fecha* f)
{
    if(f->anio >= ANIO_BASE)
        if(f->mes >= 1 && f->mes <= 12)
            if(f->dia >= 1 && f->dia <= cantDiasDelMes(f->mes, f->anio))
                return 1;

    return 0;
}

int cantDiasDelMes(int mes, int anio)
{
    static int cdm[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(mes == 2 && esBisiesto(anio))
        return 29;
    else
        return cdm[mes];
}

Fecha sumarDiasAFecha(const Fecha* f, int dias)
{
    Fecha tempFecha = *f;
    int cantDias = f->dia + dias;

    while(cantDias >= cantDiasDelMes(tempFecha.mes, tempFecha.anio))
    {
        cantDias -= cantDiasDelMes(tempFecha.mes, tempFecha.anio);
        tempFecha.anio += tempFecha.mes / 12;
        tempFecha.mes = tempFecha.mes%12 + 1;
    }

    tempFecha.dia = cantDias;

    return tempFecha;
}
void sumarDiasAFecha_inSitu(Fecha* f, int dias);
