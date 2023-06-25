#ifndef FECHA_H
#define FECHA_H

#include <stdio.h>
#include <stdlib.h>

#define ANIO_BASE 1601

#define esBisiesto(anio) (((anio) % 4 == 0 && (anio) % 100 != 0) || (anio) % 400 == 0)

typedef struct
{
    int dia;
    int mes;
    int anio;
} Fecha;

Fecha ingresarFecha();
int esFechaValida(Fecha f);
int cantDiasDelMes(int mes, int anio);

#endif // FECHA_H
