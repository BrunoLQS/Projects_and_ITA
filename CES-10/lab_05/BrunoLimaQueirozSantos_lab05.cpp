/*Copyright by BRUNO LIMA QUEIROZ SANTOS  */
/*Turma 3                                 */
/*Lab 05:Copa do Mundo 2018               */
/*Programa compilado com CodeBlocks 17.01 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
typedef enum group {a=1,b,c,d,e,f,g,h} group;
group A=a,B=b,C=c,D=d,E=e,F=f,G=g,H=h;
typedef char cadeia[26];
/* Estrutura para as informacoes sobre cada selecao em seu grupo  */
typedef struct selecao selecao;
struct selecao
{
    cadeia nome;
    int pontos,vitorias,golspro,golscontra,saldogols;
    int maxgolspro,maxgolscontra;
};
selecao matmat8[17];
selecao matmat4[9];
selecao matmat2[5];
selecao matmat1[3];
selecao matmatsemi[3];
selecao campeao;
/* Estrutura para as informacoes de cada grupo  */
typedef struct grupo grupo;
struct grupo{
    char nome;
    selecao VetorSelecoes[5];
    int Resultados[6][2];
    cadeia primeiro,segundo;
};
/* Variaveis globais  */
FILE *FileIn,*FileOut,*FileIn2;
grupo VetorGrupos[9];
/* Funcao LerSelecoes:Leitura dos nomes das selecoes e colocacao em seus respectivos grupos*/
void LerSelecoes(){
int i,j,lenght;char nomegrupo;
for(i=1,nomegrupo='A';i<=8;nomegrupo++,i++)
    {
        VetorGrupos[i].nome=nomegrupo;
        for(j=1;j<=4;j++)
        {
            fgets(VetorGrupos[i].VetorSelecoes[j].nome,31,FileIn);
            lenght=strlen(VetorGrupos[i].VetorSelecoes[j].nome);
            VetorGrupos[i].VetorSelecoes[j].nome[lenght-1]='\0';
            VetorGrupos[i].VetorSelecoes[j].pontos=0;
            VetorGrupos[i].VetorSelecoes[j].vitorias=0;
            VetorGrupos[i].VetorSelecoes[j].golspro=0;
            VetorGrupos[i].VetorSelecoes[j].golscontra=0;
            VetorGrupos[i].VetorSelecoes[j].saldogols=0;
            /*faltou coisa*/
        }
    }

}
/*função para ler a estatística e atribuí-la*/
void LerEstatistica ()
{
    for(int i=1;i<=8;i++)
    {
        for(int j=1;j<=4;j++)
        {
            fscanf(FileIn2,"%d",&VetorGrupos[i].VetorSelecoes[j].maxgolspro);
            fscanf(FileIn2,"%d",&VetorGrupos[i].VetorSelecoes[j].maxgolscontra);
        }
    }
}
void JogoPrimeiraFase(int i, int j, int group,int k)
{/*i vs j*/
    int maxi,maxj,X,Y;
    if (VetorGrupos[group].VetorSelecoes[i].maxgolspro<=VetorGrupos[group].VetorSelecoes[j].maxgolscontra)
        maxi=VetorGrupos[group].VetorSelecoes[i].maxgolspro;
    else
        maxi=VetorGrupos[group].VetorSelecoes[j].maxgolscontra;
    if(VetorGrupos[group].VetorSelecoes[j].maxgolspro<=VetorGrupos[group].VetorSelecoes[i].maxgolscontra)
        maxj=VetorGrupos[group].VetorSelecoes[j].maxgolspro;
    else
        maxj=VetorGrupos[group].VetorSelecoes[i].maxgolscontra;
    /*placar X vs Y */
    srand(time(NULL));
    X=rand()%(maxi+1);
    Y=rand()%(maxj+1);
    VetorGrupos[group].Resultados[k][0]=X;
    VetorGrupos[group].Resultados[k][1]=Y;
}
/*atribuições para um empate na fase de grupos*/
void empate (grupo*p,int i,int X, int Y)/*eu usei ponteiros*/
{
    p->VetorSelecoes[i].pontos+=1;
    p->VetorSelecoes[i].golspro+=X;
    p->VetorSelecoes[i].golscontra+=Y;
}
/*atribuições para uma vitória na fase de grupos*/
void vitoria(grupo*p,int i, int X, int Y)
{
    p->VetorSelecoes[i].golspro+=X;
    p->VetorSelecoes[i].golscontra+=Y;
    p->VetorSelecoes[i].saldogols+=(X-Y);
    p->VetorSelecoes[i].pontos+=3;
    p->VetorSelecoes[i].vitorias+=1;
}
/*atribuições para uma derrota na fase de grupos*/
void derrota(grupo*p,int i, int X,int Y)
{
    p->VetorSelecoes[i].golspro+=X;
    p->VetorSelecoes[i].golscontra+=Y;
    p->VetorSelecoes[i].saldogols+=(X-Y);
}
void DistribuiCriterios(int group,int i)
{/*Analisa os resultados de ordem i de um grupo*/
    int X,Y;
    X=VetorGrupos[group].Resultados[i][0];
    Y=VetorGrupos[group].Resultados[i][1];
    if (X==Y)/*empate*/
    {/*Distribuição de Pontos*/
        switch(i)
        {
            case 0:
            {
                empate(&VetorGrupos[group],1,X,Y);
                empate(&VetorGrupos[group],2,Y,X);
            }break;
            case 1:
            {
                empate(&VetorGrupos[group],1,X,Y);
                empate(&VetorGrupos[group],3,Y,X);
            }break;
            case 2:
            {
                empate(&VetorGrupos[group],1,X,Y);
                empate(&VetorGrupos[group],4,Y,X);
            }break;
            case 3:
            {
                empate(&VetorGrupos[group],2,X,Y);
                empate(&VetorGrupos[group],3,Y,X);
            }break;
            case 4:
            {
                empate(&VetorGrupos[group],2,X,Y);
                empate(&VetorGrupos[group],4,Y,X);
            }break;
            case 5:
            {
                empate(&VetorGrupos[group],3,X,Y);
                empate(&VetorGrupos[group],4,Y,X);
            }break;
        }
    }
    if (X>Y)/*Vitória de A contra B*/
    {
        switch(i)
        {
            case 0:
            {
                vitoria(&VetorGrupos[group],1,X,Y);
                derrota(&VetorGrupos[group],2,Y,X);
            }break;
            case 1:
            {
                vitoria(&VetorGrupos[group],1,X,Y);
                derrota(&VetorGrupos[group],3,Y,X);
            }break;
            case 2:
            {
                vitoria(&VetorGrupos[group],1,X,Y);
                derrota(&VetorGrupos[group],4,Y,X);
            }break;
            case 3:
            {
                vitoria(&VetorGrupos[group],2,X,Y);
                derrota(&VetorGrupos[group],3,Y,X);
            }break;
            case 4:
            {
                vitoria(&VetorGrupos[group],2,X,Y);
                derrota(&VetorGrupos[group],4,Y,X);
            }break;
            case 5:
            {
                vitoria(&VetorGrupos[group],3,X,Y);
                derrota(&VetorGrupos[group],4,Y,X);
            }break;
        }
    }
    if (X<Y)/*Vitória de B contra A*/
    {
        switch(i)
        {
            case 0:
            {
                derrota(&VetorGrupos[group],1,X,Y);
                vitoria(&VetorGrupos[group],2,Y,X);
            }break;
            case 1:
            {
                derrota(&VetorGrupos[group],1,X,Y);
                vitoria(&VetorGrupos[group],3,Y,X);
            }break;
            case 2:
            {
                derrota(&VetorGrupos[group],1,X,Y);
                vitoria(&VetorGrupos[group],4,Y,X);
            }break;
            case 3:
            {
                derrota(&VetorGrupos[group],2,X,Y);
                vitoria(&VetorGrupos[group],3,Y,X);
            }break;
            case 4:
            {
                derrota(&VetorGrupos[group],2,X,Y);
                vitoria(&VetorGrupos[group],4,Y,X);
            }break;
            case 5:
            {
                derrota(&VetorGrupos[group],3,X,Y);
                vitoria(&VetorGrupos[group],4,Y,X);
            }break;
        }
    }
}
/*Funcao EscreverGrupos:escrita das informacoes sobre os grupos */
void SemearResultadoFirstPhase()
{
    int k=0;
    for (int g=1;g<=8;g++)
    {/*jogos primeira fase*/
        k=0;
        for(int i=1;i<=3;i++)
        {
            for(int j=i+1;j<=4;j++)
            {
                JogoPrimeiraFase(i,j,g,k);
                k++;
            }
        }
    }
    for (int g=1;g<=8;g++)
    {/*distribuição de criterios*/
        for(int i=0;i<=5;i++)
        {
            DistribuiCriterios(g,i);
        }
    }
}
/*mudar as classificações das seleções conforme a ordenação*/
void troca( int g, int i , int j)
{
    selecao aux;
    aux=VetorGrupos[g].VetorSelecoes[i];
    VetorGrupos[g].VetorSelecoes[i]=VetorGrupos[g].VetorSelecoes[j];
    VetorGrupos[g].VetorSelecoes[j]=aux;
}
/*ordenar conforme a classificação*/
int Ordenacao(int i,int j,int g)
{/* i <j*/
    if (VetorGrupos[g].VetorSelecoes[i].pontos<VetorGrupos[g].VetorSelecoes[j].pontos)
    {
        troca(g,i,j);
        return 0;
    }
    if (VetorGrupos[g].VetorSelecoes[i].pontos==VetorGrupos[g].VetorSelecoes[j].pontos)
    {
        if((VetorGrupos[g].VetorSelecoes[i].vitorias<VetorGrupos[g].VetorSelecoes[j].vitorias))
        {
            troca(g,i,j);
            return 0;
        }
        if((VetorGrupos[g].VetorSelecoes[i].vitorias==VetorGrupos[g].VetorSelecoes[j].vitorias))
        {
            if((VetorGrupos[g].VetorSelecoes[i].saldogols<VetorGrupos[g].VetorSelecoes[j].saldogols))
            {
                troca(g,i,j);
                return 0;
            }
            if((VetorGrupos[g].VetorSelecoes[i].saldogols==VetorGrupos[g].VetorSelecoes[j].saldogols))
            {
                if((VetorGrupos[g].VetorSelecoes[i].golspro<VetorGrupos[g].VetorSelecoes[j].golspro))
                {
                    troca(g,i,j);
                    return 0;
                }
                if((VetorGrupos[g].VetorSelecoes[i].golspro==VetorGrupos[g].VetorSelecoes[j].golspro))
                {
                    if((VetorGrupos[g].VetorSelecoes[i].golscontra>VetorGrupos[g].VetorSelecoes[j].golscontra))
                    {
                        troca(g,i,j);
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}
void OrdenarGrupos()
{
    int buffer;
    for (int g=1;g<=8;g++)
    {
        for(int k=1;k<=3;k++)
        {
            for(int i=1;i<=3;i++)
            {
                buffer=Ordenacao(i,i+1,g);
            }
        }
    }
}
void Primeiros()
{
    for (int g=1;g<=8;g++)
    {
        strcpy(VetorGrupos[g].primeiro,VetorGrupos[g].VetorSelecoes[1].nome);
        strcpy(VetorGrupos[g].segundo,VetorGrupos[g].VetorSelecoes[2].nome);
        VetorGrupos[g].VetorSelecoes[1].maxgolspro+=1;
        VetorGrupos[g].VetorSelecoes[1].maxgolscontra-=1;
    }
}
void EscreverGrupos()
{
    int i,j;
    for(i=1;i<=8;i++)
    {
        fprintf(FileOut,"\n\nGRUPO %c: ",VetorGrupos[i].nome);
        fprintf(FileOut,"\n\n%-20s|%8s|%8s|%8s|%8s|%8s","Selecao","Pontos","Vitorias","GolsPro","GolsCon","SaldGols");
        fprintf(FileOut,"\n--------------------|--------|--------|--------|--------|--------");
        for(j=1;j<=4;j++)
            fprintf(FileOut,"\n%-20s|%8d|%8d|%8d|%8d|%8d",
                    VetorGrupos[i].VetorSelecoes[j].nome,
                    VetorGrupos[i].VetorSelecoes[j].pontos,
                    VetorGrupos[i].VetorSelecoes[j].vitorias,
                    VetorGrupos[i].VetorSelecoes[j].golspro,
                    VetorGrupos[i].VetorSelecoes[j].golscontra,
                    VetorGrupos[i].VetorSelecoes[j].saldogols);
    }
}
void AvsB (selecao*A,selecao*B,int *X,int *Y)
{
    int maxa,maxb;
    if (A->maxgolspro<=B->maxgolscontra)
        maxa=A->maxgolspro;
    else
        maxa=B->maxgolscontra;
    if(B->maxgolspro<=A->maxgolscontra)
        maxb=B->maxgolspro;
    else
        maxb=A->maxgolscontra;
    /*placar A vs B */
    srand(time(NULL));
    do
    {
        *X=rand()%(maxa+1);
        *Y=rand()%(maxb+1);
    }while(*X==*Y);

}
void partidaoitavasdefinal(int*X,int*Y,int i,int k)
{
    AvsB(&matmat8[i],&matmat8[i+1],X,Y);
    printf("\n\n\t %-15s  %5d   vs%3d             %-5s",matmat8[i].nome,*X,*Y,matmat8[i+1].nome);
    if(*X>*Y)
        matmat4[k]=matmat8[i];
    else
        matmat4[k]=matmat8[i+1];
}
void partidaquartasdefinal(int*X,int*Y,int i,int k)
{
    AvsB(&matmat4[i],&matmat4[i+1],X,Y);
    printf("\n\n\t %-15s  %5d   vs%3d             %-5s",matmat4[i].nome,*X,*Y,matmat4[i+1].nome);
    if(*X>*Y)
        matmat2[k]=matmat4[i];
    else
        matmat2[k]=matmat4[i+1];
}
void partidasemidefinal(int*X,int*Y,int i,int k)
{
    AvsB(&matmat2[i],&matmat2[i+1],X,Y);
    printf("\n\n\t %-15s  %5d   vs%3d             %-5s",matmat2[i].nome,*X,*Y,matmat2[i+1].nome);
    if(*X>*Y)
    {
        matmat1[k]=matmat2[i];
        matmatsemi[k]=matmat2[i+1];
    }
    else
    {
        matmat1[k]=matmat2[i+1];
        matmatsemi[k]=matmat2[i];
    }
}
void partidafin(int*X,int*Y,int i)
{
    AvsB(&matmat1[i],&matmat1[i+1],X,Y);
    printf("\n\n\t %-15s  %5d   vs%3d             %-5s",matmat1[i].nome,*X,*Y,matmat1[i+1].nome);
    if(*X>*Y)
        campeao=matmat1[i];
    else
        campeao=matmat1[i+1];
}
void partidasfin(int*X,int*Y,int i)
{
    AvsB(&matmatsemi[i],&matmatsemi[i+1],X,Y);
    printf("\n\n\t %-15s  %5d   vs%3d             %-5s",matmatsemi[i].nome,*X,*Y,matmatsemi[i+1].nome);
}
void distribuimatamata()
{
    matmat8[1]=VetorGrupos[C].VetorSelecoes[1];
    matmat8[2]=VetorGrupos[D].VetorSelecoes[2];

    matmat8[3]=VetorGrupos[A].VetorSelecoes[1];
    matmat8[4]=VetorGrupos[B].VetorSelecoes[2];

    matmat8[5]=VetorGrupos[E].VetorSelecoes[1];
    matmat8[6]=VetorGrupos[F].VetorSelecoes[2];

    matmat8[7]=VetorGrupos[G].VetorSelecoes[1];
    matmat8[8]=VetorGrupos[H].VetorSelecoes[2];

    matmat8[9]=VetorGrupos[B].VetorSelecoes[1];
    matmat8[10]=VetorGrupos[A].VetorSelecoes[2];

    matmat8[11]=VetorGrupos[D].VetorSelecoes[1];
    matmat8[12]=VetorGrupos[C].VetorSelecoes[2];

    matmat8[13]=VetorGrupos[F].VetorSelecoes[1];
    matmat8[14]=VetorGrupos[E].VetorSelecoes[2];

    matmat8[15]=VetorGrupos[H].VetorSelecoes[1];
    matmat8[16]=VetorGrupos[G].VetorSelecoes[2];
}
void oitavasdefinal(int*X,int*Y)
{
    for(int i=1;i<=8;i++)
    {
        partidaoitavasdefinal(X,Y,(2*i-1),i);
    }
}
void quartasdefinal(int*X,int*Y)
{
    for(int i=1;i<=4;i++)
    {
        partidaquartasdefinal(X,Y,(2*i-1),i);
    }
}
void semidefinal(int*X,int*Y)
{
    for(int i=1;i<=2;i++)
    {
        partidasemidefinal(X,Y,(2*i-1),i);
    }
}
/*partida decide campeão*/
void fin(int*X,int*Y)
{
     for(int i=1;i<=1;i++)
    {
        partidafin(X,Y,(2*i-1));
    }
}
/*partida 3 e 4 lugares*/
void sfin(int*X,int*Y)
{
    for(int i=1;i<=1;i++)
    {
        partidasfin(X,Y,(2*i-1));
    }
}
/* Funcao Main*/
void interromper()
{
    printf("\n\nDigite qualquer tecla para avancar");
    getch();
    printf("\n\n");
}
int main()
{
    char resp='n';
    do
    {
        system("cls");

        int X,Y;
        /* Abertura dos arquivos de entrada e de saída */

        FileIn=fopen("ListaSelecoes.txt","r");
        FileOut=fopen("RelatorioCopa2018.txt","w");
        FileIn2=fopen("EstatisticaSelecoes.txt","r");
        fprintf(FileOut,"COPA DO MUNDO DE 2018");

        /*Avisos de sobre os arquivos de entrada e saida */

        printf("Proessamento das informacoes da Copa do Mundo de 2014\n\n");
        printf("\tArquivo ListaSelecoes.txt: Contem o nome das 32 selecoes da Copa\n\n");
        printf("\tArquivo RelatorioCopa2018.txt: Relatorio da Copa\n");

        /* Processamento das informacoes sobre a Copa */
        printf("\n\n\tDigite qualquer tecla para a realizacao da leitura das selecoes e \n\tapos,das estatisticas:");
        getch();
        LerSelecoes();
        LerEstatistica();
        printf("\n\n\tDigite qualquer tecla para a apresentacao\n\tdo relatorio da primeira fase:");
        getch();
        /*até aqui os grupos já foram definidos*/
        /*Primeirafase();*/
        SemearResultadoFirstPhase();
        OrdenarGrupos();
        EscreverGrupos();
        fclose(FileIn);
        fclose(FileIn2);
        fclose(FileOut);
        system("RelatorioCopa2018.txt");
        /*consagração da primeira fase*/
        /*ROAD TO MATA-MATA*/
        distribuimatamata();
        interromper();
        system("cls");
        printf("OITAVAS DE FINAL\n");
        oitavasdefinal(&X,&Y);
        interromper();
        printf("QUARTAS DE FINAL\n");
        quartasdefinal(&X,&Y);
        interromper();
        printf("SEMI DE FINAL\n");
        semidefinal(&X,&Y);
        interromper();
        printf("FINAL\n");
        fin(&X,&Y);
        interromper();
        printf("TERCEIRO E QUARTO LUGAR\n");
        sfin(&X,&Y);
        interromper();
        printf("\n\n O CAMPEAO FOI %s", campeao.nome);
        printf("\n\nvoce desejaria fazer outra simulacao(s/n)?");
        fflush(stdin);
        scanf("%c",&resp);
        }while(resp=='s'||resp=='S');


    /*Fechamento da tela*/
    printf("\n\n");
    system("pause");
    return 0;
}

