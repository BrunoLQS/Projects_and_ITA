/*Aluno Bruno Lima Queiroz Santos        */
/*Turma 3                                */
/*Lab 5                                  */
/*Programa gerado pelo codeblocks 17.12  */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int Lista = 0;
int FilhoNaProfundidade[9]={1,1,1,1,1,1,1,1,1};
char NomeDaOperacao[11];
char Procurado[21];
char NomeDaSecaoEmInsercao[21];
char Parametro[11];/*Localizado na coluna intermediária do arquivo de entrada*/
char Lixo[2];
FILE *ArquivoDeEntrada=NULL;
FILE *ArquivoDeSaida=NULL;
typedef struct noh noh;/*ponteiro para o nó*/
struct noh{/*Nó para a árvore que armazena a hierarquia das seções   */
    char elemento[21];
    noh*pai;
    noh*irmaodireito;
    noh*filhoesquerdo;
};
enum Operacao {TITULO=0,INSERIR,REMOVER,TRANSFERIR,LISTAR,FIM,ERRODEOPERACAO};
typedef enum Operacao Operacao;
Operacao Solicitacao = TITULO;/*Estado do Automato Finito */
enum Insercao {SUB=0,SEGUINTE_A,ERRODEINSERCAO};
typedef enum Insercao Insercao;
Insercao ModoDeInsercao = SUB;
enum ExistenciaDaArvore {NAOEXISTE=0,EXISTE};
typedef enum ExistenciaDaArvore Status ;
Status ExistenciaDaArvore=NAOEXISTE;
noh* Titulo=NULL;/*declaração do ponteiro a ser raiz(armazenar o título da lista)*/
void CaptureOCabecalho(){/*Extraindo o cabecalho sobre o Arquivo de Entrada*/
    char lixo[71];
    fscanf(ArquivoDeEntrada,"%70[^\n]%*c%70[^\n]%*c%70[^\n]%*c%70[^\n]%*c",lixo,lixo,lixo,lixo);//(lixo,72,ArquivoDeEntrada);
}
void InsiraOCabecalho(){/*Inserindo o cabecalho sobre o Arquivo de Saida*/
    fprintf(ArquivoDeSaida,"INSTITUTO TECNOLOGICO DE AERONAUTICA - ITA - CES 11\nAluno: Bruno Lima Queiroz Santos");
    fprintf(ArquivoDeSaida," - TURMA 22.3\nLAB 5 - LIVRO\n--------------------------------------------------\n");
}
void VerificaOperacao(){/*Verifica a Operação e ATUALIZA o Estado de SOLICITACAO*/
    fscanf(ArquivoDeEntrada,"%10[^\n ] \n",NomeDaOperacao);//remova o espaço do buffer
    if(strcmp("INSERIR",NomeDaOperacao)==0)
        Solicitacao = INSERIR;
    else if(strcmp("REMOVER",NomeDaOperacao)==0)
            Solicitacao = REMOVER;
        else if(strcmp("TRANSFERIR",NomeDaOperacao)==0)
                Solicitacao=TRANSFERIR;
            else if(strcmp("LISTA",NomeDaOperacao)==0)
                    Solicitacao= LISTAR;
                else if(strcmp("TITULO",NomeDaOperacao)==0)
                        Solicitacao = TITULO;
                    else if(strcmp("FIM",NomeDaOperacao)==0)
                            Solicitacao = FIM;
                        else
                            Solicitacao = ERRODEOPERACAO;
}
noh*Compara(noh*X){/*retorna X se encontrou,senão retorna NULL*/
    if(X!=NULL&&strcmp(X->elemento,Procurado)==0)
        return X;
    return NULL;
}
noh* BuscaProcuradoEmPreOrdem(noh*X){/*PROCURA POR PROCURADO NA ARVORE*/
    noh*auxiliar=Compara(X);
    if(auxiliar!=NULL)
        return auxiliar;
    noh*filho=X->filhoesquerdo;
    while(filho!=NULL)
    {
        auxiliar=BuscaProcuradoEmPreOrdem(filho);
        if(auxiliar!=NULL)
            return auxiliar;
        filho=filho->irmaodireito;
    }
    return NULL;
}
void AnalisaParametro(noh**inserido){/*Analisa o Parametro para inserção , atualiza o estado ModoDeInsercao da operação inserção e atribui o inserido*/
    (*inserido)=BuscaProcuradoEmPreOrdem(Titulo);
    if((*inserido)!=NULL){
        if(strcmp("SUB",Parametro)==0)
            ModoDeInsercao=SUB;
        else if(strcmp("SEGUINTE_A",Parametro)==0)
                ModoDeInsercao=SEGUINTE_A;
            else
                ModoDeInsercao=ERRODEINSERCAO;
    }else
        ModoDeInsercao=ERRODEINSERCAO;
}
void MallocParaOTitulo(){/*Cria uma novo noh para o titulo a ser inserido*/
    noh*SubArvore=Titulo;
    Titulo=(noh*)malloc(sizeof(noh));
    Titulo->irmaodireito=NULL;
    Titulo->filhoesquerdo=SubArvore;
    fscanf(ArquivoDeEntrada,"%20[^\n ] \n",Titulo->elemento);/* Remova \n do buffer por %8c*///desprezando \n e whitespace []
    Titulo->pai=NULL;
}
void RemoverEmSemiPosOrdem(noh*X){/*Deletando a SubArvore X*/
    if((X)!=NULL){
        RemoverEmSemiPosOrdem((X)->filhoesquerdo);
        (X)->filhoesquerdo=NULL;
        noh*aux=(X)->irmaodireito;
        noh*aux2=NULL;
        if((aux)!=NULL)
            (aux2)=(aux)->irmaodireito;
        while((aux)!=NULL){
            RemoverEmSemiPosOrdem(aux);
            aux=aux2;
            if((aux2)!=NULL)
                aux2=(aux2)->irmaodireito;
        }
        (X)->irmaodireito=NULL;
        free(X);
        X=NULL;
    }
}
void OperacaoRemover(){/*CHAMADA DA OPERAÇÃO DE REMOÇÃO RECURSIVA**/
    noh*removedor=BuscaProcuradoEmPreOrdem(Titulo);
    if((removedor)==NULL)
        fprintf(ArquivoDeSaida,"ERRO: nao encontrado item %s\n--------------------------------------------------\n",Procurado);
    else {
        if((removedor)!=Titulo){/*RETIRANDO DA ÁRVORE*/
            if((removedor)->pai->filhoesquerdo==(removedor)){/*SE REMOVEDOR É FILHOESQUERDO*/
                (removedor)->pai->filhoesquerdo=removedor->irmaodireito;
            }
            else{/*removedor não é título nem filhoesquerdo*/ // removedor tem pai e irmao esquerdo*/
                noh*auxiliar=NULL;
                auxiliar=(removedor)->pai->filhoesquerdo;
                while((auxiliar)->irmaodireito!=(removedor))
                    auxiliar=(auxiliar)->irmaodireito;
                (auxiliar)->irmaodireito=(removedor)->irmaodireito;
            }
           (removedor)->irmaodireito=NULL;
           (removedor)->pai=NULL;
           RemoverEmSemiPosOrdem(removedor);
        }
        else{
            RemoverEmSemiPosOrdem(removedor);
            ExistenciaDaArvore=NAOEXISTE;
            free(Titulo);
            Titulo=NULL;
        }
    }
}
void InserirNoh(noh**novonoh,noh**inserido){/*InsereNoh na arvore desconsiderando se ele possui filhos*/
    switch(ModoDeInsercao){
        case SUB:{
            (*novonoh)->pai=(*inserido);
            (*novonoh)->irmaodireito=(*inserido)->filhoesquerdo;
            (*inserido)->filhoesquerdo=(*novonoh);
        }break;
        case SEGUINTE_A:{
            if(strcmp(Procurado,Titulo->elemento)==0)
                fprintf(ArquivoDeSaida,"ERRO: operacao invalida\n--------------------------------------------------\n");
            else{
                (*novonoh)->pai=(*inserido)->pai;
                (*novonoh)->irmaodireito=(*inserido)->irmaodireito;
                (*inserido)->irmaodireito=(*novonoh);
            }
        }break;
        case ERRODEINSERCAO:{
            if(*inserido==NULL)
                fprintf(ArquivoDeSaida,"ERRO: nao encontrado item %s\n--------------------------------------------------\n",Procurado);
            else if(*novonoh==NULL)
                    fprintf(ArquivoDeSaida,"ERRO: nao encontrado item %s\n--------------------------------------------------\n",NomeDaSecaoEmInsercao);
                else
                    fprintf(ArquivoDeSaida,"ERRO: operacao invalida\n--------------------------------------------------\n");
        }break;
    }
}
void EscreveNoArquivo(noh*X,int Profundidade){/*Escreve os nomes no arquivo*/
    if(X==Titulo)
        fprintf(ArquivoDeSaida,"LISTA %d\n\n      %s\n",Lista,Titulo->elemento);
    else{
        for(int i=1;i<=Profundidade;i++)
            fprintf(ArquivoDeSaida,"%d.",FilhoNaProfundidade[i]);
        fprintf(ArquivoDeSaida,"      %s\n",X->elemento);
    }
}
void OperacaoListar(noh*X,int Profundidade,int Ordem){/*OPERAÇÃO RECURSIVA PARA LISTAGEM*/ //POS ORDEM
    if(X!=NULL){
        int ordemposterior=0;
        FilhoNaProfundidade[Profundidade]=Ordem;
        noh*aux=X->filhoesquerdo;
        EscreveNoArquivo(X,Profundidade);
        while(aux!=NULL){
            ordemposterior++;
            OperacaoListar(aux,Profundidade+1,ordemposterior);
            aux=aux->irmaodireito;
        }
    }
}
int main(){
    //ArquivoDeEntrada=fopen("C:\\Lab5\\entrada5.txt","r");
    ArquivoDeEntrada=fopen("entrada5.txt","r");
    //ArquivoDeSaida=fopen("C:\\Lab5\\bruno5.txt","w");
    ArquivoDeSaida=fopen("bruno5.txt","w");
    CaptureOCabecalho();/*Operaçao sobre o ArquivoDeEntrada na main*/
    InsiraOCabecalho();/*Operacao sobre o ArquivoDeSaida na main*/
    while(Solicitacao!= FIM){/*AUTÔMATO FINITO*/
        VerificaOperacao();
        switch(ExistenciaDaArvore){/*AUTOMATO FINITO SOBRE A EXISTÊNCIA DA ÁRVORE*/
            case EXISTE:{/*SEGUE PARA ANALISAR A SOLICITACAO*/
                switch(Solicitacao){//CASE FIM, NAO FAÇA NADA
                    case TITULO:{
                        noh*auxiliar=Titulo;
                        auxiliar->irmaodireito=NULL;
                        auxiliar->pai=NULL;
                        MallocParaOTitulo();
                        auxiliar->pai=Titulo;
                        auxiliar=NULL;
                    }break;
                    case INSERIR:{
                        fscanf(ArquivoDeEntrada,"%20[^\n ] %10[^\n ] %20[^\n ] \n",NomeDaSecaoEmInsercao,Parametro,Procurado);
                        noh*inserido=NULL;
                        noh*novonoh=NULL;
                        AnalisaParametro(&inserido);//Modificacao do Estado ModoDeInsercao e Inserido=Procurado
                        if(ModoDeInsercao!=ERRODEINSERCAO&&inserido!=NULL){/*Particularidade da operação de Inserção*/
                            novonoh=(noh*)malloc(sizeof(noh));
                            strcpy(novonoh->elemento,NomeDaSecaoEmInsercao);
                            novonoh->filhoesquerdo=NULL;
                            novonoh->irmaodireito=NULL;
                            novonoh->pai=NULL;
                        }
                        InserirNoh(&novonoh,&inserido);
                    }break;
                    case REMOVER:{
                        fscanf(ArquivoDeEntrada,"%20[^\n ] \n",Procurado);
                        OperacaoRemover();
                    }break;
                    case TRANSFERIR:{
                        fscanf(ArquivoDeEntrada,"%20[^\n ] %10[^\n ] %20[^\n ] \n",NomeDaSecaoEmInsercao,Parametro,Procurado);
                        noh*parametrodetransferencia,*transferido;
                        AnalisaParametro(&parametrodetransferencia);//Modificacao do Estado ModoDeInsercao REVISARNOME
                        if(strcmp("SEGUINTE_A",Parametro)==0&&strcmp(Titulo->elemento,Procurado)==0)
                            ModoDeInsercao=ERRODEINSERCAO;
                        if(ModoDeInsercao!= ERRODEINSERCAO){
                            char auxiliar[21];
                            strcpy(auxiliar,Procurado);
                            strcpy(Procurado,NomeDaSecaoEmInsercao);
                            AnalisaParametro(&transferido);
                            strcpy(Procurado,auxiliar);
                            if(ModoDeInsercao!= ERRODEINSERCAO){
                                noh*auxiliar=transferido->pai->filhoesquerdo;
                                while(auxiliar->irmaodireito!=transferido)
                                    auxiliar=auxiliar->irmaodireito;
                                auxiliar->irmaodireito=transferido->irmaodireito;
                                transferido->pai=NULL;
                                transferido->irmaodireito=NULL;
                            }
                        }
                        InserirNoh(&transferido,&parametrodetransferencia);
                    }break;
                    case LISTAR:{
                        Lista+=1;
                        OperacaoListar(Titulo,0,0);//CONSERTAR
                        fprintf(ArquivoDeSaida,"--------------------------------------------------\n");
                    }break;
                    case ERRODEOPERACAO:{//n vai acontecer conforme a proposta do armando
                        fprintf(ArquivoDeSaida,"ERRO: operacao de solicitacao invalida\n--------------------------------------------------\n");
                    }break;
                }
            }break;
            case NAOEXISTE:{/*TITULO É A ÚNICA OPERAÇÃO VÁLIDA NESSE CASO*/
                switch(Solicitacao){
                    case TITULO:{/*TITULO NÃO NECESSARIAMENTE É A PRIMEIRA OPERAÇÃO, PORÉM É A PRIMEIRA OPERAÇÃO VÁLIDA*/
                        MallocParaOTitulo();
                        ExistenciaDaArvore=EXISTE;
                    }break;
                    case FIM:{/*NAO FAÇA NADA */}break;
                    default:fprintf(ArquivoDeSaida,"ERRO: o titulo ainda nao foi definido\n--------------------------------------------------\n");break;
                }
            }break;
        }
    }
    fclose(ArquivoDeEntrada);
    fclose(ArquivoDeSaida);
    return 0;
}
