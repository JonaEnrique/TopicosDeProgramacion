#include <stdio.h>
#include <stdlib.h>

#define  MEM_EST 1
#define  MEM_DIN 2

typedef void (*Accion)(void* pve, void* pvda, int filas, int columnas, int fil, int col); // fil y col son del elemento
// pve = elementos (en nuestro caso sera el puntero de matriz)
// pvda = datos de accion
// fil = filas
// col = columna
// TIP: filElemento y colElemento son para hallar elemento en posicion especifica de matriz.
void** crearMatriz(int filas, int columnas, size_t tamElem);
void destruirMatriz(void** mat, int filas);
// con doble asterisco se a que elemento apunto (void asterisco).
// void** mat es puntero doble a matriz, tenemos puntero para cada fila (i) y cada fila posee punteros internos (estos son j)
void recorrerMatriz(int filas, int columnas, void* mat, size_t tamElem, int memMat,  Accion accion, void* datosAccion);
// TIP: tamElem sera tipo de dato de la matriz
void mostrarInt(void* pve, void* pvda, int filas, int columnas, int fil, int col);
// para esto usamos el typedef void (*Accion).
void mostrarMatriz(int filas, int columnas,int mat[][columnas]);
// cant de filas viene por parametro de ser necesario.
int sumaDiagPrincMatriz(int orden, void* mat, int memMat);
int sumaDiagSecMatriz(int orden, int mat[][orden]);
int sumaTriangInfMatriz(int orden, int mat[][orden]);
void productoMatrices(int filM1, int colM1FilM2, int mat[][colM1FilM2], int colM2, int mat2[][colM2], int matP[][colM2]);

int main()
{

    int matriz[][4]=
    {
        {1, 2, 3, 4},
        {2, 2, 3, 3},
        {3, 3, 3, 3},
        {4, 4, 4, 4}
    };

    int** matrizDin = (int**) crearMatriz(4, 4, sizeof(int)); /// casteo para sacar warning, dudoso (profe lo dejo con error).
    // cargo matrizDin con matriz
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
            matrizDin[i][j] = matriz[i][j]; // es legal por ser int** (sabe su tamaño tanto en primer puntero y segundo puntero)

    }
    recorrerMatriz(4, 4, matrizDin, sizeof(int), MEM_DIN, mostrarInt, NULL);

    // Suma de elementos de matrices
    int suma = sumaDiagPrincMatriz(4, matriz, MEM_EST);
    printf("Suma de la diagonal principal con matriz estatica: %d\n", suma);
    suma = sumaDiagPrincMatriz(4, matrizDin, MEM_DIN);
    printf("Suma de la diagonal principal con matriz di namica: %d\n", suma);
    int sumaDS = sumaDiagSecMatriz(4, matriz);
    printf("Suma de la diagonal secundaria: %d\n", sumaDS);
    int sumaTI = sumaTriangInfMatriz(4, matriz);
    printf("Suma del triangular inferior: %d\n", sumaTI);
    /// ADAPTAR ULTIMAS DOS FUNCIONES PARA QUE USEN ESTATICA Y DINAMICA

    /// IMPORANTE: liberar matrizDin luego de usarla
    destruirMatriz((void**) matrizDin, 4); /// casteo para sacar warning, dudoso (profe lo dejo con error).

    // Producto de matrices
    int mat1[2][4]=
    {
        {1, 2, 3, 4 },
        {5, 6 ,7 ,8 }
    };
    int mat2[4][3]=
    {
        {1, 2, 3},
        {4, 5 ,6},
        {7, 8 ,9},
        {10, 11, 12 }
    };
    int matP[2][3];
    productoMatrices(2, 4, mat1, 3, mat2, matP);

    puts("Matriz producto: ");
    recorrerMatriz(2, 3, matP, sizeof(int), MEM_EST, mostrarInt, NULL); // NULL porque no uso datosAccion.

    return 0;
}

