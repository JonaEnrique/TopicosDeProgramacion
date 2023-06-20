#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NOMB_ARCH_BIN "alumnos.dat"
#define NOMB_ARCH_BTF "alumnosBTF.txt"
#define NOMB_ARCH_TFV "alumnosTFV.txt"
#define NOMB_ARCH_TVB "alumnosTVB.dat"

typedef struct
{
    int dni;
    char nombre[30];
    float nota;

} Alumno;

void crearLote(const char *nombreArchBin);
void leerArchivoBinGen(const char *nombreArch, size_t cantBytes, void mostrar(const void *dato));
void mostrarAlumnos(const void *dato);
void leerTxtFijo(FILE *pArch, const void *dato);
void archBinATxtFij(const char *nombreArchBin, const char *nombreArchTxt, size_t cantBytes, void accion(FILE *pArch, const void *dato));
void pasarDeTxtFijoATxtVar(const char *nomArchFij, const char *nomArchVar, size_t cantBytes, void trozar(void *dato, char *cad),void accion(FILE *pArch, const void *dato));
void pasarDeTxtVarABin(const char *nomArchVar, const char *nomArchBin, size_t cantBytes, void trozar(void *dato, char *cad), void accion(FILE *pArch, const void *dato));
void leerTxtVar(FILE *pArch, const void *dato);
void escribirBin(FILE *pArch, const void *dato);
void trozarArchFijo(void *dato, char *cad);
void trozarArchVar(void *dato, char *cad);


#endif // HEADER_H_INCLUDED
