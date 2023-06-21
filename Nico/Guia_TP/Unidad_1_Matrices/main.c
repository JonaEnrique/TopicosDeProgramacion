#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1
#define MEM_ESTATICA 1
#define MEM_DINAMICA 2
#define DIAG_PRINCIPAL 3
#define DIAG_SECUNDARIA 4
#define SUMA_TRIAN_SUP_EXCLU_DIAG_PRIN 5
#define SUMA_TRIAN_SUP_EXCLU_DIAG_SECU 6
#define SUMA_TRIAN_SUP_INCLU_DIAG_SECU 7
#define SUMA_TRIAN_INF_INCLU_DIAG_SECU 8

/** PUNTEROS MATRIZ **/
typedef void (*Accion)(void* pve, void* pvda, int filMatriz, int colMatriz, int filElemento, int colElemento);
// pve = elementos (en nuestro caso sera el puntero de matriz)
// pvda = datos de accion
// fil = filas
// col = columna
// TIP: filElemento y colElemento son para hallar elemento en posicion especifica de matriz.
void** crearMatrizDin(int filas, int columnas, size_t tamElem);
void destruirMatrizDin(void** mat, int filas);
// void** mat es puntero doble a matriz, tenemos puntero para cada fila (i) y cada fila posee punteros internos (estos son j)
void recorrerMatriz(int filas, int columnas, void* mat, size_t tamElem, int tipoMemMat, Accion accion, void* datosAccion);
// TIP: tamElem sera tipo de dato de la matriz
// NOTA: recorrerMatriz no pedido pero se usa para ver matrices con puntero.
void mostrarInt(void* pve, void* pvda, int filMatriz, int colMatriz, int filElemento, int colElemento);
int sumaDiagPrincMatriz(int orden, void* mat, int tipoMemMatriz);


/** EJERCICIOS GUIA **/
int sumatoriaDeDiagonalMatriz(int tamFila, int tamColumna, int matriz[][tamColumna], int tipoSumatoria0); // Ej. 1.10
int sumatoriaDeMatriz(int tamFila, int tamColumna, int matriz[][tamColumna], int tipoSumatoria); // Ej. 1.11
int esMatrizDiagonal(int tam, int matriz[][tam]); // Ej. 1.12
int esIdentidad(int tam, int matriz[][tam]); // Ej. 1.13
int esSimetrica(int tam, int matriz[][tam]); // Ej. 1.14
void transponer(int tamFila, int tamColumna, void* matriz, size_t tamElem, Accion accion, void* datosAccion); // Ej. 1.15 (Agregue matriz generica)
void intercambioInt(void* elemento1, void* elemento2, int filMatriz, int colMatriz, int filElemento, int colElemento); // Ej. 1.15 función por parametro
/// Consultar Ej. 1.16 (porque pide una matriz lo cual pasamos por parametro y rellenamos?)
void productosMatrices(int tamFilaMat1, int tamColMat1FilMat2, int matriz1[][tamColMat1FilMat2], int tamColMat2, int matriz2[][tamColMat2], int matrizProd[][tamColMat2]); // Ej. 1.17
int validezTorneo(int tamFila, int tamCol, int matriz[][tamCol]);
void generarResTorneo(int tamFila, int tamCol, int matriz[][tamCol], int* vector);

