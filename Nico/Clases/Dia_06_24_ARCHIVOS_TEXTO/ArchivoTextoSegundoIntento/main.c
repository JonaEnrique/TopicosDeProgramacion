#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Dia_04_15_VIRTUAL/FechaLib/Fecha.h"
/// No olvidar hacer Build Options\linker settings\add (buscar archivo libFechaLib.a en libreria Fecha)

#define TAM_DNI 8
#define TAM_APYNOM 50
#define TAM_SEXO 1
#define TAM_FECHA 8
#define TAM_SUELDO 12

#define CANT_EMPL 100
#define ARG_BIN 1
#define ARG_TXT 2
#define ARG_TIPO_TXT 3

#define TODO_OK 0
#define ERROR_ARCH 1
#define ERROR_LINEA_LARGA 2

#define TAM_LINEA 500

// conviene guardar en define cuanto ocupa cada campo

typedef struct
{
        int dni;
        char apYNom[TAM_APYNOM + 1];
        char sexo;
        Fecha fechaIngr;
        float sueldo;
}
Empleado;

/// ES UN TIPO EMPIEZA CON MAYUSCULA
typedef int (*TxtABin)(char* linea, Empleado* empl);

int generarEmpleadosBin(const char* nombArch);
int archBinATxt(const char* nombreArchBin, const char* nombreArchTxt, char tipoTxt);
int archTxtABin(const char* nombreArchBin, const char* nombreArchTxt, char tipoTxt);
int mostrarEmpleadoBin(const char* nombreArch);
void rTrim(const char* cad);
int archTxtABinMejorado(const char* nombreArchBin, const char* nombreArchTxt, char tipoTxt);
int txtVarABin(char* linea, Empleado* empl);
int txtFijoABin(char* linea, Empleado* empl);

/// MAIN
/// Paso argumentos a main
int main(int argc, char* argv[])
{
   int ret = generarEmpleadosBin(argv[ARG_BIN]);

   if(ret!=TODO_OK)
        return ret;

    ret = archBinATxt(argv[ARG_BIN], argv[ARG_TXT], argv[ARG_TIPO_TXT][0]);

    ret = archTxtABinMejorado(argv[ARG_BIN], argv[ARG_TXT], argv[ARG_TIPO_TXT][0]);

    mostrarEmpleadoBin(argv[ARG_BIN]);

    return ret;
}

int generarEmpleadosBin(const char* nombArch)
{
    Empleado empleados[CANT_EMPL]=
    {
        {11222333, "Perez, Juan", 'M', {1, 2, 2020}, 100000.00},
        {22333444, "Gomez, Ana", 'F', {2, 3, 2020}, 200000.00},
        {33444555, "Gonzalez, Luis", 'M', {3, 4, 2020}, 300000.00},
        {44555666, "Rodriguez, Maria", 'F', {4, 5, 2020}, 400000.00},
        {55666777, "Fernandez, Carlos", 'M', {5, 6, 2020}, 500000.00},
        {66777888, "Lopez, Sofia", 'F', {6, 7, 2020}, 600000.00},
        {77888999, "Martinez, Jorge", 'M', {7, 8, 2020}, 700000.00},
        {88999000, "Sanchez, Andrea", 'F', {8, 9, 2020}, 800000.00},
        {99000011, "Gimenez, Pablo", 'M', {9, 10, 2020}, 900000.00},
        {10000122, "Blanco, Carolina", 'F', {10, 11, 2020}, 1000000.00}
    };

    FILE* archEmpleados = fopen(nombArch,"wb");

    if(archEmpleados == NULL)
    {
        printf("No se pudo abrir el archivo %s\n", nombArch);
        return ERROR_ARCH;
    }

    fwrite(empleados, sizeof(Empleado), CANT_EMPL, archEmpleados);

    fclose(archEmpleados);

    return TODO_OK;
}

/// TIP para saber tamaño de bin puedo hacer un fseek (hasta el final)
/// y tirar un ftell para obtener el tamaño del archivo, luego dividido por tam empleado
/// y obtengo cantidad de registros
/// OJO si el archivo es muy grande debo hacer de uno a uno, puedo igual ir contandolos para saber tamaño.
/// Si el vector es estatico y le pongo dimension (no uso mem dinamica) debo saber cuantos elementos son (osea dividir los bytes del archivo que sacamos con ftell)
/// SI ES DINAMICA (MALLOC) CON EL TAMAÑO OBTENIDO DE FTELL YA ALCANZA.

