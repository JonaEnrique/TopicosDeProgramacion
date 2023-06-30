#include "Header.h"

int crearArchAlumnos(char *path)
{
    FILE *archAlum = fopen(path, "wb");

    if (archAlum == NULL)
        return 0;

    Alumno vecAlums[TAM_VEC_ALUM] =
        {
            {1, "Juan"},
            {2, "Pedro"},
            {3, "Maria"},
            {4, "Jose"},
            {5, "Ana"},
            {6, "Lucia"},
            {7, "Carlos"},
            {8, "Miguel"},
            {9, "Sofia"},
            {10, "Florencia"}};

    for (int i = 0; i < TAM_VEC_ALUM; i++)
        fwrite(&vecAlums[i], sizeof(Alumno), 1, archAlum);

    fclose(archAlum);

    return 1;
}

int crearArchNotas(char *path)
{
    FILE *archNotas = fopen(path, "wt");

    if (archNotas == NULL)
        return 0;

    Nota vecNotas[TAM_VEC_NOTAS] = {{1, "P1", 10},
                                    {1, "P2", 8},
                                    {2, "P1", 4},
                                    {2, "R1", 2},
                                    {2, "R2", 4},
                                    {3, "P1", 6},
                                    {3, "R2", 7},
                                    {4, "P1", 9},
                                    //{4, "P2", 8},
                                    {5, "P1", 10},
                                    {5, "P2", 10},
                                    {6, "P1", 8},
                                    {6, "P2", 9},
                                    {7, "P1", 7},
                                    {7, "P2", 8},
                                    {8, "P1", 6},
                                    {8, "P2", 7},
                                    {9, "P1", 4},
                                    {10, "P1", 2},
                                    {10, "P2", 3}};

    for (int i = 0; i < TAM_VEC_NOTAS; i++)
        fprintf(archNotas, "%d|%s|%f\n", vecNotas[i].dni, vecNotas[i].tipoExamen, vecNotas[i].nota);

    fclose(archNotas);

    return 1;
}

void mostrarArchAlumnos(char *path)
{
    FILE *archAlum = fopen(path, "rb");

    if (archAlum == NULL)
        return;

    Alumno alum;

    printf("DNI - Apellido y Nombre\n");

    while (fread(&alum, sizeof(Alumno), 1, archAlum) > 0)
        printf("%d - %s\n", alum.dni, alum.apellYNombre);

    fclose(archAlum);
}

void mostrarArchNotas(char *path)
{
    FILE *archNotas = fopen(path, "rt");

    if (archNotas == NULL)
        return;

    Nota nota;
    char cad[200];

    printf("DNI - Tipo - Nota\n");

    while (fgets(cad, sizeof(cad), archNotas))
    {
        trozarCamposNotas(cad, &nota);

        printf("%d - %s - %f\n", nota.dni, nota.tipoExamen, nota.nota);
    }

    fclose(archNotas);
}

void trozarCamposNotas(char *cad, Nota *nota)
{
    char *caracter = strchr(cad, '\n');
    *caracter = '\0';

    caracter = strrchr(cad, '|');
    sscanf(caracter + 1, "%f", &nota->nota);
    *caracter = '\0';

    caracter = strrchr(cad, '|');
    sscanf(caracter + 1, "%s", nota->tipoExamen);
    *caracter = '\0';

    sscanf(cad, "%d", &nota->dni);
}