int main()
{

    int matriz[][3]=
    {
        {1, 2, 1},
        {2, 6, 2},
        {1, 2, 3}
    };

    int matriz2[][3]=
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int matriz3[][3]=
    {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    int matriz4[][3]=
    {
        {1, 2, 3},
        {2, 3, 4},
        {3, 4, 1}
    };

    int matriz5[][4]=
    {
        {1, 2, 3, 6},
        {2, 3, 4, 5},
        {3, 4, 1, 7}
    };

    int matrizProducto[][4]=
    {
        {1, 1, 1, 1},
        {2, 2, 2, 2},
        {3, 3, 3, 3}
    };

    int matriz6[][4]=
    {
        {1, 3, 1, 1},
        {0, 2, 0, 3},
        {1, 3, 3, 1},
        {1, 0, 1, 4}
    };

    int vectResul[] = {0, 0, 0, 0};

    int** matrizDinamica = (int**) crearMatrizDin(3, 3, sizeof(int)); /// OJO: Le tire un casteo raro para sacar el warning. (profesor lo dejo con warning)
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
            matrizDinamica[i][j] = matriz[i][j]; // es legal por ser int** (sabe su tamaño tanto en primer puntero y segundo puntero)
    }
    // Cargamos matrizDinamica con Matriz (pasar a funcion)

    printf("Matriz 1:\n");
    recorrerMatriz(3, 3, matriz, sizeof(int), MEM_ESTATICA, mostrarInt, NULL);
    puts("\n");
    printf("Matriz Dinamica:\n");
    recorrerMatriz(3, 3, matrizDinamica, sizeof(int), MEM_DINAMICA, mostrarInt, NULL);
    puts("\n");
    printf("Matriz 2:\n");
    recorrerMatriz(3, 3, matriz2, sizeof(int), MEM_ESTATICA, mostrarInt, NULL);
    puts("\n");
    printf("Matriz 5:\n");
    recorrerMatriz(3, 4, matriz5, sizeof(int), MEM_ESTATICA, mostrarInt, NULL);
    puts("\n");
    printf("Matriz 6:\n");
    recorrerMatriz(3, 4, matriz6, sizeof(int), MEM_ESTATICA, mostrarInt, NULL);
    puts("\n");


    // Ej  1.10
    int suma5 = sumatoriaDeDiagonalMatriz(3, 3, matriz2, SUMA_TRIAN_SUP_EXCLU_DIAG_PRIN);
    int suma6 = sumatoriaDeDiagonalMatriz(3, 3, matriz2, SUMA_TRIAN_SUP_EXCLU_DIAG_SECU);
    int suma7 = sumatoriaDeDiagonalMatriz(3, 3, matriz2, SUMA_TRIAN_SUP_INCLU_DIAG_SECU);
    int suma8 = sumatoriaDeDiagonalMatriz(3, 3, matriz2, SUMA_TRIAN_INF_INCLU_DIAG_SECU);
    printf("Resultado de suma triangular superior sin diagonal principal: %d\n", suma5);
    printf("Resultado de suma triangular superior sin diagonal secundaria: %d\n", suma6);
    printf("Resultado de suma triangular superior con diagonal secundaria: %d\n", suma7);
    printf("Resultado de suma triangular inferior con diagonal secundaria: %d\n", suma8);

    // Ej 1.11
    int suma3 = sumatoriaDeMatriz(3, 3, matriz, DIAG_PRINCIPAL);
    int suma4 = sumatoriaDeMatriz(3, 3, matriz, DIAG_SECUNDARIA);
    printf("Resultado de suma con diagonal principal: %d\n", suma3);
    printf("Resultado de suma con diagonal secundaria: %d\n", suma4);

    //Ej. 1.13
    int resul1 = esIdentidad(3, matriz3);
    printf("Resultado de identidad de matriz: %d\n", resul1);

    //Ej. 1.14
    int resul2 = esSimetrica(3, matriz4);
    printf("Resultado de simetria de matriz: %d\n", resul2);

    //Ej. 1.15
    transponer(3, 3, matriz2, sizeof(int), intercambioInt, NULL);
    puts("\n");
    printf("Se transpone la matriz 2:\n");
    recorrerMatriz(3, 3, matriz2, sizeof(int), MEM_ESTATICA, mostrarInt, NULL);
    puts("\n");

    //Ej. 1.16

    //Ej. 1.17
    productosMatrices(3, 3, matriz, 4, matriz5, matrizProducto);
    printf("Producto de matrices entre matriz 1 y matriz 5:\n");
    recorrerMatriz(3, 4, matrizProducto, sizeof(int), MEM_ESTATICA, mostrarInt, NULL);
    puts("\n");

    //Ej. 1.18
    int resul3 = validezTorneo(4, 4, matriz6);
    printf("La matriz6 usada para el torneo tiene validez: %d\n", resul3);
    generarResTorneo(4, 4, matriz6, vectResul);
    for(int i = 0; i < 4; i++)
    {
        printf("Los resultados del equipo %d son: %d\n", i, vectResul[i]);
    }


    // Test puntero matrices
    int suma1 = sumaDiagPrincMatriz(3, matriz, MEM_ESTATICA);
    int suma2 = sumaDiagPrincMatriz(3, matrizDinamica, MEM_DINAMICA);
    printf("Resultado de suma con matriz estatica: %d\n", suma1);
    printf("Resultado de suma con matriz dinamica: %d\n", suma2);

    destruirMatrizDin((void**) matrizDinamica, 3); /// aca genera conflicto por matriz de tipo int**, preguntar!.
    puts("\n");
    puts("Fin de programa.");

    return 0;
}

