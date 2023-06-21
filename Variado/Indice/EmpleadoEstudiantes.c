#include "EmpleadoEstudiantes.h"

#define TAM_VEC_EMPL 7
#define TAM_VEC_ESTU 5

// Función de comparación para ordenar los empleados por apellido/nombre/dni
int compararEmpleados(const void* a, const void* b) {
    const Empleado* empleadoA = (const Empleado*)a;
    const Empleado* empleadoB = (const Empleado*)b;
    int resultado = strcmp(empleadoA->apellido, empleadoB->apellido);

    if (resultado == 0) {
        resultado = strcmp(empleadoA->nombre, empleadoB->nombre);

        if (resultado == 0) {
            if (empleadoA->dni < empleadoB->dni) {
                resultado = -1;
            } else if (empleadoA->dni > empleadoB->dni) {
                resultado = 1;
            }
        }
    }

    return resultado;
}

// Función de comparación para ordenar los estudiantes por apellido/nombre/dni
int compararEstudiantes(const void* a, const void* b) {
    const Estudiante* estudianteA = (const Estudiante*)a;
    const Estudiante* estudianteB = (const Estudiante*)b;
    int resultado = strcmp(estudianteA->apellido, estudianteB->apellido);

    if (resultado == 0) {
        resultado = strcmp(estudianteA->nombre, estudianteB->nombre);

        if (resultado == 0) {
            if (estudianteA->dni < estudianteB->dni) {
                resultado = -1;
            } else if (estudianteA->dni > estudianteB->dni) {
                resultado = 1;
            }
        }
    }

    return resultado;
}

bool crearArchivoEmpleado(const char *nombreArchEmpl)
{
    FILE *archEmpl = fopen(nombreArchEmpl, "wb");

    if (!archEmpl)
    {
        puts("Error al abrir archivo.");
        return false;
    }

    Empleado vecEmpl[TAM_VEC_EMPL] = {{1, "Perez", "Juan", 10000.50},
                                    {3, "Gomez", "Ana", 20000.50},
                                    {2, "Gonzalez", "Luis", 30000.50},
                                    {4, "Rodriguez", "Maria", 40000.50},
                                    {5, "Fernandez", "Carlos", 50000.50},
                                    {7, "Paredes", "Armando", 70000.50},
                                    {6, "Gonzalez", "Juana", 60000.50}};

    //qsort(vecEmpl, TAM_VEC_EMPL, sizeof(Empleado), compararEmpleados);

    fwrite(vecEmpl, sizeof(Empleado), TAM_VEC_EMPL, archEmpl);

    fclose(archEmpl);

    return true;
}

bool crearArchivoEstudiante(const char *nombreArchEstu)
{
    FILE *archEstu = fopen(nombreArchEstu, "wb");

    if (!archEstu)
    {
        puts("Error al abrir archivo.");
        return false;
    }

    Estudiante vecEstu[TAM_VEC_ESTU] = {{12345678, "Perez", "Juan", 7.5},
                                        {23456789, "Gomez", "Ana", 8.5},
                                        {34567890, "Gonzalez", "Luis", 9.5},
                                        {45678901, "Rodriguez", "Maria", 6.5},
                                        {56789012, "Fernandez", "Carlos", 5.5}};

    qsort(vecEstu, TAM_VEC_ESTU, sizeof(Estudiante), compararEstudiantes);

    fwrite(vecEstu, sizeof(Estudiante), TAM_VEC_ESTU, archEstu);

    fclose(archEstu);

    return true;
}

void mostrarArchivoEmpleado(const char *nombreArchEmpl)
{
    FILE *archEmpl = fopen(nombreArchEmpl, "rb");

    if (!archEmpl)
    {
        puts("Error al abrir archivo.");
        return;
    }

    Empleado aux;

    printf("Empleados:\n\n");
    printf("%-8s %-10s %-8s %5s\n", "DNI", "Apellido", "Nombre", "Sueldo");
    puts("-------------------------------------");

    fread(&aux, sizeof(Empleado), 1, archEmpl);

    while (!feof(archEmpl))
    {
        printf("%7d %-10s %-8s %5.2f\n", aux.dni, aux.apellido, aux.nombre, aux.sueldo);
        fread(&aux, sizeof(Empleado), 1, archEmpl);
    }

    fclose(archEmpl);
}

void mostrarArchivoEstudiante(const char *nombreArchEstu)
{
    FILE *archEstu = fopen(nombreArchEstu, "rb");

    if (!archEstu)
    {
        puts("Error al abrir archivo.");
        return;
    }

    Estudiante aux;

    printf("\nEstudiantes:\n\n");
    printf("%-8s %-10s %-8s %5s\n", "DNI", "Apellido", "Nombre", "Promedio");
    puts("-------------------------------------");

    fread(&aux, sizeof(Estudiante), 1, archEstu);

    while (!feof(archEstu))
    {
        printf("%7d %-10s %-8s %5.2f\n", aux.dni, aux.apellido, aux.nombre, aux.promedio);
        fread(&aux, sizeof(Estudiante), 1, archEstu);
    }

    fclose(archEstu);
}

int compararEmplYEst(Empleado* empleado, Estudiante* estudiante)
{
    int cmp1 = strcmp(empleado->apellido, estudiante->apellido),
        cmp2 = strcmp(empleado->nombre, estudiante->nombre),
        cmp3 = empleado->dni - estudiante->dni;

    if(cmp1 == 0)
    {
        if(cmp2 == 0)
            return cmp3;
        else
            return cmp2;
    }

    return cmp1;
}

void convertirBinATxtEmpleado(const char* nombreArchEmpl, char tipoTxt)
{
    Empleado empl;
    FILE* archEmpl = fopen(nombreArchEmpl, "rb");
    FILE* archEmplTxt = fopen("Empleados.txt", "wt");

    if(!archEmpl || !archEmplTxt)
    {
        puts("Error al abrir el archivo");
        fclose(archEmpl);
        fclose(archEmplTxt);
        exit(-1);
    }

    fread(&empl, sizeof(Empleado), 1, archEmpl);

    while(!feof(archEmpl))
    {
        fprintf(archEmplTxt, tipoTxt == 'V' ? "%d|%s|%s|%f\n" : "%8d%12s%12s%5.2f\n", empl.dni,
                                                                                     empl.apellido,
                                                                                     empl.nombre,
                                                                                     empl.sueldo);

        fread(&empl, sizeof(Empleado), 1, archEmpl);
    }

    fclose(archEmpl);
    fclose(archEmplTxt);
}
void convertirBinATxtEstudiante(const char* nombreArchEstu);
