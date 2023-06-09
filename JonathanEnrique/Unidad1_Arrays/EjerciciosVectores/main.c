#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define esPar(n) ((n)%2 ? 0:1)
#define esNumero(n) ((n) >= '0' && (n) <= '9' ? 1 : 0)
#define esLetra(n) (((n) >= 'a' && (n) <= 'z') || ((n) >= 'A' && (n) <= 'Z'))

#define TAM_VEC 10

bool insertarEnVectorPos(const int* vec, int* ce, int tamVec, int elem, int pos); // Ejercicio 1.1
bool insertarEnVecOrd(const int* vec, int* ce, int tamVec, int elem); // Ejercicio 1.2
bool eliminarDeVectorPos(const int* vec, int* ce, int tamVec, int pos); // Ejercicio 1.3
bool eliminarPrimeraAparicionDeVector(const int* vec, int* ce, int tamVec, int elem); // Ejercicio 1.4
bool eliminarTodasLasAparicionesDeVector(const int *vec, int* ce, int tamVec, int elem); // Ejercicio 1.5
bool esPalindromo(const char* cad); // Ejercicio 1.6
bool esPalindromoV2(const char* cad); // Ejercicio 1.6
int mi_atoi(const char* cad); // Ejercicio 1.7
int ocurrenciasEnCad(const char* text, const char* cad); // Ejercicio 1.8
void normalizarCad(const char* cadDest, const char* cadOrig); // Ejercicio 1.9
void normalizarCadMisma(char* cad); // Ejercicio 1.9
char* normalizarCadenaPan(const char* cadOrig, char* cadDest);

void borrarEspaciosDeCad(char* cad);
void borrarEspaciosDeCadV2(char* cadDest, const char* cadOrig);
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


//    printf("%d\n", mi_atoi("12345"));
//    printf("%d", atoi("1245"));

//    char cadenaOrigen[] = "          Hola #$%%#$&%/ mundo  6759979650070507065706   como estas";
//    char cadDestino[30];
//
//    normalizarCad(cadDestino, cadenaOrigen);
//
//    printf("Cadena oringen: |%s|\nCadena destino: |%s|\n", cadenaOrigen, cadDestino);

    char cadena[] = "          Hola #$%%#$&%/ muNdo ????????? 6759979650070507065706   como estas   \\\\////   ";
    char cadDest[30];

    normalizarCadenaPan(cadena, cadDest);
    printf("Cadena: |%s|\n", cadDest);

//    char cad[] = "reco nocer";
//
//    printf("%s es palindromo.\n", (esPalindromoV2(cad)==true) ? "Si": "No");
//    printf("%d", esPalindromoV2(cad));

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

bool esPalindromoV2(const char* cad)
{
    char auxCad[strlen(cad)],
         *ini,
         *fin;

    int n, i = 1;

    borrarEspaciosDeCadV2(auxCad, cad);

    n = strlen(auxCad)/2;
    ini = auxCad,
    fin = auxCad + strlen(auxCad) - 1;

    while(i <= n && *ini == *fin)
    {
        ini++;
        fin--;

        i++;
    }

    return (i <= n) ? true : false;
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

void borrarEspaciosDeCadV2(char* cadDest, const char* cadOrig)
{
    char* cDest = cadDest;
    char* cOrig = (char*)cadOrig;

    while(*cOrig)
    {
        if(*cOrig != ' ')
        {
            *cDest = *cOrig;

            cDest++;
        }

        cOrig++;
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

void normalizarCad(const char* cadDest, const char* cadOrig)
{
    char *cCadOrig = (char*)cadOrig,
         *cCadDest = (char*)cadDest,
         *iniPal,
         *finPal;

    while(*cCadOrig)
    {
        if(esLetra(*cCadOrig))
        {
            iniPal = cCadOrig;

            while(*cCadOrig && esLetra(*cCadOrig))
                cCadOrig++;

            finPal = (char*)cCadOrig - 1;

            while(iniPal <= finPal)
            {
                *cCadDest = *iniPal;

                iniPal++;
                cCadDest++;
            }

            *cCadDest = ' ';
            cCadDest++;
        }
        else
            cCadOrig++;
    }

    cCadDest--;
    *cCadDest = '\0';
}

void normalizarCadMisma(char* cad)
{
    char *cCad = cad,
         *cWrite = cad,
         *iniPal,
         *finPal,
         *formatearPal;

    while(*cCad)
    {
        if(esLetra(*cCad))
        {
            iniPal = cCad;

            while(*cCad && esLetra(*cCad))
                cCad++;

            finPal = cCad - 1;

            formatearPal = iniPal;
            *formatearPal = toupper(*formatearPal);

            formatearPal++;

            while(formatearPal <= finPal)
            {
                *formatearPal = tolower(*formatearPal);
                formatearPal++;
            }

            while(iniPal <= finPal)
            {
                *cWrite = *iniPal;

                iniPal++;
                cWrite++;
            }

            *cWrite = ' ';
            cWrite++;
        }
        else
            cCad++;
    }

    cWrite--;
    *cWrite = '\0';
}

char* normalizarCadenaPan(const char* cadOrig, char* cadDest)
{
    const char* orig = cadOrig;
    char* dest = cadDest;

    while(*orig)
    {
        while(*orig && !esLetra(*orig))
            orig++;

        if(!*orig)
        {
            *dest = '\0';
            return cadDest;
        }

        *dest = toupper(*orig);

        orig++;
        dest++;

        while(*orig && esLetra(*orig))
        {
            *dest = tolower(*orig);

            orig++;
            dest++;
        }

        *dest = ' ';
    }

    *(dest - 1) = '\0';

    return cadDest;
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
