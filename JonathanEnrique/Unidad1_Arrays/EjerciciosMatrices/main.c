#include <stdio.h>
#include <stdlib.h>

#define TAM_FILA 3
#define TAM_COLUM 3

int main()
{
    int matriz[TAM_FILA][TAM_COLUM] = { {1,2,3},
                                        {4,5,6},
                                        {7,8,9}};
    int acumDiagonalSuperior = 0,
        acumDiagonalInferior = 0;

    for(int i = 0; i < TAM_FILA; i++)
    {
        for(int j = 0; j < TAM_COLUM - 1; j++)
        {
            acumDiagonalSuperior += matriz[i][j];
        }
    }

    for(int i = 0; i < TAM_FILA; i++)
    {
        for(int j = TAM_COLUM - i - 1; j < TAM_COLUM; j++)
        {
            acumDiagonalInferior += matriz[i][j];
        }
    }

    printf("Diagonal superior: %d  Diagonal inferior: %d", acumDiagonalSuperior, acumDiagonalInferior);

    return 0;
}
