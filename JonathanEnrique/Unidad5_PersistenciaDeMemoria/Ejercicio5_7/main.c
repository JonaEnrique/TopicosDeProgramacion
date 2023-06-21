#include <stdio.h>
#include <stdlib.h>
#include "../BibliotecaArchivos/Archivo.h"

#define TAM_VEC_EMPL 7
#define TAM_VEC_ESTU 5

typedef struct
{
    int dni;
    char apell[20];
    char nom[20];
    float sueldo;
}Empleado;

typedef struct
{
    int dni;
    char apell[20];
    char nom[20];
    float promedio;
}Estudiante;

int crearArchivoEstudiante(const char* nombreArchEst);
int crearArchivoEmpleado(const char* nombreArchEmpl);

int procesarArchivosEmplEstd(const char* nombreArchEst, const char* nombreArchEmpl, float aumento);

int main(int argc, char* argv[])
{
    crearArchivoEmpleado(argv[1]);
    crearArchivoEstudiante(argv[2]);

    procesarArchivosEmplEstd(argv[2], argv[1], 1.728);

    return 0;
}

int crearArchivoEstudiante(const char* nombreArchEst)
{
    FILE* archEst;
    abrirArchivo(&archEst, nombreArchEst, "wb", true);

    Estudiante vecEstu[TAM_VEC_ESTU] = {{12345678, "Perez", "Juan", 7.5},
                                        {23456789, "Gomez", "Ana", 8.5},
                                        {34567890, "Gonzalez", "Luis", 9.5},
                                        {45678901, "Rodriguez", "Maria", 6.5},
                                        {56789012, "Fernandez", "Carlos", 5.5}};

    fwrite(vecEstu, sizeof(Estudiante), TAM_VEC_ESTU, archEst);

    fclose(archEst);

    return 1;
}

int crearArchivoEmpleado(const char* nombreArchEmpl)
{
    FILE* archEmpl;

    if(!abrirArchivo(&archEmpl, nombreArchEmpl, "wb", true)){
        return 0;
    }

    Empleado vecEmpl[TAM_VEC_EMPL] = {{12345678, "Perez", "Juan", 10000.50},
                                    {23456789, "Gomez", "Ana", 20000.50},
                                    {34567890, "Gonzalez", "Luis", 30000.50},
                                    {45678901, "Rodriguez", "Maria", 40000.50},
                                    {56789012, "Fernandez", "Carlos", 50000.50},
                                    {45784412, "Paredes", "Armando", 70000.50},
                                    {48518481, "Gonzalez", "Juana", 60000.50}};

    fwrite(vecEmpl, sizeof(Empleado), TAM_VEC_EMPL, archEmpl);

    fclose(archEmpl);

    return 1;
}

int procesarArchivosEmplEstd(const char* nombreArchEst, const char* nombreArchEmpl, float aumento);
