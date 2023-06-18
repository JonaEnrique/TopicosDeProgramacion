#include <stdio.h>
#include <stdlib.h>
#define TAM 4
///HEEEEEEEEEEEEEEEEEEEEEEEEEEEY
/*
Desarrollar una función para que, dada una matriz cuadrada de reales de orden N,
obtenga la sumatoria de los elementos que están por encima de
la diagonal principal (excluida ésta). Lo mismo para la diagonal secundaria.
Lo mismo incluyendo la diagonal. Lo mismo, con los que están por
debajo de la diagonal.
*/
// 1  2  3  4
// 5  6  7  8
// 9  10 11 12
// 13 14 15 16

///1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16


int main()
{
    int F[TAM][TAM];
    Ingreso(&F);
    SumatoriaPrincipal(F);
    SumatoriaPrincipalI(F);
    SumatoriaPrincipalBajo(F);
    SumatoriaSecundaria(F);
    SumatoriaSecundariaI(F);
    SumatoriaSecundariaBajo(F);
    SumatoriaSecundariaIN(F);
    return 0;
}

void SumatoriaSecundariaIN(int T[][TAM]){
    int S=0;
    for(int i=0;i<TAM;i++){
            S+=T[i][TAM-1-i];
    }
    printf("Sumatoria Bajo Secundaria: %d\n",S);
}

void SumatoriaSecundariaBajo(int T[][TAM]){
    int S=0;
    for(int i=0;i<TAM;i++){
        //Para incluir la diagonal es j=TAM-i-1
        for(int j=TAM-i;j<TAM;j++){
            S+=T[i][j];
        }
    }
    printf("Sumatoria Bajo Secundaria: %d\n",S);
}

void SumatoriaPrincipalBajo(int T[][TAM]){
    int S=0;
    for(int i=0;i<TAM;i++){
        for(int j=0;j<i;j++){
            S+=T[i][j];
        }
    }
    printf("Sumatoria Bajo Principal: %d\n",S);
}

void SumatoriaSecundariaI(int T[][TAM]){
    int S=0;
    for(int i=0;i<TAM;i++){
        for(int j=0;j<TAM-i;j++){
            S+=T[i][j];
        }
    }
    printf("Sumatoria Secundaria Incluida: %d\n",S);
}
void SumatoriaSecundaria(int T[][TAM]){
    int S=0;
    for(int i=0;i<TAM;i++){
        for(int j=0;j<TAM-i-1;j++){
            S+=T[i][j];
        }
    }
    printf("Sumatoria Secundaria Excluida: %d\n",S);
}

void SumatoriaPrincipalI(int T[][TAM]){
    int S=0;
    for(int i=0;i<TAM;i++){
        for(int j=i;j<TAM;j++){
            S+=T[i][j];
        }
    }
    printf("Sumatoria Principal Superior incluyendo: %d\n",S);
}

void SumatoriaPrincipal(int T[][TAM]){
    int S=0;
    for(int i=0;i<TAM;i++){
        for(int j=i+1;j<TAM;j++){
            S+=T[i][j];
        }
    }
    printf("Sumatoria Principal Superior sin incluir: %d\n",S);
}

void Ingreso(int T[][TAM]){
    printf("Ingrese los valores de la matriz");
    for(int i=0;i<TAM;i++){
        for(int j=0;j<TAM;j++){
            scanf("%d",&T[i][j]);
        }
    }
}
