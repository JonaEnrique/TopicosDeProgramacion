#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Fecha/Fecha.h"
#include "../SolucionParcialPlazosFijosTopicos/SolucionParcialPlazosFijos.h"

#define TODO_OK 0;
#define ERROR_ARCHIVO 1;
#define ERROR_LINEA 3;

#define esBisiesto(anio)(((anio)%4==0 && (anio)%100!=0) || (anio)%400==0)

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


int convTxtVariable(char* vector, PlazoFijo* estructura);
PlazoFijo* cargarVectorPF_ALU(const char* nombrePlazosFijos, int* ce);
void procesarPF_ALU(FILE* cuentasDat, PlazoFijo* plazosFijosVec, int ce, Fecha* fechaProceso);
int cmpVecPF(const void* vector1, const void* vector2);
void ordenarVector_ALU(void* v, int ce, size_t tamElem, Cmp cmp);
void intercambiar_ALU(void* elem1, void* elem2, size_t tamElem);
void mostrarCuentas_ALU(const char* nombreArchCuentas);
void imprimirVector(PlazoFijo* vector, const int* ce);

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

    puts("\nCuentas antes de actualizar (con ALU):");
	mostrarCuentas_ALU(argv[1]);

	FILE* cuentasDat = fopen(argv[1], "r+b");

	if(!cuentasDat)
		return 2;

	Fecha fechaProceso;
	int fechaOk = txtAFecha(argv[3], &fechaProceso);

	if(!fechaOk)
		return 3;

	PlazoFijo* plazosFijosVec = NULL;
	int ce;

	plazosFijosVec = cargarVectorPF(argv[2], &ce);

	puts("\nVector antes de ordenar:");
	imprimirVector(plazosFijosVec, &ce); /// PARA REVISAR VECTOR DINAMICO

	ordenarVector_ALU(plazosFijosVec, ce, sizeof(PlazoFijo), cmpVecPF); /// Agregada propia

	puts("\nVector despues de ordenar:");
	imprimirVector(plazosFijosVec, &ce); /// PARA REVISAR VECTOR DINAMICO

	procesarPF_ALU(cuentasDat, plazosFijosVec, ce, &fechaProceso);

	fclose(cuentasDat);

	puts("\nCuentas despues de actualizar:");
	mostrarCuentas(argv[1]);
+
	puts("\nCuentas despues de actualizar (con ALU):");
	mostrarCuentas_ALU(argv[1]);

    return 0;
}

