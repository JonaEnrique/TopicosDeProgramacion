/*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***/
/*** CABECERA ***//*** -------- ***//*** -------- ***//*** CABECERA ***//*** -------- ***//*** -------- ***//*** CABECERA ***/
/*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100
#define NOMYAPE_TAMANIO 51
#define NOTA_TAMANIO 6
#define NOTA_FINAL_TAMANIO 6
#define OBSERVACION_TAMANIO 50
#define ESTADO_FINAL_TAMANIO 6 // incluyo el \0.

#define NOMARCALUMNO 1
#define NOMARCNOTAS 2
#define NORMAACTA 3

#define TODO_OK 0
#define ERROR_ARCHIVO 1
#define ERROR_LINEA 2

typedef struct
{
    int dni;
    char nomYApe[NOMYAPE_TAMANIO];
}tAlumno;

typedef struct
{
    int dni;
    char p1[NOTA_TAMANIO];
    char p2[NOTA_TAMANIO];
    char r1[NOTA_TAMANIO];
    char r2[NOTA_TAMANIO];
}tNotas;

typedef struct
{
    int dni;
    char nomYApe[NOMYAPE_TAMANIO];
    char p1[NOTA_TAMANIO];
    char p2[NOTA_TAMANIO];
    char r1[NOTA_TAMANIO];
    char r2[NOTA_TAMANIO];
    char notaFinal[NOTA_FINAL_TAMANIO];
    char estadoFinal[ESTADO_FINAL_TAMANIO];
}tActa;

typedef struct
{
    int dni;
    char observaciones[OBSERVACION_TAMANIO];
}tObser;

/// Prototipo funcion
typedef int (*TrozadoTipo)(tNotas* notas, char* vector);

int crearArchivoAlumno(const char* nombreArchivo);
int crearArchivoNotas(const char* nombreArchivo);
int crearActa(const char* nombreArchivoAlu, const char* nombreArchivoNot, const char* nombreArchivoAct, const char* nombreArchivoObs, char tipoTxt);
int sacarInformacionDeTexto(tNotas* notas, char* notasATrozar, char* tipoTxt);
int txtVar(tNotas* notas, char* notasATrozar);
int txtFija(tNotas* notas, char* notasATrozar);
int insertarValoresEnEstruc(const tAlumno* alum, const tNotas* notas, tActa* acta, tActa* vectorActas, const int* detectoError) ;
void primeraObservacion(tNotas* notas, int* detectarError, FILE* punteroArchivo);
void terceraObservacion(tNotas* notas, FILE* punteroArchivo);
float miAtof(char* nota);
int esNumero(const char* nota);
//bool tieneDosRecuperatorios(const tActa* acta);


/*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***/
/*** MAIN     ***//*** -------- ***//*** -------- ***//*** MAIN     ***//*** -------- ***//*** -------- ***//*** MAIN     ***/
/*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***/

int main()
{

    int estado = 0;
    estado = crearArchivoAlumno("alumnos.bin");
    estado = crearArchivoNotas("notas.txt");
    estado = crearActa("alumnos.bin", "notas.txt", "acta.txt", "observaciones.txt", 'V');

    return estado;
}

/*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***/
/*** FUNCION  ***//*** -------- ***//*** -------- ***//*** FUNCION  **//*** -------- ***//*** -------- ***//***  FUNCION  ***/
/*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***//*** -------- ***/

int crearArchivoAlumno(const char* nombreArchivo)
{
    FILE *pAlum = fopen(nombreArchivo, "wb");

    if (pAlum == NULL)
        return ERROR_ARCHIVO;

    tAlumno alumnos[]=
    {
        {11222342, "Pazola, Federico"},
        {11324517, "Ludea, Gimena"},
        {22345789, "Garcia, Perez"},
        {45686723, "Fontana, Maribel"},
        {56576823, "Delacruz, Mauro"},
        {98764532, "Blanco, Alonso"},
        {99984532, "Guitarra, Loca"},
        {99998875, "Error, Cosme"},
        {99999966, "ErrorSegundo, Fulanito"}
    };

    fwrite(alumnos, sizeof(tAlumno), sizeof(alumnos), pAlum);

    fclose(pAlum);

    return TODO_OK;
}
int crearArchivoNotas(const char* nombreArchivo)
{
    FILE* pNotas = fopen(nombreArchivo, "wt");
    if(pNotas == NULL)
        return ERROR_ARCHIVO;

    tNotas notas[]=
    {
        {11222342, "7,50", "8", "A", "A"},
        {11324517, "8", "5", "A", "7"},
        {22345789, "6", "4", "A", "A"},
        {56576823, "8,75", "7,20", "A", "9"},
        {65748461, "8", "7", "A", "A"},
        {98764532, "2", "A", "A", "A"},
        {99984532, "6", "7", "A", "7"},
        {99998875, "6", "7", "5", "7"},
        {99999966, "9", "8", "A", "A"}
    };

    int i;
    int cantElementos = sizeof(notas)/sizeof(tNotas);

    for(i = 0; i < (cantElementos); i++)
    {
        fprintf(pNotas, "%d|%-5s|%-5s|%-5s|%-5s\n", notas[i].dni, notas[i].p1, notas[i].p2, notas[i].r1, notas[i].r2);
    }

    fclose(pNotas);

    return TODO_OK;
}

