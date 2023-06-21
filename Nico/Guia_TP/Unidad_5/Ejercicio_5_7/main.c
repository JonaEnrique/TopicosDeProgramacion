#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int dni;
    char ape[15];
    char nom[15];
    float promedio;
}tAlumno;

typedef struct
{
    int dni;
    char ape[15];
    char nom[15];
    double sueldo;
}tEmpleado;

int crearArchivoEmpleado(char* nombreArchivo, tEmpleado* estructura, int cantElem);
int crearArchivoAlumno(char* nombreArchivo, tAlumno* estructura, int cantElem);
int abrirArchivo(FILE** fp, const char* nombreArchivo, const char* modoApertura, int mostrarError);
int leerYmostraArchivo(char* nombreArchivo);
void actualizarPorcentajeSueldo(FILE* fpEmpleados, FILE* fpAlumnos, float porcentaje);
void mostrarEmpleado(const tEmpleado *emp);

int main()
{
    tEmpleado vectorEmpleados[] = {
    {120000, "Audo", "Beme", 120000},
    {245666, "Audo", "Cicu", 130000},
    {348970, "Dodora", "Maca", 140000},
    {424703, "Nahuel", "Escala", 150000},
    {526874, "Pepe", "Cipres", 160000},
    {632465, "Roberto", "La Pantera", 170000},
    {765468, "Xalam", "Blanco", 180000}
    };

    tAlumno vectorAlumnos[] = {
    {120000, "Audo", "Beme", 7},
    {245666, "Audo", "Cicu", 7},
    {348970, "Dodora", "Maca", 8},
    {424703, "Nahuel", "Escala", 9},
    {526874, "Pepe", "Cipres", 6.5},
    {632465, "Roberto", "La Pantera", 7},
    {765468, "Xalam", "Blanco", 6.5}
    };

    /*
    tAlumno vectorAlumnos[] = {
    {120000, "Audo", "Beme", 120000},
    {245666, "Audo", "Cicu", 140000},
    {348970, "Dodora", "Maca", 150000},
    {424703, "Miguelito", "Maca", 160000},
    {526874, "Pepe", "Cipres", 189000},
    {632465, "Roberto", "La Pantera", 200000},
    {765468, "Vito", "Escalone", 195000}
    };
    */ /// Descartado, voy a pasar uno que esten todas las personas en ambos vectores.

    FILE* fpEmpleados;
    FILE* fpAlumnos;

    crearArchivoEmpleado("Empleados.bin", vectorEmpleados, (sizeof(vectorEmpleados)/sizeof(tEmpleado)));
    crearArchivoAlumno("Alumnos.bin", vectorAlumnos, (sizeof(vectorAlumnos)/sizeof(tAlumno)));

    abrirArchivo(&fpEmpleados, "Empleados.bin", "r+b", 1);
    abrirArchivo(&fpAlumnos, "Alumnos.bin", "rb", 1);

    actualizarPorcentajeSueldo(fpEmpleados, fpAlumnos, 7.28);

    fclose(fpEmpleados);
    fclose(fpAlumnos);

    leerYmostraArchivo("Empleados.bin");
    return 0;
}

/*
int crearArchivoEmpleado(char* nombreArchivo, tEmpleado* estructura)
{
    tEmpleado vectorEmpleados[] = {
    {120000, "Audo", "Beme", 120000},
    {245666, "Audo", "Cicu", 140000},
    {348970, "Dodora", "Maca", 150000},
    {424703, "Nahuel", "Escala", 160000},
    {526874, "Pepe", "Cipres", 189000},
    {632465, "Roberto", "La Pantera", 200000},
    {765468, "Xalam", "Blanco", 195000}
    };
    FILE *fp = fopen(nombreArchivo, "wb");
    if(fp)
    {
        fwrite(vectorEmpleados, sizeof(vectorEmpleados), 1, fp);
        fclose(fp);
        return 0;
    }
    return -2;
}
*/
/*
int crearArchivoAlumno(char* nombreArchivo, tAlumno* estructura)
{
    tAlumno vectorAlumnos[] = {
    {120000, "Audo", "Beme", 7},
    {245666, "Audo", "Cicu", 7},
    {348970, "Dodora", "Maca", 8},
    {424703, "Nahuel", "Escala", 9},
    {526874, "Pepe", "Cipres", 6.5},
    {632465, "Roberto", "La Pantera", 7},
    {765468, "Xalam", "Blanco", 6.5}
    };
    FILE *fp = fopen(nombreArchivo, "wb");
    if(fp)
    {
        fwrite(vectorAlumnos, sizeof(vectorAlumnos), 1, fp);
        fclose(fp);
        return 0;
    }
    return -2;
}
*/

