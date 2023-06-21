#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*Cmp)(const void* pt1, const void* pt2);

typedef struct
{
    int dni;
    char ape[15];
    char nom[15];
    double sueldo;
}tEmpleado;

typedef struct
{
    int dni;
    int pos;
}tIndiceEmpleado;

int crearArchivoEmpleado(char* nombreArchivo, tEmpleado* estructura, int cantElem);
int crearIndice(const char* nombreArchivo, tIndiceEmpleado* estructura);
void ordenar(void* vector, int tamVector, int tamElemento, Cmp cmp);
int cmptIndiceEmpleado(const void* pt1, const void* pt2);
/*void intercambio(void* pt1, void* pt2);*/
void intercambiar(void* a, void* b, size_t tamElem);


int main()
{

    tEmpleado vectorEmpleadosDesordenado[] = {
    {424703, "Nahuel", "Escala", 150000},
    {120000, "Audo", "Beme", 120000},
    {245666, "Audo", "Cicu", 130000},
    {526874, "Pepe", "Cipres", 160000},
    {765468, "Xalam", "Blanco", 180000},
    {348970, "Dodora", "Maca", 140000},
    {632465, "Roberto", "La Pantera", 170000}
    };

    tIndiceEmpleado indice[(sizeof(vectorEmpleadosDesordenado)/sizeof(tEmpleado))]={};

    crearArchivoEmpleado("EmpleadosDesordenado.bin", vectorEmpleadosDesordenado, sizeof(vectorEmpleadosDesordenado)/sizeof(tEmpleado));
    crearIndice("EmpleadosDesordenado.bin", indice);
    ordenar(indice, sizeof(indice)/sizeof(tIndiceEmpleado), sizeof(tIndiceEmpleado), cmptIndiceEmpleado);
    puts("Prueba!");
}

int crearArchivoEmpleado(char* nombreArchivo, tEmpleado* estructura, int cantElem)
{
    FILE *fp;
    if((fp=fopen(nombreArchivo, "wb")))
    {
        fwrite((estructura), sizeof(tEmpleado), cantElem, fp); /// FIX HORRENDO QUE PERMITE QUE ANDE FWRITE, PARA SEGUNDO PARAMETRO (NUM BYTES) TOMAR SIZEOF(PUNTERO)*SIZEOF(ESCTRUCTURA)-1
        fclose(fp);
        return 0;
    }
    return -2;
}

int crearIndice(const char* nombreArchivo, tIndiceEmpleado* estructura)
{
    int contador = 0;
    tIndiceEmpleado* cursorEstructura = estructura;
    tEmpleado emp;
    FILE* fpBin;

    fpBin = fopen(nombreArchivo, "rb");
    if(!fpBin)
    {
        return -1;
    }

    fread(&emp, sizeof(tEmpleado), 1, fpBin);
    while(!feof(fpBin))
    {
        cursorEstructura->dni = emp.dni;
        cursorEstructura->pos = contador;
        cursorEstructura++;
        contador++;
        fread(&emp, sizeof(tEmpleado), 1, fpBin);
    }

    fclose(fpBin);
    return 0;
}

void ordenar(void* vector, int tamVector, int tamElemento, Cmp cmp)
{
    int i, j, menorPos;
    for(i= 0; i < tamVector-1; i++)
    {
        menorPos = i;
        for(j = i+1; j < tamVector; j++)
        {
            if(cmp(vector+menorPos*tamElemento, vector+j*tamElemento) > 0)
                menorPos = j;
        }

        intercambiar(vector+i*tamElemento, vector+menorPos*tamElemento, tamElemento);
    }

}

int cmptIndiceEmpleado(const void* pt1, const void* pt2)
{
    tIndiceEmpleado* indice1 = (tIndiceEmpleado*) pt1;
    tIndiceEmpleado* indice2 = (tIndiceEmpleado*) pt2;
    return indice1->dni-indice2->dni;
}

/*
void intercambio(void* pt1, void* pt2)
{
    tIndiceEmpleado* indice1 = (tIndiceEmpleado*) pt1;
    tIndiceEmpleado* indice2 = (tIndiceEmpleado*) pt2;
    tIndiceEmpleado* indiceAux = indice1;

    indice1 = indice2;
    indice2 = indiceAux;

}*/ /// ESTO NO GENERA EL CAMBIO COMO DEBE!

void intercambiar(void* a, void* b, size_t tamElem)
{
    void* aux = malloc(tamElem);

    memcpy(aux, a, tamElem);
    memcpy(a, b, tamElem);
    memcpy(b, aux, tamElem);

    free(aux);
}
