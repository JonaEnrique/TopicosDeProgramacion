#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool eliminarPrimeraAparicionDeVector(const int* vec, int* ce, int tamVec, int elem); // Ejercicio 1.4 Jona
void eliminarPrimerAparacionElemento (int cadena[], int elemento, int tamCadena); // Ejercicio 1.4 Nico
void eliminarTodasAparacionesElemento (int cadena[], int elemento, int tamCadena); // Ejercicio 1.5 Nico
void eliminarTodasAparacionesElementoConPuntero(int* vec, int* ce, int tamVec, int elemento); // Ejercicio 1.5 con punteros Nico
bool detectarPalindromo(const char* vec, const int* ce); // Ejercicio 1.6 funcion adicional Nico
/// EJERCICIO 1.7 ES ATOI
int detectarPalabra(const char* cadena, const char* palabra); // Ejercicio 1.8 con punteros Nico
size_t mi_strlen (char* cadena); // strlen creado por si sirve. Nico

void normalizarCadena(char* cadena);
void miToLower(char* caracter);
void miToUpper(char* caracter);
int esPalabra(char* caracter);

int main()
{
    int cadenaPrueba[10] = {1, 5, 6, 7, 8, 9, 10, 5, 7, 5};
    char cadenaPrueba2[] = "A luna dse anula";
    char cadenaPrueba3[] = "LaaL";
    char cadenaPrueba4[] = "un millon ciento veinte mil cuatrocientos veinti y dos";
    char cadenaPrueba5[] = "tres";
    //char cadenaPrueba6[] = "Buscaremos la palabra Lepricon, en respecto a su significado el Lepricon es...";
    //char palabraPrueba6[] = "Leepricon";
    char cadenaPrueba6[] = "DAAHHHola TESTEO Hola DEl";
    char palabraPrueba6[] = "Hola";
    char cadenaPrueba7[] = " ESTO es  UNA prueba         P2456aRa SAbEr  si  eSTO      si funciona     .   ";
    char CadenaPrueba8[] = "funciona     .   ";

    int ce = 10, tamVec = 10, ceCP2 = 16, ceCP3 = 4, resultadoSumaCadenas = 0,testSumaCadenas = 0, tamCadena = 0, tamCadena2 = 0, halladas = 0;
    bool valor;

    //valor=eliminarPrimeraAparicionDeVector(cadenaPrueba, &ce, tamVec,  5);
    //eliminarPrimerAparacionElemento(cadenaPrueba, 7, 10);
    //eliminarTodasAparacionesElemento(cadenaPrueba, 5, 10);
    eliminarTodasAparacionesElementoConPuntero(cadenaPrueba, &ce, tamVec, 5);
    valor = detectarPalindromo(cadenaPrueba2, &ceCP2);
    valor = detectarPalindromo(cadenaPrueba3, &ceCP3);
    halladas = detectarPalabra(cadenaPrueba6, palabraPrueba6);
    size_t tamanio = strlen(cadenaPrueba7);
    normalizarCadena(cadenaPrueba7);
    tamanio = strlen(cadenaPrueba7);
    normalizarCadena(CadenaPrueba8);

    puts("Fin de Prueba");

    return 0;
}

bool eliminarPrimeraAparicionDeVector(const int* vec, int* ce, int tamVec, int elem)
{
    int* cVec = (int*)vec;
    int* finElemsVec = (int*)vec + *ce - 1;
    int encontrado = 0;

    while(cVec <= finElemsVec)
    {
        if(encontrado || *cVec == elem)
        {
            *cVec = *(cVec + 1);
            encontrado = 1;
        }
        cVec++;
    }

    return encontrado ? (*ce = (*ce) - 1, true) : false;
}

void eliminarPrimerAparacionElemento (int cadena[], int elemento, int tamCadena)
{
    int i, j;

    for(i = 0; cadena[i] != elemento; i++) // busca el elemento en cadena.
        ;

    for(j = i; j < (tamCadena-(1)); j++) // elimina elemento desplazando el valor siguiente en cadena a la izquierda.
    {
        cadena[j]=cadena[j+1];
    }

    cadena[j]=0; // se rellena ultima posicion que quedaria con valor basura (REDUNDANTE SI INCORPORAMOS CE para saber valores validos).
}

void eliminarTodasAparacionesElemento(int cadena[], int elemento, int tamCadena)
{
    int i, d, j, cantidadElementos = 0;

    for(i = 0; i < tamCadena; i++)  // buscamos todas las aparaciones del elemento en vector
    {
        if(cadena[i] == elemento)
            cantidadElementos++;
    }

    while(cantidadElementos != 0) // usamos el contador de elementos hallados para hacer varias pasadas
    {
        for(d = 0; cadena[d] != elemento; d++)
            ;
        for(j = d; j < tamCadena-1; j++)
            cadena[j] = cadena[j+1];
        cantidadElementos--;
    }

    for(d = 0; d < tamCadena; d++) // se rellena posiciones que quedarian vacias o con valor redundante. (REDUNDANTE SI INCORPORAMOS CE para saber valores validos)
        cadena[d]=0;
}

