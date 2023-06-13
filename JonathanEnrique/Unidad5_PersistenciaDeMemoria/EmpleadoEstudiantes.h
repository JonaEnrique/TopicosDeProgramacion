#ifndef EMPLEADOESTUDIANTES_H
#define EMPLEADOESTUDIANTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    int dni;
    char apellido[20];
    char nombre[20];
    float sueldo;
}Empleado;

typedef struct
{
    int dni;
    char apellido[20];
    char nombre[20];
    float promedio;
}Estudiante;

int compararEmpleados(const void* a, const void* b);
int compararEstudiantes(const void* a, const void* b);

bool crearArchivoEmpleado(const char* nombreArchEmpl);
bool crearArchivoEstudiante(const char* nombreArchEstu);

void mostrarArchivoEmpleado(const char* nombreArchEmpl);
void mostrarArchivoEstudiante(const char* nombreArchEstu);


#endif // EMPLEADOESTUDIANTES_H
