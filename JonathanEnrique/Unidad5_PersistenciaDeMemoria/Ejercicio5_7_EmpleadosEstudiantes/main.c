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
    int cmp;

    if(!archEmpl || !archEstu)
    {
        puts("Error al abrir alguno de los archivos.");
        return 1;
    }

    fread(&empl, sizeof(Empleado), 1, archEmpl);
    fread(&estud, sizeof(Estudiante), 1, archEstu);

    while(!feof(archEmpl) && !feof(archEstu))
    {
        cmp = compararEmplYEst(&empl, &estud);

        if(cmp == 0) // El empleado estudia y trabaja pero tiene que tener promedio más de 7
        {
            if(estud.promedio >= 7)
            {
                empl.sueldo *= 1.078;

                fseek(archEmpl, -(long)sizeof(Empleado), SEEK_CUR);
                fwrite(&empl, sizeof(Empleado), 1, archEmpl);
                fseek(archEmpl, 0L, SEEK_CUR);
            }

            fread(&empl, sizeof(Empleado), 1, archEmpl);
            fread(&estud, sizeof(Estudiante), 1, archEstu);
        }

        if(cmp > 0) // El estudiante no trabaja
            fread(&estud, sizeof(Estudiante), 1, archEstu);

        if(cmp < 0) // El empleado no estudia
            fread(&empl, sizeof(Empleado), 1, archEmpl);



    }


    // Si termina el ciclo puede terminar porque los dos hicieron fin o porque alguno de los dos hizo fin
    // Si alguno de los dos hizo dejando al otro sin leer, no interesa porque queria tanto gente sin estudiar
    // o gente sin trabajar

    // Apunte de elementos de programacion que pasaron al grupo

    printf("\nArchivo empleados actualizado:\n\n");
    mostrarArchivoEmpleado(argv[1]);

    convertirBinATxtEmpleado(argv[1], 'F');

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
