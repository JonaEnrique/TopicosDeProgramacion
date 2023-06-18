#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>

typedef struct Fecha
{
    int dia;
    int mes;
    int anio;
}Fecha;

Fecha ingresarFecha();
bool esFechaValida(const Fecha* fecha);
Fecha sumarDiasAFecha(const Fecha* fecha, int dias);
int compFechas(const Fecha* f1, const Fecha* f2);
int difFechas(const Fecha* f1, const Fecha* f2);



#endif // FECHA_H_INCLUDED
