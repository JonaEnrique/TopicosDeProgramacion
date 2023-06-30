/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:
*
* DNI:
*
****************************************************************************************/

#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include "../SolucionParcialArmadoPCTopicos/TiposArmadoPC.h"
#include "../SolucionParcialArmadoPCTopicos/SolucionParcialArmadoPC.h"


#define ARG_PATH_COMP 1
#define ARG_PATH_ARM_REP 2

void mostrarArchivoComponentes_ALU(const char* pathComponentes);
void mostrarArchivoArmadoYRep_ALU(const char* pathArm);
void trozadoVariable(char* vector, ArmadoYRep* estruct);
int actualizarComponentes_ALU(const char* nombreComponentes, const char* nombreArmadoYRep);
void agregarIndexado(char* path);
int crearVector_ALU(Vector* vec, int cap, size_t tamElem);
void cargarVector_ALU(const char* nombreArch, Vector* vector, size_t tamElem);


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "spanish");	// Cambiar locale - Suficiente para máquinas Linux
    SetConsoleCP(1252); 			// Cambiar STDIN -  Para máquinas Windows
    SetConsoleOutputCP(1252);		// Cambiar STDOUT - Para máquinas Windows

    generarArchivoStockComponentes(argv[ARG_PATH_COMP]);

    generarArchivoArmadosYReparaciones(argv[ARG_PATH_ARM_REP]);

    puts("Componentes antes de actualizar:\n");
    mostrarArchivoComponentes(argv[ARG_PATH_COMP]);
    puts("");
    puts("\nComponentes antes de actualizar:\n");
    mostrarArchivoComponentes_ALU(argv[ARG_PATH_COMP]);
    puts("");

    puts("Armados/Reparaciones:");
    mostrarArchivoArmadoYRep(argv[ARG_PATH_ARM_REP]);
    puts("");
    puts("\nArmados/Reparaciones:");
    mostrarArchivoArmadoYRep_ALU(argv[ARG_PATH_ARM_REP]); /// OJO LA MIA ESTA REVELANDO UNO MAS QUE NO FIGURA EN EL ORIGINAL.
    puts("");

    ///*********************************************************************************************************
    int resp = actualizarComponentes(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
    ///******** Descomente la línea de abajo y comente la de arriba para probar su código **********************
    //int resp = actualizarComponentes_ALU(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
    ///*********************************************************************************************************

    if(resp != TODO_OK)
    {
        puts("Error actualizando los componentes.");
        return resp;
    }

    puts("\nComponentes despues de actualizar:\n");
    mostrarArchivoComponentes(argv[ARG_PATH_COMP]);

//	getchar();

    return 0;
}





int actualizarComponentes_ALU(const char* pathComponentes, const char* pathArmadoYRep)
{
    /// creo el nombre para archivo indice asi lo abro y paso a vector dinamico.
    char pathComponentesIndexados[100];
    int tamanioPath = strlen(pathComponentes);
    strncpy(pathComponentesIndexados,pathComponentes,tamanioPath);
    pathComponentesIndexados[100]='\0';
    agregarIndexado(pathComponentesIndexados);


    int estado = 0;
    FILE* fpCompBin = fopen(pathComponentes, "r+b");
    FILE* fpArmYRepTxt = fopen(pathArmadoYRep, "rt");
    FILE* fpCompIdxBin = fopen(pathComponentesIndexados, "rb");

    /// Inicio - crear vector dinamico de indice.
    fseek(fpCompIdxBin, 0L, SEEK_END);
    int tamanioIndexado = ftell(fpCompIdxBin);
    fseek(fpCompIdxBin, 0L, SEEK_SET);

    Vector* vecCompIdx;
    estado = int crearVector_ALU(vecCompIdx, tamanioIndexado, sizeof(IndComponente))
    if(estado!=0)
    {
        puts("Falla al crear vector dinamico de componentes indexados.\n")
    }
    cargarVector_ALU(pathComponentesIndexados, vecCompIdx, size_t tamElem)

    /// Fin - crear vector dinamico de indice.



    return estado;
}

void mostrarArchivoComponentes_ALU(const char* pathComponentes)
{
    FILE* fpBin = fopen(pathComponentes, "rb");
    if(!fpBin)
    {
        printf("No se logro abrir %s.", pathComponentes);
    }

    t_Componente componentes;

    printf("Codigo\t\t\tDescripcion\t\t\tStock\tPrecio\tUnitario\n");
    printf("===============================================================================\n");
    fread(&componentes, sizeof(t_Componente), 1, fpBin);
    while(!feof(fpBin))
    {
        printf("%-20s\t%-30s\t  %d\t%9.2f\n", componentes.codigo, componentes.descripcion, componentes.stock, componentes.precioUnitario); /// PREGUNTAR POR ARREGLO RARO DE ESPACIO
        fread(&componentes, sizeof(t_Componente), 1, fpBin);
    }

    fclose(fpBin);
}

void mostrarArchivoArmadoYRep_ALU(const char* pathArm)
{
    FILE* fpTxt = fopen(pathArm, "rt");
    ArmadoYRep estruct;
    char vector[200];

    if(!fpTxt)
    {
        printf("No se logro abrir %s.", pathArm);
    }

    fgets(vector, sizeof(ArmadoYRep), fpTxt);
    while(!feof(fpTxt))
    {
        trozadoVariable(vector, &estruct);
        printf("   %d\t%-21s\t   %d\t%9.2f\n", estruct.nroOp, estruct.codigo, estruct.cantidad, estruct.precioUnitario);
        fgets(vector, sizeof(ArmadoYRep), fpTxt);
    }

    fclose(fpTxt);
}

void trozadoVariable(char* vector, ArmadoYRep* estruct)
{
    char* cursor = strchr(vector, '\n');
    *cursor = '\0';
    if(!cursor)
    {
        puts("Error linea larga.");
    }

    cursor = strrchr(vector, '|');
    sscanf(cursor+1,"%lf", &estruct->precioUnitario);
    *cursor = '\0';;

    cursor = strrchr(vector, '|');
    sscanf(cursor+1,"%d", &estruct->cantidad);
    *cursor = '\0';

    cursor = strrchr(vector, '|');
    strncpy(estruct->codigo, cursor+1, 21);
    estruct->codigo[21]='\0';
    *cursor = '\0';

    sscanf(vector, "%d", &estruct->nroOp);
}

void agregarIndexado(char* path)
{
    char* cursorPath = path;
    while(*path!='.')
        cursorPath++;
    *(cursorPath+1)='\0';
    strcat(path, "idx");
}

int crearVector_ALU(Vector* vec, int cap, size_t tamElem)
{
    vec = (Vector*) malloc(cap*tamElem);
    vec->
    if(!Vector)
        return SIN_MEM;
    vec->
    return TODO_OK;
}

void cargarVector_ALU(const char* nombreArch, Vector* vector, size_t tamElem)
{

}