int crearActa(const char* nombreArchivoAlu, const char* nombreArchivoNot, const char* nombreArchivoAct, const char* nombreArchivoObs, char tipoTxt)
{
    FILE* fpAlu = fopen(nombreArchivoAlu, "rb");
    if(!fpAlu)
    {
        printf("Falla al abrir archivo %s.\n", nombreArchivoAlu);
        return ERROR_ARCHIVO;
    }
    FILE* fpNot = fopen(nombreArchivoNot, "rt");
    if(!fpNot)
    {
        printf("Falla al abrir archivo %s.\n", nombreArchivoNot);
        return ERROR_ARCHIVO;
    }
    FILE* fpAct = fopen(nombreArchivoAct, "wt");
    if(!fpAct)
    {
        printf("Falla al abrir archivo %s.\n", nombreArchivoAct);
        return ERROR_ARCHIVO;
    }
    FILE* fpObs = fopen(nombreArchivoObs, "wt");
    if(!fpObs)
    {
        printf("Falla al abrir archivo %s.\n", nombreArchivoObs);
        return ERROR_ARCHIVO;
    }

    tAlumno alum;
    tAlumno alumTempParaError;
    tNotas notas;
    tNotas notasTempParaError;
    tActa acta;

    // Extraigo cantidad de alumnos
    fseek(fpAlu, 0L, SEEK_END);
    long int tamanio = ftell(fpAlu);
    tamanio = tamanio/sizeof(tAlumno);

    char notasATrozar[100];
    tActa actas[tamanio];

    TrozadoTipo trozadoTipo = tipoTxt == 'V'? txtVar : txtFija;


    /// lectura alumno y notas
    fread(&alum, sizeof(tAlumno), 1, fpAlu);
    fgets(notasATrozar, sizeof(tNotas), fpNot);
    while(feof(fpAlu)||feof(fpNot))
    {
        trozadoTipo(&notas, notasATrozar);

        ///Analizo casos
        int detectarError=0;
        if(alum.dni>notas.dni) /// Detecto notas sin alumno
        {
            fprintf(fpObs,"La persona de dni: %d no esta vinculado a un alumno.\n", notas.dni);
            fgets(notasATrozar, sizeof(tNotas), fpNot); /// avanzo uno para detectar si existe alumno
            trozadoTipo(&notas, notasATrozar);
        }
        else if(alum.dni<notas.dni) /// Detecto alumnos sin notas
        {
            primeraObservacion(&notas, &detectarError, fpObs);
            insertarValoresEnEstruc(&alum, &notasTempParaError, &acta, actas, &detectarError);
            terceraObservacion(&notas, fpObs);
            notas.dni=alum.dni;
            strncpy(acta.p1,"A", NOTA_FINAL_TAMANIO);
            strncpy(acta.p2,"A", NOTA_FINAL_TAMANIO);
            strncpy(acta.r1,"A", NOTA_FINAL_TAMANIO);
            strncpy(acta.r2,"A", NOTA_FINAL_TAMANIO); /// En este caso para el calculo de nota final se usara A como 0 para detectarlo
            insertarValoresEnEstruc(&alumTempParaError, &notas, &acta, actas, &detectarError);
            fread(&alum, sizeof(tAlumno), 1, fpAlu);
        }
        else
        {
            primeraObservacion(&notas , &detectarError, fpObs);
            insertarValoresEnEstruc(&alum, &notas, &acta, actas, &detectarError);
            terceraObservacion(&notas, fpObs);
        }
        /// prosigo lectura en ambos archivos
        fread(&alum, sizeof(tAlumno), 1, fpAlu); /// ESTO USAR PARA TODO BIEN
        fgets(notasATrozar, sizeof(tNotas), fpNot);
    }



    return TODO_OK;
}

int txtVar(tNotas* notas, char* notasATrozar)
{
    char* act = strchr(notasATrozar, '\n');
    if(!act)
        return ERROR_LINEA;
    *act='\0';

    act = strrchr(notasATrozar, '|');
    strncpy(notas->r2, act+1, NOTA_TAMANIO);
    notas->r2[NOTA_TAMANIO]='\0';
    *act='\0';


    act = strrchr(notasATrozar, '|');
    strncpy(notas->r1, act+1, NOTA_TAMANIO);
    notas->r1[NOTA_TAMANIO]='\0';
    *act='\0';


    act = strrchr(notasATrozar, '|');
    strncpy(notas->p2, act+1, NOTA_TAMANIO);
    notas->p2[NOTA_TAMANIO]='\0';
    *act='\0';


    act = strrchr(notasATrozar, '|');
    strncpy(notas->p1, act+1, NOTA_TAMANIO);
    notas->p1[NOTA_TAMANIO]='\0';
    *act='\0';

    sscanf(notasATrozar, "%d", &notas->dni);

    return TODO_OK;
}

