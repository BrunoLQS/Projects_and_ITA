/*Aluno Bruno Lima Queiroz Santos        */
/*Turma 3                                */
/*Lab 11                                 */
/*Programa gerado pelo codeblocks 17.12  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct flight flight;
struct flight
{/*struct da lista ligada*/
    char from[32];/*nome da cidade*/
    int voo;
    int urgencia;/*uma variável boleana*/
    flight*prox;
};
void capture8linhas(FILE*ArqEntrada)
{/*capturando o exceto inicial*/
    char c[72];
    for(int i =1;i<=8;i++)
        fgets(c,72,ArqEntrada);
}
void alistamento(flight*inicio,char buffercity[32],int bufferflight)
{/*alistamento quanto o noh inicial nao esta vazio*/
    flight*auxiliar;
    auxiliar=inicio;
    int parametro=0;
    while(parametro==0)
    {/*andando dentro da lista*/
        if(auxiliar->prox==NULL)
        {/*se o seu proximo eh NULL*/
            parametro=1;
        }
        else
            auxiliar=auxiliar->prox;
    }
    /*o  proximo do auxiliar deve ser necessariamente um NULL*/
    auxiliar->prox=(flight*)malloc(sizeof(flight));
    auxiliar->prox->urgencia=0;
    auxiliar->prox->voo=bufferflight;
    strcpy(auxiliar->prox->from,buffercity);
    auxiliar=(auxiliar)->prox;
    auxiliar->prox=NULL;
}
void pouso(FILE*ArqSaida,flight**inicio)
{/*pousando o primeiro da fila*/
    flight*auxiliar;
    auxiliar=(*inicio);
    if((*inicio)->prox!=NULL)
        (*inicio)=(*inicio)->prox;
    else
        (*inicio)=NULL;
    fprintf(ArqSaida,"%04d    ",(auxiliar)->voo);
    fprintf(ArqSaida,"%s",(auxiliar)->from);
    free((auxiliar));
}
void urgencia(flight**inicio,int bufferflight)
{/*organizar a lista quando o noh inicial nao esta vazio*/
    flight*auxiliar;
    flight*marcador;
    flight*ultimourgente;
    marcador=(*inicio);
    auxiliar=marcador;
    ultimourgente=marcador;
    while(marcador->voo!=bufferflight)
    {
        auxiliar=marcador;
        marcador=marcador->prox;
    }
    marcador->urgencia=1;
    /*auxiliar e o antecessor ao determinado urgente*/
    if((*inicio)->urgencia==1)
    {/*o inicio e urgente*/
        if(auxiliar->urgencia!=1)
        {
            while(ultimourgente->prox!=auxiliar&&ultimourgente->prox->urgencia==1)
            {
                ultimourgente=ultimourgente->prox;
            }
            auxiliar->prox=marcador->prox;
            marcador->prox=ultimourgente->prox;
            ultimourgente->prox=marcador;
        }
    }
    else
    {
        auxiliar->prox=marcador->prox;
        marcador->prox=(*inicio);
        *inicio=marcador;
    }
}
void fim(FILE*ArqSaida,flight**inicio)
{/*final quando a lista esta cheia*/
    flight*aux;
    fprintf(ArqSaida,"\nSituacao da fila\n\n");
    while((*inicio)!=NULL)
    {
        fprintf(ArqSaida,"%04d    ",(*inicio)->voo);
        fprintf(ArqSaida,"%s",(*inicio)->from);
        aux=(*inicio);
        (*inicio)=(*inicio)->prox;
        free(aux);
    }
}
void simulador(FILE*ArqEntrada,FILE*ArqSaida)
{/*programa propriamente dito*/
    flight*inicio;/*declarando um ponteiro simples para apontar para a lista*/
    inicio=NULL;
    char buffer[15];
    int bufferflight;
    char buffercity[32];
    capture8linhas(ArqEntrada);/*o cursor deslocou-se 8 linhas*/
    fprintf(ArqSaida,"Simulador de aeroporto\n");
    fprintf(ArqSaida,"Para torre de controle\n");
    fprintf(ArqSaida,"AUTORIZACOES DE POUSO\n");
    fprintf(ArqSaida,"=========================================\n");
    fprintf(ArqSaida,"FLIGHT  FROM\n\n");
    while(feof(ArqEntrada)==0)
    {/*enquanto o arquivo nao chegou ao final*/
        /*de antemão, atribuem-se as 3 leituras*/
        fscanf(ArqEntrada,"%s ",buffer);
        fscanf(ArqEntrada,"%d ",&bufferflight);
        fgets(buffercity,30,ArqEntrada);
        if(feof(ArqEntrada)==0)
        {
            if(inicio==NULL)
                {/*se a lista esta vazia*/
                    if(strcmpi(buffer,"pede_pouso")==0)
                    {/*strcmpi indiferencia maiusculas de minusculas*/
                        inicio=(flight*)malloc(sizeof(flight));
                        /*abrindo a lista*/
                        inicio->prox=NULL;
                        inicio->urgencia=0;
                        inicio->voo=bufferflight;
                        strcpy(inicio->from,buffercity);
                        /*acima,copiaram-se os dados para o noh inicial*/
                    }
                    else
                    {
                        if(strcmpi(buffer,"pista_liberada")==0)
                            fprintf(ArqSaida,"0000    Nenhum aviao pousando\n");
                        else
                        {/*o ultimo caso é o FIM, pois nao é concebível urgencia*/
                            fprintf(ArqSaida,"\nSituacao da fila\n\nfila vazia");
                        }
                    }
                }
                else
                {/*se a lista e preenchida*/
                    if(strcmpi(buffer,"pede_pouso")==0)
                    {
                        alistamento(inicio,buffercity,bufferflight);
                    }
                    else
                    {
                        if(strcmpi(buffer,"pista_liberada")==0)
                        {
                           pouso(ArqSaida,&inicio);
                        }
                        else
                        {
                            if(strcmpi(buffer,"URGENCIA")==0)
                            {
                                flight**ini;
                                ini=&inicio;
                                urgencia(ini,bufferflight);
                            }
                            else
                            {/*FIM*/
                                fim(ArqSaida,&inicio);
                            }
                        }
                    }
                }
        }
    }
}
int main()
{/*chamadas de funções e variáveis*/
    FILE*ArqEntrada;
    FILE*ArqSaida;
    //ArqEntrada=fopen("C:\\lab11\\entrada11.txt","r");/*abertura do arquivo em modo leitura*/
    ArqEntrada=fopen("entrada11.txt","r");/*abertura do arquivo em modo leitura*/
    //ArqSaida=fopen("C:\\lab11\\brunolima11.txt","w");/*abertura em modo escrita*/
    ArqSaida=fopen("brunolima11.txt","w");/*abertura em modo escrita*/
    simulador(ArqEntrada,ArqSaida);/*execução do simulador*/
    fclose(ArqEntrada);/*encerramento do arquivo para que os seus dados persistam*/
    fclose(ArqSaida);/*encerramento do arquivo para que o escrito persista nele*/
    return 0;/*encerramento do programa*/
}
