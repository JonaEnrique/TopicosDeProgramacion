#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Fecha/Fecha.h"
#include "../SolucionParcialPlazosFijosTopicos/SolucionParcialPlazosFijos.h"


/*

VECTOR ORDENADO POR CUENTAS

3|1000|3400.00|50.00|3/1/2019|60
1|2000|2500.00|40.00|5/3/2019|30
6|2000|6250.00|65.00|12/5/2018|90
5|3000|5350.00|55.00|16/6/2018|180
2|5000|2000.00|54.00|24/5/2018|90
4|7000|10000.00|48.00|12/4/2019|180



FECHA ACTUAL: 3/6/2019

*/

void procesarPF_ALU(FILE* cuentasDat, PlazoFijo* plazosFijosVec, int ce, Fecha* fechaProceso);
int txtAFecha_ALU(const char* txt, Fecha* fecha);
void trozarCamposPF_ALU(char* cad, PlazoFijo* pf);
PlazoFijo* cargarVectorPF_ALU(const char* nombrePlazosFijos, int* ce);
void ordenarVector_ALU(void* vec, int ce, size_t tamElem, Cmp cmp);
int cmpPFCuentas_ALU(const void* pf1, const void* pf2);
int cmpFechas_ALU(const Fecha* f1, const Fecha* f2);


int main(int argc, char* argv[])
{
    generarArchivos(argv[1], argv[2]);

    if(argc != 4)
    {
        puts("Cantidad incorrecta de parámetros.");
        return 1;
    }

    puts("Cuentas antes de actualizar:");
    mostrarCuentas(argv[1]);

    FILE* cuentasDat = fopen(argv[1], "r+b");

    if(!cuentasDat)
        return 2;

    Fecha fechaProceso;
    int fechaOk = txtAFecha_ALU(argv[3], &fechaProceso);

    if(!fechaOk)
        return 3;

    PlazoFijo* plazosFijosVec = NULL;
    int ce;

    plazosFijosVec = cargarVectorPF_ALU(argv[2], &ce);

    ordenarVector_ALU(plazosFijosVec, ce, sizeof(PlazoFijo), cmpPFCuentas_ALU);

    procesarPF_ALU(cuentasDat, plazosFijosVec, ce, &fechaProceso);

    fclose(cuentasDat);

    puts("\nCuentas despues de actualizar:");
    mostrarCuentas(argv[1]);

    return 0;
}

void procesarPF_ALU(FILE* cuentasDat, PlazoFijo* plazosFijosVec, int ce, Fecha* fechaProceso)
{
    PlazoFijo* curPlazoFijoVec = plazosFijosVec;
    PlazoFijo* finVecPlazoFijo = plazosFijosVec + ce - 1;
    Cuenta cuentaAct;
    int cmp, interes;
    float acumPF = 0;
    Fecha fResuSumaPlazoFijo;

    fread(&cuentaAct, sizeof(Cuenta), 1, cuentasDat);

    while(!feof(cuentasDat) && curPlazoFijoVec <= finVecPlazoFijo)
    {
        cmp = cuentaAct.cuenta - curPlazoFijoVec->cuenta;

        if(cmp == 0)
        {
            fResuSumaPlazoFijo = sumarDiasAFecha(&curPlazoFijoVec->fechaConstitucion, curPlazoFijoVec->dias);
            interes = cmpFechas_ALU(fechaProceso, &fResuSumaPlazoFijo) >= 0 ? 1:0;

            acumPF += interes*(curPlazoFijoVec->monto + (curPlazoFijoVec->dias/365.00) * (curPlazoFijoVec->interesAnual/100.00) * curPlazoFijoVec->monto);

            curPlazoFijoVec++;
        }

        if(cmp < 0)
        {
            cuentaAct.saldo += acumPF;

            fseek(cuentasDat, -(long)sizeof(Cuenta), SEEK_CUR);
            fwrite(&cuentaAct, sizeof(Cuenta), 1, cuentasDat);
            fseek(cuentasDat, 0L, SEEK_CUR);
            fread(&cuentaAct, sizeof(Cuenta), 1, cuentasDat);

            acumPF = 0;
        }

        if(cmp > 0)
            curPlazoFijoVec++;
    }

    if(!feof(cuentasDat))
    {
        cuentaAct.saldo += acumPF;

        fseek(cuentasDat, -(long)sizeof(Cuenta), SEEK_CUR);
        fwrite(&cuentaAct, sizeof(Cuenta), 1, cuentasDat);
    }
}

