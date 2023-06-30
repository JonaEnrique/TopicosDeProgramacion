/*#include <stdio.h>

void* _ordenarSeleccion(void* vec, int ce, unsigned tam, int cmp(const void*, const void*)){
    return NULL;
}
int _cmpEmpleadoNombre(const void* a, const void* b){
    return -1;
}

int _cmp_enteros(const void* a, const void* b){
    return -1;
}

int _cmp_str(const void* a, const void* b){
    return -1;
}

char* _mstrstr(const char *s1, const char *s2){
    return NULL;
}

*/

#include <stdio.h>
#include <stdlib.h>
#include "examen.h"
#include <ctype.h>
#include <string.h>

void* _ordenarSeleccion(void* vec, int ce, unsigned tam, int cmp(const void*, const void*))
{

    void* pvec = (char*)vec+tam;
    void* aux;
    int cant = 0, cant2 = 0;

    while(cant < ce-1)
    {
        cant2 = cant;
        while(cant2 < ce-1)
        {
            if(cmp(vec,pvec) > 0)
            {
                aux = malloc(tam);
                memcpy(aux,vec,tam);
                memcpy(vec,pvec,tam);
                memcpy(pvec,aux,tam);
                free(aux);
            }
            cant2++;
            pvec= (char*)pvec+tam;
        }

        vec = (char*)vec+tam;
        pvec = (char*)vec+tam;
        cant++;
    }

    return NULL;
}
int _cmpEmpleadoNombre(const void* a, const void* b)
{
    const tEmpleado* valor1 = (const tEmpleado*) a;
    const tEmpleado* valor2 = (const tEmpleado*) b;

    return _cmp_str(valor1->nomYAp ,valor2->nomYAp);

}

int _cmp_enteros(const void* a, const void* b)
{
    const int* valor1 = (const int*)a;
    const int* valor2 = (const int*)b;

    return (*valor1-(*valor2));
}

int _cmp_str(const void* a, const void* b)
{
    const char* valor1 = (const char*) a;
    const char* valor2 = (const char*) b;

    while(*valor1 && *valor2 && (*valor1 == *valor2))
    {
        valor1++;
        valor2++;
    }
    return (*valor1-*valor2);
}

char* _mstrstr(const char *s1, const char *s2)
{
    const char* cad1 = s1;
    const char* cad2 = s2;
    int cont= strlen(cad2);

    while(*cad1 && *cad2)
    {
        if(*cad1 == *cad2)
        {
            cad2++;
        }
        else
        {
            cad2 = s2;
        }
        cad1++;

    }
    if(!*cad2)
    {
        return ((char*) cad1 - cont);
    }
    return NULL;
}
