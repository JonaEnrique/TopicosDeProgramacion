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

typedef struct
{
    FILE* arch;
    Vector vec;
}DatosAccion;

void mostrarElemCompIdx_ALU(void* compActual, void* datosAccion);
void mostrarElemArmadoYRep_ALU(void* actArmaYRep, void* datosAccion);
int actualizarComponentes_ALU(const char* pathComponentes, const char* pathArmadoYRep);
void actCompDesdeIdxHaciaArch_ALU(void* elemArmadoYRep, void* datosAccion);
int cmpIdx_ALU(const void* elem1, const void* elem2);


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

    puts("Armados/Reparaciones:");
    mostrarArchivoArmadoYRep(argv[ARG_PATH_ARM_REP]);
    puts("");

    ///*********************************************************************************************************
    //int resp = actualizarComponentes(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
    ///******** Descomente la línea de abajo y comente la de arriba para probar su código **********************
    int resp = actualizarComponentes_ALU(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
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
///	Resolver.
/// Nota: Resuelva esta, y todas las funciones que necesite, en este archivo. Que será el que debe entregar. No modifique ni entregue otro/s archivos del proyecto.
/// Agregue el sufijo "_ALU" a todas las funciones que genere.
    char pathComponentesIdx[strlen(pathComponentes) + 1];

    obtenerPathIdx(pathComponentes, pathComponentesIdx);

    Vector vecComponentesIdx;
    crearVector(&vecComponentesIdx, 10, sizeof(IndComponente));
    cargarVector(pathComponentesIdx, &vecComponentesIdx, sizeof(IndComponente));

    Vector vecArmadoYRep;
    crearVector(&vecArmadoYRep, 30, sizeof(ArmadoYRep));
    cargarArmadosYRepEnVector(pathArmadoYRep, &vecArmadoYRep);

    DatosAccion datos;

    FILE* archComponentes = fopen(pathComponentes, "r+b");

    if(!archComponentes)
        return 0;

    datos.arch = archComponentes;
    datos.vec = vecComponentesIdx;

    recorrerVector(&vecArmadoYRep, actCompDesdeIdxHaciaArch_ALU, &datos);


    fclose(archComponentes);

//    recorrerVector(&vecComponentesIdx, mostrarElemCompIdx_ALU, (char*)pathComponentes);
//    recorrerVector(&vecArmadoYRep, mostrarElemArmadoYRep_ALU, NULL);

    // datosAccion ?

    return TODO_OK;
}

void mostrarElemCompIdx_ALU(void* compActual, void* datosAccion)
{
    IndComponente* indComp = (IndComponente*)compActual;
    t_Componente compLeido;

    FILE* archComp = fopen(datosAccion, "rb");

    if(!archComp)
        return;

    fseek(archComp, indComp->nroReg * sizeof(t_Componente), SEEK_SET);
    fread(&compLeido, sizeof(t_Componente), 1, archComp);

    printf("IND: %s %d - %s %s %d %f\n",
                           indComp->codigo
                          , indComp->nroReg
                          , compLeido.codigo
                          , compLeido.descripcion
                          , compLeido.stock
                          , compLeido.precioUnitario);

    fclose(archComp);
}

void mostrarElemArmadoYRep_ALU(void* actArmaYRep, void* datosAccion)
{
    ArmadoYRep* actAR = (ArmadoYRep*)actArmaYRep;

    printf("%d %s %d %f\n", actAR->nroOp, actAR->codigo, actAR->cantidad, actAR->precioUnitario);
}

void actCompDesdeIdxHaciaArch_ALU(void* elemArmadoYRep, void* datosAccion)
{
    DatosAccion* datos = (DatosAccion*)datosAccion;
    //ArmadoYRep* vecAYR = (ArmadoYRep*)elemArmadoYRep;
    Vector vecIndComponentes = datos->vec;
    FILE* archComponentes = datos->arch;

    t_Componente auxComp;
    IndComponente auxIndComp;

    strcpy(auxIndComp.codigo, ((ArmadoYRep*)elemArmadoYRep)->codigo);

    buscarEnVectorOrd(&vecIndComponentes, &auxIndComp, cmpIdx_ALU);

    fseek(archComponentes, auxIndComp.nroReg*sizeof(t_Componente), SEEK_SET);
    fread(&auxComp, sizeof(t_Componente), 1, archComponentes);

    if(auxComp.stock >= ((ArmadoYRep*)elemArmadoYRep)->cantidad)
        auxComp.stock -= ((ArmadoYRep*)elemArmadoYRep)->cantidad;

    auxComp.precioUnitario = ((ArmadoYRep*)elemArmadoYRep)->precioUnitario;

    fseek(archComponentes, -(long)sizeof(t_Componente), SEEK_CUR);

    fwrite(&auxComp, sizeof(t_Componente), 1, archComponentes);
}

int cmpIdx_ALU(const void* elem1, const void* elem2)
{
    return strcmp(((IndComponente*)elem1)->codigo, ((IndComponente*)elem2)->codigo);
}
