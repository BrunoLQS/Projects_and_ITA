/* Copyright by Bruno Lima Queiroz Santos*/
/* Turma 3                              */
/* Lab 02:  */
/* */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int k,base,soma,esq,dir,qtdPrimo,qtdQp,somaM3,qtdImp,qtdP;
// base � o n�mero inserido pelo usu�rio que origina os demais; o k � o contador;
char c; // � o caractere que define a vontade do usu�rio prosseguir ou n�o com os ciclos.

void imprimirB (int base, int shiftado) {// fun��o para imprimir os n�meros na tela da televis�o em bin�rio
    int numBits=8;
    int i = numBits;

    while(i>0){

        if (isalpha(base)){
            if (shiftado&128)
                printf("%c",base);
            else
                printf(".");
        }
        else{
             if (shiftado&128)
                printf("1");
            else
                printf("0");
        }
        i--;
        shiftado<<=1;
    }
        return ;

}

int shift1 (int inicial){ //fun��o para deslocar o n�mero 1 bit a direita de cima para baixo no lado esquerdo da tv.
    int a;
    a= inicial&1;
    inicial = ((inicial>>1)+(a*128));
    return inicial;
}
int shift3 (int ini){ // fun��o para deslocar o n�mero 3 bits � esquerda de baixo para cima no lado direito da tv.
    int i = 3;
    while(i>0){
        ini = shift1(ini);
        i--;
    }

}
int ehPrimo(int n){ // fun��o para verificar se o n�mero � primo
        int i=1;
        if (n==1)
            return 0;

        while(i*i<=n)
        {

        if (n%i==0)
          return 0;

          i++;
        }
        return 1;
}
int ehQP(int n){// fun��o para verificar se � quadrado perfeito
        int i=1;
        if (n==1)
            return 0;

        while(i*i<=n)
        {

        if (i*i==n)
          return 1;

          i++;
        }
        return 0;
}
int imp(int n) {// fun��o para verificar se o n�mero � par, sen�o � �mpar
if (n%2==0)
    return 0;
else
    return 1;
}
int m3(int n) {// fun��o para verificar se o n�mero � m�ltiplo de 3
    if(n%3==0)
        return n;
    else
        return 0;
}
int main () {
    printf("\n\t a TV ASC-II consiste em apresentar o numero digitado em binario com base selecionada");
    c= 's';
   while (c == 'S' || c == 's') {
        printf("\n\t Digite o numero [0,255] a partir do qual montarah-se a TV ASC- II:\n\n");
        int valido = 0,valido2 =0;
        int base = -1;
        while (valido ==0){
            scanf("%d",&base);
            fflush(stdin);
            if (base>=0 && base <=255)
                valido = 1;
            else
                printf("\nNumero Invalido, digite novamente: ");
            }

        esq = base;
        dir = shift3(base);
        k=soma=qtdP=qtdQp=qtdImp=qtdPrimo=somaM3=0;


        printf("\n\n\t\t        \\    /");
        printf("\n\t\t         \\  /");
        printf("\n\t\t          \\/");
        printf("\n\t\t_______________________");
        printf("\n\t\t| ___________________ |");
        while(k<8){

            printf("\n\t\t| |");
            imprimirB(base,esq);
            printf("|");
            imprimirB(base,dir);
            printf("| |");
            soma+=esq+dir;
            qtdPrimo+=ehPrimo(esq)+ehPrimo(dir);
            qtdQp+=ehQP(esq)+ehQP(dir);
            somaM3+=m3(esq)+m3(dir);
            qtdImp+=imp(esq)+imp(dir);
            qtdP=16- qtdImp;
            esq = shift1(esq);
            dir = shift3(dir);
            k++;

        }
        printf("\n\t\t| ------------------- |");
        printf("\n\t\t| o o o o           O |");
        printf("\n\t\t|_____________________|");


        printf("\n\nSOMA DOS NUMEROS : \n\t%d",soma);
        printf("\n\nQUANTIDADE DE PRIMOS : \n\t%d",qtdPrimo);
        printf("\n\nQUANTIDADE DE QUADRADOS PERFEITOS : \n\t%d",qtdQp);
        printf("\n\nSOMA DOS MULTIPLOS DE 3 : \n\t%d",somaM3);
        printf("\n\nQUANTIDADE DE IMPARES  : \n\t%d",qtdImp);
        printf("\n\nQUANTIDADE DE PARES : \n\t%d\n\n",qtdP);




        printf("Deseja testar outro numero?(s/n) ");

        while (valido2 ==0){
            scanf("%c",&c);
            fflush(stdin);
            if (c == 'n' || c == 'N'|| c == 's' || c == 'S')
                valido2 = 1;
            else
                printf("\nCaracter Invalido, digite novamente: ");
            }



    }
    return 0;
    system("PAUSE");
}
