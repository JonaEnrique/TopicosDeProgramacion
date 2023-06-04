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
int valorNumericoDeCaracteres (const char* cadCaracter,int tamCadCar); // Ejercicio 1.7 con punteros Nico
int detectorNumero(char* cadPalabra, int resultado); // Ejercicio 1.7 funcion Nico
int detectarCasosVariasCifras(char* cadPalabras,int resultado); // Ejercicio 1.7 funcion Nico
void limpiarVector(char* vector); // Ejercicio 1.7 funcion Nico
/** EL 1.7 que hice no es el indicado. **/
int totalElementosVector (char* vector);


int main()
{
    int cadenaPrueba[10] = {1, 5, 6, 7, 8, 9, 10, 5, 7, 5};
    char cadenaPrueba2[] = "A luna dse anula";
    char cadenaPrueba3[] = "LaaL";
    char cadenaPrueba4[] = "un millon ciento veinte mil cuatrocientos veinti y dos";
    char cadenaPrueba5[] = "tres";
    int ce = 10, tamVec = 10, ceCP2 = 16, ceCP3 = 4, resultadoSumaCadenas = 0,testSumaCadenas = 0, tamCadena = 0, tamCadena2 = 0;
    bool valor;

    //valor=eliminarPrimeraAparicionDeVector(cadenaPrueba, &ce, tamVec, 5);
    //eliminarPrimerAparacionElemento(cadenaPrueba, 7, 10);
    //eliminarTodasAparacionesElemento(cadenaPrueba, 5, 10);
    eliminarTodasAparacionesElementoConPuntero(cadenaPrueba, &ce, tamVec, 5);
    valor = detectarPalindromo(cadenaPrueba2, &ceCP2);
    valor = detectarPalindromo(cadenaPrueba3, &ceCP3);
    tamCadena = totalElementosVector(cadenaPrueba4);
    tamCadena2 = totalElementosVector(cadenaPrueba5);
    resultadoSumaCadenas = valorNumericoDeCaracteres(cadenaPrueba4, tamCadena);


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
    */ /// REVISAR PORQUE NO ANDA CON FOR (OJO PUDO SER PORQUE HICE MAL CALCULO DE ULTIMA POSICION DE VECTOR
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

int valorNumericoDeCaracteres (const char* cadCaracter,int tamCadCar)
{
    char* cursorCadCarIni = (char*)cadCaracter;
    char* cursorCadCarFin= (char*)cadCaracter + (tamCadCar - 1);
    char cadPalabra[tamCadCar]; // Tuve que armar un puntero a esta cadena medio raro, preguntar porque quise hacerlo char* de una y da problema...
    char* cursorCadPalabra = cadPalabra;
    limpiarVector(cursorCadPalabra); /// OJO ESTO ME ARMA UN VECTOR CON MUCHO MAS ESPACIO DEL DEBIDO CORREGIR!
    int resultado = 0, llegadaAlFinal = 0, huboEspacio = 0, flagCifras = 0, contadorTemp = 0;
    int resultadoTemp1 = 0, resultadoTemp2 = 0, resultadoTemp3 = 0; // ya voy 3 horas asi que esto lo hice rapido debe haber una mejor mecanica

    // asumo que esta todo en letras minusculas.
    for(cursorCadCarIni = (char*)cadCaracter; cursorCadCarIni <= cursorCadCarFin; cursorCadCarIni++)
    {
        *cursorCadPalabra = *cursorCadCarIni;

        if(cursorCadCarIni == cursorCadCarFin)
        {
            llegadaAlFinal = 1;
            cursorCadPalabra++;
            *cursorCadPalabra = '\0';
        }
        if(*cursorCadCarIni == ' ')
        {
            cursorCadCarIni++;
            cursorCadPalabra++;
            *cursorCadPalabra = '\0';
            huboEspacio = 1;
        }

        if(huboEspacio == 1 || llegadaAlFinal == 1)
        {

            flagCifras = detectarCasosVariasCifras(cadPalabra, resultado);
            if(flagCifras == 1)
            {
                if(contadorTemp == 2)
                {
                resultadoTemp3 += resultado;
                resultadoTemp3 += detectorNumero(cadPalabra, resultadoTemp3);
                limpiarVector(cadPalabra); // Necesario para no generar error por multiplicacion y para poder enviar una sola palabra a funcion detectorNumero
                cursorCadPalabra = cadPalabra;
                contadorTemp++;
                }
                if(contadorTemp == 1)
                {
                resultadoTemp2 += resultado;
                resultadoTemp2 += detectorNumero(cadPalabra, resultadoTemp2);
                limpiarVector(cadPalabra);
                cursorCadPalabra = cadPalabra;
                contadorTemp++;
                }
                if(contadorTemp == 0)
                {
                resultadoTemp1 += resultado;
                resultadoTemp1 += detectorNumero(cadPalabra, resultadoTemp1);
                limpiarVector(cadPalabra);
                cursorCadPalabra = cadPalabra;
                contadorTemp++;
                }
                resultado = 0; // Resteo valor para seguir calculando.
                huboEspacio = 0;
                // resultadTemp salva el numero si tiene mil o mas (porque lo multiplico al resultado en detectorNumero y daria error si hago sumas y luego multiplico).
            }

            resultado += detectorNumero(cadPalabra, resultado); // Llamo al resultado por si debo multiplicar.
            limpiarVector(cadPalabra);
            cursorCadPalabra = cadPalabra;
            huboEspacio = 0;
        }

        cursorCadPalabra++;

        /** PARA HACER: LIMPIAR EL VECTOR PORQUE SI NO LEE CUALQUIER COSA. **/
    }

    resultado += resultadoTemp1 + resultadoTemp2 + resultadoTemp3;
    return resultado;
}

int detectarCasosVariasCifras(char* cadPalabras,int resultado)
{
    int valor;

    if (strcmp(cadPalabras,"billon") == 0)
        valor = 1;
    else if (strcmp(cadPalabras,"millon") == 0)
        valor = 1;
    else if (strcmp(cadPalabras,"mil") == 0)     // pag 85 del libro de Kerni plantea este modelo para multiples if
        valor = 1;

    return valor;
}

int detectorNumero(char* cadPalabra, int resultado)
{
    int numero; // Debe haber una manera más facil de hacer esto.

    if (strcmp(cadPalabra,"y") == 0)
        numero = 0;
    else if (strcmp(cadPalabra,"un") == 0)
        numero = 1;
    else if (strcmp(cadPalabra,"billon") == 0)
        numero = resultado * 1000000000000;
    else if (strcmp(cadPalabra,"millon") == 0)
        numero = resultado * 1000000;
    else if (strcmp(cadPalabra,"mil") == 0)
        numero = resultado * 1000;
    else if (strcmp(cadPalabra,"cero") == 0)
        numero = 0;
    else if (strcmp(cadPalabra,"uno") == 0)
        numero = 1;
    else if (strcmp(cadPalabra,"dos") == 0)
        numero = 2;
    else if (strcmp(cadPalabra,"tres") == 0)
        numero = 3;
    else if (strcmp(cadPalabra,"cuatro") == 0)
        numero = 4;
    else if (strcmp(cadPalabra,"cinco") == 0)
        numero = 5;
    else if (strcmp(cadPalabra,"seis") == 0)
        numero = 6;
    else if (strcmp(cadPalabra,"siete") == 0)
        numero = 7;
    else if (strcmp(cadPalabra,"ocho") == 0)
        numero = 8;
    else if (strcmp(cadPalabra,"nueve") == 0)
        numero = 9;
    else if (strcmp(cadPalabra,"diez") == 0)
        numero = 10;
    else if (strcmp(cadPalabra,"once") == 0)
        numero = 11;
    else if (strcmp(cadPalabra,"doce") == 0)
        numero = 12;
    else if (strcmp(cadPalabra,"trece") == 0)
        numero = 13;
    else if (strcmp(cadPalabra,"catorce") == 0)
        numero = 14;
    else if (strcmp(cadPalabra,"quince") == 0)
        numero = 15;
    else if (strcmp(cadPalabra,"dieciseis") == 0)
        numero = 16;
    else if (strcmp(cadPalabra,"diecisiete") == 0)
        numero = 17;
    else if (strcmp(cadPalabra,"dieciocho") == 0)
        numero = 18;
    else if (strcmp(cadPalabra,"diecinueve") == 0)
        numero = 19;
    else if (strcmp(cadPalabra,"veinte") == 0)
        numero = 20;
    else if (strcmp(cadPalabra,"veintiuno") == 0)
        numero = 21;
    else if (strcmp(cadPalabra,"veintidos") == 0)
        numero = 22;
    else if (strcmp(cadPalabra,"veintitres") == 0)
        numero = 23;
    else if (strcmp(cadPalabra,"veinticuatro") == 0)
        numero = 24;
    else if (strcmp(cadPalabra,"veinticinco") == 0)
        numero = 25;
    else if (strcmp(cadPalabra,"veintiseis") == 0)
        numero = 26;
    else if (strcmp(cadPalabra,"veintisiete") == 0)
        numero = 27;
    else if (strcmp(cadPalabra,"veintiocho") == 0)
        numero = 28;
    else if (strcmp(cadPalabra,"veintinueve") == 0)
        numero = 29;
    else if (strcmp(cadPalabra,"treinta") == 0)
        numero = 30;
    else if (strcmp(cadPalabra,"cuarenta") == 0)
        numero = 40;
    else if (strcmp(cadPalabra,"cincuenta") == 0)
        numero = 50;
    else if (strcmp(cadPalabra,"sesenta") == 0)
        numero = 60;
    else if (strcmp(cadPalabra,"setenta") == 0)
        numero = 70;
    else if (strcmp(cadPalabra,"ochenta") == 0)
        numero = 80;
    else if (strcmp(cadPalabra,"noventa") == 0)
        numero = 90;
    else if (strcmp(cadPalabra,"noventa") == 0)
        numero = 90;
    else if (strcmp(cadPalabra,"cien") == 0)
        numero = 100;
    else if (strcmp(cadPalabra,"ciento") == 0)
        numero = 100;
    // Salteo los femeninos porque si no esto no termina más...
    else if (strcmp(cadPalabra,"dosciento") == 0)
        numero = 200;
    else if (strcmp(cadPalabra,"trescientos") == 0)
        numero = 300;
    else if (strcmp(cadPalabra,"cuatrocientos") == 0)
        numero = 400;
    else if (strcmp(cadPalabra,"quinientos") == 0)
        numero = 500;
    else if (strcmp(cadPalabra,"seiscientos") == 0)
        numero = 600;
    else if (strcmp(cadPalabra,"setecientos") == 0)
        numero = 700;
    else if (strcmp(cadPalabra,"ochosientos") == 0)
        numero = 800;
    else if (strcmp(cadPalabra,"novecientos") == 0)
        numero = 900;


    return numero;

}

int totalElementosVector (char* vector)
{
    int resultado = 0;
    for(char* cursorVector = vector; *cursorVector != '\0'; cursorVector++, resultado++)
        ;
    return resultado;
}

void limpiarVector(char* vector)
{
    char* cursorVector;
    for(cursorVector = vector; *cursorVector != '\0'; cursorVector++)
    {
        *cursorVector = 0; // No necesario si pongo un '\0' luego de lo que use pero sirve para debugear pq no veo datos randoms.
    }
}

