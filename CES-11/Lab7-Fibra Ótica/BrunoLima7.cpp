/*     Aluno Bruno Lima Queiroz Santos               */
/*     Turma 3                                                  */
/*     Lab 7                                                      */
/*     Programa gerado pelo codeblocks 17.12      */

/* ---- bibliotecas ----   */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* ---------------------   */

/*

    Tecnicas usadas :

-> Grafos nao orientados  ;
-> Grafos implementados por Lista de Adjacencias  ;
-> TAD ( Tipos Abstratos de Dados )  ;

*/


/* ------------ definicoes de constantes ---------------------- */

#define MAXIMOV 150
#define MAXIMOA 1000
#define TRUE 1
#define FALSE 0

/* ---------------------------------------------------------------  */

/* -------------------- definicoes de tipos ----------------------*/

typedef int vertice; // bijecao entre  o numero do vertice e nome do vertice
typedef int aresta;
typedef int custo;
typedef int boolean;

typedef char nomedopredio[  11  ] ;

typedef enum metodo { first=0, second } metodo;

typedef struct celula* link;
typedef struct celula{
    vertice v;
    link prox;
    custo c;
}celula;

typedef struct grafo{
    vertice V;
    aresta A;
    link*adj;
}grafo;
typedef grafo*Grafo;

typedef struct conexoes{ // para organizar as arestas por descobrimento
    boolean NuvemEstaVazia;
    boolean EstaNaNuvem[ 1 + MAXIMOV ];
}nuvem;

typedef struct Aresta{  /* O MESMO TIPO */
    vertice v,w;
    custo c;
} Aresta;

typedef boolean Sentido[ 1 + MAXIMOV ];

/* ---------------------------------------------------------------  */
/* --------------------- Variaveis globais -------------------  */

nomedopredio Predio[ 1 + MAXIMOV ];

Aresta ArestaDoOutput[ 1 + MAXIMOA];

Sentido SentidoDoInput[ 1 + MAXIMOV ];

nuvem central;

metodo m= first;

FILE*ArqEntrada;
FILE*ArqSaida;

/* ---------------------------------------------------------------  */
/* ------------------------ TAD para o grafo ------------------*/

Grafo InicializacaoGrafo ( metodo m ){
    Grafo G= ( Grafo )malloc(sizeof( *G) );
    G->V =0;
    G->A =0;
    switch ( m ){
        case first:{
            G->adj=(  link* ) malloc ( ( 1+ MAXIMOV ) * sizeof ( link )  );
            for (int i = 0; i<( 1+ MAXIMOV ); i++)
                G->adj[ i ] = NULL;
        }break;
        case second: {
            G->adj = NULL;
        }break;
        default: break;
    }
    return G;
}
link NovaCelula(vertice v, custo c , link prox){
    link a = ( link )malloc( sizeof( *a ) );
    a->v = v;
    a->c = c;
    a->prox = prox;
    return a;
}
void InserirNovaCelula( Grafo G,vertice x, vertice y, custo cxy ){ /*nao cria lacos */ // INSERCAO NAS DUAS LISTAS DE ADJACENCIAS
    //G->A++;
    for (link Search = G->adj[ x ]  ; Search != NULL ; Search = Search->prox ){
        if( Search->v== y)
            return ; /* se ja existe conexao X-Y  */
    }
    G->adj[ x ] = NovaCelula( y , cxy , G->adj[ x ] ); /*   elemento add pelo inicio da lista       */
}
boolean AchouCelula( Grafo G, vertice x , vertice y){
    link Search = G->adj[ x ];
    while( Search!= NULL && Search->v != y)
        Search= Search->prox;
    if( Search!= NULL)
        return TRUE;
    else return FALSE;
}
/* =============== FIM DO TAD PARA O GRAFO ===========  */

void InicializaCentral( Grafo Input ){
    for( vertice i=1 ; i<= Input->V; i++ ){
        central.EstaNaNuvem[ i ] = TRUE;
    }
    central.NuvemEstaVazia=FALSE;
}
/*   retorna a Aresta  [ ( contador -> v  ) ]  */
link ARESTA ( Grafo Input , vertice v, vertice contador ){
    if( v!= contador && AchouCelula( Input, v, contador ) ){
        link a = Input->adj[ contador ];
        while( a!=NULL  &&  a->v != v )
        a=a->prox;
        return a;
    }
    else return NULL;
}
/*   determina a aresta mais barata do grafo em concepcao ao elemento     */
boolean EhMaisBarato( link arestatestada , link arestafixa ){ /* verifica se a testada eh mais barata que a fixada */
    if( ( arestafixa == NULL)  ||  arestatestada->c <= arestafixa->c )
        return TRUE;
    else return FALSE;
}
void AlgoritmoDePrim( Grafo Input, Grafo Output ){ /* Algoritmo de Prim implementado */
    vertice v = 1;
    vertice w= 1;
    central.EstaNaNuvem[ v ] = FALSE;
    Output->V++;
    link aresta= NULL;
    Aresta aplicacao;
    aplicacao.v=1;
    aplicacao.w=1;
    int Cout=0;
    while(  !central.NuvemEstaVazia  ){
        aplicacao.c=-1;
        for(  v=1 ; v<= Input->V  ; v++  ){
            for( w = 1 ; w<= Input->V ; w++ ){
                if( !central.EstaNaNuvem[ v ]&&central.EstaNaNuvem[ w ] ){
                // a aplicacao v-> w eh possivelmente vahlida
                // resta verificar se ha aresta v -> w
                    aresta= ARESTA( Input , w , v );
                    if( (aresta!=NULL) &&
                        (aplicacao.c==-1 || (aresta->c <= aplicacao.c)
                         )
                    ){
                        aplicacao.c = aresta->c;
                        aplicacao.v = v;
                        aplicacao.w = w;
                    }
                }
            }
        }
        if( aplicacao.c != -1 ){ // INSERCAO DE PRIM
            //InserirNovaCelula( Output, aplicacao.v , aplicacao.w, aplicacao.c );
            Output->V++;
            central.EstaNaNuvem[ aplicacao.w ] = FALSE;
            ArestaDoOutput[ ++Output->A ].c= aplicacao.c;
            if( SentidoDoInput[ aplicacao.v ][ aplicacao.w ] ){
                ArestaDoOutput[ Output->A ].v=aplicacao.v;
                ArestaDoOutput[ Output->A ].w=aplicacao.w;
            }
            else{
                ArestaDoOutput[ Output->A ].v=aplicacao.w;
                ArestaDoOutput[ Output->A ].w=aplicacao.v;
            }
        }
        Cout=0;
        for( int i =1 ; i<= Input->V ; i++ )
            if( central.EstaNaNuvem[ i ] )
                Cout++;
        if( Cout == 0 )
            central.NuvemEstaVazia = TRUE;
    }
}

