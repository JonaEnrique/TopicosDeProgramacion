#include "integrador.h"

/**** PARA TESTEO DE ARCHIVOS ****/

void imprimirIndice(tIndiceAlumno* indice, int* cantElementos)
{
    tIndiceAlumno* cursorIndice = indice;
    tIndiceAlumno* cursorIndiceFin = indice+(*cantElementos-1);
    while(cursorIndice<=cursorIndiceFin)
    {
        printf("DNI:%d, POS:%d\n", cursorIndice->dni, cursorIndice->pos);
        cursorIndice++;
    }
}

int leerYmostraArchivo(char* nombreArchivo)
{
    tAlumno alum;
    FILE *fp = fopen(nombreArchivo, "rb");
    if(!fp)
    {
        return -1;
    }
    fread(&alum, sizeof(tAlumno), 1, fp);
    while(!feof(fp))
    {
        imprimirAlumno(&alum);
        fread(&alum, sizeof(tAlumno), 1, fp);
    }
    fclose(fp);
    return 0;
}

/**** PARA TESTEO DE ARCHIVOS ****/

Fecha ingresarFecha(void)
{
    Fecha fecha;
    printf("Ingrese fecha del proceso en formato dia/mes/ano.\n");
    scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
    while(!esFechaValida(&fecha))
    {
        printf("Fecha erronea, ingrese nuevamente la fecha en formato dia/mes/año.\n");
        scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
    }
    return fecha;
}

bool esFechaValida(const Fecha* fecha)
{
    if(fecha->anio >= ANIO_BASE)
        if(fecha->mes >= 1 && fecha->mes <= 12)
            if(fecha->dia >= 1 && fecha->dia <= cantDiasMes(fecha))
            {
                return true;
            }

    return false;
}

