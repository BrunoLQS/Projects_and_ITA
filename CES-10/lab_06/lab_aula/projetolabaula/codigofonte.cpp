/*  Copyright by BRUNO LIMA QUEIROZ SANTOS  */
/*  Turma 3                                 */
/*  Lab 06: Criptografia em arquivo texto   */
/*  Programa compilado com CodeBlocks 17.02 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct lista lista ;
struct lista
{/*struct para o uso da listal igada*/
    char letra;/*letra do arquivo*/
    int c;/*numero da letra*/
    lista *prox;
};
long int potenciacao(long int num,int exp,int d)
{/*potenciando base d,isto é, potenciando por modulo d*/
    int aux=num;
    for(int i=1;i<exp;i++)
    {
        num=num*aux;
        if(num>d)
            num=num%d;
    }
    return num;
}
int MDC(long int FI ,long int e)
{/*função que retorna o MDC entre FI and e*/
    long int a,b,c;
    a=FI,b=e,c=1;
    while(c!=0)
    {
        c=a%b;
        if(c!=0)
        {/*para a proxima iteraçao*/
            a=b;
            b=c;
        }
    }
    return b;
}
void recebedoisprimos(int *Pont1,int *Pont2,int *Primos)
{/*funcao para receber valores*/
    int entrada=0;
    int qtdeprimos=-1;
    do
    {
        system("cls");
        printf("\n\t\tDigite dois numeros primos menores que 100:");
        if(qtdeprimos==0||qtdeprimos==1)
        {/*caso o problema seja nao ter digitado valores primos*/
            printf("\n\t\tVoce digitou numeros nao primos.Digite denovo:");
        }
        else
        {/*caso o problema seja maior: valores fora do escopo */
            if(entrada==1)
                printf("\n\t\tVoce digitou numeros fora do escopo.Digite denovo:");
        }
        fflush(stdin);
        scanf("%d",Pont1);
        fflush(stdin);
        scanf("%d",Pont2);
        if(*Pont1>1&&*Pont2>1)
        {/*primeira verificacao dos numeros*/
            if(*Pont1<100&&*Pont2<100)
            {/*segunda verificacao dos numeros*/
                qtdeprimos=0;
                for(int i=1;i<=25;i++)
                {/*comparando os digitos com os primos menores que 100*/
                    if(*Pont1==*(Primos+i))
                        qtdeprimos+=1;
                    if(*Pont2==*(Primos+i))
                        qtdeprimos+=1;
                }
                if(qtdeprimos==2)/*se ambos sao primos*/
                    entrada=2;
            }
            else
            {/*digitos fora do escopo*/
                qtdeprimos=-1;
                entrada=1;
            }
        }
        else
        {/*digitos fora do escopo*/
            qtdeprimos=-1;
            entrada=1;
        }
    }while(entrada<2);
}
void conjunton(int*Pont1,int*Pont2,int*n, long int*FI,long int*e)
{/*gerando n , fi e o E(chave publica) e imprimindo na tela alguns resultados*/
    *n=(*Pont1)*(*(Pont2));/*gerando o n*/
    *FI =(-1+*(Pont1))*(-1+*(Pont2));/*Gerando o FI de euller*/
    int mdc=0;
    while(mdc!=1&&*e<*FI)
    {/*em busca do e mínimo tal que o m . d .c seja compatível com o requisito*/
        (*e)+=1;
        mdc=MDC(*FI,*e);
    }
    int encontrados=0;
    mdc=0;
    /*impressão sobre a tela*/
    printf("\n\n");
    printf("\t\t\t\tTABELA DE RESULTADOS");
    printf("\n");
    printf("proximos dois 'e' possiveis:");
    for(int i=(*e);encontrados<2&&i<*FI;i++)
    {/*buscando na sequencia*/
        mdc=MDC(*FI,i);
        if(mdc==1)
        {
            encontrados+=1;
            mdc=0;
            printf("%11d|",i);
        }
    }
}
void cbaixatocalta(char*c)
{/*conversao da caixa alta para(to) a caixa baixa*/
    switch(*c)
    {/*força bruta para analisar as letras*/
        case 'a':   *c='A';break;
        case 'b':   *c='B';break;
        case 'c':   *c='C';break;
        case 'd':   *c='D';break;
        case 'e':   *c='E';break;
        case 'f':   *c='F';break;
        case 'g':   *c='G';break;
        case 'h':   *c='H';break;
        case 'i':   *c='I';break;
        case 'j':   *c='J';break;
        case 'l':   *c='L';break;
        case 'm':   *c='M';break;
        case 'n':   *c='N';break;
        case 'o':   *c='O';break;
        case 'p':   *c='P';break;
        case 'q':   *c='Q';break;
        case 'r':   *c='R';break;
        case 's':   *c='S';break;
        case 't':   *c='T';break;
        case 'u':   *c='U';break;
        case 'v':   *c='V';break;
        case 'x':   *c='X';break;
        case 'z':   *c='Z';break;
        default:break;
    }
}
void traducao(char *c, int *num)
{/*designaçãao do numero correspondente a letra*/
    switch(*c)
    {/*força bruta para achar o numero correspondente*/
        case 'A':   *num=1;break;
        case 'B':   *num=2;break;
        case 'C':   *num=3;break;
        case 'D':   *num=4;break;
        case 'E':   *num=5;break;
        case 'F':   *num=6;break;
        case 'G':   *num=7;break;
        case 'H':   *num=8;break;
        case 'I':   *num=9;break;
        case 'J':   *num=10;break;
        case 'L':   *num=11;break;
        case 'M':   *num=12;break;
        case 'N':   *num=13;break;
        case 'O':   *num=14;break;
        case 'P':   *num=15;break;
        case 'Q':   *num=16;break;
        case 'R':   *num=17;break;
        case 'S':   *num=18;break;
        case 'T':   *num=19;break;
        case 'U':   *num=20;break;
        case 'V':   *num=21;break;
        case 'X':   *num=22;break;
        case 'Z':   *num=23;break;
    }
}
void listamentoligado(FILE *ArqEntrada,lista*noh,long int e,int n)
{/*construção da lista ligada*/
    noh->prox=NULL;/*aterramento preliminar*/
    int m;
    long int aux;
    while(feof(ArqEntrada)==0)
    {/*leitura do arquivo*/
        noh->prox=(lista*)malloc(sizeof(lista));/*uso da memória RAM*/
        noh=noh->prox;/*andando sobre a lista*/
        fscanf(ArqEntrada,"%c ",&noh->letra);/*um espacamento e suficiente para ignorar todos*/
        cbaixatocalta(&noh->letra);/*validando a caixa alta*/
        traducao(&noh->letra,&m);/*atribuindo o inteiro da letra*/
        aux=potenciacao(m,e,n);
        noh->c=aux;
        noh->prox=NULL;
    }
}
void mensagemcriptografada(FILE *ArqSaida,lista*noh)
{/*escrevendo no arquivo de forma criptografada*/
    fprintf(ArqSaida,"MENSAGEM CRIPTOGRAFADA\n\n");
    noh=noh->prox;
    while(noh!=NULL)
    {/*enquanto o noh nao for final*/
        fprintf(ArqSaida,"  %d  ",noh->c);
        noh=noh->prox;
    }

}
void achard (long int*d,int n,int e)
{/*determinar o d*/
    int achou=0,qtde=1;
    long int numero,convdireta1[24],convinversa1[24];
    for(int i=1;i<=23;i++)
    {/*preenchendo a matriz*/
        convdireta1[i]=potenciacao(i,e,n);
    }
    while(achou!=23&&qtde<=4294967295)/*limitacao ao tamanho do unsigned int*/
    {
        achou=0;
        for(int i=1;i<=23;i++)
        {/*preenchendo a matriz inversa*/
            convinversa1[i]=potenciacao(convdireta1[i],qtde,n);
        }
        for(int i=1;i<=23;i++)
        {/*verificacao*/
            if (convinversa1[i]==i)
            {
                achou+=1;
            }
        }
        qtde++;
    }
    qtde--;/*corrigindo o valor*/
    *d=qtde;/*determinando o d*/
    printf("\nTentativas para determinar d:");
    printf("%10d|",qtde);
}
void descriptografar(long int *b2, long int b1, long int d,int n)
{/*gerando o numero correspondente*/
    *b2=potenciacao(b1,d,n);
}
void leituradescript(FILE*Entrada,long int d, int n)
{
    char c[24];
    long int b1,b2;
    fgets(c,24,Entrada);/*removendo o título*/
    printf("\n\n");
    while(feof(Entrada)==0)
    {/*escrevendo na tela de video finalmente a descriptografia*/
        fscanf(Entrada,"%d ",&b1);
        descriptografar(&b2,b1,d,n);/*analisar b1 e converte-lo a b2*/
        switch(b2)
        {
            case 1:printf("a");break;
            case 2:printf("b");break;
            case 3:printf("c");break;
            case 4:printf("d");break;
            case 5:printf("e");break;
            case 6:printf("f");break;
            case 7:printf("g");break;
            case 8:printf("h");break;
            case 9:printf("i");break;
            case 10:printf("j");break;
            case 11:printf("l");break;
            case 12:printf("m");break;
            case 13:printf("n");break;
            case 14:printf("o");break;
            case 15:printf("p");break;
            case 16:printf("q");break;
            case 17:printf("r");break;
            case 18:printf("s");break;
            case 19:printf("t");break;
            case 20:printf("u");break;
            case 21:printf("v");break;
            case 22:printf("x");break;
            case 23:printf("z");break;
        }
    }
    printf("\n\n");
}
int main()
{
    /*criptografando um texto*/
    FILE *ArqEntrada,*ArqSaida;
    ArqEntrada=fopen("mensagem.txt","r");/*atribuição da porta do arquivo de entrada*/
    ArqSaida=fopen("mensagemCriptografada.txt","w");/*atribuição da porta do arquivo de saida*/
    int p1,p2,n;/*primos para a geração do código*/ //n obtido
    long int FI=0,e=1;
    int primos[26]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
    lista noh;/*declaracao do noh cabeca*/
    recebedoisprimos(&p1,&p2,primos);/*recebendo os primos*/
    conjunton(&p1,&p2,&n,&FI,&e);/* definindo FI e a chave pública*/
    listamentoligado(ArqEntrada,&noh,e,n);
    mensagemcriptografada(ArqSaida,&noh);
    fclose(ArqEntrada);/*encerramento do arquivo de entrada*/
    fclose(ArqSaida);/*encerramento do arquivo de saida*/
    /*descriptografando o texto na força bruta*/
    FILE *Entrada,Saida;
    long int d=1;
    /*sei que 19 corresponde a 24 para a chave pública*/
    /*acharei o valor menor d tal que 24 corresponda a 19*/
    Entrada=fopen("mensagemCriptografada.txt","r");
    achard(&d,n,e);
    leituradescript(Entrada,d,n);
    fclose(Entrada);

    return 0;
}