boolean achou ( Grafo G , char name[ 11 ] , vertice* posic ){ /* verificacao de vertices armazenados */
    for( int i = 0; i<= G->V ; i++ ){
        if( strcmp( name, Predio[ i ] )==0  ){
            *posic = i;
            return TRUE;
        }
    }
    *posic = 1 + G->V;
    return FALSE;
}

/* -------------------  cabecalho dos arq. entrada e saida ---------------- */

void removercabecalho(){
    char lixo[ 72 ];
    for(int i=0; i< 6; i++)
        fgets( lixo, 71 , ArqEntrada ); // fgets é melhor para remover exatamente n linhas do arquivo conhecendo-se o tamanho maximo dela
}
void inserecabecalhofirst(){
    fprintf( ArqSaida, "Arquivo saida\nResposta do Algoritmo de Prim\nbla bla\n\n" );
    fprintf( ArqSaida, "---------------------------------------\n" );
    fprintf( ArqSaida, "Ordem de selecao pelo algoritmo\n" );
    fprintf( ArqSaida, "---------------------------------------\n" );
}
void inserecabecalhosecond(){
    fprintf( ArqSaida, "---------------------------------------\n" );
    fprintf( ArqSaida, "Ordem crescente de custos\n" );
    fprintf( ArqSaida, "---------------------------------------\n" );
}
/* -------------------------------------------------------------------------- */
void OrdemDeSelecaoPeloAlgoritmo( Grafo Output, metodo m ){
    int Arestas = Output->A;
    int aresta=1;
    vertice v,w;
    custo c,total=0;
    while( aresta<= Arestas ){
        v = ArestaDoOutput[ aresta ].v;
        w = ArestaDoOutput[ aresta ].w;
        c = ArestaDoOutput[ aresta++ ].c;
        total+=c;
        fprintf( ArqSaida,"%-10s %-10s %3d\n", Predio[ v ] , Predio[ w ] , c );
    }
    if( m == first )
        fprintf( ArqSaida,"\nCusto total: %d\n\n", total );
}
void BubbleSort( Grafo Output ){ /* BubbleSort sobre as arestas */
    int limite = Output->A;
    int trocou=TRUE;
    for( int i = 0; i<= limite-1 && trocou ; i++ ){
        trocou= FALSE;
        for( int j = i; j<= limite-1; j++){
            if( ArestaDoOutput[ j ].c > ArestaDoOutput[ j +1 ].c ){
                ArestaDoOutput[ 0 ] = ArestaDoOutput[ j + 1 ];
                ArestaDoOutput[ j + 1 ] = ArestaDoOutput[ j ];
                ArestaDoOutput[  j ] = ArestaDoOutput[ 0 ];
                trocou= TRUE;
            }
        }
    }
}
int main(){
    //ArqEntrada=fopen("C:\\Lab7\\entrada7.txt","r");
    ArqEntrada=fopen("entrada7.txt","r");
   //ArqSaida=fopen("C:\\Lab7\\brunolima7.txt","w");
   ArqSaida=fopen("brunolima7.txt","w");
    char str1[ 11 ], str2[ 11 ];
    Aresta ARESTA;
    removercabecalho();
    Grafo Input = InicializacaoGrafo( first );
    Grafo Output = InicializacaoGrafo( second );
    /* abaixo  armazenamento do INPUT na forma de grafo  */
    while(  fscanf( ArqEntrada, "%10[^\n\t    ]   %10[^\n\t    ]    %d      " , str1 , str2 , &ARESTA.c ) != EOF  ){ // EXTRACAO EXPERTA
        if( !achou( Input , str1 , &ARESTA.v ) )
            strcpy( Predio[  ++Input->V  ], str1 );
        if ( !achou( Input, str2 , &ARESTA.w ) )
            strcpy( Predio[ ++Input-> V ], str2 );
        InserirNovaCelula( Input , ARESTA.v , ARESTA.w , ARESTA.c );
        InserirNovaCelula( Input , ARESTA.w , ARESTA.v , ARESTA.c );
        SentidoDoInput[ ARESTA.v ][ ARESTA.w ]= TRUE;
        SentidoDoInput[ ARESTA.w ][ ARESTA.v ]= FALSE;
        Input->A++;
    }
    InicializaCentral( Input );
    AlgoritmoDePrim( Input, Output );
    inserecabecalhofirst();
    OrdemDeSelecaoPeloAlgoritmo( Output  , first );
    BubbleSort( Output );
    inserecabecalhosecond();
    OrdemDeSelecaoPeloAlgoritmo( Output ,  second);
    fclose(ArqSaida);
    fclose(ArqEntrada);
    return 0;
}