void eliminarTodasAparacionesElementoConPuntero(int* vec, int* ce, int tamVec, int elemento) /// DUDA: tamVec lo usamos para algo?
{
    int* posFinalVector = vec + (*ce - 1);
    int* vecIndice1 = vec, * vecIndice2 = vec;
    int cantidadElementos = 0, encontrado = 0, d;

    while(vecIndice1 <= posFinalVector)
    {
        if(*vecIndice1 == elemento)
            cantidadElementos++;
        vecIndice1++;
    }

    for(d = 0; d != cantidadElementos; d++)
    {
        while(vecIndice2 <= posFinalVector)
        {
            if(*vecIndice2 == elemento || encontrado == 1)
            {
                *vecIndice2 = *(vecIndice2 + 1);
                encontrado = 1;
            }
            vecIndice2++;
        }
        encontrado = 0;
        vecIndice2 = vec;
    }
    *ce = (*ce) - cantidadElementos;

    /*
    for(vecIndice1 = vec; vecIndice1 <= posFinalVector; vecIndice1++)  // buscamos todas las aparaciones del elemento en vector
    {
        if(*vecIndice1 == elemento)
            cantidadElementos++;
    }

    for(d = 0; d != cantidadElementos; d--)
    {
        for(vecIndice2 = vec; vecIndice2 < posFinalVector; vecIndice2++)
        {
            if(*vecIndice2 == elemento || encontrado == 1)
            {
                *vecIndice2 = *(vecIndice2 + 1);
                encontrado = 1;
            }
        }
        encontrado = 0;
    }
    *ce = (*ce) - cantidadElementos;
    */ /// REVISAR PORQUE NO ANDA CON FOR (OJO PUDO SER PORQUE HICE MAL CALCULO DE ULTIMA POSICION DE VECTOR)
}

bool detectarPalindromo(const char* vec, const int* ce)
{
    char* vecInicio = (char*)vec;
    char* vecFinal = (char*)vec + (*ce - 1);
    int noPalindromo = 0;

    while(vecInicio != vecFinal && noPalindromo != 1 && vecInicio < vecFinal)
    {
        if(*vecInicio == ' ')
        {
            vecInicio++;
        }
        if(*vecFinal == ' ')
        {
            vecFinal--;
        }
        if(tolower(*vecInicio) != tolower(*vecFinal))
        {
            noPalindromo = 1;
        }
        vecInicio++;
        vecFinal--;
    }

    return noPalindromo ? false : true;
}

int detectarPalabra(const char* cadena, const char* palabra)
{
    int halladas = 0, finalizada = 0;
    char* cursorCad;
    // char* tempCursorCad = (char*) cadena; // creado para trampas como HHHola (donde se repite primer letra)
    char* cursorPal = (char*) palabra;

    for(cursorCad = (char*) cadena; finalizada != 1; cursorCad++)
    {

        if(*cursorCad == *cursorPal)
        {

            cursorPal++;
            if(!*cursorPal)
                halladas++;
        }
        else
        {
            cursorPal = (char*) palabra;
            cadena++; // llamado a cadena que no genera warning porque solo se toca direccion
            cursorCad = (char*) cadena;
        }
        if(*cursorCad == '\0')
            finalizada = 1; // forzado para que llegue hasta el final, si evaluamos en el for se corta antes de llegar al \0 de la palabra

            // Jona tiene un metodo con While que es mas compacto que el for presentado.
            // Se usa While(cursorCad) y se elimina el ultimo if de nuestro for
            // fuera del While tambien verifico if(!*cursorCad) halladas++ para detectar ultimo caso.

    }

    return halladas;
}

size_t mi_strlen (char* cadena)
{
    char *cursorCad;
    while (*cursorCad != '\0')
        cursorCad++;
    return cursorCad - cadena; // para referencia ver 5.4 de Kernighan
}

void normalizarCadena(char* cadena)
{
    int finInicio = 0, salto = 0, inicio = 0, palabraDetectada = 0;
    char* cursorCad, * tempCursorCad, * tempCursorFinPalabra;

    for(cursorCad = cadena; *cursorCad; cursorCad++)
    {
        if((*cursorCad == ' ' || *cursorCad == '\t') && finInicio == 0)
            {
            for(cursorCad = cadena; (*cursorCad = *(cursorCad + 1)); cursorCad++)
                ;
            cursorCad = cadena;
            }

        if(*cursorCad == ' ' || *cursorCad == '\t')
        {
            salto = 1;
            if(*cursorCad == *(cursorCad + 1))
            {
                tempCursorCad = cursorCad;
                for(cursorCad = cursorCad; (*cursorCad = *(cursorCad + 1)); cursorCad++) // Elimino repeticion de espacio
                    ;
                cursorCad = tempCursorCad;
            }

        }

        if(esPalabra(cursorCad))
        {
            miToLower(cursorCad);
            finInicio = 1;
            if(inicio == 0)
            {
                miToUpper(cursorCad);
                inicio = 1;
            }
            if(salto == 1)
            {
                miToUpper(cursorCad);
                salto = 0;
            }
            tempCursorFinPalabra = cursorCad+1;
            palabraDetectada = 1;
        }

        if(*cursorCad != ' ' && *cursorCad != '\t')
        {
            palabraDetectada = 1;
            tempCursorFinPalabra = cursorCad+1;
        }

        if(palabraDetectada == 1 && salto == 1 && !(*(cursorCad + 1)))
        {
            while(*cursorCad)
            {
                for(cursorCad = tempCursorFinPalabra;(*cursorCad = *(cursorCad+1)); cursorCad++)
                    ;
                cursorCad = tempCursorFinPalabra;
            }
        }

    }
}

void miToLower(char* caracter)
{
    if((*caracter) >= 'A' && (*caracter) <= 'Z')
    {
        *caracter += ('a' - 'A');
    }

}

void miToUpper(char* caracter)
{
    if((*caracter) >= 'a' && (*caracter) <= 'z')
    {
        *caracter -= ('a' - 'A');
    }

}

int esPalabra(char* caracter)
{
    if(((*caracter) >= 'A' && (*caracter) <= 'Z') || ((*caracter) >= 'a' && (*caracter) <= 'z'))
    {
         return 1;
    }
    return 0;
}