int crearArchivoEmpleado(char* nombreArchivo, tEmpleado* estructura, int cantElem)
{
    FILE *fp;
    if(abrirArchivo(&fp, nombreArchivo, "wb", 1))
    {
        fwrite((estructura), sizeof(tEmpleado), cantElem, fp); /// FIX HORRENDO QUE PERMITE QUE ANDE FWRITE, PARA SEGUNDO PARAMETRO (NUM BYTES) TOMAR SIZEOF(PUNTERO)*SIZEOF(ESCTRUCTURA)-1
        fclose(fp);
        return 0;
    }
    return -2;
}

int crearArchivoAlumno(char* nombreArchivo, tAlumno* estructura, int cantElem)
{
    FILE *fp;
    if(abrirArchivo(&fp, nombreArchivo, "wb", 1))
    {
        fwrite(estructura, sizeof(tAlumno), cantElem, fp);
        fclose(fp);
        return 0;
    }
    return -2;
}

int abrirArchivo(FILE** fp, const char* nombreArchivo, const char* modoApertura, int mostrarError)
{
    *fp = fopen(nombreArchivo, modoApertura);
    if(*fp==NULL)
    {
        if(mostrarError == 1)
        {
            fprintf(stderr,
                    "Error al abrir \"%s\" en modo \"%s\".", nombreArchivo, modoApertura);
        }
        return 0;
    }
    return 1;
}

void actualizarPorcentajeSueldo(FILE* fpEmpleados, FILE* fpAlumnos, float porcentaje)
{
    tEmpleado emp;
    tAlumno alu;
    long posInicialAlu = ftell(fpAlumnos);
    long posInicialEmp = ftell(fpEmpleados);
    rewind(fpEmpleados);
    rewind(fpAlumnos);

    fread(&emp, sizeof(tEmpleado), 1, fpEmpleados);
    fread(&alu, sizeof(tAlumno), 1, fpAlumnos);
    while(!feof(fpAlumnos) && !feof(fpAlumnos))
    {
        if(alu.promedio > 7)
            emp.sueldo *= porcentaje;
        fseek(fpEmpleados, -(long)sizeof(tEmpleado), SEEK_CUR);
        fwrite(&emp, sizeof(tEmpleado), 1, fpEmpleados);
        fseek(fpEmpleados, 0L, SEEK_CUR); // actualizo cursor para poder volver a leer
        fread(&emp, sizeof(tEmpleado), 1, fpEmpleados);
        fread(&alu, sizeof(tAlumno), 1, fpAlumnos);
    }

    fseek(fpEmpleados, posInicialEmp, SEEK_SET);
    fseek(fpAlumnos, posInicialAlu, SEEK_SET);
}

int leerYmostraArchivo(char* nombreArchivo)
{
    tEmpleado emp;
    FILE *fp = fopen(nombreArchivo, "rb");
    if(!fp)
    {
        return -1;
    }
    fread(&emp, sizeof(tEmpleado), 1, fp);
    while(!feof(fp))
    {
        mostrarEmpleado(&emp);
        fread(&emp, sizeof(tEmpleado), 1, fp);
    }
    fclose(fp);
    return 0;
}

void mostrarEmpleado(const tEmpleado *emp)
{
    printf("%d, %s , %s, %10f\n", emp->dni, emp->ape, emp->nom, emp->sueldo);
}





