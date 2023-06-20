#include "header.h"

/**

    Texto fijo:     12345678sadsfdfdsfsdf       8.50\n
    Texto variable  12354|maria pia|8.5\n

    EJERCICIO
    B->TF->TV->B
**/

int main()
{
    crearLote(NOMB_ARCH_BIN);

    leerArchivoBinGen(NOMB_ARCH_BIN, sizeof(Alumno), mostrarAlumnos);   //crea arch bin

    archBinATxtFij(NOMB_ARCH_BIN, NOMB_ARCH_BTF, sizeof(Alumno), leerTxtFijo); // pasa de Bin a Text Fijo

    pasarDeTxtFijoATxtVar(NOMB_ARCH_BTF, NOMB_ARCH_TFV, sizeof(Alumno), trozarArchFijo, leerTxtVar);    //pasar de texto fijo a texto variable

    pasarDeTxtVarABin(NOMB_ARCH_TFV,NOMB_ARCH_TVB, sizeof(Alumno), trozarArchVar, escribirBin);

    printf("\nEs este:\n");
    leerArchivoBinGen(NOMB_ARCH_TVB, sizeof(Alumno), mostrarAlumnos);

    return 0;
}


