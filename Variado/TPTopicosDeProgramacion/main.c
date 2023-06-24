#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(int argc, char* argv[])
{
    char op;

    // Ingresar fecha de proceso

    // Validar argv[1]
    crearArchivoAlumno(argv[1]);

    t_indice* indice = crearIndiceAlumno(argv[1], TAM_VEC_ALUM);

    int cant = TAM_VEC_ALUM;

    op = mostrarMenu("Elija una opcion\n\n"
                        "A - Alta\n"
                        "B - Baja\n"
                        "F - Buscar\n"
                        "D - Listar los datos de bajo\n"
                        "O - Listar en orden\n"
                        "--> ",
                        "ABS");
    switch(op)
    {
        case 'A':
            ingresoPorTecladoAlums(argv[1], indice, &cant);
            break;
    }

//    for(int i = 0; i < cant; i++){
//        printf("%ld %d\n", indice[i].dni, indice[i].ind);
//    }

    // Archivo alumnos
    printf("\nAlumnos:\n");
    mostrarArchAlum(argv[1]);

    return 0;
}
