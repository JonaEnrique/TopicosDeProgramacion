#include "Fecha.h"

bool esFechaValida(const Fecha* f)
{
    if(f->anio >= ANIO_BASE)
        if(f->mes >= 1 && f->mes <= 12)
            if(f->dia >= 1 && f->dia <= cantDiasMes(f->mes, f->anio))
                return true;

    return false;
}

int cantDiasMes(int mes, int anio)
{
    static int cdm[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(mes == 2 && esBisiesto(anio))
        return 29;

    return cdm[mes];
}

Fecha ingresarFecha()
{
    Fecha f;

    puts("Ingrese fecha(dd/mm/aa):");
    scanf("%d/%d/%d", &f.dia, &f.mes, &f.anio);

    while(!esFechaValida(&f))
    {
        puts("Ingreso mal la fecha, vuelva a ingresar: ");
        scanf("%d/%d/%d", &f.dia, &f.mes, &f.anio);
    }

    return f;
}

Fecha sumarDiasFecha(Fecha fechaUser, int dias)
{
    int df = fechaUser.dia + dias,
        mf = fechaUser.mes,
        af = fechaUser.anio;

    Fecha fSuma;

    while(df > cantDiasMes(mf, af))
    {
        df -= cantDiasMes(mf, af);
        mf++;

        if(mf > 12)
        {
            mf = 1;
            af++;
        }
    }

    fSuma.dia = df;
    fSuma.mes = mf;
    fSuma.anio = af;

    return fSuma;
}

