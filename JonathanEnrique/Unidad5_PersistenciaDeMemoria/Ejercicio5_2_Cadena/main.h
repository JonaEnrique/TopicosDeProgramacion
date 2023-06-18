#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

#define esLetra(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))

typedef struct
{
    char* iniPal;
    char* finPal;
} Palabra;

int cmpPalabra(Palabra* p1, Palabra* p2);

int buscarPrimeraPalabra(const char *cad, Palabra *primeraPalabra);
int contarPalabraEnCad(const char *cad, Palabra *pal);
int contarPalabrasEnCad(const char *cad);
int strlen_pal(Palabra* pal);
int longPalMasLarga(const char *cad);

void mostrarPalabra(Palabra* p);

#endif // MAIN_H
