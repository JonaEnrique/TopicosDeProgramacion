#include <stdio.h>
#include <stdlib.h>
#include "../BibliotecaArchivos/Archivo.h"

int main()
{
    FILE* arch;

    if(!abrirArchivo(&arch, "Prueba.dat", "rb", true))
        exit(1);

    fclose(arch);

    return 0;
}
