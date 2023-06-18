#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool abrirArchivo(FILE** fp,
                  const char* nombreArchivo,
                  const char* modoApertura,
                  bool mostrarError);

#endif // ARCHIVO_H
