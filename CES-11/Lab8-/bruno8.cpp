/*Aluno Bruno Lima Queiroz Santos        */
/*Turma 3                                */
/*Lab 8                                  */
/*Programa gerado pelo codeblocks 17.12  */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define boolean int
#define TRUE 1
#define FALSE 0
#define PADRAO 0
#define DESCOBERTO 1
#define VISITADO 2
typedef int Grafo [ 52 ][ 52 ] ;
typedef struct vertices{
    char name [ 31 ];
    char letra;
}vertice;
vertice V[ 52 ]; // nome do vertice
Grafo Adjacencia = { 0 };/* i -- > j  */ // Matriz de adjacencGrafo Aresta;
Grafo Tempo = { 0 }; /* i --> j */
int quant=0;
int Pilha[ 52 ]={ 0 };
int State[ 52 ]= { 0 };
int QuantPilha=0;
int maximo[ 52 ] = {  0  };
int MAX = 0;
int marcador = 0;
int sucessor[ 52 ] = { 0 };
typedef struct Informacoes{
    char tarefa;
    char descricao[ 31 ];
    int Duracao;
    char TarefasPrecedentes[ 52 ];
} info;
info Informacoes[ 51 ]; // ARMAZENAR O INPUT ANTES DE ORGANIZA-LO
int PilhaVazia( int *QuantPilha ){ // TAD PARA PILHA VERIICAR SE A PILHA ESTA VAZIA
    if( *QuantPilha==0)
        return TRUE;
    else return FALSE;
}
void RemoveTopo( int *QuantPilha ){ // TAD PARA PILHA REMOVER O TOPO
    if( PilhaVazia( QuantPilha) )
        system(" pause " );
    else (*QuantPilha)--;
}
int Topo( int *Pilha , int *QuantPilha){ //TAD PARA PILHA  APRESENTAR TOPO
    if( PilhaVazia( QuantPilha )  )
        system(" pause " );
    return Pilha[ *QuantPilha ];
}
void Insere( int *Pilha, int *QuantPilha , int Tarefa ){ // TAD PARA PILHA INSERCAO
    if( *QuantPilha == 52 )
        system( "pause" );
    else{
        Pilha[ 1+ *QuantPilha ] = Tarefa;
        (*QuantPilha)++;
    }
}
int EhFimDeGrafo( int z ){ /* se z eh um vertice terminal*/
    if( Adjacencia[ z ][quant + 1] )
        return  TRUE;
    return FALSE;
}
int AchouCiclo( int y ){ /*  algoritmo para verificar se ha ciclo recursivamente      */
    int r=FALSE;
    if( y<=quant+1 ){
        Insere( Pilha , &QuantPilha , y );
        State[ y ] = DESCOBERTO;
        for( int i = 1; i<=quant+1; i++){
            if( Adjacencia[ y ][ i ] ){
                if( State[ i ] == DESCOBERTO ){
                    r= TRUE;
                    Insere( Pilha, &QuantPilha , i );
                }
                else if( State[ i ] == PADRAO )
                            r = AchouCiclo( i );
                if ( r )
                    return r;
            }
        }
        State[ y ] =VISITADO;
        RemoveTopo( &QuantPilha );
    }
    return r;
}
int ExisteCiclo( int x ){  /*  retorna a classificacao do grafo ciclico ou aciclico     */
    for( int i = x; i<= quant+1 ; i++)
        if(  State[ i ] == PADRAO && AchouCiclo( i ) )
            return TRUE;
    return FALSE;
}
int QuantidadeDePrecedentes( char descricao[ 31 ] ){ /*  retorna a quantidade de precedentes  */
    int q=0;
    if( descricao[ 1 ] == '.' )
        return q;
    else
        for( int i= 1; descricao[ i ]!= '\0'&& i<=31 ; i++){
            q++;
        }
    return q;
}
int VPosic( char letra, int i ){ /*  Determinar a posicao do vertice V  */
   for( int j=1 ; j<= i ; j++)
        if( V[ j ].letra == letra )
            return j;
    return 0;
}
boolean FimDeNome( char A, char B){ /*  blank characters  */
    if( A=='\t' )
        return TRUE;
    if( A== 32 && B == 32 ) //Numero correspondente
        return TRUE;
    return FALSE;
}
void fextracao( FILE*ArqEntrada, int tam , int posic){ /* Funcao para extrair descricao do arquivo */
    char A,B;
    int t=0;
    fscanf( ArqEntrada, "%c" , &B);
    A = B;
    while(  !FimDeNome(A,B)  &&  t< tam) {
        A=B;
        fscanf( ArqEntrada, "%c" , &B);
        if( !FimDeNome( A, B ) )
            Informacoes[ posic ].descricao[ t ] = A;
        t++;
    }
    if( t< tam )
        Informacoes[ posic ].descricao[ t-1 ] = '\0';
    else Informacoes[ posic ].descricao[ t ] ='\0';
}
void OrdemTopologica ( int y ){ /* reaproveitar-se-ah a Pilha */
    if( y<=quant+1 && State[ y ]==PADRAO ){ // O FINAL ( nao eh um vertice) SERA EMPILHADO NA ORDEM TOPOLOGICA !!!
        State[ y ] = DESCOBERTO;
        for( int i = 1; i<=quant+1; i++)
            if( Adjacencia[ y ][ i ] )
                OrdemTopologica( i );
        State[ y ] =VISITADO;
        Insere( Pilha , &QuantPilha , y );
    }
}
int EhSemPrecedente( int v ){ /*  valida se o vertice eh um ponto inicial no grafo      */
    for( int i=1; i<=quant;i++){
        if( Adjacencia[ i ][ v ] )
            return FALSE;
    }
    return TRUE;
}
void Maximo(  int v, int k  ){ /*   pondera o vertice de forma analoga ao algoritmo de Djkstra        */
    for(  int i =k  ;   i<= QuantPilha   ;   i++  ){
        if( Adjacencia[  Pilha[ i ]   ][ v ]   &&   maximo[  Pilha[ i ]  ]  <  Tempo[ Pilha[ i ] ][ v ] + maximo[ v ] ){
            maximo[  Pilha[ i ]   ] = Tempo[  Pilha[ i ]  ][ v ] + maximo[ v ];
            sucessor[   Pilha[ i ]   ] = v;
        }
    }
}
void CaminhoCritico( ){ /*     Define o caminho critico no grafo                */
    for( int i=1;i<=quant; i++){
        if( EhFimDeGrafo( i ) ){
            maximo[  i  ] = Tempo[ i ][ quant+1 ];
            sucessor[   i   ] = quant+1;
        }
    }
    for( int i = 1 ;   i<=QuantPilha   ;  i++   ) // Indice 1 eh fim ....
        Maximo( Pilha[ i ] , i );
    for( int i = 1 ; i<=quant; i++){
        if( EhSemPrecedente( i ) && maximo[ i ] > MAX ){
            MAX=maximo[ i ];
            marcador = i;
        }
    }
}
int main(){
    FILE  *ArqEntrada, *ArqSaida;
    //ArqEntrada = fopen("C:\\Lab8\\entrada8.txt","r");
    ArqEntrada = fopen("entrada8.txt","r");
    { /* Escopo para extracao do arquivo */
        char Lixo[ 63 ];
        for( int i = 1; i<= 7 ; i++ )
        fgets( Lixo ,62 , ArqEntrada );
        char Precedentes[ 101 ];
        fscanf(ArqEntrada,"   %s    ", &Lixo[ 0 ] );
        int j=1;
        do{ /*   Funcao para extrair do arquivo informacoes  */
            Informacoes[ ++quant ].tarefa = Lixo[ 0 ];
            fextracao( ArqEntrada, 30 , quant );/* funcao para extrair do arquivo o nome descritivo */
            fscanf( ArqEntrada," %d  " , &Informacoes[ quant ].Duracao );
            fscanf( ArqEntrada,"%s  ", Precedentes ); //TRADICIONAL
            j=1;
            for( int i = 0; i<= strlen( Precedentes ); i+=2 ) // STRLEN para tradicional
                Informacoes[ quant ].TarefasPrecedentes[  j++  ] = Precedentes[ i ];
            fscanf(ArqEntrada,"%s  ", &Lixo[ 0 ] );
        }while( Lixo[ 0 ]!= '-'  );
    }
    fclose( ArqEntrada );
    { /* Escopo para a organizacao do INPUT   */
        for( int i = 1; i<= quant ; i++ ){ /* Introduzindo os vertices */
            V[ i ].letra = Informacoes[ i ].tarefa;
            strcpy( V[ i ].name , Informacoes[ i ].descricao );
        }
        char Precedente;
        int posicA,quantPrecedentes;
        for( int posicB= 1; posicB<= quant; posicB++ ){ /* Introduzindo as arestas A to B*/
            quantPrecedentes=QuantidadeDePrecedentes( Informacoes[ posicB ].TarefasPrecedentes );
            for( int i = 0 ; i< quantPrecedentes ;  ){
                Precedente=Informacoes[ posicB ].TarefasPrecedentes[ ++i ];
                posicA=VPosic( Precedente , quant );
                Adjacencia[ posicA ][ posicB ]= TRUE;
                Tempo[ posicA ][ posicB ]= Informacoes[ posicA ].Duracao;
            }
        }
        posicA=0;
        int j=1;
        int SemDescendente = TRUE;
        for( int i=1; i<=quant; i++){ /* Introduzindo conexao entre o grafo e FIM  na col quant+1*/
            while(  SemDescendente &&  j<=quant  ){
                if( Adjacencia[ i ][ j ] )
                    SemDescendente= FALSE;
                j++;
            }
            if( SemDescendente== TRUE ){
                Adjacencia[  i  ][  quant+1  ] = TRUE;
                Tempo[ i ][  quant+1  ] = Informacoes[ i ].Duracao;
            }
            j=1;
            SemDescendente = TRUE;
        }
    }
    int existeciclo;
    existeciclo = ExisteCiclo( 1 );
    //ArqSaida = fopen( "C:\\Lab8\\bruno8.txt","w");
    ArqSaida = fopen( "bruno8.txt","w");
    fprintf(ArqSaida,"Exemplo de arquivo de saida\n");
    fprintf(ArqSaida,"PERT/CPM\n");
    fprintf(ArqSaida,"Pode escrever qualquer coisa no cabecalho.\n");
    fprintf(ArqSaida,"Coloque exatamente 5 linhas antes do traco.\n\n");
    fprintf(ArqSaida,"------------------------------------------------------------\n");
    fprintf(ArqSaida,"\n");
    if( existeciclo ){
        fprintf(ArqSaida,"UM CICLO:\n\n");
        for ( int i =1 ; V[ Pilha[ i ]  ].letra!= V[ Pilha[ QuantPilha ]  ].letra; i++ );
        for ( int i =1 ; i<= QuantPilha ; i++ )
            fprintf(ArqSaida,"%-2c" , V[  Pilha[ i ] ].letra );
        fprintf(ArqSaida,"\n\n");
        fprintf(ArqSaida,"------------------------------------------------------------\n");
        fprintf(ArqSaida,"\nCAMINHO CRITICO:\n\n");
        fprintf(ArqSaida,"NAO EH POSSIVEL BUSCAR CAMINHO CRITICO\n\n");
        fprintf(ArqSaida,"------------------------------------------------------------");
    }
    else{ // DETERMINE A ORDEM TOPOLOGICA
        for( int c =51; c>=0 ; c--){
            Pilha[ c ]  = PADRAO;
            State[ c ] = PADRAO;
        }
        QuantPilha = PADRAO;
        for ( int i=1; i<=quant ; i++)
            OrdemTopologica( i );
        fprintf(ArqSaida,"UMA ORDENACAO TOPOLOGICA:\n");
        fprintf(ArqSaida,"\n");
        for( int i = QuantPilha; i>=2; i--)
            fprintf(ArqSaida,"%-2c", V[ Pilha[ i ] ].letra );
        fprintf(ArqSaida,"\n\n");
        fprintf(ArqSaida,"------------------------------------------------------------\n");
        fprintf(ArqSaida,"\n");
        fprintf(ArqSaida,"CAMINHO CRITICO:\n\n");
        fprintf(ArqSaida,"TAREFA        DESCRICAO           DURACAO\n\n");
        CaminhoCritico( );
        int t = marcador;
        while( t!= quant+1 ){
            fprintf(ArqSaida," %2c   %-30s %2d\n" , V[ t ].letra , V[ t ].name , Tempo[ t ][ sucessor[ t ] ] );
            t = sucessor[ t ];
        }
        fprintf(ArqSaida,"                                   ----\n");
        fprintf(ArqSaida,"TEMPO MINIMO PARA O PROJETO:         %2d semanas", MAX);
    }
    fclose(ArqSaida );
    return 0;
}
