#include "Archivo.h"

bool abrirArchivo(FILE** fp, const char* nombreArchivo, const char* modoApertura, bool mostrarError)
{
    *fp = fopen(nombreArchivo, modoApertura);

    if(*fp == NULL)
    {
        if(mostrarError)
            printf("Error al crear archivo %s con modo de apertura %s.", nombreArchivo, modoApertura);

        return false;
    }

    return true;
}