int cantDiasMes(const Fecha* fecha)
{
    int cdm[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(fecha->mes == 2 && esBisiesto(fecha->anio))
        return 29;
    else
        return cdm[fecha->mes];
}

void validarArchivo(const char* nombreArchivo)
{
    FILE* fpBin = fopen(nombreArchivo, "rb");
    if(!fpBin)
        printf("No se pudo abrir");
    fclose(fpBin);
}

int cmpIndice(const void* pt1, const void* pt2)
{
    tIndiceAlumno* indice1 = (tIndiceAlumno*) pt1;
    tIndiceAlumno* indice2 = (tIndiceAlumno*) pt2;
    return indice1->dni-indice2->dni;
}

tIndiceAlumno* crearIndiceDinamico(const char* nombreArchivo, int* cantElemIndice )
{
    int contador = 0;
    tAlumno alumno;

    FILE* fpBin;

    fpBin = fopen(nombreArchivo, "rb");

    if(!fpBin)
    {
        printf("No se pudo leer el archivo %s.\n", nombreArchivo);
        return NULL;
    }

    /// Averiguo tamaño
    size_t tamanio;
    fseek(fpBin, 0L, SEEK_END);
    tamanio = ftell(fpBin);
    tamanio = tamanio/sizeof(tAlumno);

    /// Creo estructura para indice
    tIndiceAlumno* indiceAlumnos = malloc(sizeof(tIndiceAlumno)*tamanio);
    tIndiceAlumno* cursorIndiceAlumnos = indiceAlumnos;

    /// Reacomodo puntero
    rewind(fpBin);

    fread(&alumno, sizeof(tAlumno), 1, fpBin);
    while(!feof(fpBin))
    {
        cursorIndiceAlumnos->dni = alumno.dni;
        cursorIndiceAlumnos->pos = contador;
        cursorIndiceAlumnos++;
        contador++;
        fread(&alumno, sizeof(tAlumno), 1, fpBin);
    }
    fclose(fpBin);

    *cantElemIndice = tamanio;
    ordenar(indiceAlumnos, cantElemIndice, sizeof(indiceAlumnos), cmpIndice);

    return indiceAlumnos;
}

void menu(tIndiceAlumno* indice, const char* nombreArchivo, int* cantElemIndice, const Fecha* fechaProceso)
{
    char opcion[50];
    do
    {
    menuSinErr("Elija una opcion\n\n"
                        "A - Alta\n"
                        "B1 - Baja\n"
                        "B2 - Buscar\n"
                        "L1 - Listar los dados de baja\n"
                        "L2 - Listar en orden\n"
                        "S - Salir\n"
                        "--> ",
                        "AB1B2L1L2S", opcion);
    printf("Opcion elegida: %s\n", opcion);
    llamarOpcion(opcion, indice, nombreArchivo, cantElemIndice, fechaProceso); // lo hice return int para que pueda saltarme if que faltan
    }while(strcmp(opcion,"S")!=0);
}

void menuSinErr(const char* msj, const char* opc, char* cadenaGuardado) // HECHO PARA EVITAR UN NULL
{
    do
    {
        printf("%s", msj);
        fflush(stdin);
        scanf("%s", cadenaGuardado);
    }while(strstr((const char*) opc, (const char*) cadenaGuardado) == NULL);
}

void llamarOpcion(const char* opcion, tIndiceAlumno* indice, const char* nombreArchivo, int* cantElemIndice, const Fecha* fechaProceso)
{
    if(strcmp(opcion, "A")==0)
    {
        alta(indice, nombreArchivo, cantElemIndice, fechaProceso);
    }
    else if(strcmp(opcion, "B1")==0)
    {
        baja(indice, nombreArchivo, cantElemIndice, fechaProceso);
    }
    else if(strcmp(opcion, "B2")==0)
    {
        buscar(indice, nombreArchivo, cantElemIndice);
    }
    else if(strcmp(opcion, "L1")==0)
    {
        listar1(nombreArchivo);
    }
    else //if(strcmp(opcion, "L2")==0)
    {
        listar2(indice, nombreArchivo, cantElemIndice);
    }
}

int crearArchivo(char* nombreArchivo, tAlumno* estructura, int cantElem)
{
    FILE *fp;
    if(!(fp=fopen(nombreArchivo, "wb")))
    {
        printf("Error al crear el archivo \"%s\" .\n", nombreArchivo);
        return -1;
    }
    fwrite((estructura), sizeof(tAlumno), cantElem, fp);
    fclose(fp);
    return 0;
}


void ordenar(void* vector, const int* tamVector, size_t tamElemento, Cmp cmp)
{
    int i, j, menorPos;
    for(i= 0; i < (*tamVector)-1; i++)
    {
        menorPos = i;
        for(j = i+1; j < (*tamVector); j++)
        {
            if(cmp(vector+menorPos*tamElemento, vector+j*tamElemento) > 0)
                menorPos = j;
        }

        intercambiar(vector+i*tamElemento, vector+menorPos*tamElemento, tamElemento);
    }

}

void intercambiar(void* a, void* b, size_t tamElem)
{
    void* aux = malloc(tamElem);

    memcpy(aux, a, tamElem);
    memcpy(a, b, tamElem);
    memcpy(b, aux, tamElem);

    free(aux);
}

void alta(tIndiceAlumno* indice, const char* nombreArchivo, int* cantElemIndice, const Fecha* fechaProceso)
{
    int dniIngresado = 0, hallado = 0, invalido = 0;
    tIndiceAlumno* cursorIndice = indice;
    tIndiceAlumno* cursorIndicefin = indice+(*cantElemIndice-1);
    /// indice + cantidad elementos, no multiplico porque conoce su tipo de dato.

    tAlumno alum;
    FILE* fpBin;

    printf("Ingrese el dni del alumno.");
    scanf("%d", &dniIngresado);
    fflush(stdin);

    /// calculo totalidad Indice

    /// Validar dni en Indice
    while(hallado != 1 && cursorIndice<=cursorIndicefin)
    {
        if(dniIngresado == cursorIndice->dni)
        {
            hallado = 1;
        }
        cursorIndice++;
    }

    if(hallado==1)
    {
        printf("Este dni ya existe en el listado de alumnos.");
        return;
    }
    alum.dni = dniIngresado;

    printf("Ingrese el apellido y nombre, EJ: Caballero, Lucas.\n");
    fgets(alum.apeYNom, 50, stdin);
    size_t tam = strlen(alum.apeYNom);
    alum.apeYNom[tam-1]='\0';
    fflush(stdin);
    printf("Ingrese el fecha de nacimiento en formato: dd/mm/aaaa .\n");
    scanf("%d/%d/%d", &alum.fechaNacimiento.dia, &alum.fechaNacimiento.mes, &alum.fechaNacimiento.anio);
    fflush(stdin);
    printf("Ingrese sexo.\n");
    scanf("%c", &alum.sexo);
    fflush(stdin);
    printf("Ingrese la carrera: INF, ELE, IND, ECO, DER, ADM, MED, EDF, FIL.\n");
    fgets(alum.carrera, 4, stdin);
    printf("Ingrese la cantidad de materia aprobadas.\n");
    scanf("%d", &alum.matAprobadas);
    fflush(stdin);

    if(esFechaValida(&alum.fechaNacimiento)==0)
        invalido = 1;

    ///paso todas las evaluaciones
    alum.fechaIngreso.dia = fechaProceso->dia;
    alum.fechaIngreso.mes = fechaProceso->mes;
    alum.fechaIngreso.anio = fechaProceso->anio;
    alum.estado = 'A';

    /// Abrir archivo
    fpBin = fopen(nombreArchivo, "r+b");
    if(invalido==0)
    {
        fseek(fpBin, 0L, SEEK_END);
        fwrite(&alum, sizeof(tAlumno), 1, fpBin);
        /// Amplio Indice
        indice = realloc(indice, (*cantElemIndice+1)*sizeof(tIndiceAlumno));
        if(!indice) // seria (indice==NULL)
            {
            printf("Fallo realloc");
            invalido=1;
            }
        if(invalido==0)
            {
                cursorIndice = indice+(*cantElemIndice);
                cursorIndice->dni = alum.dni;
                cursorIndice->pos = *cantElemIndice;
                *cantElemIndice+=1;
                ordenar(indice, cantElemIndice, sizeof(indice), cmpIndice);
                imprimirIndice(indice, cantElemIndice);
            }
    }

    /** PARA MOSTRAR **/
    fseek(fpBin, 0L, SEEK_SET);
    fread(&alum, sizeof(tAlumno), 1, fpBin);
    while(!feof(fpBin))
    {
        imprimirAlumno(&alum);
        fread(&alum, sizeof(tAlumno), 1, fpBin);
    }

    fclose(fpBin);
}

void eliminarAluIndice(tIndiceAlumno* indice, const int* posicion, const int* cantElemIndice)
{
    tIndiceAlumno* cursorIndiceFin = indice+(*cantElemIndice-1);
    tIndiceAlumno* cursorIndice =indice+(*posicion);

    while(cursorIndice <= cursorIndiceFin)
    {
        *cursorIndice=*(cursorIndice+1);
        cursorIndice++;
    } /// Asignamos memoria dinamica de nuevo
    indice = realloc(indice, (*cantElemIndice-1)*sizeof(tIndiceAlumno));
}

void baja(tIndiceAlumno* indice, const char* nombreArchivo, int* cantElemIndice, const Fecha* fechaProceso)
{
    int dniBaja = 0, hallado = 0;
    FILE* fpBin = fopen(nombreArchivo, "r+b");
    tAlumno alum;
    tIndiceAlumno* cursorIndice = indice;
    tIndiceAlumno* cursorIndiceFin = indice+(*cantElemIndice-1);

    printf("Ingrese el dni del alumno a dar de baja.\n");
    scanf("%d", &dniBaja);

    while(hallado != 1 && cursorIndice<=cursorIndiceFin)
    {
        if(dniBaja==cursorIndice->dni)
        {
            hallado = 1;
        }
        cursorIndice++;
    }
    cursorIndice--;

    if(hallado==0)
    {
        printf("No existe el alumno buscado.\n");
        return;
    }
    else //if(hallado==1)
    {
        fseek(fpBin, (long)(sizeof(tAlumno)*(cursorIndice->pos)), SEEK_CUR);
        fread(&alum, sizeof(tAlumno), 1, fpBin);
        fseek(fpBin, -(long)(sizeof(tAlumno)), SEEK_CUR);
        // fseek(fpBin, 0L, SEEK_CUR); /// DESPUES DE FREAD HACER FSEEK SINO HACE CUALQUIER COSA, ya hice previamente.
        alum.estado='B';
        alum.fechaIngreso.dia = fechaProceso->dia;
        alum.fechaIngreso.mes = fechaProceso->mes;
        alum.fechaIngreso.anio = fechaProceso->anio;
        fwrite(&alum, sizeof(tAlumno), 1, fpBin);
        eliminarAluIndice(indice, &cursorIndice->pos, cantElemIndice);
    }
    fclose(fpBin);
}

void imprimirAlumno(const tAlumno* alumno)
{
    printf("%8ld%-50s%2d/%2d/%4d%c%2d/%2d/%4d%-50s%d%c\n",
            alumno->dni,
            alumno->apeYNom,
            alumno->fechaNacimiento.dia,
            alumno->fechaNacimiento.mes,
            alumno->fechaNacimiento.anio,
            alumno->sexo,
            alumno->fechaIngreso.dia,
            alumno->fechaIngreso.mes,
            alumno->fechaIngreso.anio,
            alumno->carrera,
            alumno->matAprobadas,
            alumno->estado);
}

void buscar(tIndiceAlumno* indice, const char* nombreArchivo, const int* cantElemIndice)
{
    int hallado = 0, dniAlumno = 0;
    tIndiceAlumno* cursorIndice = indice;
    tIndiceAlumno* cursorIndiceFin = indice+(*cantElemIndice-1);
    tAlumno alum;

    FILE* fpBin = fopen(nombreArchivo, "rb");
    if(!fpBin)
    {
        printf("Falla al realizar lectura del archivo %s.\n", nombreArchivo);
        return;
    }

    printf("Ingrese el dni del alumno a buscar, sin incluir puntos.\n");
    scanf("%d", &dniAlumno);

    while(hallado != 1 && cursorIndice<=cursorIndiceFin)
    {
        if(cursorIndice->dni==dniAlumno)
            hallado = 1;
        cursorIndice++;
    }
    cursorIndice--;

    if(hallado == 1)
    {
        fseek(fpBin, (long)(cursorIndice->pos*sizeof(tAlumno)), SEEK_CUR);
        fread(&alum, sizeof(tAlumno), 1, fpBin);
        if(alum.estado == 'B')
        {
            printf("El dni ingresado no esta registrado como alumno.\n");
            return;
        }
        else
        {
            imprimirAlumno(&alum);
        }

    }
    else
    {
        printf("El dni ingresado no esta registrado como alumno.\n");
        return;
    }
    fclose(fpBin);
}

void listar1(const char* nombreArchivo)
{
    FILE* fpBin = fopen(nombreArchivo, "rb");
    if(!fpBin)
    {
        printf("No se pudo abrir el archivo %s\n.", nombreArchivo);
        return;
    }

    tAlumno alum;
    fread(&alum, sizeof(tAlumno), 1, fpBin);
    while(!feof(fpBin))
    {
        if(alum.estado == 'B')
            imprimirAlumno(&alum);
        fread(&alum, sizeof(tAlumno), 1, fpBin);
    }
}

void listar2(tIndiceAlumno* indice, const char* nombreArchivo, const int* cantElemIndice)
{
    tIndiceAlumno* cursorIndice = indice;
    tIndiceAlumno* cursorIndiceFin = indice+*cantElemIndice;

    FILE* fpBin = fopen(nombreArchivo, "rb");
    if(!fpBin)
    {
        printf("No se puedo abrir el archivo%s.\n", nombreArchivo);
        return;
    }
    /// TERMINAR ESTO.

}