int procesarActas(char *pathActas, char *pathAlumnos, char *pathNotas)
{
    FILE *archAlumnos = fopen(pathAlumnos, "rb");
    FILE *archNotas = fopen(pathNotas, "rt");
    FILE *archActas = fopen(pathActas, "wt");
    FILE *archObservaciones = fopen("observaciones.txt", "wt");

    if (!archAlumnos || !archNotas || !archActas)
        return 0;

    Alumno alum;
    Nota nota;
    char cadNota[200];
    int comp = 0;
    Acta acta = {0, "", -1, -1, -1, -1, -1, ""};
    int notaMenor;
    char cadTemp[20];

    fread(&alum, sizeof(Alumno), 1, archAlumnos);
    fgets(cadNota, sizeof(cadNota), archNotas);

    while (!feof(archAlumnos) && !feof(archNotas))
    {
        if (comp >= 0)
            trozarCamposNotas(cadNota, &nota);

        comp = alum.dni - nota.dni;

        if (comp == 0)
        {
            acta.dni = alum.dni;
            strcpy(acta.apellYNombre, alum.apellYNombre);

            if (strcmp(nota.tipoExamen, "P1") == 0)
                acta.P1 = nota.nota;

            if (strcmp(nota.tipoExamen, "P2") == 0)
                acta.P2 = nota.nota;

            if (strcmp(nota.tipoExamen, "R1") == 0)
                acta.R1 = nota.nota;

            if (strcmp(nota.tipoExamen, "R2") == 0)
                acta.R2 = nota.nota;

            fgets(cadNota, sizeof(cadNota), archNotas);
        }

        if (comp < 0)
        {
            if (acta.R1 > 0)
                acta.P1 = acta.R1; // Si tiene recuperatorio, pisa la nota final

            if (acta.R2 > 0)
                acta.P2 = acta.R2; // Si tiene recuperatorio, pisa la nota final

            if (acta.P1 > 0 && acta.P2 > 0 && !(acta.R1 > 0 && acta.R2 > 0))
            {
                if ((acta.P1 >= 1 && acta.P1 <= 3) && (acta.P2 >= 1 && acta.P2 <= 3))
                {
                    acta.notaFinal = (acta.P1 + acta.P2) / 2;
                    strcpy(acta.condicionFinal, "Rec");
                }
                else if ((acta.P1 >= 4 && acta.P1 <= 7) && (acta.P2 >= 4 && acta.P2 <= 7))
                {
                    acta.notaFinal = (acta.P1 + acta.P2) / 2;
                    strcpy(acta.condicionFinal, "Apr");
                }
                else if ((acta.P1 >= 7 && acta.P1 <= 10) && (acta.P2 >= 7 && acta.P2 <= 10))
                {
                    acta.notaFinal = (acta.P1 + acta.P2) / 2;
                    strcpy(acta.condicionFinal, "Pro");

                    if (acta.R1 > 0 || acta.R2 > 0)
                    {
                        fprintf(archObservaciones, "%d|%s|%s|", acta.dni,
                                acta.apellYNombre,
                                acta.P1 > 0 ? (floatToString(acta.P1, cadTemp, sizeof(cadTemp)), cadTemp) : "A");
                        fprintf(archActas, "%s|", acta.P2 > 0 ? (floatToString(acta.P2, cadTemp, sizeof(cadTemp)), cadTemp) : "A");
                        fprintf(archActas, "%s|", acta.R1 > 0 ? (floatToString(acta.R1, cadTemp, sizeof(cadTemp)), cadTemp) : "A");
                        fprintf(archActas, "%s|", acta.R2 > 0 ? (floatToString(acta.R2, cadTemp, sizeof(cadTemp)), cadTemp) : "A");
                        fprintf(archActas, "%s|%s\n", acta.notaFinal > 0 ? (floatToString(acta.notaFinal, cadTemp, sizeof(cadTemp)), cadTemp) : "A", acta.condicionFinal);
                    }
                }
                else
                {
                    notaMenor = acta.P1 <= acta.P2 ? acta.P1 : acta.P2;

                    if (notaMenor < 4)
                        strcpy(acta.condicionFinal, "Rec");

                    if (notaMenor >= 4 && notaMenor < 7)
                        strcpy(acta.condicionFinal, "Apr");

                    if (notaMenor >= 7 && notaMenor <= 10) // Podria no ir?
                        strcpy(acta.condicionFinal, "Pro");

                    acta.notaFinal = notaMenor;
                }
            }
            else
            {
                if (acta.R1 > 0 && acta.R2 > 0)
                {
                    strcpy(acta.condicionFinal, "Err");
                    fprintf(archObservaciones, "%d|%s|%s|", acta.dni,
                            acta.apellYNombre,
                            acta.P1 > 0 ? (floatToString(acta.P1, cadTemp, sizeof(cadTemp)), cadTemp) : "A");
                    fprintf(archActas, "%s|", acta.P2 > 0 ? (floatToString(acta.P2, cadTemp, sizeof(cadTemp)), cadTemp) : "A");
                    fprintf(archActas, "%s|", acta.R1 > 0 ? (floatToString(acta.R1, cadTemp, sizeof(cadTemp)), cadTemp) : "A");
                    fprintf(archActas, "%s|", acta.R2 > 0 ? (floatToString(acta.R2, cadTemp, sizeof(cadTemp)), cadTemp) : "A");
                    fprintf(archActas, "%s|%s\n", acta.notaFinal > 0 ? (floatToString(acta.notaFinal, cadTemp, sizeof(cadTemp)), cadTemp) : "A", acta.condicionFinal);
                }
                else
                    strcpy(acta.condicionFinal, "Aus");
            }

            fprintf(archActas, "%d|%s|%s|", acta.dni,
                    acta.apellYNombre,
                    acta.P1 > 0 ? (floatToString(acta.P1, cadTemp, sizeof(cadTemp)), cadTemp) : "A");
            fprintf(archActas, "%s|", acta.P2 > 0 ? (floatToString(acta.P2, cadTemp, sizeof(cadTemp)), cadTemp) : "A");
            fprintf(archActas, "%s|", acta.R1 > 0 ? (floatToString(acta.R1, cadTemp, sizeof(cadTemp)), cadTemp) : "A");
            fprintf(archActas, "%s|", acta.R2 > 0 ? (floatToString(acta.R2, cadTemp, sizeof(cadTemp)), cadTemp) : "A");
            fprintf(archActas, "%s|%s\n", acta.notaFinal > 0 ? (floatToString(acta.notaFinal, cadTemp, sizeof(cadTemp)), cadTemp) : "A", acta.condicionFinal);

            acta.P1 = -1;
            acta.P2 = -1;
            acta.R1 = -1;
            acta.R2 = -1;
            acta.notaFinal = -1;

            fread(&alum, sizeof(Alumno), 1, archAlumnos);
        }

        if (comp > 0) // Una nota no tiene su correspondiente alumno
            fgets(cadNota, sizeof(cadNota), archNotas);
    }

    while (!feof(archAlumnos))
        fread(&alum, sizeof(Alumno), 1, archAlumnos);

    while (!feof(archNotas))
        fgets(cadNota, sizeof(cadNota), archNotas);

    fclose(archAlumnos);
    fclose(archNotas);
    fclose(archActas);
    fclose(archObservaciones);

    return 1;
}

void floatToString(float number, char *buffer, int bufferSize)
{
    // Usamos snprintf para convertir el n�mero en una cadena de caracteres
    // con un formato de "%.2f" para redondear a 2 decimales
    snprintf(buffer, bufferSize, "%.2f", number);
}
