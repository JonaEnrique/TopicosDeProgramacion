#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_VEC_ALUM 10
#define TAM_VEC_NOTAS 19

typedef struct
{
    int dni;
    char apellYNombre[31];

}Alumno;

typedef struct
{
    int dni;
    char tipoExamen[3];
    float nota;
}Nota;

typedef struct
{
    int dni;
    char apellYNombre[31];
    float P1, P2, R1, R2;
    float notaFinal;
    char condicionFinal[4];
}Acta;

int crearArchAlumnos(char *path);
int crearArchNotas(char *path);

int procesarActas(char *pathActas, char *pathAlumnos, char *pathNotas);

void mostrarArchAlumnos(char *path);
void mostrarArchNotas(char *path);

void trozarCamposNotas(char* cad, Nota* nota);

void floatToString(float number, char *buffer, int bufferSize);

#endif // HEADER_H