int txtFija(tNotas* notas, char* notasATrozar)
{
    char* act = strchr(notasATrozar, )
}

int insertarValoresEnEstruc(const tAlumno* alum, const tNotas* notas, tActa* acta, tActa* vectorActas, const int* detectoError) /// ESTA COSA DEBE AVANZAR EL VECTOR ACTA
{
    char vectorNF[NOTA_TAMANIO];
    char vectorEF[ESTADO_FINAL_TAMANIO];
    ftoa(calcularEF(notas, detectoError), vectorEF);
    ftoa(calcularNF(notas, detectoError), vectorNF);

    strncpy(acta->estadoFinal, vectorEF, sizeof[ESTADO_FINAL_TAMANIO]);
    acta->r2[NOMYAPE_TAMANIO]='0'; sizeof[NOTA_TAMANIO];
    strncpy(acta->notaFinal, vectorNF);
    acta->r2[NOMYAPE_TAMANIO]='0';
    strncpy(acta->r2, notas->r2, sizeof(NOTA_TAMANIO));
    acta->r2[NOMYAPE_TAMANIO]='0';
    strncpy(acta->r1, notas->r1, sizeof(NOTA_TAMANIO));
    acta->r1[NOMYAPE_TAMANIO]='0';
    strncpy(acta->p2, notas->p2, sizeof(NOTA_TAMANIO));
    acta->p2[NOMYAPE_TAMANIO]='0';
    strncpy(acta->p1, notas->p1, sizeof(NOTA_TAMANIO));
    acta->p1[NOMYAPE_TAMANIO]='0';
    strncpy(acta->nomYApe, alum->nomYApe, sizeof(NOMYAPE_TAMANIO));
    acta->nomyApe[NOMYAPE_TAMANIO]='0';
    acta->dni=acta->dni;
}

void terceraObservacion(tNotas* notas, FILE* punteroArchivo)
{
    float parcial1 = miAtof(notas->p1);
    float parcial2 = miAtof(notas->p2);
    float recuperatorio1 = miAtof(notas->r1);
    float recuperatorio2 = miAtof(notas->r2);
    if(parcial1>7 && parcial2>7)
        if(recuperatorio1>0 || recuperatorio2>0)
            fprintf(punteroArchivo,"El alumno de dni: %d rindio un recuperatorio a pesar de tener aprobado los dos parciales.\n", notas->dni);
}

void primeraObservacion(tNotas* notas, int* detectarError, FILE* punteroArchivo)
{
   if(!(strcmp(notas->r1,"A"))&&(strcmp(notas->r2,"A"))) /// Detecto 2 recuperatorios
   {
       *detectarError=1;
        /// strncpy(acta.estadoFinal,"Err", NOTA_FINAL_TAMANIO); PASAR ESTO A LA FUNCION DE INSERTAR EN ESTRUCTURA CON UN IF EVALUANDO DETECTARERROR
        fprintf(punteroArchivo,"El alumno de dni: %d posee 2 recuperatorios.\n", notas->dni);
   }
}

float miAtof(char* nota)
{
    float val=0, potencia=0, signo=0;
    char* cursorNota = nota;
    if(*nota=='A')
    {
        return 0;
    }
    /// elimino espacio
    while(*cursorNota==' ')
    {
        cursorNota++;
    }
    signo = (*cursorNota=='-')?-1:1;
    if(*cursorNota == '+' || *cursorNota == '-')
        cursorNota++;
    for(val=0.0;esNumero(cursorNota);cursorNota++)
    {
        val= 10.0*val+(*cursorNota-'0');
    }
    if(*cursorNota==',')
        cursorNota++;
    for(potencia=1.0;esNumero(nota);cursorNota++)
    {
        val = 10.0*val+(*cursorNota-'0');
        potencia*=10.0;
    }
    return signo * (val/potencia);
}

int esNumero(const char* nota)
{
    return (*nota>='0'&&*nota<='0');
}

float calcularEF(tNotas notas,int* detectarError)
{
    float parcial1=(strcmp(*notas->p1,"A")!=0)?miAtof(*notas->p1):0f);
    float parcial2=(strcmp(*notas->p2,"A")!=0)?miAtof(*notas->p2):0f);
    float recuperatorio1=(strcmp(*notas->r1,"A")!=0)?miAtof(*notas->r1):0f);
    float recuperatorio2=(strcmp(*notas->r2,"A")!=0)?miAtof(*notas->r2):0f);
    if(detectarError==1)
    {
        notas->
    }
}

calcularNT(tNotas notas,int* detectarError)
{

}