void** crearMatriz(int filas, int columnas, size_t tamElem)
{
    void** mat = malloc(filas * sizeof(void*));

    if(!mat)
        return NULL; // malloc no pudo reservar

    void** ult = mat + filas - 1; // conoce su tamaño al ser void** (tiene tamaños void osea es variable direccion tipo void y usa aritmetica de punteros), distinto seria si fuera void* (en este caso debo aclarar su tamElem).

    for(void** i = mat; i <= ult; i++) // conozco que es void asi que no avanzamos como suele ser con puntero
    {
        *i = malloc(columnas * tamElem); // reserve memoria para una fila

        if(!*i) // chequeo si malloc sirvio
        {
            for(void** j = mat; j < i; j++)
            {
                free(*j);
            }

            free(mat);

            return NULL; // no pudo crear matriz
        }
    }

    return mat;
}

void destruirMatriz(void** mat, int filas)
{
    void** ult = mat + filas - 1;

    for(void** i = mat; i <= ult; i++)
    {
        free(*i);
    }

    free(mat);
}

void recorrerMatriz(int filas, int columnas, void* mat, size_t tamElem, int memMat, Accion accion, void* datosAccion)
{
    /// NOTA: mat es puntero debido al uso de matrices tipo void (no sabemos que nos va a llegar)
    if(memMat == MEM_EST)
    {
        for(int i = 0; i < filas; i++)
        {
            for(int j = 0; j < columnas; j++)
            {   /// OJO para reccorer matriz como puntero usamos:
                /// mat + (i * columnas + j) * tamElem
                /// TIP: En (i *) columnas estamos multiplicando para movernos por el ancho de cada columna)
                /// TIP: En (+ j) nos permitira pararnos en la columna deseada.
                /// TIP: (* tamELem) es para que multiplicar por el tamaño en bytes del elemento.
                accion(mat + (i * columnas + j) * tamElem, datosAccion, filas, columnas, i, j); // j es columna a acceder. LA ACCION ES MOSTRAR MATRIZ OSEA PRINTF
            }
            // putchar('\n'); Este no va porque quizas deba grabar en un archivo
        }
    }
    /// ESTO ES DINAMICA
    else
    {
        void** matDin = (void **)mat; /// FIX porque pasamos por parametro void* mat pero en realidad puede ser void** mat por ser DINAMICA.
        for(int i = 0; i < filas; i++)
        {
            for(int j = 0; j < columnas; j++)
            {
                accion(matDin[i] + j * tamElem, datosAccion, filas, columnas, i, j); // j es columna a acceder.
            }
        }

    }
}

void mostrarMatriz(int filas, int columnas,int mat[][columnas])
{
    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            printf("%d ", mat[i][j]);
        }
        putchar('\n');
    }
}

// int sumaDiagPrincMatriz(int orden, int mat[][orden])
int sumaDiagPrincMatriz(int orden, void* mat, int memMat)
{
    int acum = 0;

    if(memMat == MEM_DIN)
    {
        int** matDin = (int**) mat;
        for(int i = 0; i < orden; i++)
        {
            acum += matDin[i][i];
        }
    }
    else
    {
        int* matEst = (int*)mat;
        for(int i =  0; i < orden; i++)
        {
            acum += matEst[i * orden + i];
        }
    }

    return acum;

}

int sumaDiagSecMatriz(int orden, int mat[][orden]) // en vez de usar la principal tomamos la invertida (va desde 3,0 a 0,3)
{
    int acum = 0;
    int ordenMenosUno = orden - 1;

    for(int i = 0; i < orden; i++)
    {
        acum += mat[i][ordenMenosUno - i];
    }

    return acum;
}

int sumaTriangInfMatriz(int orden, int mat[][orden])
{
    int acum = 0;

    for(int i = 1; i < orden; i++)
    {
        for(int j = 0; j < i; j++)
        {
            acum += mat[i][j];
        }
    }

    return acum;
}

void productoMatrices(int filM1, int colM1FilM2, int mat1[][colM1FilM2], int colM2, int mat2[][colM2], int matP[][colM2])
{
    for(int i = 0; i < filM1; i++)
    {
        for(int j = 0; j < colM2; j++)
        {
            matP[i][j] = 0;

            for(int k = 0; k < colM1FilM2; k++)
            {
                matP[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void mostrarInt(void* pve, void* pvda, int filas, int columnas, int fil, int col)
{
    int* elem = (int*)pve;
    printf("%d ", *elem);

    if(col + 1 == columnas)
        putchar('\n');
}
