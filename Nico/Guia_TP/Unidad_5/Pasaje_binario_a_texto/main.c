#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int dni;
    char ape[15];
    char nom[15];
    double sueldo;
}tEmpleado;

int crearArchivoEmpleado(char* nombreArchivo, tEmpleado* estructura, int cantElem);
int crearArchivoTextoDesdeBinarioTipoVariable(char* nombreArchivoOrigen, char* nombreArchivoDestino);
int crearArchivoTextoDesdeBinarioTipoFijo(char* nombreArchivoOrigen, char* nombreArchivoDestino);
int crearArchivoBinarioDesdeTextoTipoVariable(const char* nombreArchivoOrigen, const char* nombreArchivoDestino);
int leerYmostraArchivo(char* nombreArchivo);
void trozarCamposLongitudVariable(tEmpleado* estructura, char* cadena);
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

    crearArchivoEmpleado("Empleado.bin", vectorEmpleados, (sizeof(vectorEmpleados)/sizeof(tEmpleado)));
    crearArchivoTextoDesdeBinarioTipoVariable("Empleado.bin","EmpleadoTipoVariable.txt");
    crearArchivoTextoDesdeBinarioTipoFijo("Empleado.bin","EmpleadoTipoFijo.txt");
    crearArchivoBinarioDesdeTextoTipoVariable("EmpleadoTipoVariable.txt", "EmpleadoTipoVariable.bin");
    leerYmostraArchivo("EmpleadoTipoVariable.bin");

    return 0;
}

int crearArchivoEmpleado(char* nombreArchivo, tEmpleado* estructura, int cantElem)
{
    FILE *fp;
    if((fp=fopen(nombreArchivo, "wb")))
    {
        fwrite((estructura), sizeof(tEmpleado), cantElem, fp); /// FIX HORRENDO QUE PERMITE QUE ANDE FWRITE, PARA SEGUNDO PARAMETRO (NUM BYTES) TOMAR SIZEOF(PUNTERO)*SIZEOF(ESCTRUCTURA)-1
        fclose(fp);
        return 0;
    }
    return -2;
}

int crearArchivoTextoDesdeBinarioTipoVariable(char* nombreArchivoOrigen, char* nombreArchivoDestino)
{
    tEmpleado emp;
    FILE *fpBin,
         *fpText;

    fpBin = fopen(nombreArchivoOrigen, "rb");
    if(!fpBin)
    {
        return -1;
    }
    fpText = fopen(nombreArchivoDestino, "wt");
    if(!fpText)
    {
        return -2;
    }
    fread(&emp, sizeof(tEmpleado), 1, fpBin);
    while(!feof(fpBin))
    {
        fprintf(fpText, "%d|%s|%s|%.2lf\n",
                emp.dni,
                emp.ape,
                emp.nom,
                emp.sueldo);
        /// Utilizado para escribir archivos de texto
        /// para hacer formato fijo debo alterar con la longitud deseada
        /// EJEMPLO: fprintf(fpTextFijo,"%.*ld%-.*s%-.*s%.*f\n",SIZE_DNI,reg.dni,SIZE_NAME,reg.name,SIZE_SURNAME,reg.surName,SIZE_AVERAGE,reg.average)
        /// SIZE_DNI puede ser sizeof(emp.dni)
        fread(&emp, sizeof(tEmpleado), 1, fpBin);
    }
    fclose(fpBin);
    fclose(fpText);
    return 0;
}

int crearArchivoTextoDesdeBinarioTipoFijo(char* nombreArchivoOrigen, char* nombreArchivoDestino)
{
    tEmpleado emp;
    FILE* fpText,
        * fpBin;

    fpBin = fopen(nombreArchivoOrigen, "rb");
    if(!fpBin)
    {
        return -1;
    }

    fpText = fopen(nombreArchivoDestino, "wt");
    if(!fpText)
    {
        return -2;
    }

    fread(&emp, sizeof(tEmpleado), 1, fpBin);
    while(!feof(fpBin))
    {
        fprintf(fpText,"%08d%-*.*s%-*.*s%9.2lf\n",
                emp.dni,
                ((int)sizeof(emp.ape)-1),   // el *. generara un espacio en la impresion en archivo, el .* indicara cuanto imprime, el - ajusta argumento a la izquierda de su campo.
                ((int)sizeof(emp.ape)-1),
                emp.ape,
                ((int)sizeof(emp.nom)-1),
                ((int)sizeof(emp.nom)-1),
                emp.nom,
                emp.sueldo);
        fread(&emp, sizeof(tEmpleado), 1, fpBin);
    }

    fclose(fpText);
    fclose(fpBin);
    return 0;
}

int crearArchivoBinarioDesdeTextoTipoVariable(const char* nombreArchivoOrigen, const char* nombreArchivoDestino)
{
    char cad[500]; // tamaño elegido a cuenta propia (debe ser grande)
    tEmpleado emp;
    FILE *fpBin,
         *fpText;

    fpText = fopen(nombreArchivoOrigen, "rt");
    if(!fpText)
    {
        return -1;
    }

    fpBin = fopen(nombreArchivoDestino, "wb");
    if(!fpBin)
    {
        return -2;
    }

    while(fgets(cad, sizeof(cad), fpText))
    {
        trozarCamposLongitudVariable(&emp, cad);
        fwrite(&emp, sizeof(tEmpleado), 1, fpBin);
    }

    fclose(fpBin);
    fclose(fpText);
    return 0;
}

void trozarCamposLongitudVariable(tEmpleado* estructura, char* cadena)
{
    char* aux = strchr(cadena, '\n'); // localiza primera aparicion de c
    *aux = '\0';

    aux = strrchr(cadena, '|');// localiza ultima aparicion de c
    sscanf(aux+1, "%lf", &estructura->sueldo); // sumo uno para evitar caracter "|"
    *aux = '\0';

    aux = strrchr(cadena, '|');
    strcpy(estructura->ape, aux+1);
    *aux = '\0';

    aux = strrchr(cadena, '|');
    strcpy(estructura->nom, aux+1);
    *aux = '\0';

    sscanf(cadena, "%d", &estructura->dni);
}

/// Traidos de otro ejercicio
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



