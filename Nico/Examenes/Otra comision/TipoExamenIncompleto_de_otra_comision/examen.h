#ifndef EXAMEN_H_INCLUDED
#define EXAMEN_H_INCLUDED

#define MAX_COL 100
#define MAXNOMEMP 31
typedef struct{
    int dni;
    char nomYAp[MAXNOMEMP];
    double sueldo;
}tEmpleado;


void* _ordenarSeleccion(void* vec, int ce, unsigned tam, int cmp(const void*, const void*));
int _cmpEmpleadoNombre(const void*, const void*);
int _cmp_enteros(const void* a, const void* b);
int _cmp_str(const void* a, const void* b);
char* _mstrstr(const char *s1, const char *s2);


int cmpEmpleadoNombre(const void*, const void*);
int cmp_enteros(const void* a, const void* b);
int cmp_str(const void* a, const void* b);
void* ordenarSeleccion(void* vec, int ce, unsigned tam, int cmp(const void*, const void*));
char* mstrstr(const char *s1, const char *s2);
#endif // EXAMEN_H_INCLUDED
