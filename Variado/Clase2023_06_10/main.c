#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERR_ARCH 1
#define TAM_VEC_PROD 5
#define TAM_VEC_MOV 10

typedef struct {
    char codigo[5];
    char descripcion[30];
    float precio;
    int stock;
}Producto;

typedef struct {
    char codigo[5];
    int cantidad;
    char tipo;
}Movimiento;

void crearArchivoProd(const char* pathProd);
void crearArchivoMov(const char* pathMov);
void procesarProdNuevo(Movimiento* mov, FILE* archMovs, FILE* archProdsAct);
int actualizaciorProds(const char* nombreArchProds, const char* nombreArchMovs);
int compararMovimientos(const void* a, const void* b);
int compararProductos(const void* a, const void* b);
void mostrarArchivoProd(const char* path);
void mostrarArchivoMov(const char* path);
int pasarDeBinATxtProd(const char* pathProductosBin, const char* pathProductosTxt, char tipoTxt);
int pasarDeTxtABinProd(const char* pathProductosTxt, const char* pathProductosBin, char tipoTxt);
void trozarCamposProd(char* cad, Producto* prod, char tipoTxt);

int main(int argc, char *argv[])
{
    crearArchivoProd(argv[1]);
    crearArchivoMov(argv[2]);

    pasarDeBinATxtProd(argv[1], argv[3], 'V');
    pasarDeTxtABinProd(argv[3], argv[1], 'V');

    puts("Archivo de productos antes de actualizar: \n");
    mostrarArchivoProd(argv[1]);

    puts("\nArchivo de movimientos: \n");
    mostrarArchivoMov(argv[2]);

    actualizaciorProds(argv[1], argv[2]);

    puts("\nArchivo productos despues de actualizar: \n");
    mostrarArchivoProd(argv[1]);

//    FILE* arch = fopen(argv[1], "r + b");
//
//    if(!arch)
//    {
//        printf("No se pudo abrir el archivo");
//        return ERR_ARCH;
//    }
//
//    float porc = atof(argv[2])/100 + 1;
//    Producto prodNue;
//
//    fread(&prodNue, sizeof(Producto), 1, arch);
//
//    while(!feof(arch))
//    {
//        printf("%s %s %f %d\n", prodNue.codigo, prodNue.descripcion, prodNue.precio, prodNue.stock);
//
//        prodNue.precio *= porc;
//
//
//        fseek(arch, -(long)sizeof(Producto), SEEK_CUR);
//        fwrite(&prodNue, sizeof(Producto), 1, arch);
//        fseek(arch, 0, SEEK_CUR);
//
//        fread(&prodNue, sizeof(Producto), 1, arch);
//    }
//
//    fclose(arch);

    return 0;
}

int actualizaciorProds(const char* nombreArchProds, const char* nombreArchMovs)
{
    FILE* archProds = fopen(nombreArchProds, "rb");
    FILE* archMovs = fopen(nombreArchMovs, "rb");
    FILE* archProdsAct = fopen("prodsAct.temp", "wb");

    int comp;
    Producto prodNue;
    Movimiento mov;

    fread(&prodNue, sizeof(Producto), 1, archProds);
    fread(&mov, sizeof(Movimiento), 1, archMovs);

    while(!feof(archProds) && !feof(archMovs))
    {
        comp = strcmp(prodNue.codigo, mov.codigo);

        if(comp == 0)
        {
            prodNue.stock += mov.cantidad;

            fread(&mov, sizeof(Movimiento), 1, archMovs);
        }

        if(comp < 0)
        {
            fwrite(&prodNue, sizeof(Producto), 1, archProdsAct);
            fread(&prodNue, sizeof(Producto), 1, archProds);
        }

        if(comp > 0)
        {
            procesarProdNuevo(&mov, archMovs, archProdsAct);
        }
    } // while

    while(!feof(archProds))
    {
        fwrite(&prodNue, sizeof(Producto), 1, archProdsAct);
        fread(&prodNue, sizeof(Producto), 1, archProds);
    }

    while(!feof(archMovs))
    {
        procesarProdNuevo(&mov, archMovs, archProdsAct);
    }

    fclose(archProds);
    fclose(archMovs);
    fclose(archProdsAct);

    remove(nombreArchProds);
    rename("prodsAct.temp", nombreArchProds);

    return 0;
}

void procesarProdNuevo(Movimiento* mov, FILE* archMovs, FILE* archProdsAct)
{
    Producto prodNue;

    strcpy(prodNue.codigo, mov->codigo);
    prodNue.stock = mov->cantidad;

    *prodNue.descripcion = '\0';

    fread(mov, sizeof(Movimiento), 1, archMovs);

    while(!feof(archMovs) && strcmp(prodNue.codigo, mov->codigo) == 0)// Corte de control?
    {
        prodNue.stock += mov->cantidad;
        fread(mov, sizeof(Movimiento), 1, archMovs);
    }

    fwrite(&prodNue, sizeof(Producto), 1, archProdsAct);
}

