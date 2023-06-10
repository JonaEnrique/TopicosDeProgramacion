#include <stdio.h>
#include <stdlib.h>

#define ERR_ARCH 1

typedef struct {
    char codigo[5];
    char descripcion[30];
    float precio;
    int stock;
}Producto;

typedef struct {
    int codigo[5];
    int cantidad;
    char tipo;
}Movimiento;

void procesarProdNuevo(Movimiento* mov, FILE* archMovs, FILE* archProdsAct);
int actualizaciorProds(const char* nombreArchProds, const char* nombreArchMovs);

int main(int argc, char *argv[])
{
    FILE* arch = fopen(argv[1], "r + b");

    if(!arch)
    {
        printf("No se pudo abrir el archivo");
        return ERR_ARCH;
    }

    float porc = atof(argv[2])/100 + 1;
    Producto prodNue;

    fread(&prodNue, sizeof(Producto), 1, arch);

    while(!feof(arch))
    {
        printf("%d %s %f %d\n", prodNue.codigo, prodNue.descripcion, prodNue.precio, prodNue.stock);

        prodNue.precio *= porc;


        fseek(arch, -sizeof(Producto), SEEK_CUR);
        fwrite(&prodNue, sizeof(Producto), 1, arch);
        fseek(arch, 0, SEEK_CUR);
        
        fread(&prodNue, sizeof(Producto), 1, arch);
    }

    fclose(arch);

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

    while(!feof(archMovs) && strcmp(prodNue.codigo, mov->codigo) == 0) // Corte de control?
    {
        prodNue.stock += mov->cantidad;
        fread(mov, sizeof(Movimiento), 1, archMovs);
    }

    fwrite(&prodNue, sizeof(Producto), 1, archProdsAct);
}
