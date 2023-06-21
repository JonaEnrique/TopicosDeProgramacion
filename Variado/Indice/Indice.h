#ifndef INDICE_H
#define INDICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EmpleadoEstudiantes.h"

typedef struct
{
    int dni;
    int indice;
}EmpleadoInd;

EmpleadoInd* crearIndiceEmpleado(const char* nombreArch, int cantRegistros, int (*cmp)(const void* a, const void* b));
void intercambiar(void* a, void* b, size_t tamElem);
void ordenamientoSeleccion(void* vec, int cantElem, size_t tamElem, int (*cmp)(const void* a, const void* b));

#endif // INDICE_H
