#include <stdio.h>
#include <stdlib.h>

void PedidoNumeros(FILE*,int*,int*);

int main()
{
    FILE *fp=fopen("Numeros.txt","wt");
    if(fp==NULL)
        exit(1);
    int One=0,Seven=0;
    int K=rand()%10,X=0;
    fprintf(fp,"123456 123456 123456 123456 123456 123456 123456\n");
    while(!(One==1&&Seven==1) ){
    PedidoNumeros(fp,&One,&Seven);
    }
    while(X<K){
        PedidoNumeros(fp,&One,&Seven);
        X++;
    }
    fclose(fp);
    return 0;
}
void PedidoNumeros(FILE *fp,int* O,int* S){
    int M=(rand()%7)+1;
    printf("Ingresa %d numeros\n",M);//7
    for(int i=0;i<M;i++){///7 ->0 6
        short int N;
        scanf("%hd",&N);
        fprintf(fp,"%6hu ",N);
    }
    fprintf(fp,"\n");
    if(M==1)
        *O=1;
    else if(M==7)
        *S=1;
}
