#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define esPar(n) ((n)%2 ? 0:1)
#define esNumero(n) ((n) >= '0' && (n) <= '9' ? 1 : 0)

#define TAM_VEC 10

bool insertarEnVectorPos(const int* vec, int* ce, int tamVec, int elem, int pos); // Ejercicio 1.1
bool insertarEnVecOrd(const int* vec, int* ce, int tamVec, int elem); // Ejercicio 1.2
bool eliminarDeVectorPos(const int* vec, int* ce, int tamVec, int pos); // Ejercicio 1.3
bool eliminarPrimeraAparicionDeVector(const int* vec, int* ce, int tamVec, int elem); // Ejercicio 1.4
bool eliminarTodasLasAparicionesDeVector(const int *vec, int* ce, int tamVec, int elem); // Ejercicio 1.5
bool esPalindromo(const char* cad); // Ejercicio 1.6
int mi_atoi(const char* cad); // Ejercicio 1.7
int ocurrenciasEnCad(const char* text, const char* cad); // Ejercicio 1.8

void borrarEspaciosDeCad(char* cad);
void tolowerCad(char* cad);
void mostrarVector(int* vec, int ce);

int main()
{
//    int vec[TAM_VEC] = {1, 2, 3, 4, 5, 6, 7, 8, 9},
//        pos = 1,
//        ce = 9,
//        elem = 5;
//
//    insertarEnVectorPos(vec, &ce, TAM_VEC, elem, pos);
//
//    mostrarVector(vec, ce);


    printf("%d\n", mi_atoi("12345"));
    printf("%d", atoi("1245"));
    

    return 0;
}

bool insertarEnVectorPos(const int* vec, int* ce, int tamVec, int elem, int pos)
{
    if(pos <= 0 || pos > tamVec || *ce < 0)
        return false;

    int* finVecElems = (int*)vec + *ce - (*ce == tamVec ? 1 : 0); // Si la cantidad de elementos es igual al tamaño del vector le resto uno porque no me importa si pisa el ultimo ya que el vector está lleno
    int* insertPos = (int*)vec + pos - 1;

    for(int* i = finVecElems; i > insertPos; i--) // Corremos los elementos uno para la derecha
        *i = *(i - 1);

    *insertPos = elem; // Insertamos el elemento

    if(tamVec != *ce) // Si el tama�o es igual significa que el vector est� en su maximo tama�o y no hay que modificarlo
        *ce = *ce + 1;

    return true;
}

bool insertarEnVecOrd(const int* vec, int* ce, int tamVec, int elem)
{
    int *fin = (int*)vec + *ce - 1, *cVec = (int*)vec, *finVec = (int*)vec + tamVec - 1;

    while(cVec <= fin && elem - *cVec > 0)
        cVec++;

    while(cVec < fin){
        *fin = *(fin - 1);
        fin--;
    }

    if(cVec <= finVec)
        *cVec = elem;

    if(tamVec != *ce)
        *ce = *ce + 1;

    return true;
}

bool eliminarDeVectorPos(const int* vec, int* ce, int tamVec, int pos)
{
    if(pos <= 0 || pos > tamVec || *ce < 0)
        return false;

    int* posElim = (int*)vec + pos - 1;
    int* finElemsVec = (int*)vec + *ce - 1;

    for(int* i = posElim; i < finElemsVec; i++){
        *i = *(i + 1);
    }

    *ce = *(ce) - 1;

    return true;
}

bool eliminarPrimeraAparicionDeVector(const int* vec, int* ce, int tamVec, int elem)
{
    int* cVec = (int*)vec;
    int* finElemsVec = (int*)vec + *ce - 1;
    int encontrado = 0;

    while(cVec <= finElemsVec){
        if(encontrado || *cVec == elem){
            *cVec = *(cVec + 1);
            encontrado = 1;
        }
        cVec++;
    }

    return encontrado ? (*ce = (*ce) - 1, true) : false;
}

bool eliminarTodasLasAparicionesDeVector(const int *vec, int* ce, int tamVec, int elem)
{
    int* cVec = (int*)vec;
    int* finElemsVec = (int*)vec + *ce - 1;
    int* cVecEliminador;

    while(cVec <= finElemsVec)
    {
        if(*cVec == elem){
            cVecEliminador = cVec;
            while(cVecEliminador < finElemsVec){ // No hace falta incluir al ultimo porque ya decrementando ce indicamos que queda como basura el final y decrementar el fin de elementos de vec
                *cVecEliminador = *(cVecEliminador + 1);
                cVecEliminador++;
            }

            *ce = *ce - 1;
            finElemsVec--;
        }
        else
            cVec++;
    }

    return true;
}

bool esPalindromo(const char* cad)
{
    char copiaCad[strlen(cad)];
    strcpy(copiaCad, cad);

    borrarEspaciosDeCad(copiaCad);
    tolowerCad(copiaCad);

    int n = strlen(copiaCad), cantComp = (n - 1)/2 + esPar(n);
    char *ini = copiaCad, *fin = copiaCad + n - 1;

    while(cantComp != 0 && *ini == *fin){
        ini++;
        fin--;

        cantComp--;
    }

    return cantComp ? false : true;
}

int ocurrenciasEnCad(const char* text, const char* cad)
{
    int ocurr = 0;
    char *cText = (char*)text, *cCad = (char*)cad;

    while(*cText)
    {
        if(*cText == *cCad)
        {
            cText++;
            cCad++;
        }
        else
        {
            if(!*cCad)
                ocurr++;

            cCad = (char*)cad;
            text++;
            cText = (char*)text;
        }
    }

    if(!*cCad)
        ocurr++;

    return ocurr;
}

void mostrarVector(int* vec, int ce)
{
    int* fin = vec + ce;

    for(int* i = vec; i < fin; i++)
        printf("%d ", *i);

    printf("\n");
}

void borrarEspaciosDeCad(char* cad)
{
    char* caracterAEliminar;

    while(*cad){
        if(*cad == ' '){
            caracterAEliminar = cad;
            while(*caracterAEliminar){
                *caracterAEliminar = *(caracterAEliminar + 1);
                caracterAEliminar++;
            }
        }
        else
            cad++;
    }
}

void tolowerCad(char* cad){
    while(*cad){
        *cad = tolower(*cad);
        cad++;
    }
}

int mi_atoi(const char* cad)
{
    char* cCad = (char*)cad;
    int n = 0;

    while(*cCad){
        if(esNumero(*cCad))
            n = 10 * n + (*cCad - '0');

        cCad++;
    }

    return n;
}



// Pimera version del ejercicio 1.4 que no funciona del todo

//    while(cVec <= finElemsVec && *cVec != elem){ // Busco el elemento y me voy moviendo hasta encontrarlo
//        cVec++;
//    }
//
//    while(cVec <= finElemsVec){ // Desde el elemento que encontre voy pisando ese mismo con los elementos de la derecha
//        *cVec = *(cVec + 1);
//        cVec++;
//    }
