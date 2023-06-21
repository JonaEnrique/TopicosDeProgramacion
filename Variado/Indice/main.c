#include <stdio.h>
#include <stdlib.h>
#include "Indice.h"

#define TAM_VEC_EMPL 7

int cmpEmplIndDNI(const void* a, const void* b);

int main(int argc, char* argv[])
{
    crearArchivoEmpleado(argv[1]);

    EmpleadoInd* indiceEmpl = crearIndiceEmpleado(argv[1], TAM_VEC_EMPL, compararEmpleados);

    ordenamientoSeleccion(indiceEmpl, TAM_VEC_EMPL, sizeof(EmpleadoInd), cmpEmplIndDNI);

    Empleado empl;

    FILE* archEmpl = fopen(argv[1], "rb");

    if(!archEmpl)
        exit(-1);

    printf("%-8s %-10s %-8s %5s\n", "DNI", "Apellido", "Nombre", "Sueldo");
    puts("-------------------------------------");

    for(int i = 0; i < TAM_VEC_EMPL; i++){
        fseek(archEmpl, indiceEmpl[i].indice*sizeof(Empleado), SEEK_SET);

        fread(&empl, sizeof(Empleado), 1, archEmpl);
        printf("%7d %-10s %-8s %5.2f\n", empl.dni, empl.apellido, empl.nombre, empl.sueldo);
    }


    fclose(archEmpl);
    free(indiceEmpl);

    return 0;
}

int cmpEmplIndDNI(const void* a, const void* b)
{
    return ((EmpleadoInd*)a)->dni - ((EmpleadoInd*)b)->dni;
}