void crearArchivoProd(const char* pathProd)
{
    FILE* archProd = fopen(pathProd, "wb");

    if(!archProd)
        return;

    Producto vecProd[TAM_VEC_PROD] = { {"ABCD", "desc", 1000.00, 5},
                                  {"EFGH", "desc", 2000.00, 10},
                                  {"IJKL", "desc", 1800.50, 8},
                                  {"MNOP", "desc", 1000.00, 7},
                                  {"RSTU", "desc", 2500.90, 10} };

    fwrite(vecProd, sizeof(Producto), TAM_VEC_PROD, archProd);

    qsort(vecProd, TAM_VEC_PROD, sizeof(Producto), compararProductos);

    fclose(archProd);
}

void crearArchivoMov(const char* pathMov)
{
    FILE* archMov = fopen(pathMov, "wb");

    if(!archMov)
        return;

    Movimiento vecMov[TAM_VEC_MOV] = { {"ABCD", 5, 'E'},
                                  {"EFGH", 10, 'S'},
                                  {"IJKL", 8, 'E'},
                                  {"MNOP", 7, 'S'},
                                  {"RSTU", 10, 'E'},
                                  {"ABCD", 5, 'S'},
                                  {"EFGH", 10, 'E'},
                                  {"IJKL", 8, 'S'},
                                  {"NUEV", 7, 'E'},
                                  {"NUEV", 10, 'S'} };

    qsort(vecMov, TAM_VEC_MOV, sizeof(Movimiento), compararMovimientos);

    fwrite(vecMov, sizeof(Movimiento), TAM_VEC_MOV, archMov);

    fclose(archMov);
}

int compararMovimientos(const void* a, const void* b)
{
    Movimiento* movA = (Movimiento*)a;
    Movimiento* movB = (Movimiento*)b;

    return strcmp(movA->codigo, movB->codigo);
}

int compararProductos(const void* a, const void* b)
{
    Producto* prodA = (Producto*)a;
    Producto* prodB = (Producto*)b;

    return strcmp(prodA->codigo, prodB->codigo);
}

void mostrarArchivoProd(const char* path)
{
    FILE* arch = fopen(path, "rb");

    if(!arch)
        return;

    Producto prod;

    fread(&prod, sizeof(Producto), 1, arch);

    while(!feof(arch))
    {
        printf("%s %s %f %d\n", prod.codigo, prod.descripcion, prod.precio, prod.stock);
        fread(&prod, sizeof(Producto), 1, arch);
    }

    fclose(arch);
}

void mostrarArchivoMov(const char* path)
{
    FILE* arch = fopen(path, "rb");

    if(!arch)
        return;

    Movimiento mov;

    fread(&mov, sizeof(Movimiento), 1, arch);

    while(!feof(arch))
    {
        printf("%s %d %c\n", mov.codigo, mov.cantidad, mov.tipo);
        fread(&mov, sizeof(Movimiento), 1, arch);
    }

    fclose(arch);
}

int pasarDeBinATxtProd(const char* pathProductosBin, const char* pathProductosTxt, char tipoTxt)
{
    FILE* archProdBin = fopen(pathProductosBin, "rb");
    FILE* archProdTxt = fopen(pathProductosTxt, "wt");

    if(!archProdBin || !archProdTxt)
         return ERR_ARCH;

    Producto actProd;

    fread(&actProd, sizeof(Producto), 1, archProdBin);

    while(!feof(archProdBin))
    {
        fprintf(archProdTxt, tipoTxt == 'V' ? "%s|%s|%f|%d\n" : "%5s%15s%5.2f%2d\n", actProd.codigo,
                                                                                 actProd.descripcion,
                                                                                 actProd.precio,
                                                                                 actProd.stock);

        fread(&actProd, sizeof(Producto), 1, archProdBin);
    }

    fclose(archProdBin);
    fclose(archProdTxt);

    return 1;
}

int pasarDeTxtABinProd(const char* pathProductosTxt, const char* pathProductosBin, char tipoTxt)
{
    FILE* archProdBin = fopen(pathProductosBin, "wb");
    FILE* archProdTxt = fopen(pathProductosTxt, "rt");

    if(!archProdBin || !archProdTxt)
         return ERR_ARCH;

    char cad[1000];
    Producto actProd;

    fgets(cad, sizeof(cad), archProdTxt);

    while(!feof(archProdTxt))
    {
        trozarCamposProd(cad, &actProd, tipoTxt);

        fwrite(&actProd, sizeof(Producto), 1, archProdBin);

        fgets(cad, sizeof(cad), archProdTxt);
    }

    return 1;
}

void trozarCamposProd(char* cad, Producto* prod, char tipoTxt)
{
    char* caracter = strchr(cad, '\n');
    *caracter = '\0';

    if(tipoTxt == 'V')
    {
        caracter = strrchr(cad, '|');
        sscanf(caracter + 1, "%d", &prod->stock);
        *caracter = '\0';

        caracter = strrchr(cad, '|');
        sscanf(caracter + 1, "%f", &prod->precio);
        *caracter = '\0';

        caracter = strrchr(cad, '|');
        sscanf(caracter + 1, "%s", prod->descripcion);
        *caracter = '\0';

        strcpy(prod->codigo, cad);
    }
}
