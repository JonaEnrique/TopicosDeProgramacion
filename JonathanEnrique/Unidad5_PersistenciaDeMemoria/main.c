#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool abrirArchivo(FILE** fp, const char* nombreArchivo, const char* modoApertura, int mostrarError);

int main()
{
    printf("Hello world!\n");
    return 0;
}

bool abrirArchivo(FILE** fp, const char* nombreArchivo, const char* modoApertura, int mostrarError)
{
    *fp = fopen(nombreArchivo, modoApertura);

    if(*fp == NULL)
    {
        if (mostrarError == 1)
        {
            fprintf(stderr, "Error abriendo \"%s\" en modo \"%s\".",
            nombreArchivo,
            modoApertura);

            return 0;
        }
        
    }
}