int txtAFecha_ALU(const char* txt, Fecha* fecha)
{
    Fecha tempFecha;

    sscanf(txt, "%d/%d/%d", &tempFecha.dia, &tempFecha.mes, &tempFecha.anio);

    if(esFechaValida(&tempFecha))
    {
        *fecha = tempFecha;
        return 1;
    }
    else
        return 0;
}

PlazoFijo* cargarVectorPF_ALU(const char* nombrePlazosFijos, int* ce)
{
    FILE* archPlazosFijos = fopen(nombrePlazosFijos, "rt");

    if(!archPlazosFijos)
        return NULL;

    PlazoFijo actPF;
    PlazoFijo* vecPF = NULL;

    char cad[1000];
    *ce = 0;

    fgets(cad, sizeof(cad), archPlazosFijos);

    while(!feof(archPlazosFijos))
    {
        trozarCamposPF_ALU(cad, &actPF);

        vecPF = (PlazoFijo*)realloc(vecPF, ((*ce) + 1) * sizeof(PlazoFijo));

        if(!vecPF)
        {
            fclose(archPlazosFijos);
            return NULL;
        }

        memcpy(vecPF + (*ce), &actPF, sizeof(PlazoFijo)); // Si no es void no hace falta multiplicar el *ce por sizeof(PlazoFijo)
        //insertarPFEnVectorOrd(vecPF, ce, &actPF);

        (*ce)++;

        fgets(cad, sizeof(cad), archPlazosFijos);
    }

    fclose(archPlazosFijos);

    return vecPF;
}

void trozarCamposPF_ALU(char* cad, PlazoFijo* pf)
{
    char* caracter = strchr(cad, '\n');
    *caracter = '\0';

    /*** dias ***/
    caracter = strrchr(cad, '|');
    sscanf(caracter + 1, "%d", &pf->dias);
    *caracter = '\0';

    /*** fechaDeConstitucion ***/
    caracter = strrchr(cad, '|');
    sscanf(caracter + 1, "%d/%d/%d", &pf->fechaConstitucion.dia
                                   , &pf->fechaConstitucion.mes
                                   , &pf->fechaConstitucion.anio);
    *caracter = '\0';

    /*** interesAnual ***/
    caracter = strrchr(cad, '|');
    sscanf(caracter + 1, "%f", &pf->interesAnual);
    *caracter = '\0';

    /*** monto ***/
    caracter = strrchr(cad, '|');
    sscanf(caracter + 1, "%f", &pf->monto);
    *caracter = '\0';

    /*** cuenta ***/
    caracter = strrchr(cad, '|');
    sscanf(caracter + 1, "%d", &pf->cuenta);
    *caracter = '\0';

    /*** monto ***/
    sscanf(cad, "%d", &pf->nroPF);
}

void ordenarVector_ALU(void* vec, int ce, size_t tamElem, Cmp cmp)
{
    int i, j, posMen;

    for(i = 0; i < ce - 1; i++)
    {
        posMen = i;
        for(j = i + 1; j < ce; j++)
            if(cmp(vec + posMen*tamElem, vec + j*tamElem) > 0)
                posMen = j;

        intercambiar(vec + posMen*tamElem, vec + i*tamElem, tamElem);
    }
}

int cmpPFCuentas_ALU(const void* pf1, const void* pf2)
{
    return ((PlazoFijo*)pf1)->cuenta - ((PlazoFijo*)pf2)->cuenta;
}

int cmpFechas_ALU(const Fecha* f1, const Fecha* f2)
{
    if(f1->anio - f2->anio == 0)
    {
        if(f1->mes - f2->mes == 0)
            return f1->dia - f2->dia;
        else
            return f1->mes - f1->mes;
    }


    return f1->anio - f2->anio;
}
