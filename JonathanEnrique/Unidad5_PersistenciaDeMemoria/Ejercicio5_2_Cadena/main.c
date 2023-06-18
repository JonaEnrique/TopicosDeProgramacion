#include "main.h"

int main()
{
    char cad[] = "Hola holaaaaaaaaaaaaaaaaaaaaaaaa Hola como estasHola";
    Palabra primeraPalabra;
    int cantPPEnCad;

    buscarPrimeraPalabra(cad, &primeraPalabra);
    cantPPEnCad = contarPalabraEnCad(cad, &primeraPalabra);

    printf("La primera palabra es ");
    mostrarPalabra(&primeraPalabra);
    printf(" y su cantidad de repeticiones en texto es %d", cantPPEnCad);

    printf("\nCantidad: %d\n", contarPalabrasEnCad(cad));

    printf("La longitud de la palabra mas larga es: %d", longPalMasLarga(cad));

    return 0;
}


int cmpPalabra(Palabra* p1, Palabra* p2)
{
    char  *cPal1 = p1->iniPal,
          *cPal2 = p2->iniPal;

    while(cPal1 <= p1->finPal && cPal2 <= p2->finPal && *cPal1 == *cPal2)
    {
        cPal1++;
        cPal2++;
    }

    if(cPal1 > p1->finPal && cPal2 > p2->finPal)
        return 0;
    else if(cPal1 > p1->finPal)
        return -1;
    else if(cPal2 > p2->finPal)
        return 1;
    else
        return *cPal1 - *cPal2;
}

int buscarPrimeraPalabra(const char *cad, Palabra *primeraPalabra)
{
    char  *cCad = (char*)cad;

    while(*cCad && !esLetra(*cCad))
        cCad++;

    if(!*cCad)
        return 0;

    primeraPalabra->iniPal = cCad;

    while(*cCad && esLetra(*cCad))
        cCad++;

    primeraPalabra->finPal = cCad - 1;

    cCad++;

    return 1;
}

int contarPalabraEnCad(const char *cad, Palabra *pal)
{
    char  *cCad = (char*)cad;
    Palabra cPal;
    int contPal = 0;

    while(*cCad)
    {
        while(*cCad && !esLetra(*cCad))
            cCad++;

        if(!*cCad)
            return 0;

        cPal.iniPal = cCad;

        while(*cCad && esLetra(*cCad))
            cCad++;

        cPal.finPal = cCad - 1;

        if(cmpPalabra(&cPal, pal) == 0)
            contPal++;
    }

    return contPal;
}

int contarPalabrasEnCad(const char *cad)
{
    char  *cCad = (char*)cad;
    int contPal = 0;

    while(*cCad)
    {
        while(*cCad && !esLetra(*cCad))
            cCad++;

        if(!*cCad)
            return 0;

        while(*cCad && esLetra(*cCad))
            cCad++;

        contPal++;
    }

    return contPal;
}

int strlen_pal(Palabra* pal)
{
    char  *cPal = pal->iniPal;
    int cont = 0;

    while(cPal <= pal->finPal)
    {
        cont++;
        cPal++;
    }

    return cont - 1;
}

int longPalMasLarga(const char *cad)
{
    char  *cCad = (char*)cad;
    int maxLongPal,
        primera = 1,
        longPal;
    Palabra tempPal;

    while(*cCad)
    {
        while(*cCad && !esLetra(*cCad))
            cCad++;

        if(!*cCad)
            return 0;

        tempPal.iniPal = cCad;

        while(*cCad && esLetra(*cCad))
            cCad++;

        tempPal.finPal = cCad;

        if(primera)
        {
            maxLongPal = strlen_pal(&tempPal);
            primera = 0;
        }
        else
        {
            if((longPal = strlen_pal(&tempPal)) > maxLongPal)
                maxLongPal = longPal;
        }
    }

    return maxLongPal;
}

void mostrarPalabra(Palabra* p)
{
    char  *cPal = p->iniPal;

    while(cPal <= p->finPal)
    {
        printf("%c", *cPal);
        cPal++;
    }
}

