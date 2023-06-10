#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_VEC 10
#define TAM_VEC_PERSONA 15

typedef struct
{
    int dni;
    char apellido[20];
    char nombres[30];
    float peso;
}Persona;

int compararEntero(const void* arg1, const void* arg2); // Ejercicio 3.9
int compararPersonaDNI(const void* arg1, const void* arg2); // Ejercicio 3.10
int compararPersonaNombreYApellido(const void* arg1, const void* arg2); // Ejercicio 3.11
int buscarXdni(const Persona *p, Persona *d); // No le hace falta la cantidad de elementos?? -> // Ejercicio 3.12
int buscarXnombresApellido(const Persona *p, Persona *d); // No le hace falta la cantidad de elementos?? -> // Ejercicio 3.13

void mostrarVecEntero(int* vec, int ce);
void mostrarVecPer(Persona* vecPer, int ce);

int main(int argc, char* argv[])
{
    for(int i = 0; i < argc; i++){
        printf("Parametro %d: %s\n", i, argv[i]);
    }

    int num1 = atoi(argv[1]), num2 = atoi(argv[2]), resu;
    char* operador = argv[3];

    if(*operador == '+')
        resu = num1 + num2;
    else if(*operador == '-')
            resu = num1 - num2;
         else if(*operador == '*')
                resu = num1 * num2;
              else
                resu = num1 / num2;

    printf("\nResultado: %d\n", resu);

//    int vec[TAM_VEC] = {2, 1, 3, 5, 6, 8, 9, 10, 7, 4};
//    Persona vecPer[TAM_VEC_PERSONA] = { {12345678, "Lopez", "Juan", 70.5},
//        {98765432, "Garcia", "Maria", 62.3},
//        {56789012, "Rodriguez", "Carlos", 80.0},
//        {34567890, "Fernandez", "Luisa", 55.8},
//        {78901234, "Gonzalez", "Pedro", 68.2},
//        {55555555, "Torres", "Ana", 58.6},
//        {22222222, "Martinez", "Pablo", 75.0},
//        {99999999, "Sanchez", "Laura", 61.4},
//        {11111111, "Perez", "Lucia", 63.7},
//        {22223333, "Romero", "Gabriel", 67.9},
//        {44445555, "Luna", "Valeria", 55.2},
//        {77778888, "Silva", "Diego", 72.6},
//        {99999988, "Mendoza", "Sofia", 59.8},
//        {11110000, "Cruz", "Matias", 64.1},
//        {34543678, "Lopez", "Alberto", 70.5} };
//
//    qsort(vec, TAM_VEC, sizeof(vec[0]), compararEntero);
//    qsort(vecPer, TAM_VEC_PERSONA, sizeof(Persona), compararPersonaNombreYApellido);
//    Persona buscado = {5, "Lopez", "Juan", 87.03};
//    // buscarXdni(vecPer, &buscado);
//    buscarXnombresApellido(vecPer, &buscado);
//
//    printf("Ordenamiento de enteros:\n");
//    mostrarVecEntero(vec, TAM_VEC);
//    printf("Ordenamiento de personas:\n");
//    mostrarVecPer(vecPer, TAM_VEC_PERSONA);

    return 0;
}

int compararEntero(const void* arg1, const void* arg2)
{
    return -1 * (*(int*)arg1 - *(int*)arg2);
}

void mostrarVecEntero(int* vec, int ce)
{
    int* finVec = vec + ce;

    for(int* i = vec; i < finVec; i++){
        printf("%d ", *i);
    }

    printf("\n");
}

int compararPersonaDNI(const void* arg1, const void* arg2)
{
    return ((Persona*)arg1)->dni - ((Persona*)arg2)->dni;
}

void mostrarVecPer(Persona* vecPer, int ce)
{
    Persona* finVec = vecPer + ce;

    for(Persona* i = vecPer; i < finVec; i++){
        printf("%d %s %s %f", i->dni, i->apellido, i->nombres, i->peso);
        printf("\n");
    }
}

int compararPersonaNombreYApellido(const void* arg1, const void* arg2)
{
    int cmpNom = strcmp(((Persona*)arg1)->nombres, ((Persona*)arg2)->nombres);
    int cmpApell = strcmp(((Persona*)arg1)->apellido, ((Persona*)arg2)->apellido);

    //return cmpNom != 0 ? cmpNom : cmpApell;
    return cmpApell != 0 ? cmpApell : cmpNom;
}

int buscarXdni(const Persona *p, Persona *d)
{
    int encontrado = 0;
    Persona* finVecPer = (Persona*)p + TAM_VEC_PERSONA - 1;

    for(Persona* i = (Persona*)p; i <= finVecPer && !encontrado; i++){
        if(i->dni == d->dni){
            strcpy(i->nombres, d->nombres);
            strcpy(i->apellido, d->apellido);
            i->peso = d->peso;

            encontrado = 1;
        }
    }

    return encontrado;
}

int buscarXnombresApellido(const Persona *p, Persona *d)
{
    int encontrado = 0, cmp1, cmp2;
    Persona* finVecPer = (Persona*)p + TAM_VEC_PERSONA - 1;

    for(Persona* i = (Persona*)p; i <= finVecPer && !encontrado; i++){
        if((cmp1 = strcmp(i->nombres, d->nombres)) == 0 && (cmp2 = strcmp(i->apellido, d->apellido) == 0)){
            i->dni = d->dni;
            i->peso = d->peso;

            encontrado = 1;
        }
    }

    return encontrado;
}
