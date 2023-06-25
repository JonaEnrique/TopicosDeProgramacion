#ifndef FECHA_H
#define FECHA_H

typedef struct
{
    int dia;
    int mes;
    int anio;
} Fecha;

Fecha ingresarFecha();
int esFechaValida(Fecha f);

#endif // FECHA_H
