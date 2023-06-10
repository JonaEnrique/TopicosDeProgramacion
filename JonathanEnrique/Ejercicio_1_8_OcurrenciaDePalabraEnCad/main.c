#include <stdio.h>
#include <stdlib.h>

int ocurrenciasEnCad(const char* text, const char* cad);

int main()
{
    char text[] = "Hola Mundo, Hola mundoHoMundo\n";
    char cadABuscar[] = "Hola Mundo";

    printf("Cantidad de  ocurrencias: %d\n", ocurrenciasEnCad(text, cadABuscar));

    return 0;
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