/// OJO buscar el tamaño de anchoVariable no es posible debido a que no es un ancho exacto por cada registro.
/// Para ancho Fijo si es posible dado que cada campo ocupa un tamaño especifico.
/// REVISAR ESTO ULTIMO! VER EN TIEMPO 42:00

int archBinATxt(const char* nombreArchBin, const char* nombreArchTxt, char tipoTxt)
{
    FILE* archBin = fopen(nombreArchBin, "rb");

    if(!archBin)
        return ERROR_ARCH;

    FILE* archTxt = fopen(nombreArchTxt, "wt");

    if(!archTxt)
       return ERROR_ARCH;

    /// uso para distinguir entre fijo o variable
    char* formatoTxt = tipoTxt == 'V'? "%d|%s|%c|%d/%d/%d|%f\n" : "%08d%-50s%c%02d%02d%02d%012.2f\n";

    Empleado empl;
    fread(&empl, sizeof(Empleado), 1, archBin);
    while(!feof(archBin))
    {
        fprintf
        (
            archTxt,
            formatoTxt,
            empl.dni, empl.apYNom, empl.sexo,
            empl.fechaIngr.dia, empl.fechaIngr.mes, empl.fechaIngr.anio,
            empl.sueldo
        );
        fread(&empl, sizeof(Empleado), 1, archBin);
    }

    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}

/// FREAD ES PARA BINARIO
/// FWRITE ES PARA BINARIO

/// FPRINT ES PARA TEXTO
/// FSCANF ES PARA TEXTO (UN PASO MAS QUE FGETS, LEE LA LINEA Y HACE CONVERSION A VARIABLE)
/// FGETS ES PARA TEXTO (LEE LINEA DE ARCHIVO TEXTO HASTA ENTER, COPIA EN VECTOR CHAR)
int archTxtABin(const char* nombreArchBin, const char* nombreArchTxt, char tipoTxt)
{
    FILE* archBin = fopen(nombreArchBin, "wb");

    if(!archBin)
        return ERROR_ARCH;

    FILE* archTxt = fopen(nombreArchTxt, "rt");

    if(!archTxt)
       return ERROR_ARCH;

    /// uso para distinguir entre fijo o variable
    char* formatoTxt = tipoTxt == 'V'? "%d|%[^|]|%c|%d/%d/%d|%f\n" : "%8d%50[^\n]%c%2d%2d%2d%12f"; // en segundo salteamos ultimo enter porque fscanf corta con ese ultimo \n.
    // para s (el que sigue de %d) usamos la siguiente mecanica: reconocer todos los caracteres hasta [^|] pero sin ponerlo en el campo


    Empleado empl;
    /// OJO FSCANF NO SE LLEVA BIEN CON FEOF POR ESO USAMOS RETORNO DE FSCANF (AL LLEGAR A FINAL DEVUELVE VALOR CONSTANTE EOF)
    while
    (   fscanf
        (
            archTxt,
            formatoTxt,
            &empl.dni, empl.apYNom, &empl.sexo,
            &empl.fechaIngr.dia, &empl.fechaIngr.mes, &empl.fechaIngr.anio,
            &empl.sueldo
         ) != EOF // seguir while mientras fscanf no de EOF
                    // No hace falta & para empl.apYNom ya que es un vector y el contenido es la direccion del vector (es un puntero)
    )
    {
        rTrim(empl.apYNom); // SACAMOS ULTIMOS ESPACIOS SI HAY
        fwrite(&empl, sizeof(Empleado), 1, archBin);
    }
    /// Ojo fscanf podria fallar en casos como sueldo 10000,250 aca me mato porque uso coma en vez de punto
    /// para detectar errores en lo que mandan hay dos casos
    /// no hay fin de linea AHI NO PODEMOS SEGUIR
    /// error dentro de una linea (mal formato de palabra) no pasa nada se puede normalizar
    /// error dentro de una linea (mal ingresado sueldo) eso es grave
    /// error dentro de una linea (mal ingresado dni tiene 40.200.222, no sirve punto) esto es grave y necesito correjir para seguir


    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}

