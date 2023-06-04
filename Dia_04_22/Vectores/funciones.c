#include "funciones.h"

int insertarEnVectorOrd(int *vec, int *ce, int tam, int elem)
{
    if(*ce == tam)
        return VEC_LLENO;

    int posIns = buscarPosIns(vec, *ce, elem);

    if(elem == vec[posIns])
        return DUPLICADO;

    for(int i = (*ce) - 1; i >= posIns; i--)
        vec[i+1] = vec[i];

    vec[posIns] = elem;

    (*ce)++;

    return TODO_OK;
}

int buscarPosIns(int *vec, int ce, int elem)
{
    int li = 0, ls  = ce -1, n, comp;

    bool encontrado = false;

    while(!encontrado && li <= ls)
    {
        n = (li+ls)/2;

        comp = elem - vec[n];
        if(comp == 0)
            encontrado = true;

        if(comp < 0)
            ls = n - 1;

        if(comp > 0)
            li = n + 1;
    }

    return encontrado ? n : li;
}

void mostrarVector(int* vec, int ce)
{
    int* cursorVec = vec;

    for(int i = 0; i < ce; i++)
    {
        printf("%d\n", *cursorVec);
        cursorVec++;
    }
}

//int eliminarVecOrd(int* vec, int ce, int elem)
//{
//    for(i = 0; i < ce; i++)
//    {
//        if(elem > )
//    }
//}
