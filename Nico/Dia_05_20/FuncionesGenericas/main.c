#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_VEC 10

typedef int (*Cmp)(const void* , const void*);

void ordenarVectorSeleccion(void* v, int ce, size_t tamElem, Cmp cmp);
void intercambiar(void* x, void* y, size_t tamElem);
void* buscarMenor(void* ini, void* fin, size_t tamElem, Cmp cmp);

int cmpInt(const void* entero1, const void* entero2);

void mostrarVector(int* vec, int cantElem);

int main()
{
    int vec[TAM_VEC] = {4, 8, 7, 9, 5, 0, 1};
    int ce = 7;

    mostrarVector(vec, ce);

    ordenarVectorSeleccion(vec, ce, sizeof(int), cmpInt);

    mostrarVector(vec, ce);

    return 0;
}

void ordenarVectorSeleccion(void* v, int ce, size_t tamElem, Cmp cmp)
{
  void *m, *ult = v + (ce*tamElem);

  for(void* i = v; i < ult; i += tamElem)
  {
    m = buscarMenor(i, ult, tamElem, cmp);

    if(m != i)
      intercambiar(m, i, tamElem);
  }
}

void intercambiar(void* x, void* y, size_t tamElem)
{
  void* xTemp = malloc(tamElem);
  if(!xTemp){puts("Sin mem");return;}

  memcpy(xTemp, x, tamElem);
  memcpy(x, y, tamElem);
  memcpy(y, xTemp, tamElem);

  free(xTemp);
}

void* buscarMenor(void* ini, void* fin, size_t tamElem, Cmp cmp)
{
  void* m = ini;

  for(void* j = ini + tamElem; j < fin; j += tamElem)
  {
    if(cmp(j, m) < 0)
      m = j;
  }

  return m;
}

int cmpInt(const void* entero1, const void* entero2)
{
  return *(int*)entero1 - *(int*)entero2;
}

void mostrarVector(int* vec, int cantElem)
{
  int* fin = vec + cantElem;

  for(int* i = vec; i < fin; i++)
    printf("%d ", *i);

  printf("\n");
}
