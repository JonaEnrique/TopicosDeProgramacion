#ifndef FECHA_H
#define FECHA_H

#include <stdio.h>
#include <stdlib.h>

#define ANIO_BASE 1601
#define esBisiesto(a) (((a)%4 == 0 && (a)%100 != 0) || ((a)%400 == 0))

typedef struct
{
    int dia;
    int mes;
    int anio;
}Fecha;

int esFechaValida(const Fecha* f);
int cantDiasDelMes(int mes, int anio);
Fecha sumarDiasAFecha(const Fecha* f, int dias);
void sumarDiasAFecha_inSitu(Fecha* f, int dias);

#endif // FECHA_H
