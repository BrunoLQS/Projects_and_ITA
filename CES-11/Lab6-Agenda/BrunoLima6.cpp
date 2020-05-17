/*   Aluno Bruno Lima Queiroz Santos                 */
/*   Turma 3                                                      */
/*    Lab 6                                                          */
/*Programa gerado pelo codeblocks 17.12     */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
typedef enum  tarefa {NOVA=0,PROXIMA,FIM} tarefa;
typedef struct noh{
    char CharDescricao[71];
    int Importancia;
}NOH;
typedef struct heap{
    int QuantidadeDeElementos; // Quantidade de elementos
    int QuantidadeMaximaDeElementos; // Quantidade Maxima de Elementos
    NOH*vetor;// vetor a ser alocado dinamicamente
}HEAP;
void Inicializar(HEAP*Heap,int*QuantidadeMaximaDeElementos){/*  INICIALIZAR  */ //OK
    Heap->vetor= (NOH*)malloc((*QuantidadeMaximaDeElementos+1)*sizeof(NOH));
    Heap->QuantidadeDeElementos=0;
    Heap->QuantidadeMaximaDeElementos=*QuantidadeMaximaDeElementos;
}
void Insert(HEAP*Heap,char*CharDescricao,int* Importancia){/*  INSERE NOVO ELEMENTO NA HEAP  */ //OK
    int posicao = ++Heap->QuantidadeDeElementos;/*   POSICAO COMECA NA NOVA FOLHA E SOBE A ÁRVORE   */
    NOH X; /* ELEMENTO A SER INSERIDO */
    X.Importancia = *Importancia;
    strcpy(X.CharDescricao,CharDescricao);
    Heap->vetor[posicao]=X;
    while((posicao)!=1 && Heap->vetor[posicao/2].Importancia < X.Importancia ){// SE A POSICAO E DIFERENTE DE 1, ENTAO HA PAI E A COMPARACAO PROSSEGUE
        Heap->vetor[posicao]=Heap->vetor[posicao/2];
        posicao/=2;
    }
    Heap->vetor[posicao]=X;
}
int HeapCheio(HEAP*Heap){/*   VERIFICA SE O HEAP ESTA CHEIO  */ //OK
    if(Heap->QuantidadeDeElementos==Heap->QuantidadeMaximaDeElementos)
        return TRUE;
    else return FALSE;
}
int HeapVazio(HEAP*Heap){/*   VERIFICA SE O HEAP ESTA VAZIO  */   // OK
    if(Heap->QuantidadeDeElementos==0)
        return TRUE;
    else return FALSE;
}
NOH Maximum(HEAP*Heap){/*  Retorna o elemento de maxima prioridade  */
    return (Heap->vetor[1]);
}
void RemoveMax(HEAP*Heap){/*  REMOVE O ELEMENTO DE MAXIMA PRIORIDADE  */
    Heap->vetor[1]=Heap->vetor[Heap->QuantidadeDeElementos];
    Heap->QuantidadeDeElementos--;
    int posicao = 1;
    int esquerda=0;
    int direita=0;
    int trocou=1;
    NOH X;
    while (posicao<Heap->QuantidadeDeElementos&&trocou==1){
        esquerda=0;
        direita=0;
        trocou=0;
        if((2*posicao)<=Heap->QuantidadeDeElementos&&(Heap->vetor[(2*posicao)].Importancia)>(Heap->vetor[(posicao)].Importancia))
            esquerda=1;
        if((1+2*posicao)<=Heap->QuantidadeDeElementos&&Heap->vetor[(1+2*posicao)].Importancia>Heap->vetor[(posicao)].Importancia)
            direita=1;
        if(esquerda==1&&direita==1){
            if(Heap->vetor[(2*posicao)].Importancia>Heap->vetor[(1+2*posicao)].Importancia)
                direita=0;
            else
                esquerda=0;
        }
        if(esquerda==1){
            X=Heap->vetor[posicao];
            Heap->vetor[posicao]=Heap->vetor[2*posicao];
            Heap->vetor[2*posicao]=X;
            posicao=2*posicao;
            trocou=1;
        }
        if(direita==1){
            X=Heap->vetor[posicao];
            Heap->vetor[posicao]=Heap->vetor[1+2*posicao];
            Heap->vetor[1+2*posicao]=X;
            posicao=1+2*posicao;
            trocou=1;
        }
    }
}
void Finalizar(HEAP*Heap){
    free(Heap->vetor);
}
int main(){
    tarefa TAREFA=NOVA;/*  Orientacao para a tomada de decisao  */  //variavel tarefa
    HEAP Heap;  // variavel heap
    char CharTarefa[8],CharDescricao[71];
    int Importancia=0;
    int QuantidadeMaximaDeElementos=0;
    FILE*ArquivoDeEntrada;
    FILE*ArquivoDeSaida;
    //ArquivoDeEntrada=fopen("C:\\Lab6\\entrada6.txt","r");
    ArquivoDeEntrada=fopen("entrada6.txt","r");
    //ArquivoDeSaida=fopen("C:\\Lab6\\bruno6.txt","w");
    ArquivoDeSaida=fopen("bruno6.txt","w");
    for(int i=1;i<=5;i++)//COMECO DO ELIMINAR CABECALHO
        fscanf(ArquivoDeEntrada,"%70[^\n]  ",(CharDescricao));
    fscanf(ArquivoDeEntrada,"%d   ",&QuantidadeMaximaDeElementos);
    for(int i=1;i<=3;i++)
        fscanf(ArquivoDeEntrada,"%70[^\n]    ",(CharDescricao));/*  Atravessando o cabecalho  */// FIM DO ELIMINAR CABECALHO
    fprintf(ArquivoDeSaida,"Agenda Eletronica - Formato de arquivo de saida.\n");
    fprintf(ArquivoDeSaida,"Aluno Bruno Lima Queiroz Santos T3\n");
    fprintf(ArquivoDeSaida,"INSTITUTO TECNOLOGICO DE AERONAUTICA\n");
    fprintf(ArquivoDeSaida,"DATA 12-11-2018 \n");
    fprintf(ArquivoDeSaida,"Curso de CES-11   PROFESSOR ARMANDO\n");
    fprintf(ArquivoDeSaida,"--------------------------------------------------\n");
    fprintf(ArquivoDeSaida,"RESPOSTAS DAS CONSULTAS\n");
    fprintf(ArquivoDeSaida,"--------------------------------------------------\n");
    Inicializar(&Heap,&QuantidadeMaximaDeElementos);/*  INICIALIZANDO A VARIAVEL HEAP  */
    while(TAREFA!=FIM){
        fscanf(ArquivoDeEntrada,"%8[^\t\n ]   ",&CharTarefa);
        {/*  MODIFICANDO A TAREFA  */
            if(strcmp("NOVA",CharTarefa)==0)
                TAREFA=NOVA;
            else if(strcmp("PROXIMA",CharTarefa)==0)
                    TAREFA=PROXIMA;
                    else if(strcmp("FIM",CharTarefa)==0)
                        TAREFA=FIM;
        }
        switch(TAREFA){
            case NOVA : { /*  NOVA  */
                fscanf(ArquivoDeEntrada,"%d      %71[^\n\t]   ",&Importancia,&CharDescricao);
                if (HeapCheio(&Heap)==TRUE)
                    fprintf(ArquivoDeSaida,"ERRO     Agenda cheia. Impossivel inserir.\n"); // ATENTAR PARA O ESPACAMENTO DO ERRO !!!
                else Insert(&Heap,CharDescricao,&Importancia);
            }break;
            case PROXIMA:{ /*  PROXIMA  */
                if(HeapVazio(&Heap)==TRUE)
                    fprintf(ArquivoDeSaida,"AVISO    Nao ha tarefas na agenda  :-)\n");
               else{
                    NOH X = Maximum(&Heap);
                    RemoveMax(&Heap);
                    fprintf(ArquivoDeSaida,"%2d       %s\n",X.Importancia,X.CharDescricao);
               }
            }break;
            case FIM:{ /*  FIM  */
                fprintf(ArquivoDeSaida,"\n--------------------------------------------------\n");
                fprintf(ArquivoDeSaida,"FICA PARA O DIA SEGUINTE\n");
                fprintf(ArquivoDeSaida,"--------------------------------------------------\n");
                if(HeapVazio(&Heap)==TRUE)
                    fprintf(ArquivoDeSaida,"Agenda vazia! Nao restam tarefas para o dia seguinte.\n");
                else{
                    NOH X;
                    while(HeapVazio(&Heap)!=TRUE){
                        X= Maximum(&Heap);
                        RemoveMax(&Heap);
                        fprintf(ArquivoDeSaida,"%2d       %s\n",X.Importancia,X.CharDescricao);
                    }
                }
                Finalizar(&Heap);
            }break;
        }
    }
    fclose(ArquivoDeEntrada);
    fclose(ArquivoDeSaida);
    return 0;
}


