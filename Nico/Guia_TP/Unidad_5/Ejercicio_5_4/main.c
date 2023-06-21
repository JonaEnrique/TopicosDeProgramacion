#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10
#define CAPICUPA 10
#define MULTIPLO5 11
#define MULTIPLO6 12
#define MULTIPLO11 13
#define MAYORA100 14

int analizarNumero(const char* cadena);
int miAtoi(const char* cadena);
void imprimirCategoria(int valor);

int main()
{
    int resultado = 0, escaneo = 0;
    char cadNumero[TAM]={};
    printf("Ingrese numero a analizar\n");
    escaneo = scanf("%s", cadNumero);
    if(!escaneo)
        printf("error lectura");
    resultado = analizarNumero(cadNumero);
    printf("La cadena analizada es: ");
    imprimirCategoria(resultado);
}

int analizarNumero(const char* cadena)
{
    int resultado = 0;
    return resultado; /// HACER!
}

int miAtoi(const char* cadena)
{
    char* cursorCadena = (char*) cadena;
    int signo = 0, sumatoria = 0;
    while(*cadena == ' ')
    {
        cursorCadena++;
    }
    signo = (*cadena == '-') ? -1 : 1;
    while(*cadena >=  '0' && *cadena <= '9')
    {
        sumatoria = sumatoria*10 + (*cadena - '0');
    }
    return signo*sumatoria;
}

void imprimirCategoria(int valor)
{
    if(valor == 10)
        printf("capicua.");
    if(valor == 11)
        printf("multiplo de 5.");
    if(valor == 12)
        printf("multiplo de 6.");
    if(valor == 13)
        printf("multiplo de 11.");
    if(valor == 14)
        printf("mayor a 100.");
}
