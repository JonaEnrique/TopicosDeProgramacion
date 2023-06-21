#include "Indice.h"

EmpleadoInd* crearIndiceEmpleado(const char* nombreArch, int cantRegistros, int (*cmp)(const void* a, const void* b))
{
    Empleado empl;
    int i = 0;

    FILE* archEmpl = fopen(nombreArch, "rb");

    if(!archEmpl)
    {
        puts("Error al abrir archivo.");
        exit(-1);
    }

    EmpleadoInd* indice = (EmpleadoInd*)malloc(cantRegistros * sizeof(EmpleadoInd));

    if(!indice)
        free(indice);

    fread(&empl, sizeof(Empleado), 1, archEmpl);

    while(!feof(archEmpl))
    {
        indice[i].dni = empl.dni;
        indice[i].indice = i;

        i++;
        fread(&empl, sizeof(Empleado), 1, archEmpl);
    }


    fclose(archEmpl);

    return indice;
}

void intercambiar(void* a, void* b, size_t tamElem)
{
    void* aux = malloc(tamElem);

    memcpy(aux, a, tamElem);
    memcpy(a, b, tamElem);
    memcpy(b, aux, tamElem);

    free(aux);
}

void ordenamientoSeleccion(void* vec, int cantElem, size_t tamElem, int (*cmp)(const void* a, const void* b))
{
    int posMin;

    for(int i = 0; i < cantElem - 1; i++)
    {
        posMin = i;

        for(int j = i + 1; j < cantElem; j++)
            if(cmp(vec + posMin*tamElem, vec + j*tamElem) > 0)
                posMin = j;

        intercambiar(vec + i*tamElem, vec + posMin*tamElem, tamElem);
    }
}
