#include "Cadena.h"


int main()
{
    char cadOrig[] = "@#$%esTO%^$&*eS{}:uNA@#$%CadENa#$%^";
    char cadDest[100];

    // normalizarCadena(cadOrig, cadDest);

    normalizarCadena2(cadOrig, cadDest);

    printf("%s\n", cadDest);

    /// PARA VER CADENA EN DEBUG
    /// Escribir en Watches "cadDest"
    /// Ir a properties de "cadDest"
    /// Seleccionar formato "character"
    /// Tildar "Watch as array"
    /// Indicar cantidad en "Count"

    /// En la guia esta tenemos varios ej, hacer la palabra mas larga,
    /// funcion que indicar la longitud de palabra,
    /// hallar palabra que mas veces se repite en texto

    /// Aparte normalizar apellido y nombre
    /// variante es que APELLIDO TODO MAYUSCULA
    /// ejemplo nicolas, CARO (buscamos , para hacer toupper)
    /// mas de una coma debemos corregir

    return 0;
}
