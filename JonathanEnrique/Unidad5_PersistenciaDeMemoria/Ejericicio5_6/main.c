#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ingreso(char m[][20]);
void mostrarMatriz(char m[][20]);
void llenarMatriz(char m[][20]);

int main()
{
    char matriz[20][20] = {{0}};

    llenarMatriz(matriz);
    ingreso(matriz);

    mostrarMatriz(matriz);

    return 0;
}

void ingreso(char m[][20])
{
    for(int i = 0; i < 1; i++)
    {
        char cad[20];
        char* cCad = cad;

        printf("Ingrese un nombre y apellido: ");
        fgets(cad, 19, stdin);

        while(*cCad)
        {
            if(*cCad == '\n')
                *cCad = '\0';

            cCad++;
        }

        strcpy(m[i], cad);
    }
}

void mostrarMatriz(char m[][20])
{
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            printf("%c", m[i][j]);
        }

        printf("\n");
    }
}

void llenarMatriz(char m[][20])
{
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            m[i][j] = '0';
        }
    }
}
