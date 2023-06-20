#include "header.h"

void pasarDeTxtVarABin(const char *nomArchVar, const char *nomArchBin, size_t cantBytes,
                       void trozar(void *dato, char *cad),
                       void accion(FILE *pArch, const void *dato))
{
        FILE * pArchVar = fopen(nomArchVar, "rt");
        FILE * pArchBin = fopen(nomArchBin, "wb");
        void *dato = malloc(cantBytes);
        char cad[300];

        if(!pArchVar || !pArchBin || !dato)
        {
            fclose(pArchVar);
            fclose(pArchBin);
            free(dato);
        }

        while(fgets(cad, sizeof(cad), pArchVar))
        {
            trozar(dato, cad);
            accion(pArchBin, dato);
        }

        fclose(pArchVar);
        fclose(pArchBin);
        free(dato);
}

void escribirBin(FILE *pArch, const void *dato)
{
    Alumno *alu = (Alumno*)dato;
    fwrite(alu, sizeof(Alumno), 1, pArch);
}


void leerTxtVar(FILE *pArch, const void *dato)
{
    Alumno *alu = (Alumno*)dato;
    fprintf(pArch, "%d|%s|%f\n", alu->dni, alu->nombre, alu->nota);
}

void trozarArchFijo(void *dato, char *cad)
{
    Alumno *alu = (Alumno*)dato;

    char *aux = cad;

    while(*aux)
    {
        aux++;
    }
    *aux = '\0';

    aux -=6;
    sscanf(aux, "%f", &(alu->nota));
    *aux = '\0';

    aux -=29;
    strcpy(alu->nombre, aux);
    *aux = '\0';

    sscanf(cad, "%d", &(alu->dni));
}

void trozarArchVar(void *dato, char *cad)
{
    Alumno* alum = (Alumno*)dato;
    char* caracter = strchr(cad, '\n');

    *caracter = '\0';

    caracter = strrchr(cad, '|');
    sscanf(caracter + 1, "%f", &(alum->nota));
    *caracter = '\0';

    caracter = strrchr(cad, '|');
    sscanf(caracter + 1, "%s", alum->nombre);
    *caracter = '\0';

    sscanf(cad, "%d", &(alum->dni));
}

void pasarDeTxtFijoATxtVar(const char *nomArchFij, const char *nomArchVar, size_t cantBytes,
                           void trozar(void *dato, char *cad),void accion(FILE *pArch, const void *dato))
{
    FILE * pArchFij = fopen(nomArchFij, "rt");
    FILE * pArchVar = fopen(nomArchVar, "wt");
    void *dato = malloc(cantBytes);
    char aux[1000];

    if(!pArchFij || !pArchVar || !dato)
    {
        fclose(pArchFij);
        fclose(pArchVar);
        free(dato);
        return;
    }

    while(fgets(aux, sizeof(aux), pArchFij))
    {
        trozar(dato, aux);
        accion(pArchVar, dato);
    }

    fclose(pArchFij);
    fclose(pArchVar);
    free(dato);
}

void leerTxtFijo(FILE *pArch, const void *dato)
{
    Alumno *alu = (Alumno*)dato;
    fprintf(pArch, "%8d%-29s%5.02f\n", alu->dni, alu->nombre, alu->nota);
}

void archBinATxtFij(const char *nombreArchBin, const char *nombreArchTxt, size_t cantBytes,
                    void accion(FILE *pArch, const void *dato))
{
    FILE * pArchBin  = fopen(nombreArchBin, "rb");
    FILE * pArchTxt  = fopen(nombreArchTxt, "wt");
    void *dato =  malloc(cantBytes);

    if(!pArchBin || !pArchTxt || !dato)
    {
        fclose(pArchBin);
        fclose(pArchTxt);
        free(dato);
        return;
    }

    fread(dato, cantBytes, 1, pArchBin);

    while(!feof(pArchBin))
    {
        accion(pArchTxt, dato);
        fread(dato, cantBytes, 1, pArchBin);
    }

    fclose(pArchBin);
    fclose(pArchTxt);
    free(dato);
}

void mostrarAlumnos(const void *dato)
{
    Alumno *alu = (Alumno*)dato;

    printf("DNI: [%d], Nombre Y Apellido: [%s], Nota: [%.2f]\n",
           alu->dni, alu->nombre, alu->nota);
}

void leerArchivoBinGen(const char *nombreArch, size_t cantBytes, void mostrar(const void *dato))
{
    void *dato = malloc(cantBytes);
    FILE *pArch = fopen(nombreArch, "rb");

    if(!pArch || !dato)
    {
        fclose(pArch);
        free(dato);
        return;
    }
    fread(dato, cantBytes, 1, pArch);
    while(!feof(pArch))
    {
        mostrar(dato);
        fread(dato, cantBytes, 1, pArch);
    }

    fclose(pArch);
    free(dato);
}

void crearLote(const char *nombreArchBin)
{
    Alumno vAlu[] =
    {
        {41758954, "Nombre01", 8.50},
        {41498954, "Nombre02", 10},
        {41258954, "Nombre03", 8},
        {42758954, "Nombre04", 6},
        {43758954, "Nombre05", 5}
    };

    FILE *pArch = fopen(nombreArchBin, "wb");

    if(!pArch)
        return;

    fwrite(vAlu, sizeof(vAlu), 1, pArch);
    fclose(pArch);
}
