#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>

#define TODO_OK 0
#define VEC_LLENO 1
#define DUPLICADO 2


int insertarEnVectorOrd(int *vec, int *ce, int tam, int dem);
int buscarPosIns(int* vec, int ce, int elem);
int eliminarVecOrd(int* vec, int ce, int elem);
void mostrarVector(int* vec, int ce);

#endif // FUNCIONES_H_INCLUDED