/** EJERCICIOS GUIA **/
int sumatoriaDeDiagonalMatriz(int tamFila, int tamColumna, int matriz[][tamColumna], int tipoSumatoria)
{
    int sumatoria = 0, i, j, columnaMenosUnoMenosI = 0;

    if(tipoSumatoria == SUMA_TRIAN_SUP_EXCLU_DIAG_PRIN)
    {
        for(i = 0; i < tamFila; i++)
        {
            for(j = 2; j > i; j--)
            {
                sumatoria += matriz[i][j];
            }
        }
    }
    else if(tipoSumatoria == SUMA_TRIAN_SUP_EXCLU_DIAG_SECU)
    {

        for(i = 0; i < tamFila; i++)
        {
            columnaMenosUnoMenosI = (tamColumna-1)-i;
            for(j = 0; j < columnaMenosUnoMenosI; j++)
            {
                sumatoria += matriz[i][j];
            }
        }
    }
    else if(tipoSumatoria == SUMA_TRIAN_SUP_INCLU_DIAG_SECU)
    {

        for(i = 0; i < tamFila; i++)
        {
            columnaMenosUnoMenosI = (tamColumna-1)-i;
            for(j = 0; j <= columnaMenosUnoMenosI; j++)
            {
                sumatoria += matriz[i][j];
            }
        }
    }
    else if(tipoSumatoria == SUMA_TRIAN_INF_INCLU_DIAG_SECU)
    {

        for(i = 0; i < tamFila; i++)
        {
            columnaMenosUnoMenosI = (tamColumna-1)-i;
            for(j = (tamColumna-1); j >= columnaMenosUnoMenosI; j--)
            {
                sumatoria += matriz[i][j]; /// REVISAR
            }
        }
    }

    return sumatoria;
}
int sumatoriaDeMatriz(int tamFila, int tamColumna, int matriz[][tamColumna], int tipoSumatoria)
{
    int sumatoria = 0, i;

    if(tipoSumatoria == DIAG_PRINCIPAL)
    {
        for(i = 0; i < tamFila; i++)
        {
            sumatoria += matriz[i][i];
        }
    }
    else if(tipoSumatoria == DIAG_SECUNDARIA)
    {
        for(int i = 0; i < tamFila; i++)
        {
            sumatoria += matriz[i][tamColumna - i -1];
        }
    }

    return sumatoria;
}

int esMatrizDiagonal( int tam, int matriz[][tam])
{
    int validez = 1; // empezamos diciendo que es verdad.

    for(int i = 0; i < tam; i++)
        for(int j = 0; j < tam; j++)
            if(i != j && matriz[i][j] != 0)
            {
                validez  = 0;
            }
            else if(i == j && matriz[i][j] == 0){
                validez = 0;
            }

    return validez;
}

int esIdentidad (int tam, int matriz[][tam])
{
    int validez = 1;
    for(int i = 0; i < tam; i++)
        for(int j = 0; j <= i; j++)
        {
            if(i!=j && (matriz[i][j]!=0 || matriz[j][i]!=0))
                validez = 0;
            if(i==j && matriz[i][j]!=1)
                validez = 0;
        }
    return validez;
}

int esSimetrica (int tam, int matriz[][tam])
{
    int validez = 1;
    for(int i = 0; i < tam; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(matriz[i][j]!=matriz[j][i])
                validez = 0;
        }
    }
    return validez;
}

void transponer (int tamFila, int tamColumna, void* matriz, size_t tamElem, Accion accion, void* datosAccion)
{
    /// ESTATICA
    for(int i = 0; i < tamFila; i++)
    {
        for(int j = 0; j < i; j++)
        {
            accion((matriz+(i*tamColumna+j)*tamElem),(matriz+(j*tamColumna+i)*tamElem),tamFila, tamColumna, i, j);
            // se pretende llamar a intercambioInt
        }
    }
}

void intercambioInt(void* elemento1, void* elemento2, int filMatriz, int colMatriz, int filElemento, int colElemento)
{   // Sigue modelo de Accion accion

    int* int1 = (int*) elemento1;
    int* int2 = (int*) elemento2;
    int* intAuxiliar = (int*) elemento1;

    *intAuxiliar = *int1;
    *int1 = *int2;
    *int2 = *intAuxiliar;
}

