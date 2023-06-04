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

/*  Mis apuntes:
    - Ojo con la funcion strcat que no controla el tamaño. Si defino una cadena a concatenar declarandola como cadena[] va
    a traer problemas porque la cadena se crea con el tamaño justo sin dejar espacio a concatenar otra
*/

int mi_strlen(const char* cad);
char* mi_strcpy(char* cadD, const char* cadO);
char* mi_strncpy(char* cadD, const char* cadO, int n);
char* mi_strcat(char* cad1, const char* cad2);
char* mi_strncat(char* cad1, const char* cad2, int n);
int mi_strcmp(const char* cad1, const char* cad2);
char* mi_strchr(const char* cad, char c);
char* mi_strrchr(const char* cad, char c);
char* mi_strstr(const char* cad, const char* subCad);

int main()
{
    char cad1[] = "HollaHolHolaMundo";

    printf("|%s|\n", mi_strstr(cad1, "Hola"));
    printf("|%s|", strstr(cad1, "Hola"));

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

char* mi_strcat(char* cad1, const char* cad2)
{
    char *cadCursor1 = cad1,
         *cadCursor2 = (char*)cad2;

    while(*cadCursor1)
        cadCursor1++;

    while(*cadCursor2)
    {
        *cadCursor1 = *cadCursor2;

        cadCursor1++;
        cadCursor2++;
    }

    *cadCursor1 = '\0';

//    while(!*cad1) // Voy a mover el puntero y pierdo el inicio para retornarlo
//        cad1++;

    return cad1;
}

char* mi_strncat(char* cad1, const char* cad2, int n)
{
    char *cadCursor1 = cad1,
         *cadCursor2 = (char*)cad2;

    int cont = 0;

    while(*cadCursor1)
        cadCursor1++;

    while(*cadCursor2 && cont < n)
    {
        *cadCursor1 = *cadCursor2;

        cadCursor1++;
        cadCursor2++;

        cont++;
    }

    *cadCursor1 = '\0';

    return cad1;
}

int mi_strcmp(const char* cad1, const char* cad2)
{
    char *aux1 = (char*)cad1,
         *aux2 = (char*)cad2;

    while(*aux1 && *aux1 == *aux2)
    {
        aux1++;
        aux2++;
    }

    return *aux1 - *aux2;
}

char* mi_strchr(const char* cad, char c)
{
    char* aux = (char*)cad;

    while(*aux && *aux != c)
        aux++;

    return *aux ? aux : (c == '\0' ? aux : NULL);
}

char* mi_strrchr(const char* cad, char c)
{
    char* aux = (char*)cad;

    while(*aux)
        aux++;

    while(aux >= cad && *aux != c)
        aux--;

    return aux >= cad ? aux : NULL;
}

char* mi_strstr(const char* cad, const char* subCad)
{
    const char* auxCad = cad;
    const char* auxSubCad = subCad;

    while(*auxCad && *auxSubCad)
    {
        if(*auxCad == *auxSubCad)
        {
            auxSubCad++;
            auxCad++;
        }
        else
        {
            auxCad = cad + 1; // Va a empezar siempre en el siguiente caracter donde esté parado cad
            auxSubCad = subCad; // Se va reiniciando cada vez que algun caracter de la cadena principal no coincida
            cad++; // Cad se va moviendo caracter a caracter para ir cambiando el inicio de la subcadena a analizar
        }
    }

    return *auxSubCad ? NULL : (char*)cad;

//    char *auxCad = (char*)cad, *auxSubCad = (char*)subCad, *ini = (char*)cad;
//
//    while(*auxCad && *auxSubCad)
//    {
//        if(*auxCad == *auxSubCad)
//        {
//            auxSubCad++;
//            auxCad++;
//        }
//        else
//        {
//            if(auxSubCad != subCad)
//            {
//                auxSubCad = (char*)subCad;
//                ini = auxCad;
//            }
//            else
//            {
//                auxSubCad++;
//                auxCad++;
//            }
//        }
//
//    }
//
//    return *auxSubCad ? NULL : ini;
}

// Jonathan
// Nicolas
// Pobremos