int mostrarEmpleadoBin(const char* nombreArch)
{
    FILE* archEmpleados = fopen(nombreArch, "rb");

    if(archEmpleados == NULL)
    {
        printf("No se pudo abrir el archivo %s\n", nombreArch);
        return ERROR_ARCH;
    }

    Empleado empl;
    fread(&empl, sizeof(Empleado), 1, archEmpleados);
    while(!feof(archEmpleados))
    {
        printf
        (
            "%08d,\t%-30s\t%c\t%02d/%02d/%04d\t%012.2f\n",
            empl.dni, empl.apYNom, empl.sexo,
            empl.fechaIngr.dia, empl.fechaIngr.mes, empl.fechaIngr.anio,
            empl.sueldo
        );

        fread(&empl, sizeof(Empleado), 1, archEmpleados);
    }

    fclose(archEmpleados);

    return TODO_OK;
}

/// ESTO DEBE IR EN LIBRERIA CADENAS
void rTrim(const char* cad)
{
    char* fin = (char*) cad;

    while(*fin)
        fin++;

    fin--;

    while(*fin == ' ')
        fin--;

   *(fin+1) = '\0';
}


int archTxtABinMejorado(const char* nombreArchBin, const char* nombreArchTxt, char tipoTxt)
{
    FILE* archBin = fopen(nombreArchBin, "wb");

    if(!archBin)
        return ERROR_ARCH;

    FILE* archTxt = fopen(nombreArchTxt, "rt");

    if(!archTxt)
       return ERROR_ARCH;

    TxtABin txtABin = tipoTxt == 'V'? txtVarABin : txtFijoABin;

    Empleado empl;
    char linea[TAM_LINEA];
    fgets(linea, TAM_LINEA, archTxt); // lee maximo TAM_LINEA menos uno y pone un \0.
    while(!feof(archTxt))
    {
        /// debemos crear puntero a funcion y uso ternario. asi me ahorro andar pregutando if
        txtABin(linea, &empl);
        fwrite(&empl, sizeof(Empleado), 1, archBin);
        fgets(linea, TAM_LINEA, archTxt);
    }
    /// con esto queremos corregir los posibles casos con errores vistos previamente.
    /// SI HAY ERROR SE DEBE USAR TROZADO.

    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}

/// como un fscanf pero modificado para verificar campos validos
int txtVarABin(char* linea, Empleado* empl)
{
    char* act = strchr(linea, '\n');

    if(!act)
        return ERROR_LINEA_LARGA;

    *act = '\0';
    act=strrchr(linea, '|');
    sscanf(act+1, "%f", &empl->sueldo);

    *act = '\0';
    act=strrchr(linea, '|');
    sscanf(act+1,"%d/%d/%d", &empl->fechaIngr.dia, &empl->fechaIngr.mes, &empl->fechaIngr.anio);

    *act = '\0';
    act = strrchr(linea, '|');
    empl->sexo = *(act+1);

    *act = '\0';
    act = strrchr(linea, '|');
    strncpy(empl->apYNom, act+1, TAM_APYNOM);
    empl->apYNom[TAM_APYNOM]='\0';

    *act = '\0';
    sscanf(linea, "%d", &empl->dni);

    return TODO_OK;
}

int txtFijoABin(char* linea, Empleado* empl)
{
    char* act = strchr(linea, '\n');

    if(!act)
        return ERROR_LINEA_LARGA;

    *act = '\0';
    act -= TAM_SUELDO;
    sscanf(act, "%f", &empl->sueldo);

    *act = '\0';
    act -= TAM_FECHA;
    sscanf(act,"%2d/%2d/%4d", &empl->fechaIngr.dia, &empl->fechaIngr.mes, &empl->fechaIngr.anio);

    *act = '\0';
    act -= TAM_SEXO;
    empl->sexo = *act;

    *act = '\0';
    act -= TAM_APYNOM;
    strcpy(empl->apYNom, act);
    rTrim(empl->apYNom);

    *act = '\0';
    sscanf(linea, "%d", &empl->dni);

    return TODO_OK;
}