void productosMatrices (int tamFilaMat1, int tamColMat1FilMat2, int matriz1[][tamColMat1FilMat2], int tamColMat2, int matriz2[][tamColMat2], int matrizProd[][tamColMat2])
{
        for(int i = 0; i < tamFilaMat1; i++)
        {
            for(int j = 0; j < tamColMat2; j++)
            {
                matrizProd[i][j] = 0;
                for(int k = 0; k < tamColMat1FilMat2; k++)
                {
                    matrizProd[i][j] += matriz1[i][k] * matriz2[k][j];
                }
            }
        }
}

int validezTorneo(int tamFila, int tamCol, int matriz[][tamCol])
{
    int validez = 1;
    for(int i = 0; i < tamFila; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(!(matriz[i][j] == 3 || matriz[i][j] == 1 || matriz[i][j] == 0))
                validez = 0;
            if(matriz[i][j] == 3 && matriz[j][i] != 0)
                validez = 0;
            if(matriz[i][j] == 1 && matriz[j][i] != 1 )
                validez = 0;
            if(matriz[i][j] == 0 && matriz[j][i] != 3)
                validez = 0;
        }
    }
    return validez;
}

void generarResTorneo(int tamFila, int tamCol, int matriz[][tamCol], int* vector)
{
    int* cursorVec = vector;
    for(int i = 0; i < tamFila; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(matriz[i][j] == 3)
            {
                *(cursorVec + i) += 3;
                cursorVec = vector;
            }
            if(matriz[i][j] == 1)
            {
                *(cursorVec + i) += 1;
                cursorVec = vector;
                *(cursorVec + j) += 1;
                cursorVec = vector;
            }
            if(matriz[i][j] == 0)
            {
                *(cursorVec + j) += 3;
                cursorVec = vector;
            }
        }
    }
}       /// VALIDAR QUE ANDE

/** PUNTEROS MATRIZ **/
void** crearMatrizDin(int filas, int columnas, size_t tamElem)
{
    void** mat = malloc(filas * sizeof(void*));

    if(!mat)
        return NULL; // malloc no pudo reservar

    void** ult = mat + filas - 1; // conoce su tamaño al ser void** (tiene tamaños void osea es variable direccion tipo void y usa aritmetica de punteros), distinto seria si fuera void* (en este caso debo aclarar su tamElem).

    for(void** i = mat; i <= ult; i++)
    {
        *i = malloc(columnas * tamElem);

        if(!*i)
        {
            for(void** j = mat; j < i; j++)
            {
                free(*j);
            }

            free(mat);

            return NULL;
        }
    }

    return mat;
}

void destruirMatrizDin(void** mat, int filas)
{
    void** ult = mat + filas - 1;

    for(void** i = mat; i <= ult; i++)
    {
        free(*i);
    }

    free(mat);
}

void recorrerMatriz(int filas, int columnas, void* mat, size_t tamElem, int tipoMemMat, Accion accion, void* datosAccion) // tipoMemMat indica estatica o dinamica
{
    /// ESTO ES ESTATICA
    if( tipoMemMat == MEM_ESTATICA)
    {
        for(int i = 0; i < filas; i++)
        {
            for(int j = 0; j < columnas; j++)
            {
                accion(mat + (i * columnas + j) * tamElem, datosAccion, filas, columnas, i, j);
            }
        }
    }
    /// ESTO ES DINAMICA
    else
    {
        void** matDin = (void**)mat; /// FIX porque pasamos por parametro void* mat pero en realidad puede ser void** mat por ser DINAMICA.
        for(int i = 0; i < filas; i++)
        {
            for(int j = 0; j < columnas; j++)
                {
                    accion(matDin[i] + j * tamElem, datosAccion, filas, columnas, i, j); // recordar al ser void** usamos aritmetica de punteros y ahora solo necesitamos saber el tamaño de j dado que es generico (void).
                }
        }
    }


}

void mostrarInt(void* pve, void* pvda, int filMatriz, int colMatriz, int filElemento, int colElemento)
{
    int* elem = (int*) pve;
    printf("%d ", *elem);

    if(colElemento + 1 == colMatriz)
        putchar('\n');
}

int sumaDiagPrincMatriz(int orden, void* mat, int tipoMemMatriz)
{
    int acum = 0;

    if(tipoMemMatriz == MEM_DINAMICA)
    {
        int** matDinamica = (int**) mat;
        for(int i = 0; i < orden; i++)
        {
            acum += matDinamica[i][i];
        }
    }
    else
    {
        int* matEstatica = (int*) mat;
        for(int i = 0; i < orden; i++)
        {
            acum += matEstatica[i * orden + i]; // recordar que no conoce el tamaño de elementos, no usamos matEstatica[][];
        }
    }

    return acum;
}
