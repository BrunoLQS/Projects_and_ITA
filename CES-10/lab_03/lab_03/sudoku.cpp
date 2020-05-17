/* Copyright by BRUNO LIMA QUEIROZ SANTOS */
/* Turma 3                                */
/* Lab03: Sudoku Inteligente    */
/* Programa compilado com codeblocks 17.12*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<locale.h>


void telainicial(int erro,int ptos,int recorde,int a00, int a01, int a02, int a03, int a04,int a10, int a11, int a12, int a13, int a14,int a20, int a21, int a22, int a23, int a24,int a30, int a31, int a32, int a33, int a34,int a40, int a41, int a42, int a43, int a44){
    int mat[5][5]={{a00,a01,a02,a03,a04},{a10,a11,a12,a13,a14},{a20,a21,a22,a23,a24},{a30,a31,a32,a33,a34},{a40,a41,a42,a43,a44}};
    for(int i=0;i<=4;i++){
        for(int j=0;j<=4;j++){
            if (mat[i][j]>=0 && mat[i][j]<=5)
                mat[i][j]+=48;
            else
                mat[i][j]=88;
        }
    }
    printf("\n\t\t---------------------------------------");
    printf("\n\t\t| erros: %d | pontos: %d | recorde: %d |" ,erro,ptos,recorde);
    printf("\n\t\t---------------------------------------");
    printf("\n\n\t\t              SUDOKU 5X5");
    printf("\n\t\t   ---------------------------------");
    printf("\n\t\t    | %c  |   %c  |  %c  |  %c  |  %c  |",mat[0][0],mat[0][1],mat[0][2],mat[0][3],mat[0][4]);
    printf("\n\t\t   ---------------------------------");
    printf("\n\t\t    | %c  |   %c  |  %c  |  %c  |  %c  |",mat[1][0],mat[1][1],mat[1][2],mat[1][3],mat[1][4]);
    printf("\n\t\t   ---------------------------------");
    printf("\n\t\t    | %c  |   %c  |  %c  |  %c  |  %c  |",mat[2][0],mat[2][1],mat[2][2],mat[2][3],mat[2][4]);
    printf("\n\t\t   ---------------------------------");
    printf("\n\t\t    | %c  |   %c  |  %c  |  %c  |  %c  |",mat[3][0],mat[3][1],mat[3][2],mat[3][3],mat[3][4]);
    printf("\n\t\t   ---------------------------------");
    printf("\n\t\t    | %c  |   %c  |  %c  |  %c  |  %c  |",mat[4][0],mat[4][1],mat[4][2],mat[4][3],mat[4][4]);
    printf("\n\t\t   ---------------------------------");

}
/* a fun��o acima imprime a tela do sudoku */
int verificaErro(int a00,int a01, int a02, int a03, int a04,int a10, int a11, int a12, int a13, int a14,int a20, int a21, int a22, int a23, int a24,int a30, int a31, int a32, int a33, int a34,int a40, int a41, int a42, int a43,int a44){
    int matrz[5][5]={{a00,a01,a02,a03,a04},{a10,a11,a12,a13,a14},{a20,a21,a22,a23,a24},{a30,a31,a32,a33,a34},{a40,a41,a42,a43,a44}};
    for (int i=0;i<=4;i++){//para cada linha i
        int maux[5] = {0,0,0,0,0};/*vetor auxiliar � zerado antes da verifica��o ao longo de uma linha*/
        for (int j=0;j<=4;j++){
            switch (matrz[i][j]){
                case 0: break;
                case 1: maux[0]+=1; if (maux[0] > 1 )return 1;break;
                case 2: maux[1]+=1; if (maux[1] > 1 )return 1;break;
                case 3: maux[2]+=1; if (maux[2] > 1 )return 1;break;
                case 4: maux[3]+=1; if (maux[3] > 1 )return 1;break;
                case 5: maux[4]+=1; if (maux[4] > 1 )return 1;break;
            }
        }
    }
    for (int j=0;j<=4;j++){//para cada coluna j
        int maux[5] = {0,0,0,0,0};/*vetor auxiliar � zerado antes da verifica��o ao longo de uma coluna*/
        for (int i=0;i<=4;i++){
            switch (matrz[i][j]){
                case 0: break;
                case 1: maux[0]+=1; if (maux[0] > 1 )return 1;break;
                case 2: maux[1]+=1; if (maux[1] > 1 )return 1;break;
                case 3: maux[2]+=1; if (maux[2] > 1 )return 1;break;
                case 4: maux[3]+=1; if (maux[3] > 1 )return 1;break;
                case 5: maux[4]+=1; if (maux[4] > 1 )return 1;break;
            }
        }
    }
return 0;
}
/* se a fun��o "verificaErro" acima retorna 1, h� erro no arranjo dos numeros conforme as regras do sudoku, sen�o  retorna 0 e est� correto */

