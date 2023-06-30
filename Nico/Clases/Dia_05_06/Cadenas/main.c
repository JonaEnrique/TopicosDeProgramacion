#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Cadenas clase 06/05 */

/*  ASCII
    UTF-8,-16
    Unicode */

/* Propias versiones de string.h */

/* const adelanta no modifica el contenido de la direccion*/

/*  int strlen(const char* cad);
    char* strcpy(char* cadD, const char* cadO);
    char* strncpy(char* cadD, const char* cadO, int n)
    char* strcat(char* cad1, const char* cad2)
    char* strncat(char* cad1, const char* cad2)
    int strcmp(const char* cad1, const char* cad2, int n)
    char* strchr(const char* cad, char c)
    char* strstr(const char* cad, const char* subCad)*/

/* Replace -> reemplazar subcadena con otra subcadena

cadena, subcadena y reemplazode subcadena
Teniendo en cuenta los tamaños porque puede ser más chica o más grande

una ocurrencia
varias ocurrencias*/

int mi_strlen(const char* cad);
char* mi_strcpy(char* cadD, const char* cadO);
char* mi_strncpy(char* cadD, const char* cadO, int n);

int main()
{
    char cadena1[] = "hola mundo";
    char cadena2[] = "pepe";

    mi_strncpy(cadena1, cadena2, 10);

    printf("|%s|", cadena1);

    return 0;
}

int mi_strlen(const char* cad)
{
    char* cursor = (char*)cad;
    int cont = 0;

    while(*cursor != '\0')
    {
        cont++;
        cursor++;
    }

    return cont;
}

char* mi_strcpy(char* cadD, const char* cadO)
{
    char* cursorD = cadD, *cursorO = (char*)cadO;

    while(*cursorO != '\0')
    {
        *cursorD = *cursorO;

        cursorD++;
        cursorO++;
    }

    *cursorD = '\0';

    return cadD;
}

char* mi_strncpy(char* cadD, const char* cadO, int n)
{
    char* cursorD = cadD, *cursorO = (char*)cadO;
    int cont = 0;

    while(*cursorO != '\0' && cont < n)
    {
        *cursorD = *cursorO;

        cursorD++;
        cursorO++;

        cont++;
    }

    *cursorD = '\0';

    return cadD;
}

