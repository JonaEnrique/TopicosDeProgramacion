#include "header.h"

char mostrarMenu(const char *msj, const char *opc)
{
    char op;

    do
    {
        printf("%s", msj);
        fflush(stdin);
        scanf("%c", &op);
        op = toupper(op);
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

        i++;
        cInd++;
        fread(&alum, sizeof(t_alumno), 1, archAlum);
    }

    ordenarSeleccion(indice, cantRegistros, sizeof(t_indice), compararDNI);

    fclose(archAlum);

    return indice;
}

int compararDNI(const void *a, const void *b)
{
    t_indice *indA = (t_indice *)a;
    t_indice *indB = (t_indice *)b;

    return indA->dni - indB->dni;
}

void ingresoPorTecladoAlums(const char *nombreDelArchivo, t_indice *indice, int *cantRegistros)
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

        if (!indice)
            return;

        alumIndNue.dni = alumNue.dni;
        alumIndNue.ind = *cantRegistros;

        *(indice + *cantRegistros) = alumIndNue;

        (*cantRegistros)++;

        ordenarSeleccion(indice, *cantRegistros, sizeof(t_indice), compararDNI);

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
    t_indice *cInd = indice;

    for (int i = 0; i < cantRegistros; i++)
    {
        if (alumno->dni == cInd->dni)
        {
            alumno->ind = cInd->ind;
            return 1;
        }

        cInd++;
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

void ordenarSeleccion(void *vec, int cantElem, size_t tamElem, int (*cmp)(const void *a, const void *b))
{
    int posMin;

    for (int i = 0; i < cantElem - 1; i++)
    {
        posMin = i;
        for (int j = i + 1; j < cantElem; j++)
            if (cmp(vec + posMin * tamElem, vec + j * tamElem))
                posMin = j;

        intercambiar(vec + i * tamElem, vec + posMin * tamElem, tamElem);
    }
}

void intercambiar(void *a, void *b, size_t tamElem)
{
    void *aux = malloc(tamElem);

    if (!aux)
        return;

    memcpy(aux, a, tamElem);
    memcpy(a, b, tamElem);
    memcpy(b, aux, tamElem);

    free(aux);
}

void darDeBajaAlum(const char *nombreArch, t_indice *indice, int *cantReginstros)
{
    FILE *archAlum = fopen(nombreArch, "r+b");

    if (!archAlum)
        return;

    t_alumno alum;
    t_indice alumInd;

    do
    {
        printf("Ingrese DNI de la persona a dar de baja: ");
        fflush(stdin);
        scanf("%ld", &alumInd.dni);
    } while ((alumInd.dni <= 10000000 || alumInd.dni >= 99999999));

    if(buscarEnIndiceAlum(indice, &alumInd, *cantReginstros)){
        fseek(archAlum, alumInd.ind * sizeof(t_alumno), SEEK_SET);
        fread(&alum, sizeof(t_alumno), 1, archAlum);

        alum.estado = 'B';

        fseek(archAlum, -(long)sizeof(t_alumno), SEEK_CUR);
        //fseek(archAlum, 0L, SEEK_CUR);
        fwrite(&alum, sizeof(t_alumno), 1, archAlum);

        eliminarDeIndiceAlum(indice, &alumInd, cantReginstros);
    }
    else
        puts("No se encontro el alumno.");

    fclose(archAlum);
}

int eliminarDeIndiceAlum(t_indice* indice, t_indice* alumno, int* cantRegistros)
{
    int i = 0;

    while (i < *cantRegistros && alumno->dni != (indice + i)->dni)
        i++;

    if (i == *cantRegistros)
        return 0;

    for (; i < *cantRegistros - 1; i++)
        *(indice + i) = *(indice + i + 1);

    *cantRegistros = *cantRegistros - 1;

    indice = realloc(indice, *cantRegistros * sizeof(t_indice));

    return 1;
}

int buscarAlum(const char* nombreDelArchivo, t_indice* indice, int cantRegistros)
{
    FILE *archAlum = fopen(nombreDelArchivo, "rb");

    if (!archAlum)
        return 0;

    t_alumno alum;
    t_indice alumInd;

    do
    {
        printf("Ingrese DNI de la persona a buscar: ");
        fflush(stdin);
        scanf("%ld", &alumInd.dni);
    } while ((alumInd.dni <= 10000000 || alumInd.dni >= 99999999));

    if(buscarEnIndiceAlum(indice, &alumInd, cantRegistros)){
        fseek(archAlum, alumInd.ind * sizeof(t_alumno), SEEK_SET);
        fread(&alum, sizeof(t_alumno), 1, archAlum);

        printf("%ld %s %c %s %d %c\n", alum.dni, alum.apellYNombre, alum.sexo, alum.carrera, alum.cantMatAprob, alum.estado);
    }
    else
        puts("No se encontro el alumno.");

    fclose(archAlum);

    return 1;
}

void mostrarAlumnosDadosDeBaja(const char* nombreDelArchivo)
{
    FILE* archAlum = fopen(nombreDelArchivo, "rb");

    if(!archAlum)
        return;

    t_alumno alum;

    fread(&alum, sizeof(t_alumno), 1, archAlum);

    while(!feof(archAlum))
    {
        if(alum.estado == 'B')
            printf("%ld %s %c %s %d %c\n", alum.dni, alum.apellYNombre, alum.sexo, alum.carrera, alum.cantMatAprob, alum.estado);

        fread(&alum, sizeof(t_alumno), 1, archAlum);
    }

    fclose(archAlum);
}

void mostrarAlumnosEnOrden(const char* nombreDelArchivo, t_indice* indice, int cantRegistros)
{
    FILE *archAlum = fopen(nombreDelArchivo, "rb");

    if (!archAlum)
        return;

    t_alumno alum;
    t_indice* cInd = indice;

    for(int i = 0; i < cantRegistros; i++){
        fseek(archAlum, cInd->ind * sizeof(t_alumno), SEEK_SET);
        fread(&alum, sizeof(t_alumno), 1, archAlum);

        printf("%ld %s %c %s %d %c\n", alum.dni, alum.apellYNombre, alum.sexo, alum.carrera, alum.cantMatAprob, alum.estado);

        cInd++;
    }


    fclose(archAlum);
}
