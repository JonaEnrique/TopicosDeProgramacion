#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_VEC_ALUM 2

typedef struct
{
    long dni;
    char apellYNombre[50];
//    t_alumno fechaNac;
    char sexo;
//    t_fecha fechaIngreso;
    char carrera[4];
    int cantMatAprob;
    char estado;
}t_alumno;

typedef struct
{
    long dni;
    int ind;
}t_indice;



char mostrarMenu(const char* msj, const char* opc);
int crearArchivoAlumno(const char* nombreDelArchivo);
t_indice* crearIndiceAlumno(const char* nombreDelArchivo, int cantRegistros);
void ingresoPorTecladoAlums(const char* nombreDelArchivo, t_indice* indice, int* cantRegistros);
int buscarEnIndiceAlum(t_indice* indice, t_indice* alumno, int cantRegistros);
int compararDNI(const void* a, const void* b);
void mostrarArchAlum(const char *nombreDelArchivo);


