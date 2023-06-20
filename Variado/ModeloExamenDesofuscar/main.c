#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 512

//#define RENDIREXAMEN
#ifdef RENDIREXAMEN
    #define desofuscarArchivo _desofuscarArchivo
#endif // EXAMEN

#define ARCHIVOOFUSCADO     "ofuscado.txt"
#define ARCHIVODESOFUSCADO  "desofuscado.txt"

char* buscarCaracterEnCad(char c, const char* cad);

int main()
{
    /*
    Ejercicio tipo examen
    ----------------------

    Desofusque el archivo de texto generado por la funcion crearArchivoFrasesOfuscadasPorPosicion
    Cada palabra de las citas presentes se ha ofuscado tomando cada letra y si la misma se encuentra en el grupo
    "abcdghijkoqtuv" se remplaza por la letra que esta hacia la izquierda tantos lugares como posicion en la palabra
    ocupa. Una palabra es un conjunto contiguo de caracteres considerados por la funcion isalpha.
    Ejemplo:
    Si la palabra es hola
    "h":un lugar atras porque es la primera letra de la palabra, queda "g"
    "o":dos lugares atras, queda "j"
    "l":No figura en grupo, no se modifica, queda "l"
    "a":cuatro lugares hacia atras, queda "q".
    Resultado esperado: hola => gjlq
    Sabiendo como se ha ofuscado implemente un algoritmo que le muestre la frase desofuscada.

    Algunos consejos:
    .Antes de codificar piense una estrategia de solucion
    .Separe el problema en partes y prueba individualmente cada una si es necesario.

    .
    Disclaimer: Las citas no representan las opiniones de quien formulo el ejercicio :)
    */



//    if(!crearArchivoFrasesOfuscadasPorPosicion(ARCHIVOOFUSCADO)){
//        puts("No se pudo crear archivo de frases ofuscadas");
//    }
//
//    desofuscarArchivo(ARCHIVOOFUSCADO, ARCHIVODESOFUSCADO);

     char cad[] = "abcdghijkoqtuv";
     char palabraOfuscada[] = "gjlqminoa";
//     char* finPal = palabraOfuscada + strlen(palabraOfuscada) - 1;
//     char* finCad = cad + strlen(cad) - 1;
     char* cCad,
           *cPal = palabraOfuscada;

    int desplazamiento;

     while(*cPal)
     {
         if((cCad = buscarCaracterEnCad(*cPal, cad)))
         {
            desplazamiento = ((cPal - palabraOfuscada)) + 1;

            if(((cCad - cad) + desplazamiento) >= strlen(cad))
                cCad = cad + (((cCad - cad) + desplazamiento) % strlen(cad));
            else
                cCad += desplazamiento;

            *cPal = *cCad;
         }

         cPal++;
     }

    printf("%s", palabraOfuscada);

    return 0;
}

char* buscarCaracterEnCad(char c, const char* cad)
{
    char* cCad = (char*)cad;

    while(*cCad && *cCad != c){
        cCad++;
    }

    return *cCad ? cCad : NULL;
}
