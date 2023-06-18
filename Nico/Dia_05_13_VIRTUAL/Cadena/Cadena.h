#ifndef CADENA_H_INCLUDED
#define CADENA_H_INCLUDED
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


// tiene to toupper y tolower

typedef struct
{
    char* cursor; // parecido a estructura files de archivos
}
SecuenciaPalabras;

typedef struct
{
    char* ini;
    char* fin;
}
Palabra;

#define esLetra(c) (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z'))
#define miToupper(c) (((c) >= 'a' && (c) <= 'z')? (c) - ('a' - 'A'):(c))
#define miTolower(c) (((c) >= 'A' && (c) <= 'Z')? (c) + ('a' - 'A'):(c))

// hacerlas macro es más rapido

char* normalizarCadena(const char* cadOrig, char* cadDest);
char* normalizarCadena2(const char* cadOrig, char* cadDest);
void crearSecuenciaPalabras(SecuenciaPalabras* sec, const char* cad);
bool leerPalabra(SecuenciaPalabras* sec, Palabra* pal);
bool escribirPalabra(SecuenciaPalabras* sec, const Palabra* pal, Palabra* palEsc);
bool escribirCaracter(SecuenciaPalabras* sec, char c);
void aTitulo(Palabra* pal);
void mostrarPalabra(const Palabra* pal);
bool reposicionarSecuenciaPalabras(SecuenciaPalabras* sec, int despl);
void cerrarSecuenciaPalabras(SecuenciaPalabras* sec);

#endif // CADENA_H_INCLUDED
