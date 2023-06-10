#include "main.h"

int main()
{
    Fecha fechaUser = ingresarFecha();

    printf("Dir fechaUser: %p", &fechaUser);

    int dias;

    scanf("%d", &dias);
    Fecha fSuma = sumarDiasFecha(fechaUser, dias);
    printf("La suma es %d/%d/%d", fSuma.dia, fSuma.mes, fSuma.anio);

    return 0;
}
