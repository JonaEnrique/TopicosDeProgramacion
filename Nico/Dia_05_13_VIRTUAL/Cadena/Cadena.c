#include "Cadena.h"

char* normalizarCadena(const char* cadOrig, char* cadDest)
{
    const char* orig = cadOrig;
    char* dest = cadDest;

    while(*orig)
    {
        while(*orig && !esLetra(*orig)) // siempre que avanzo chequeo si existe caracter nulo
            orig++;

        if(!*orig) // Si es caracter nulo O no hay caracter origen, (para que no quede todo ciclo adentro
        {
            *dest = '\0';
            return cadDest;
        }

        *dest = toupper(*orig);
        orig++;
        dest++;

        while(*orig && esLetra(*orig))
        {
            *dest = tolower(*orig);
            orig++;
            dest++;
        }

        *dest = ' '; // este es un espacio
        dest++;
    }

    *(dest-1) = '\0'; // recordar siempre poniamos un espacio;

    return cadDest;
} /// ESTO ERA LA PRIMERA VERSION

char* normalizarCadena2(const char* cadOrig, char* cadDest)
{
    SecuenciaPalabras secLect, secEscr;
    Palabra pal, palEscr;

    crearSecuenciaPalabras(&secLect, cadOrig);
    crearSecuenciaPalabras(&secEscr, cadDest);

    while(leerPalabra(&secLect, &pal))
    {
        // mostrarPalabra(&pal); //testeo
        // putchar(' '); // estos dos son para saber si funciona norCad2
        escribirPalabra(&secEscr, &pal, &palEscr); // agregamos que devuelva donde escibio
        aTitulo(&palEscr);
        escribirCaracter(&secEscr, ' ');
    }

    reposicionarSecuenciaPalabras(&secEscr, -1);
    cerrarSecuenciaPalabras(&secEscr);

    return cadDest;
}

void crearSecuenciaPalabras(SecuenciaPalabras* sec, const char* cad)
{
        sec->cursor = (char*)cad; // casteamos a char* solo para esta expresion (mentimos), asi no es char con const (da error)
}

bool leerPalabra(SecuenciaPalabras* sec, Palabra* pal)
{
    while(*sec->cursor && !esLetra(*sec->cursor))
        sec->cursor++;

    if(!*sec->cursor)
        return false;

    pal->ini = sec->cursor;
    sec->cursor++;

    while(*sec->cursor && esLetra(*sec->cursor))
            sec->cursor++;

    pal->fin = sec->cursor - 1;

    return true;
}

bool escribirPalabra(SecuenciaPalabras* sec, const Palabra* pal, Palabra* palEscr)
{
    palEscr->ini = sec->cursor;

    for(char* i = pal->ini; i <= pal->fin; i++, sec->cursor++)
        *sec->cursor = *i;

    palEscr->fin = sec->cursor - 1;

    return true;
}

bool escribirCaracter(SecuenciaPalabras* sec, char c)
{
    *sec->cursor = c;
    sec->cursor++;

    return true;
}

void aTitulo(Palabra* pal)
{
    *pal->ini = miToupper(*pal->ini);

    for(char *i = pal->ini + 1; i <= pal->fin; i++)  // ini+1 para no pasar a minus la primera
        *i = miTolower(*i);
}

void mostrarPalabra(const Palabra* pal) // para testear
{
    for(char* i = pal->ini; i <= pal->fin;i++ )
        putchar(*i);
}

bool reposicionarSecuenciaPalabras(SecuenciaPalabras* sec, int despl)
{
    sec->cursor += despl;
    return true;
}

void cerrarSecuenciaPalabras(SecuenciaPalabras* sec)
{
    *sec->cursor = '\0';
}
