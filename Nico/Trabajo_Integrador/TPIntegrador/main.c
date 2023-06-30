#include "Integrador.h"

#define ARCH_ALUMNO 1

int main(int argc, char* argv[])
{
    /// CREAR VECTOR INDICE EN FUNCION Y CREAR MEMORIA DINAMICA ADENTRO DE FUNCION CON MALLOC DENTRO DE PUNTERO (NO MUERE EN FUNCION QUEDA EN HEAP RECORDAR LIBERAR)
    tAlumno vecAlum[] = {
                        { 12345678, "Perez, Juan", { 1, 1, 1990 }, 'M', { 1, 1, 2010 }, "ISI", 45, 'A' },
                        { 87654321, "Gomez, Maria", { 1, 1, 1990 }, 'F', { 1, 1, 2010 }, "ISI", 34, 'A' },
                        { 49887745, "Rolomeo, Benjamin", {1, 12, 1994}, 'M', {1,1,2010}, "ISI", 15, 'A'}
                        };
    Fecha fechaPrograma;
    tIndiceAlumno* indiceAlumnos;
    int cantElemIndice = 0;

    /// PARA TESTEO RAPIDO
    fechaPrograma.anio = 2023;
    fechaPrograma.dia = 04;
    fechaPrograma.mes = 05;

    if(esFechaValida(&fechaPrograma)==0)
        puts("Fecha invalida");
    crearArchivo(argv[ARCH_ALUMNO], vecAlum, sizeof(vecAlum)/sizeof(tAlumno));
    //fechaPrograma = ingresarFecha(); // SALTEO PARA HACER TESTEOS.
    validarArchivo(argv[ARCH_ALUMNO]);
    indiceAlumnos = crearIndiceDinamico(argv[ARCH_ALUMNO], &cantElemIndice );
    menu(indiceAlumnos, argv[ARCH_ALUMNO], &cantElemIndice, &fechaPrograma);
    free(indiceAlumnos); /// termine de usar memoria dinamica para indice.

    return 0;
}
