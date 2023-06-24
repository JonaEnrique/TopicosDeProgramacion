#include "header.h"

char mostrarMenu(const char *msj, const char *opc)
{
    char op;

    do
    {
        printf("%s", msj);
        fflush(stdin);
        scanf("%c", &op);
    } while (strchr(opc, op) == NULL);

    return op;
}

int crearArchivoAlumno(const char *nombreDelArchivo)
{
    FILE *arch = fopen(nombreDelArchivo, "wb");

    if (arch == NULL)
        return 0;

    t_alumno vecAlum[TAM_VEC_ALUM] = {{12345678, "Perez, Juan", 'M', "ISI", 0, 'A'},
                                      {23456789, "Gonzalez, Maria", 'F', "ISI", 0, 'A'}};

    fwrite(vecAlum, sizeof(t_alumno), TAM_VEC_ALUM, arch);

    fclose(arch);

    return 1;
}

t_indice *crearIndiceAlumno(const char *nombreDelArchivo, int cantRegistros) // Podria averiguar la cantidad de registros automaticamente
{
    FILE *archAlum = fopen(nombreDelArchivo, "rb");
    t_indice *indice = (t_indice *)malloc(cantRegistros * sizeof(t_indice));

    if (archAlum == NULL)
    {
        free(indice);
        fclose(archAlum);
    }

    t_alumno alum;
    t_indice *cInd = indice;
    int i = 0;

    fread(&alum, sizeof(t_alumno), 1, archAlum);

    while (!feof(archAlum))
    {
        cInd->dni = alum.dni;
        cInd->ind = i;

        printf("Se creo en indice: %ld %d\n", cInd->dni, cInd->ind);

        i++;
        cInd++;
        fread(&alum, sizeof(t_alumno), 1, archAlum);
    }

    qsort(indice, cantRegistros, sizeof(t_indice), compararDNI);

    fclose(archAlum);

    return indice;
}

int compararDNI(const void* a, const void* b)
{
    t_indice* indA = (t_indice*)a;
    t_indice* indB = (t_indice*)b;

    return indA->dni - indB->dni;
}

void ingresoPorTecladoAlums(const char *nombreDelArchivo, t_indice *indice, int* cantRegistros)
{
    FILE *archAlum = fopen(nombreDelArchivo, "r+b");

    if (!archAlum)
    {
        puts("Error al abrir el archivo.");
        fclose(archAlum);
    }

    t_alumno alumNue;
    t_indice alumIndNue;

    do
    {
        printf("Ingrese DNI: ");
        fflush(stdin);
        scanf("%ld", &alumNue.dni);
    } while ((alumNue.dni <= 10000000 || alumNue.dni >= 99999999) && alumNue.dni != -1);

    while (alumNue.dni != -1)
    {
        alumIndNue.dni = alumNue.dni;

        if (buscarEnIndiceAlum(indice, &alumIndNue, *cantRegistros))
        {
            printf("El alumno ingreado ya se encuentra en el sistema.\n");
            return;
        }

        do
        {
            printf("Ingrese nombre y apellido: ");
            fflush(stdin);
            gets(alumNue.apellYNombre);
        } while (strlen(alumNue.apellYNombre) > 50);

        do
        {
            printf("Ingrese sexo: ");
            fflush(stdin);
            scanf("%c", &alumNue.sexo);
        } while (alumNue.sexo != 'M' && alumNue.sexo != 'F');

        do
        {
            printf("Ingrese carrera: ");
            fflush(stdin);
            gets(alumNue.carrera);
        } while (strlen(alumNue.carrera) > 20);

        do
        {
            printf("Ingrese cantidad de materias aprobadas: ");
            fflush(stdin);
            scanf("%d", &alumNue.cantMatAprob);
        } while (alumNue.cantMatAprob < 0 || alumNue.cantMatAprob > 50);

        alumNue.estado = 'A';

        fseek(archAlum, 0L, SEEK_END);
        fwrite(&alumNue, sizeof(t_alumno), 1, archAlum);

        indice = realloc(indice, (*cantRegistros + 1) * sizeof(t_indice));

        if(!indice)
            return;

        alumIndNue.dni = alumNue.dni;
        alumIndNue.ind = *cantRegistros;

        *(indice + *cantRegistros) = alumIndNue;

        (*cantRegistros)++;

        qsort(indice, *cantRegistros, sizeof(t_indice), compararDNI);

        /* Nuevo ingreso */

        do
        {
            printf("Ingrese DNI: ");
            fflush(stdin);
            scanf("%ld", &alumNue.dni);
        } while ((alumNue.dni <= 10000000 || alumNue.dni >= 99999999) && alumNue.dni != -1);
    }

    fclose(archAlum);
}

int buscarEnIndiceAlum(t_indice *indice, t_indice *alumno, int cantRegistros)
{
    t_indice* cInd = indice;

    for(int i = 0; i < cantRegistros; i++){
        if(alumno->dni == cInd->dni){
            alumno->ind = cInd->ind;
            return 1;
        }
    }

    return 0;
}

void mostrarArchAlum(const char *nombreDelArchivo)
{
    FILE *archAlum = fopen(nombreDelArchivo, "rb");

    if (!archAlum)
    {
        puts("Error al abrir el archivo.");
        fclose(archAlum);
    }

    t_alumno alum;

    fread(&alum, sizeof(t_alumno), 1, archAlum);

    while (!feof(archAlum))
    {
        printf("%ld %s %c %s %d %c\n", alum.dni, alum.apellYNombre, alum.sexo, alum.carrera, alum.cantMatAprob, alum.estado);
        fread(&alum, sizeof(t_alumno), 1, archAlum);
    }

    fclose(archAlum);
}
