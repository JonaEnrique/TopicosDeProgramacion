#include <stdio.h>
#include <stdlib.h>

void pasajeMatriz(char* vectorOrigen, char matrizDestino[][85]);

char matrizAlumno[99][85]={};
char vectorTemp[30];

int main()
{
    FILE *fp;
    fp = fopen("Alumnos.txt", "wt");
    if(fp == NULL)
    {
        printf("Fallo la apertura.");
        return -1;
    }

    int alumno = 0;
    while(finalizado!=1)
    {
    printf("Ingrese NyA de alumno.");
    scanf("%s", matrizAlumno[alumno][0]);
    printf("Ingrese notas de alumno.");
    scanf("%s", vectorTemp);
    pasajeMatriz(vectorTemp, matrizAlumno);
    }

    )

    fclose(fp)
}

void pasajeMatriz(char* vectorOrigen, char matrizDestino[][85])
{
    int posicionNumeros = 35;
    while(vectorOrigen)
    {
        While(*vectorOrigen==' ')
            vectorOrigen++;
        matrizDestino[][posicionNumeros]= *vectorOrigen
        posicionNumeros++;
        vectorOrigen++;
    }

}
