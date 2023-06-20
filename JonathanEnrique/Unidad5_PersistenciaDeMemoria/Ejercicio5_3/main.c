#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//char* cantEnterosFormato(char* cad, int cant);

int main()
{
    int n;
    char cad[30];

    for(int i = 0; i < 5; i++)
    {
        scanf("%d", &n);
        sprintf(cad, "%6d ", n);
    }

    sprintf(cad, "\n");

    printf("|%s|", cad);
//

//    FILE* archTxt = fopen("datos.txt", "wt");
//
//    if(archTxt == NULL)
//        exit(-1);
//
//    fprintf(archTxt, "123456 123456 123456 123456 123456 123456 123456\n");
//
//    for(int i = 0; i < 5; i++)
//    {
//        scanf("%d", &n);
//        fprintf(archTxt, "%6d", n);
//        if(i < 5 - 1)
//            fprintf(archTxt, " ");
//    }
//
//    fprintf(archTxt, "\n");


//    printf("|%s|", cad);


//    fclose(archTxt);

//    char cad[30];
//    char formato[30] = "\0";
//    int n1;
//
//    scanf("%d", &n1);
//
//    sprintf(cad, cantEnterosFormato(formato, 1), n1);
//
//    printf("%s\n", cad);
//    printf("%s", formato);

    return 0;
}

//char* cantEnterosFormato(char* cad, int cant)
//{
//    char* cCad = cad;
//
//    for(int i = 1; i <= cant; i++)
//    {
//        strcat(cCad, "%d ");
//        cCad += 3;
//    }
//
//    *(cCad) = '\0';
//
//    return cad;
//}
