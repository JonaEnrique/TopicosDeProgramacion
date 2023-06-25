#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Fecha.h"

#define TAM_VEC_ALUM 2

typedef struct
{
    long dni;
    char apellYNombre[50];
    Fecha fechaNac;
    char sexo;
    Fecha fechaIngreso;
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
void ingresoPorTecladoAlums(const char* nombreDelArchivo, t_indice* indice, int* cantRegistros, Fecha fechaProceso);
int buscarEnIndiceAlum(t_indice* indice, t_indice* alumno, int cantRegistros);
int compararDNI(const void* a, const void* b);
void mostrarArchAlum(const char *nombreDelArchivo);
void ordenarSeleccion(void* vec, int cantElem, size_t tamElem, int (*cmp)(const void* a, const void* b));
void intercambiar(void* a, void* b, size_t tamElem);
void darDeBajaAlum(const char* nombreArch, t_indice* indice, int* cantReginstros, Fecha fechaProceso);
int eliminarDeIndiceAlum(t_indice* indice, t_indice* alumno, int* cantRegistros);
int buscarAlum(const char* nombreDelArchivo, t_indice* indice, int cantRegistros);
void mostrarAlumnosDadosDeBaja(const char* nombreDelArchivo);
void mostrarAlumnosEnOrden(const char* nombreDelArchivo, t_indice* indice, int cantRegistros);
