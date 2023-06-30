#ifndef INTEGRADOR_H_INCLUDED
#define INTEGRADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define esBisiesto(anio) ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0)
#define ANIO_BASE 1601

typedef int (*Cmp)(const void* pt1, const void* pt2);

typedef struct
{
    int dia;
    int mes;
    int anio;
}Fecha;

typedef struct
{
    long int dni;
    char apeYNom[50];
    Fecha fechaNacimiento;
    char sexo;
    Fecha fechaIngreso;
    char carrera[4];
    int matAprobadas;
    char estado;
}tAlumno;

typedef struct
{
    int dni;
    int pos;
}tIndiceAlumno;

/**** PARA TESTEO DE ARCHIVOS ****/
void imprimirIndice(tIndiceAlumno* indice, int* cantElementos);
int leerYmostraArchivo(char* nombreArchivo);
/**** PARA TESTEO DE ARCHIVOS ****/

Fecha ingresarFecha(void);
bool esFechaValida(const Fecha* fecha);
int cantDiasMes(const Fecha* fecha);
void validarArchivo(const char* nombreArchivo);
tIndiceAlumno* crearIndiceDinamico(const char* nombreArchivo, int* cantElemIndice);
void menu(tIndiceAlumno* indice, const char* nombreArchivo, int* cantElemIndice, const Fecha* fechaProceso);
void menuSinErr(const char* msj, const char* opc, char* cadenaGuardado);
int crearArchivo(char* nombreArchivo, tAlumno* estructura, int cantElem);
void llamarOpcion(const char* opcion, tIndiceAlumno* indice, const char* nombreArchivo,  int* cantElemIndice, const Fecha* fechaProceso);
void ordenar(void* vector, const int* tamVector, size_t tamElemento, Cmp cmp);
void intercambiar(void* a, void* b, size_t tamElem);
void alta(tIndiceAlumno* indice, const char* nombreArchivo, int* cantElemIndice, const Fecha* fechaProceso);
void baja(tIndiceAlumno* indice, const char* nombreArchivo, int* cantElemIndice, const Fecha* fechaProceso);
void imprimirAlumno(const tAlumno* alumno);
void buscar(tIndiceAlumno* indice, const char* nombreArchivo, const int* cantElemIndice);
void listar1(const char* nombreArchivo);
void listar2(tIndiceAlumno* indice, const char* nombreArchivo, const int* cantElemIndice);
void eliminarAluIndice(tIndiceAlumno* indice, const int* posicion, const int* cantElemIndice);

#endif // INTEGRADOR_H_INCLUDED