/* a fun��o abaixo versotini verifica se h� problemas no sorteio inicial para a apresenta��o da tela sudoku */
int versortini(int x1, int x2, int x3, int x4, int x5, int x6, int y1, int y2, int y3 , int y4, int y5, int y6){
    int mat2 [6][6] = {{0},{0},{0},{0},{0},{0}};/* a matriz � zerada antes do looping */
    mat2[x1][y1]+=1;
    mat2[x2][y2]+=1;
    mat2[x3][y3]+=1;
    mat2[x4][y4]+=1;
    mat2[x5][y5]+=1;
    mat2[x6][y6]+=1;
    for(int i=0;i<=5;i++){
        for(int j=0;j<=5;j++){
            if(mat2[i][j]>1)
                return 1;
        }
    }
    return 0;
    }
/* a fun��o acima retorna 1 se houver erro no sorteio inicial das entradas , sen�o retorna 0 */
int verificposi(int x1, int y1, int a00,int a01, int a02, int a03, int a04, int a10, int a11, int a12, int a13, int a14, int a20, int a21, int a22, int a23, int a24, int a30, int a31, int a32, int a33, int a34, int a40, int a41, int a42, int a43, int a44){
    int matrz[5][5]={{a00,a01,a02,a03,a04},{a10,a11,a12,a13,a14},{a20,a21,a22,a23,a24},{a30,a31,a32,a33,a34},{a40,a41,a42,a43,a44}};
    if (matrz[x1][y1] !=0)
        return 1;
    else
        return 0;
}
/*a fun��o acima retorna 1 se a posi��o estiver indispon�vel, sen�o retorna 0*/
int verificjogada(int x1,int y1,int a00,int a01, int a02, int a03, int a04,int a10, int a11, int a12, int a13, int a14,int a20, int a21, int a22, int a23, int a24,int a30, int a31, int a32, int a33, int a34,int a40, int a41, int a42, int a43,int a44){
    /*desde que x1,y1 seja uma entrada v�lida */
    int matrz[5][5]={{a00,a01,a02,a03,a04},{a10,a11,a12,a13,a14},{a20,a21,a22,a23,a24},{a30,a31,a32,a33,a34},{a40,a41,a42,a43,a44}};
    int k=1;int z;
    do{int i=0;int j=0;
        z=0;/* a jogada � poss�vel at� que se verifique o contr�rio */
        matrz[x1][y1]=k;
        int maux[5] = {0,0,0,0,0};/* zera-se o vetor auxiliar antes de cada looping*/
        /*� conveniente zera o vetor  na declara��o*/
        do{//para cada linha i
            switch (matrz[i][y1]){
                case 0: break;
                case 1: maux[0]+=1;
                        if (maux[0] > 1 ){
                            z=1;
                        }
                        break;
                case 2: maux[1]+=1;
                        if (maux[1] > 1 ){
                            z=1;
                        }
                        break;
                case 3: maux[2]+=1;
                        if (maux[2] > 1 ){
                            z=1;
                        }
                        break;
                case 4: maux[3]+=1;
                        if (maux[3] > 1 ){
                            z=1;
                        }
                        break;
                case 5: maux[4]+=1;
                        if (maux[4] > 1 ){
                            z=1;
                        }
                        break;
                default:break;
            }
            i++;
        }while(i<=4 && z!=1);
        for (int L=0;L<=4;L++){/* zera-se o vetor auxiliar antes de cada looping*/
            maux[L]=0;
        }
        do{//para cada coluna j
            switch (matrz[x1][j]){/*examinando a linha fixa*/
                case 0: break;
                case 1: maux[0]+=1;
                        if (maux[0] > 1 ){
                            z=1;
                        }
                        break;
                case 2: maux[1]+=1;
                        if (maux[1] > 1 ){
                            z=1;
                        }
                        break;
                case 3: maux[2]+=1;
                        if (maux[2] > 1 ){
                            z=1;
                        }
                        break;
                case 4: maux[3]+=1;
                        if (maux[3] > 1 ){
                            z=1;
                        }
                        break;
                case 5: maux[4]+=1;
                        if (maux[4] > 1 ){
                            z=1;
                        }break;
                default: break;
            }
            j++;
        }while(j<=4 && z!=1);
        k++;
    }while(k<=5 && z!=0);/* z=0 j� � suficiente para a verifica��o*/
    if (z==1 && k==6){
        return 1;
    }
    if (z==0){
        return 0;
    }
    return 1;/*esse return � simb�lico para o programa n�o enxer o saco que t� faltando*/
/*todos os casos j� foram contemplado pelas verifica��es if-clause*/
}
/* a fun��o acima retorna 1 se n�o � poss�vel fazer uma jogada na posi��o recebida,sen�o retorna 0*/
int verificafim(int erro,int a00,int a01, int a02, int a03, int a04,int a10, int a11, int a12, int a13, int a14,int a20, int a21, int a22, int a23, int a24,int a30, int a31, int a32, int a33, int a34,int a40, int a41, int a42, int a43,int a44){
    int kverificposi=0;
    if (erro==5){/*ap�s 5 erros , final de jogo*/
        return 1;/*o jogo acabou*/
    }
    for (int i=0;i<=4;i++){/*verifica  obstinadamente se h� alguma posi��o dispon�vel na tabela*/
        for (int j=0;j<=4;j++){
            kverificposi=verificposi(i,j,a00, a01, a02, a03, a04, a10, a11, a12, a13, a14, a20, a21,  a22, a23, a24, a30, a31, a32, a33, a34, a40,  a41, a42, a43, a44);
            if (kverificposi==0){
                return 0;/* o jogo continua*/
            }
        }
    }
    return 1;/* o jogo terminou*/
}
/* a fun��o acima retorna 1 se o jogo acabou,sen�o retorna 0*/
void telafinal(int erro,int R,int r,int krecorde){
    if (erro==5){/* se o jogador perdeu*/
        char mat[5][5]={{'X','X','X','X','X'},{'X','X','X','X','X'},{'X','X','X','X','X'},{'X','X','X','X','X'},{'X','X','X','X','X'}};
        system("cls");
        printf("\n\t    ____________________________________________");
        printf("\n\n\t    | VOC� PERDEU! | Recorde: %d | pontua��o : %d |" ,r,R);
        printf("\n\t    ____________________________________________");
        printf("\n\t\t---------------------------------");
        printf("\n\t\t | %c  |   %c  |  %c  |  %c  |  %c  |",mat[0][0],mat[0][1],mat[0][2],mat[0][3],mat[0][4]);
        printf("\n\t\t---------------------------------");
        printf("\n\t\t | %c  |   %c  |  %c  |  %c  |  %c  |",mat[1][0],mat[1][1],mat[1][2],mat[1][3],mat[1][4]);
        printf("\n\t\t---------------------------------");
        printf("\n\t\t | %c  |   %c  |  %c  |  %c  |  %c  |",mat[2][0],mat[2][1],mat[2][2],mat[2][3],mat[2][4]);
        printf("\n\t\t---------------------------------");
        printf("\n\t\t | %c  |   %c  |  %c  |  %c  |  %c  |",mat[3][0],mat[3][1],mat[3][2],mat[3][3],mat[3][4]);
        printf("\n\t\t---------------------------------");
        printf("\n\t\t | %c  |   %c  |  %c  |  %c  |  %c  |",mat[4][0],mat[4][1],mat[4][2],mat[4][3],mat[4][4]);
        printf("\n\t\t---------------------------------");
        if (krecorde==1){
            printf("\n\t\tESSA PARTIDA FOI UM RECORDE !");
        }

    }
    else{
        int mat[5][5]={{R,R,R,R,R},{R,R,R,R,R},{R,R,R,R,R},{R,R,R,R,R},{R,R,R,R,R}};
        system("cls");
        printf("\n\t    _________________________________________________");
        printf("\n\n\t     | VOC� VENCEU! | Recorde: %d | Pontua��o: %d |" ,r,R);
        printf("\n\t    _________________________________________________");
        printf("\n\t    ------------------------------------------------");
        printf("\n\t\t | %d  |   %d  |  %d  |  %d  |  %d  |",mat[0][0],mat[0][1],mat[0][2],mat[0][3],mat[0][4]);
        printf("\n\t    ------------------------------------------------");
        printf("\n\t\t | %d  |   %d  |  %d  |  %d  |  %d  |",mat[1][0],mat[1][1],mat[1][2],mat[1][3],mat[1][4]);
        printf("\n\t    ------------------------------------------------");
        printf("\n\t\t | %d  |   %d  |  %d  |  %d  |  %d  |",mat[2][0],mat[2][1],mat[2][2],mat[2][3],mat[2][4]);
        printf("\n\t    ------------------------------------------------");
        printf("\n\t\t | %d  |   %d  |  %d  |  %d  |  %d  |",mat[3][0],mat[3][1],mat[3][2],mat[3][3],mat[3][4]);
        printf("\n\t    ------------------------------------------------");
        printf("\n\t\t | %d  |   %d  |  %d  |  %d  |  %d  |",mat[4][0],mat[4][1],mat[4][2],mat[4][3],mat[4][4]);
        printf("\n\t    ------------------------------------------------");
        if (krecorde==1){
            printf("\n\t\tESSA PARTIDA FOI UM RECORDE !");
        }
    }
}
int verificaw(int w){ /*se w est� fora do escopo num�rico, retorna-se 1*/
        if(w<10){
            return 1;
        }
        if(15<w && w<20){
            return 1;
        }
        if(25<w && w<30){
            return 1;
        }
        if(35<w && w<40){
            return 1;
        }
        if(45<w && w<50){
            return 1;
        }
        if(55<w){
            return 1;
        }
    return 0;
}
int verificaLacunas(int a00,int a01, int a02, int a03, int a04,int a10, int a11, int a12, int a13, int a14,int a20, int a21, int a22, int a23, int a24,int a30, int a31, int a32, int a33, int a34,int a40, int a41, int a42, int a43,int a44){
    int z =25;
    for (int i=0;i<=4;i++){
        for(int j=0;j<=4;j++){
                z-=verificposi(i,j,a00,a01,a02,a03,a04,a10,a11,a12,a13,a14,a20,a21,a22,a23,a24,a30,a31,a32,a33,a34,a40,a41,a42,a43,a44);
        }
    }
    return z;
}
/*retorna a quantidade de lacunas no tabuleiro*/
int main(){
    int recorde=0; int N=0;char c;
    do{/* looping para jogar novamente , caso o jogador escolha isso*/
        N++;
        setlocale(LC_ALL,"Portuguese");
        int sdk[5][5]={{0},{0},{0},{0},{0}};/*definindo a matriz do sudoku*/
        int x1,x2,x3,x4,x5,x6,y1,y2,y3,y4,y5,y6,kverificafim;
        int zx; int zy;int sinalerrow=0;int erro=0;int ptos;int kverificaLacunas;int krecorde=0;
        kverificafim=0; ptos=100; int kverificaposi=0;
        srand(time(NULL));
        int kversortini=1;
        while (kversortini==1){ /*sorteio das posi��es no sudoku a ser preenchidas � aqui*/
        x1= rand()%5;y1= rand()%5;
        x2= rand()%5;y2= rand()%5;
        x3= rand()%5;y3= rand()%5;
        x4= rand()%5;y4= rand()%5;
        x5= rand()%5;y5= rand()%5;
        x6= rand()%5;y6= rand()%5;
        kversortini=versortini(x1,x2,x3,x4,x5,x6,y1,y2,y3,y4,y5,y6);/*invocando a fun��o para validar o sorteio*/
        }
        int kverificaErro =1;
        while (kverificaErro==1){/*sorteio dos n�meros nas referidas posi��es sorteadas*/
        sdk[x1][y1]=1+rand()%5;
        sdk[x2][y2]=1+rand()%5;
        sdk[x3][y3]=1+rand()%5;
        sdk[x4][y4]=1+rand()%5;
        sdk[x5][y5]=1+rand()%5;
        sdk[x6][y6]=1+rand()%5;
        kverificaErro=verificaErro(sdk[0][0],sdk[0][1],sdk[0][2],sdk[0][3],sdk[0][4],sdk[1][0],sdk[1][1],sdk[1][2],sdk[1][3],sdk[1][4],sdk[2][0],sdk[2][1],sdk[2][2],sdk[2][3],sdk[2][4],sdk[3][0],sdk[3][1],sdk[3][2],sdk[3][3],sdk[3][4],sdk[4][0],sdk[4][1],sdk[4][2],sdk[4][3],sdk[4][4]);
        }
        do{/*Um jogo*/
            int estado=1;int w; int w1; int w2; int w3;int m=0;
            kverificafim=verificafim(erro,sdk[0][0],sdk[0][1],sdk[0][2],sdk[0][3],sdk[0][4],sdk[1][0],sdk[1][1],sdk[1][2],sdk[1][3],sdk[1][4],sdk[2][0],sdk[2][1],sdk[2][2],sdk[2][3],sdk[2][4],sdk[3][0],sdk[3][1],sdk[3][2],sdk[3][3],sdk[3][4],sdk[4][0],sdk[4][1],sdk[4][2],sdk[4][3],sdk[4][4]);
            if (kverificafim!=1){
            system("cls");/*para apagar a tela a cada ciclo*/
            telainicial(erro,ptos,recorde,sdk[0][0],sdk[0][1],sdk[0][2],sdk[0][3],sdk[0][4],sdk[1][0],sdk[1][1],sdk[1][2],sdk[1][3],sdk[1][4],sdk[2][0],sdk[2][1],sdk[2][2],sdk[2][3],sdk[2][4],sdk[3][0],sdk[3][1],sdk[3][2],sdk[3][3],sdk[3][4],sdk[4][0],sdk[4][1],sdk[4][2],sdk[4][3],sdk[4][4]);
            if(sinalerrow==1){/*informa o erro tipo 1 na jogada*/
               printf("\n\t\t   Voc� digitou uma posi��o imposs�vel!");
            }
            if(sinalerrow==2){/*informa o erro tipo 2 na jogada*/
               printf("\n\t\t   Voc� digitou uma posi��o indispon�vel");
            }
            printf("\n\t\t   Digite um numero  inteiro positivo\n\t\t   de dois d�gitos representando\n\t\t   a posi��o a ser manipulada:");
            scanf("%d",&w);
            fflush(stdin);
            w1=w/10 -1;
            w2=w%10 -1;
            sinalerrow=0;/*chave para uma impress�o na tela*/
            /*sequ�ncia de verifica��es*/
            sinalerrow=verificaw(w);
            if(sinalerrow==1){
            ptos-=5;
            erro+=1;
            }
            else{
            kverificaposi=verificposi(w1,w2,sdk[0][0],sdk[0][1],sdk[0][2],sdk[0][3],sdk[0][4],sdk[1][0],sdk[1][1],sdk[1][2],sdk[1][3],sdk[1][4],sdk[2][0],sdk[2][1],sdk[2][2],sdk[2][3],sdk[2][4],sdk[3][0],sdk[3][1],sdk[3][2],sdk[3][3],sdk[3][4],sdk[4][0],sdk[4][1],sdk[4][2],sdk[4][3],sdk[4][4]);
            if(kverificaposi!=0){
            erro+=1;
            sinalerrow=2;
            ptos-=5;
            }
            else{
            printf("\n\t\t   Digite um numero inteiro \n\t\t   a ser inserido:");/*a posi��o est� validada*/
            scanf("%d",&w3);
            fflush(stdin);
            if(w3>0){
            if(w3<6){
                sdk[w1][w2]=w3;
                if(verificaErro(sdk[0][0],sdk[0][1],sdk[0][2],sdk[0][3],sdk[0][4],sdk[1][0],sdk[1][1],sdk[1][2],sdk[1][3],sdk[1][4],sdk[2][0],sdk[2][1],sdk[2][2],sdk[2][3],sdk[2][4],sdk[3][0],sdk[3][1],sdk[3][2],sdk[3][3],sdk[3][4],sdk[4][0],sdk[4][1],sdk[4][2],sdk[4][3],sdk[4][4])==0){
                }
                else{
                erro+=1;
                sdk[w1][w2]=0;
                ptos-=5;
                m=1;
                system("cls");/*para apagar a tela a cada ciclo*/
                telainicial(erro,ptos,recorde,sdk[0][0],sdk[0][1],sdk[0][2],sdk[0][3],sdk[0][4],sdk[1][0],sdk[1][1],sdk[1][2],sdk[1][3],sdk[1][4],sdk[2][0],sdk[2][1],sdk[2][2],sdk[2][3],sdk[2][4],sdk[3][0],sdk[3][1],sdk[3][2],sdk[3][3],sdk[3][4],sdk[4][0],sdk[4][1],sdk[4][2],sdk[4][3],sdk[4][4]);
                printf("\n\t\t   Voc� errou conforme a regra do sudoku");
                }
            }
            else{/*se w3>6, capture o erro porque o valor est� fora do escopo*/
                erro+=1;
                ptos-=5;
                m=2;
            }
            }
            if(w3<0){
            if(verificjogada(w1,w2,sdk[0][0],sdk[0][1],sdk[0][2],sdk[0][3],sdk[0][4],sdk[1][0],sdk[1][1],sdk[1][2],sdk[1][3],sdk[1][4],sdk[2][0],sdk[2][1],sdk[2][2],sdk[2][3],sdk[2][4],sdk[3][0],sdk[3][1],sdk[3][2],sdk[3][3],sdk[3][4],sdk[4][0],sdk[4][1],sdk[4][2],sdk[4][3],sdk[4][4])==0){
                sdk[w1][w2]=0;
                ptos-=5;
                erro+=1;
                m=3;
            }
            else{
                sdk[w1][w2]=88;
            }
            }
            system("cls");
            telainicial(erro,ptos,recorde,sdk[0][0],sdk[0][1],sdk[0][2],sdk[0][3],sdk[0][4],sdk[1][0],sdk[1][1],sdk[1][2],sdk[1][3],sdk[1][4],sdk[2][0],sdk[2][1],sdk[2][2],sdk[2][3],sdk[2][4],sdk[3][0],sdk[3][1],sdk[3][2],sdk[3][3],sdk[3][4],sdk[4][0],sdk[4][1],sdk[4][2],sdk[4][3],sdk[4][4]);
            kverificafim=verificafim(erro,sdk[0][0],sdk[0][1],sdk[0][2],sdk[0][3],sdk[0][4],sdk[1][0],sdk[1][1],sdk[1][2],sdk[1][3],sdk[1][4],sdk[2][0],sdk[2][1],sdk[2][2],sdk[2][3],sdk[2][4],sdk[3][0],sdk[3][1],sdk[3][2],sdk[3][3],sdk[3][4],sdk[4][0],sdk[4][1],sdk[4][2],sdk[4][3],sdk[4][4]);
            if(kverificafim!=1){
            switch(m){
                case 0:break;
                case 1:printf("\n\t\t   Voc� errou conforme a regra do sudoku!");break;
                case 2:printf("\n\t\t   Voc� digitou um n�mero fora do escopo!");break;
                case 3:printf("\n\t\t   Voc� errou a jogada!");break;
            }
            printf("\n\t\t   Voce gostaria de uma jogada auxiliar(s/n)?");
            scanf("%c",&c);
            fflush(stdin);
            /*Antes de acionar a jogada inteligente,verifica-se se j� h� END GAME*/
            if(c =='s' || c =='S'){/*jogada aleat�ria em posi��o dispon�vel condicionada ao desejo do jogador*/
            ptos-=2;/*desconta uma pontua��o*/
            int z=1;
            do{/* sorteia posi��es at� que seja poss�vel efetuar uma jogada,pressup�e-se que h� posi��es livres */
                do{/*sorteio de posi��o at� encontrar posi��o aleat�ria*/
                zx=rand()%5;zy=rand()%5;
                kverificaposi=verificposi(zx,zy,sdk[0][0],sdk[0][1],sdk[0][2],sdk[0][3],sdk[0][4],sdk[1][0],sdk[1][1],sdk[1][2],sdk[1][3],sdk[1][4],sdk[2][0],sdk[2][1],sdk[2][2],sdk[2][3],sdk[2][4],sdk[3][0],sdk[3][1],sdk[3][2],sdk[3][3],sdk[3][4],sdk[4][0],sdk[4][1],sdk[4][2],sdk[4][3],sdk[4][4]);
                }while(kverificaposi!=0);
                int i=0;
                do{/* redescri��o do estado */
                    int j=0;
                    do{/*verifiica se h� posi��o jog�vel conforme as regras de sudoku*/
                        if(verificposi(i,j,sdk[0][0],sdk[0][1],sdk[0][2],sdk[0][3],sdk[0][4],sdk[1][0],sdk[1][1],sdk[1][2],sdk[1][3],sdk[1][4],sdk[2][0],sdk[2][1],sdk[2][2],sdk[2][3],sdk[2][4],sdk[3][0],sdk[3][1],sdk[3][2],sdk[3][3],sdk[3][4],sdk[4][0],sdk[4][1],sdk[4][2],sdk[4][3],sdk[4][4])==0){
                            if(verificjogada(i,j,sdk[0][0],sdk[0][1],sdk[0][2],sdk[0][3],sdk[0][4],sdk[1][0],sdk[1][1],sdk[1][2],sdk[1][3],sdk[1][4],sdk[2][0],sdk[2][1],sdk[2][2],sdk[2][3],sdk[2][4],sdk[3][0],sdk[3][1],sdk[3][2],sdk[3][3],sdk[3][4],sdk[4][0],sdk[4][1],sdk[4][2],sdk[4][3],sdk[4][4])==0){
                            /*se o retorno das duas verifica��es � nulo,isto � ,a posi��o (i,j) est� dispon�vel
                            E uma jogada ,conforme as regras do sudoku ,� realiz�vel nela*/
                                estado=0;
                            }
                        }
                        j++;
                    }while(estado!=0 && j<=4);
                i++;
                }while(i<=4 && estado!=0);
                switch (estado){/*avalia se h� posi��es transform�veis conforme as regras do sudoku*/
                    case 0:{/* � poss�vel montar uma jogada inteligente conforme as regras do sudoku em alguma posi��o*/
                        int kverificjogada = verificjogada(zx,zy,sdk[0][0],sdk[0][1],sdk[0][2],sdk[0][3],sdk[0][4],sdk[1][0],sdk[1][1],sdk[1][2],sdk[1][3],sdk[1][4],sdk[2][0],sdk[2][1],sdk[2][2],sdk[2][3],sdk[2][4],sdk[3][0],sdk[3][1],sdk[3][2],sdk[3][3],sdk[3][4],sdk[4][0],sdk[4][1],sdk[4][2],sdk[4][3],sdk[4][4]);
                        /* a fun��o acima verifica se h� jogada  realiz�vel nessa posi��o sem implicar erro */
                        if (kverificjogada ==0){
                            for (z=1;z==1;){
                                sdk[zx][zy]= 1+rand()%5;
                                kverificaErro=verificaErro(sdk[0][0],sdk[0][1],sdk[0][2],sdk[0][3],sdk[0][4],sdk[1][0],sdk[1][1],sdk[1][2],sdk[1][3],sdk[1][4],sdk[2][0],sdk[2][1],sdk[2][2],sdk[2][3],sdk[2][4],sdk[3][0],sdk[3][1],sdk[3][2],sdk[3][3],sdk[3][4],sdk[4][0],sdk[4][1],sdk[4][2],sdk[4][3],sdk[4][4]);
                                if(kverificaErro == 0){
                                    z=0;
                                }
                            }
                        }
                    } break;
                    case 1:{/* � imposs�vel montar uma jogada conforme as regras do sudoku em qualquer posi��o dispon�vel */
                        int kverificposi = verificposi(zx,zy,sdk[0][0],sdk[0][1],sdk[0][2],sdk[0][3],sdk[0][4],sdk[1][0],sdk[1][1],sdk[1][2],sdk[1][3],sdk[1][4],sdk[2][0],sdk[2][1],sdk[2][2],sdk[2][3],sdk[2][4],sdk[3][0],sdk[3][1],sdk[3][2],sdk[3][3],sdk[3][4],sdk[4][0],sdk[4][1],sdk[4][2],sdk[4][3],sdk[4][4]);
                        /* a fun��o acima verifica se a posi��o est� dispon�vel*/
                        if (kverificposi ==0){/*se  a posi��o for dispon�vel , ela dever� ser preenchida com X*/
                            sdk[zx][zy]= 88;
                            z=0;
                        }
                    }break;
                }
            }while(z!=0);
            }
            }
            }
            }
            }
        }while(erro<=5 && kverificafim==0);
        system("cls");
        kverificaLacunas=verificaLacunas(sdk[0][0],sdk[0][1],sdk[0][2],sdk[0][3],sdk[0][4],sdk[1][0],sdk[1][1],sdk[1][2],sdk[1][3],sdk[1][4],sdk[2][0],sdk[2][1],sdk[2][2],sdk[2][3],sdk[2][4],sdk[3][0],sdk[3][1],sdk[3][2],sdk[3][3],sdk[3][4],sdk[4][0],sdk[4][1],sdk[4][2],sdk[4][3],sdk[4][4]);
        ptos-=(10*kverificaLacunas);
        if (ptos<0){/* � inconceb�vel pontua��o negativa*/
            ptos=0;
        }
        if(ptos>recorde){
            recorde=ptos;
            krecorde=1;
            }
        else{
            if(N==1){/*a primeira partida sempre � recorde!*/
                krecorde=1;
            }
        }
        telafinal(erro,ptos,recorde,krecorde);
        printf("\n\n\t\t Voc� gostaria de jogar novamente(s/n)?");
        scanf("%c",&c);
        fflush(stdin);
        }while(c=='s' || c=='S');
return 0;
system("pause");
}
