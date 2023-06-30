#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main(int argc, char* argv[])
{
    crearArchAlumnos(argv[1]);
    crearArchNotas(argv[2]);

    printf("Archivo alumnos: %s\n", argv[1]);
    mostrarArchAlumnos(argv[1]);

    printf("Archivo notas: %s\n", argv[2]);
    mostrarArchNotas(argv[2]);


    procesarActas(argv[3], argv[1] , argv[2]);
    return 0;
}
