#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "EmpleadoEstudiantes.h"

//bool abrirArchivo(FILE** fp, const char* nombreArchivo, const char* modoApertura, int mostrarError);

int main(int argc, char* argv[])
{
    crearArchivoEmpleado(argv[1]);
    crearArchivoEstudiante(argv[2]);

    mostrarArchivoEmpleado(argv[1]);
    mostrarArchivoEstudiante(argv[2]);

    FILE* archEmpl = fopen(argv[1], "r+b");
    FILE* archEstu = fopen(argv[2], "rb");
    Empleado empl;
    Estudiante estud;

    if(!archEmpl || !archEstu)
    {
        puts("Error al abrir alguno de los archivos.");
        return 1;
    }

    fread(&empl, sizeof(Empleado), 1, archEmpl);
    fread(&estud, sizeof(Empleado), 1, archEstu);

    while(!feof(archEmpl) && !feof(archEstu))
    {
        if(empl)
    }

    fclose(archEmpl);
    fclose(archEstu);

    return 0;
}

//bool abrirArchivo(FILE** fp, const char* nombreArchivo, const char* modoApertura, int mostrarError)
//{
//    *fp = fopen(nombreArchivo, modoApertura);
//
//    if(*fp == NULL)
//    {
//        if (mostrarError == 1)
//        {
//            fprintf(stderr, "Error abriendo \"%s\" en modo \"%s\".",
//            nombreArchivo,
//            modoApertura);
//
//            return 0;
//        }
//
//    }
//}