bool esFechaValida_ALU(const Fecha* f)
{
    if(f->anio >= 1604)
        if(f->mes>=1 && f->mes<=12)
            if(f->dia >= 1 && f->dia <= cantDiasMes(f->mes,f->anio))
                return true;
    return false;
}
int cantDiasMes_ALU(int mes, int anio)
{
    int static diasMes[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

    if(mes == 2 && esBisiesto(anio))
    {
        return 29;
    }
    else
    {
        return diasMes[mes];
    }
}

Fecha sumarDiasAFecha_ALU(const Fecha* f, unsigned dias)
{
    Fecha fecha = *f;
    fecha.dia+=dias;
    int cantDM = 0;

    if(fecha.dia > (cantDM = cantDiasMes(fecha.mes, fecha.anio)))
    {
        fecha.dia-=cantDM;
        fecha.anio+=fecha.mes/12;
        fecha.mes =fecha.mes%12+1;
    }
    return fecha;
}


void sumarDiasAFechaInSitu_ALU(Fecha* f, unsigned dias)
{
    f->dia+=dias;
    int cantDM = 0;

    while(f->dia > (cantDM = cantDiasMes(f->mes, f->anio)))
    {
        f->dia-=cantDM;
        f->anio+=f->mes/12;
        f->mes =f->mes%12+1;
    }
}

int cmpFechas_ALU(const Fecha* f1, const Fecha* f2)
{
    if(f1->anio == f2->anio)
    {
        if(f1->mes == f2->mes)
        {
            if(f1->dia == f2->dia)
            {
                return 0;
            }
            else
            {
                return f1->dia-f2->dia;
            }
        }
        else
        {
            return f1->mes-f2->mes;
        }
    }
    else
    {
        return f1->anio-f2->anio;  /// CONSULTAR QUE ONDA ESTE
    }
}

int cmpMeses_ALU(const Mes* mes1, const Mes* mes2)
{
    if(mes1->anio == mes2->anio)
    {
        if(mes1->mes == mes2->mes)
        {
            return 0;
        }
        else
        {
            return mes1->mes-mes2->mes; /// CONSULTAR QUE ONDA ESTE
        }
    }
    else
    {
       return mes1->anio-mes2->anio;
    }
}
/// ES POSIBLE QUE NO SE USE

Mes getMes_ALU(const Fecha* f)
{
    Mes mes;
    mes.mes=f->mes;
    mes.anio=f->anio; /// CONSULTAR QUE ONDA ESTE
    return mes;
}
/// ES POSIBLE QUE NO SE USE

/*
int difEnDiasEntreFechas(const Fecha* f1, const Fecha* f2)
{

}

int diaDelAnio(const Fecha* f)
{

}
*/ /// ES POSIBLE QUE NO SE USE

Mes strToMes_ALU(const char* str)
{
    int valor = 0;
    Mes mesConvertido;
    char* cursorStr = (char*) str;
    while(*cursorStr!='/')
    {
        ; // salteo los dias
    }
    cursorStr++;
    while(*cursorStr!='/')
    {
        valor=10*valor+(*cursorStr-'0'); // sumo mes
    }
    mesConvertido.mes=valor;
    valor = 0;
    while(*cursorStr!='\0')
    {
        valor=10*valor+(*cursorStr-'0');
    }
    mesConvertido.anio=valor;  /// ES POSIBLE QUE NO SE USE

    return mesConvertido;
}

int txtAFecha_ALU(const char* txt, Fecha* fecha)
{
    Fecha tempFecha;
    sscanf(txt, "%d/%d/%d", &tempFecha.dia, &tempFecha.mes, &tempFecha.anio);

    if(esFechaValida_ALU(&tempFecha))
    {
        *fecha = tempFecha;
        return 1;
    }
    return 0;
}

/// FECHA

int convTxtVariable(char* vector, PlazoFijo* estructura)
{
    char* caracter = strchr(vector,'\n');
    if(!caracter)
    {
        return ERROR_LINEA
    }
    *caracter='\0';

    caracter = strrchr(vector,'|');
    sscanf(caracter+1,"%d",&estructura->dias);
    *caracter='\0';

    caracter = strrchr(vector,'|');
    sscanf(caracter+1,"%d/%d/%d", &estructura->fechaConstitucion.dia, &estructura->fechaConstitucion.mes, &estructura->fechaConstitucion.anio);
    *caracter='\0';

    caracter = strrchr(vector,'|');
    sscanf(caracter+1,"%f", &estructura->interesAnual);
    *caracter='\0';

    caracter = strrchr(vector,'|');
    sscanf(caracter+1,"%f", &estructura->monto);
    *caracter='\0';

    caracter = strrchr(vector,'|');
    sscanf(caracter+1,"%d", &estructura->cuenta);
    *caracter='\0';

    sscanf(vector,"%f", &estructura->interesAnual);
    return TODO_OK;
}

PlazoFijo* cargarVectorPF_ALU(const char* nombrePlazosFijos, int* ce)
{

    char vectorParaTrozar[300];
    PlazoFijo estructura;
    PlazoFijo* vectorDinamico = NULL;
    FILE* fpPlazoFijo = fopen(nombrePlazosFijos, "wt");
    fgets(vectorParaTrozar, sizeof(PlazoFijo), fpPlazoFijo);
    *ce=0;

    while(!feof(fpPlazoFijo))
    {
        convTxtVariable(vectorParaTrozar, &estructura);

        vectorDinamico = (PlazoFijo*)realloc(vectorDinamico, ((*ce)+1)*sizeof(PlazoFijo));
        if(!vectorDinamico)
        {
            puts("No hubo espacio de memoria suficiente para realizar realloc");
            return NULL;
        }
        memcpy(vectorDinamico+(*ce), &estructura, sizeof(PlazoFijo));
        //*vectorDinamico = estructura;
        *ce+=1;

        fgets(vectorParaTrozar, sizeof(PlazoFijo), fpPlazoFijo);
    }

    return vectorDinamico; /// CAMBIAR POR PUNTERO A VECTOR DINAMICO
}

void procesarPF_ALU(FILE* cuentasDat, PlazoFijo* plazosFijosVec, int ce, Fecha* fechaProceso)
{
    int compCuentas = 0, compFechas = 0;
    float totalPF = 0;
    PlazoFijo* cursorPFVec = plazosFijosVec;
    PlazoFijo* PFVecFin = plazosFijosVec+(ce-1);

    Cuenta clienteNue;
    Fecha fechaPF;

    fread(&clienteNue, sizeof(Cuenta), 1, cuentasDat);
    while(!feof(cuentasDat) && cursorPFVec <= PFVecFin)
    {

        compCuentas = clienteNue.cuenta-cursorPFVec->cuenta;

        if(compCuentas == 0)
        {
            fechaPF = cursorPFVec->fechaConstitucion;
            sumarDiasAFechaInSitu_ALU(&fechaPF, cursorPFVec->dias);
            compFechas = cmpFechas_ALU(fechaProceso, &fechaPF);
            if(compFechas>0)
            {
                totalPF = cursorPFVec->monto + ((cursorPFVec->dias/365.00) * (cursorPFVec->interesAnual/100.00) * cursorPFVec->monto);
                clienteNue.saldo += totalPF;
            }
            cursorPFVec++;
        }
        else if(compCuentas < 0) /// encontramos un plazo fijo de una nueva cuenta
        {
            fseek(cuentasDat, -(long)sizeof(Cuenta),SEEK_CUR);
            fwrite(&clienteNue, sizeof(Cuenta), 1, cuentasDat);
            fseek(cuentasDat, 0L ,SEEK_CUR); // para evitar fallas entre pasaje write a read
            fread(&clienteNue, sizeof(Cuenta), 1, cuentasDat);
        }
        else if(compCuentas > 0)
        {
            cursorPFVec++;
        }
    }
        if(!feof(cuentasDat))
    {
        // clienteNue.saldo += totalPF;
        /// no hago esto porque ya lo hice en compCuentas == 0, PERO SI DEBO CARGARLO porque eso lo hacia en compCuentas < 0 y no llegue.
        fseek(cuentasDat,-(long)sizeof(Cuenta), SEEK_CUR);
        fread(&clienteNue, sizeof(Cuenta), 1, cuentasDat);
    }
}

int cmpVecPF(const void* vector1, const void* vector2)
{
    return ((PlazoFijo*)vector1)->cuenta - ((PlazoFijo*)vector2)->cuenta;
}
void intercambiar_ALU(void* elem1, void* elem2, size_t tamElem)
{
    void* aux = malloc(1*tamElem);
    if(!aux)
    {
        puts("No hay memoria suficiente para utilizar malloc.");
    }

    memcpy(aux,elem1,tamElem);
    memcpy(elem1,elem2,tamElem);
    memcpy(elem1,aux,tamElem);

    free(aux);
}

void ordenarVector_ALU(void* v, int ce, size_t tamElem, Cmp cmp)
{
    void *m, *ult = v + (ce*tamElem);

    for(void* i = v; i < ult; i += tamElem)
    {
        m = i;
        for(void* j = i + tamElem; j < ult; j += tamElem)
        {
        if(cmpVecPF(j, m) < 0)
            m = j;
        }
        if(m != i)
            intercambiar(m, i, tamElem);
    }
}

void mostrarCuentas_ALU(const char* nombreArchCuentas)
{
    FILE* fpBin = fopen(nombreArchCuentas, "rb");
    if(!fpBin)
    {
        puts("No se pudo abrir el archivo.\n");
    }
    Cuenta cuenta;

    fread(&cuenta, sizeof(Cuenta), 1, fpBin);
    while(!feof(fpBin))
    {
        printf("%d\t%-20s\t%9.2f\n", cuenta.cuenta, cuenta.cliente, cuenta.saldo);
        fread(&cuenta, sizeof(Cuenta), 1, fpBin);
    }

    fclose(fpBin);
}

void imprimirVector(PlazoFijo* vector, const int* ce)
{
    PlazoFijo* cursorVector = vector;
    PlazoFijo* cursorVectorFin = vector+(*ce-1);
    while(cursorVector <= cursorVectorFin)
    {
            printf("nroPF: %d cuenta: %d monto: % f interesAnual: %f Fecha: %d/%d/%d dias: %d\n",
                   cursorVector->nroPF, cursorVector->cuenta, cursorVector->monto,
                   cursorVector->interesAnual, cursorVector->fechaConstitucion.dia,
                   cursorVector->fechaConstitucion.mes, cursorVector->fechaConstitucion.anio, cursorVector->dias);
            cursorVector++;
    }

}
