#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#include <stdio.h>
#include<stdbool.h>

#define ANIO_BASE 1601
#define esBisiesto(a) (((a)%4 == 0 && (a)%100 != 0) || (a)%400 == 0)

typedef struct{
    int dia,
        mes,
        anio;
}Fecha;

bool esFechaValida(const Fecha* f);
int cantDiasMes(int mes, int anio);
Fecha ingresarFecha();
Fecha sumarDiasFecha(Fecha fechaUser, int dias);

#endif // FECHA_H_INCLUDED
