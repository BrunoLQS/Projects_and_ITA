/* Copyright by BRUNO LIMA QUEIROZ SANTOS  */
/* Turma 3                                 */
/* Lab 04: Mini SGBD                       */
/* Programa compilado com CodeBlocks 17.12 */
#include <stdio.h>//biblioteca para usar os sistemas de input e output
#include <stdlib.h>//biblioteca para apagar a tela esporadicamente (system("cls");)
#include <windows.h>//biblioteca para o gotoxy
#include <locale.h>//biblioteca para a grafia(setlocale)
#include <string.h>//biblioteca para auxiliar o uso das strings

char resposta=0,respostaexit=0,respostareturn=0;
char buffer[100],aux[100],teclado[12][100];
char busca[21];
int parametro=0,parametroexit=0,error=0,parametroreturn=0,salary=0,number=0,option=0,egress=0,screen=0,max=0,NUM=0;
typedef struct empregado colaborador;

struct endereco//struct para um endere�o.
{
    char rua[16];
    int numero;
    char cidade[21];
    char cep[10];
};
struct empregado//ficha de um empregado:typdef struct empregado colaborador;
{
    char nomecompleto[21];
    char rg[11];
    char cargo[16];
    float salario;
    char natalidade[7];
    struct endereco endereco;
};
colaborador employee[100],help;/*declara��es globais*/
int maior(int x1, int x2)/*fun��o para compar dois inteiros*/
{
    if (x1>=x2)
        return x1;
    else
        return x2;

}
void grafia()//fun��o para liberar a acentua��o ortogr�fica.
{
    setlocale(LC_ALL,"Portuguese");
}
void desgrafia()//fun��o para desliberar a acentua��o ortogr�fica.
{
    setlocale(LC_ALL,"C");//Restaurando o padr�o C
}
//fun��o gotoxy � usada para levar o cursor a uma determinada coordenada da tela.
void gotoxy(int x, int y)//fun��o gotoxy, x � a coordenada da coluna,da esquerda � direita, y � a coordenada da linha de cima a baixo
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}
//para a moldura,margeamento [11,67;10,35+y] ( x varia de 11 a 67; y varia de 10 a 35+y)
void moldura(int y)//moldura constru�da por meio da tabela ASC II estendida  usando-se o caractere 220 na margem horizontal.
{
    //margeamento horizontal foi feita com o caractere 220 da tabela ASC II estendida
    {// margeamento horizontal , com espa�amento vertical de (26+y)linhas
        for (int x1=1;x1<=78;x1++)//moldura horizontal  ao longo da (10+y)� linha
        {
            gotoxy(x1,10);
            printf("%c",220);
        }
        for (int x2=1;x2<=78;x2++)//moldura horizontal inferior  ao longo da (35+y)� linha
        {
            gotoxy(x2,(35+y));
            printf("%c",220);
        }
    }
    //margeamento vertical foi feito usando o caractere 219 na tabela ASC II estendida
    {// margeamento vertical, com espa�amento horizontal de 57 colunas
        for (int y1=11;y1<=(35+y);y1++)//moldura vertical � esquerda [(25+y)espa�amentos] ao longo da 11� coluna
        {
            gotoxy(1,y1);
            printf("%c",219);
        }
        for(int y2=11;y2<=(35+y);y2++)//moldura vertical � direita [(25+y) espa�amentos] ao longo da 67� coluna
        {
            gotoxy(78,y2);
            printf("%c",219);
        }
    }
    /*as posi��es iniciais para inserir os caracteres n�o s�o coincidentes porque eles n�o s�o iguais, em um margeamento usou-se
    220 e em outro usou-se 219*/
    {//Rodap� creditador
        gotoxy(13,(37+y));
        printf("Mini SGBD produzido por BrunoLimaQueirozSantos");
    }
}
void deletemoldura(int y)//apagar moldura
{
    {//apagar margem horizontal
        for (int x1=11;x1<=67;x1++)//apagar margem horizontal superior [57 espa�amentos] ao longo da (10+y)� linha
        {
            gotoxy(x1,10);
            printf(" ");
        }
        for (int x2=11;x2<=67;x2++)//apagar margem horizontal inferior [57 espa�amentos] ao longo da (35+y)� linha
        {
            gotoxy(x2,(35+y));
            printf(" ");
        }
    }
    //deletar margeamento vertical foi feito usando o caractere 219 na tabela ASC II estendida
    {// deletar margeamento vertical, com espa�amento horizontal de 57 colunas
        for (int y1=11;y1<=(35+y);y1++)//apagar moldura vertical � esquerda
        {
            gotoxy(11,y1);
            printf(" ");
        }
        for(int y2=11;y2<=(35+y);y2++)//apagar margem vertical � direita
        {
            gotoxy(67,y2);
            printf(" ");
        }
    }
    {// apagar o Rodap� creditador
        gotoxy(13,(37+y));
        printf("                                               ");
    }
}
void space(int y)//fun��o para dar espa�amento entre o excerto final e a impress�o acima dele.
{
    gotoxy(0,40+y);
}
void organizarbuffer()//fun��o para retirar o espa�amento capturado inconvenientemente no in�cio
{
    for(int i=0;i<strlen(buffer);i++)
    {
        buffer[i]=buffer[i+1];
    }
}
void rebuffer()//fun��o para reorganizar o buffer
{
    int tamanho;
    organizarbuffer();/*retirando o caractere na posi��o 0*/
    tamanho=strlen(buffer);
    tamanho-=1;/*a posi��o come�a do zero*/
    buffer[tamanho]='\0';/*retirando o \n ao final da string*/
}
void apagar(int x1,int x2,int y)//fun��o para apagar  faixa de linha da tela.
{
    gotoxy(x1,y);
    for(int i=x1;i<=x2;i++)
        printf(" ");
}
void verificaresposta(int x, int y)//fun��o para capturar uma resposta e verific�-la,baseado no par�metro.
{
    parametro=0;
    do//do-while pr� resposta inv�lida � pergunta
    {
        if(parametro==1)//solicita��o de nova resposta
        {
            gotoxy(13,13);
            grafia();
            printf("Voc� digitou uma resposta inv�lida! digite novamente.");
            desgrafia();
        }
        gotoxy(x,y);//cursor ao lado da pergunta pr�-resposta
        fflush(stdin);
        scanf("%c",&resposta);
        switch(resposta)
        {
            case 's': parametro=0;break;
            case 'S': parametro=0;break;
            case 'N': parametro=0;break;
            case 'n': parametro=0;break;
            default : parametro=1; break;
        }
        if(parametro==1)
            apagar(x,(x),y);
        else//Apagar subt�tulo
            apagar(13,65,13);
    }while(parametro!=0);
    gotoxy(x,y);//encerrar fun��o posicionando o cursor adequadamente.
}
void verificarespostaexit(int x, int y)//fun��o para capturar uma resposta de sa�da  e verific�-la,baseado no parametroexit.
{
    parametroexit=0;
    do//do-while pr� resposta inv�lida � pergunta
    {
        if(parametroexit==1)//solicita��o de nova resposta
        {
            gotoxy(13,13);
            grafia();
            printf("Voc� digitou uma resposta inv�lida! digite novamente.");
            desgrafia();
        }
        gotoxy(x,y);//cursor ao lado da pergunta pr�-resposta
        fflush(stdin);
        scanf("%c",&respostaexit);
        switch(respostaexit)
        {
            case 's': parametroexit=0,egress=1;break;
            case 'S': parametroexit=0,egress=1;break;
            case 'N': parametroexit=0,egress=0,screen=0;break;
            case 'n': parametroexit=0,egress=0,screen=0;break;
            default:  parametroexit=1; break;
        }
        if(parametroexit==1)
            apagar(x,x,y);
        else//Apagar subt�tulo
            apagar(13,65,13);
    }while(parametroexit!=0);
    gotoxy(x,y);//encerrar fun��o posicionando o cursor adequadamente.
}
void perguntafinal(int x , int y)//fun��o para imprimir op��o de sair do programa ou de retornar � tela inicial
{
    gotoxy(x,y);
    grafia();
    printf("Voc� gostaria de sair do programa(s/n)?");//para posicionar o cursor adiante,x->(x+39) & y->y
    desgrafia();
    gotoxy(x,(y+1));
    grafia();
    printf("Sen�o, voltar � tela inicial.");
    desgrafia();
}
void tostruct()//para atribuir a struct
{
    FILE *arquivoLeitura=fopen("minisgbd.txt","r");
    int i=0;
    while(feof(arquivoLeitura)==0&&i<100)
    {//armazenar fichas do file na struct
        fscanf(arquivoLeitura,"%s",buffer);
        if(strcmp(buffer,"1.Nome")==0)
        {
            max=i;
            fscanf(arquivoLeitura,"%s",buffer);/*capture Completo: para o buffer*/
            fgets(buffer,23,arquivoLeitura);/*foi capturado o \n
            no final e o espa�amento inicial porque o fgets n�o os ignora.*/
            rebuffer();
            strcpy(employee[i].nomecompleto,buffer);/*armazenando no struct*/
            fscanf(arquivoLeitura,"%s",buffer);/*capture 2.RG:*/
            fgets(buffer,13,arquivoLeitura);/*capture o RG com espa�amento inicial e o \n*/
            rebuffer();
            strcpy(employee[i].rg,buffer);
            fscanf(arquivoLeitura,"%s",buffer);/*capture 3.Fun��o:*/
            fgets(buffer,18,arquivoLeitura);/*capture a fun��o com o espa�amento inicial e o \n*/
            rebuffer();
            strcpy(employee[i].cargo,buffer);
            fscanf(arquivoLeitura,"%s",buffer);/*capture 4.Sal�rio:*/
            fscanf(arquivoLeitura,"%f",&employee[i].salario);/*capture o valor do sal�rio*/
            fgets(buffer,3,arquivoLeitura);/*capture \n**/
            fgets(buffer,22,arquivoLeitura);/*capture 5.Data de Nascimento:*/
            fgets(buffer,9,arquivoLeitura);/* capture a data de nascimento com o espa�amento inicial e o \n*/
            rebuffer();
            strcpy(employee[i].natalidade,buffer);
            fgets(buffer,13,arquivoLeitura);/*capture 6.Endere�o: e \n*/
            fscanf(arquivoLeitura,"%s",buffer);/*capture a.rua:*/
            fgets(buffer,18,arquivoLeitura);/*capture a rua com o espa�amento inicial e o \n*/
            rebuffer();
            strcpy(employee[i].endereco.rua,buffer);
            fscanf(arquivoLeitura,"%s",buffer);/*capture b.N�mero:*/
            fscanf(arquivoLeitura,"%d",&employee[i].endereco.numero);/*capture atribuindo o n�mero*/
            fscanf(arquivoLeitura,"%s",buffer);/*capture c.Cidade:*/
            fgets(buffer,23,arquivoLeitura);
            rebuffer();
            strcpy(employee[i].endereco.cidade,buffer);
            fscanf(arquivoLeitura,"%s",buffer);/*capture d.CEP:*/
            fgets(buffer,12,arquivoLeitura);
            rebuffer();
            strcpy(employee[i].endereco.cep,buffer);
            i++;
        }
    }
    fclose(arquivoLeitura);
}
void restruct(int y)//para rearranjar as structs
{
    help=employee[y];
    employee[y]=employee[y+1];
    employee[y+1]=help;
}
void telainicial()//ir� imprimir a tela inicial.
{
    int i=0;
    FILE *arquivoEntrada=fopen("miniSGBD.txt","a");
    fclose(arquivoEntrada);//� preciso gerar o arquivo imediatamente .
    do
    {//la�o perdurado enquanto o usu�rio digita incorretamente
        //lembre-se que o margeamento � [11,67;10,35]
        system("cls");
        moldura(0);
        if((screen<1||screen>4)&&i!=0)
        {
            gotoxy(15,14);
            grafia();
            printf("Voc� digitou uma op��o inv�lida! digite novamente.");
            desgrafia();
            }
        if(error==1)
        {
            gotoxy(15,14);
            grafia();
            printf("A capacidade m�xima foi atingida!digite novamente.");
        }
        {//imprimindo o bem-vindo ao Mini SGBD
            gotoxy(29,12);
            printf("Bem-vindo ao Mini SGBD");
        }
        {  //descri��o das op��es, bem como do t�tulo de op��es
            grafia();
            gotoxy(15,16);
            printf("Escolha sua Op��o:");
            gotoxy(15,18);
            printf("1-para cadastrar novo funcion�rio");
            gotoxy(15,20);
            printf("2-consulta simples");
            gotoxy(15,22);
            printf("3-consulta avan�ada");
            gotoxy(15,24);
            printf("4-sair");
            desgrafia();
        }
        {  //capturando a op��o
            gotoxy(33,16);
            fflush(stdin);
            scanf("%d",&screen);
            if(screen==1)
            {
                tostruct();
                if(max==99)
                    error=1;
            }
            else
                error=0;
        }
        i++;
    }while((screen<1||screen>4||error==1));
}
void teladecadastro()//processo na tela de cadastro; tela 1;(2� tela)
{
    colaborador pessoa;//declarando uma struct do tipo colaborador; para admnistr�-la s� precisa referenciar pessoa
    /*declarando uma struct , todos os outros tipos de struct e union dentro do escopo dela s�o declarados simultaneamente*/
    FILE *arqRegistro;
    arqRegistro=fopen("minisgbd.txt","a");//este fopen � para apendar o arquivo.
    {//atribui��o autom�tica de endere�o
        strcpy(pessoa.endereco.rua,"H8,Pc.Mar.Ed.G.");//a atribui��o direta s� pode ser feita na declara��o da matriz.ent�o,usou-se a fun��o para n�o declarar elemento a elemento.
        pessoa.endereco.numero=50;
        strcpy(pessoa.endereco.cidade,"Sao Jose dos Campos");
        strcpy(pessoa.endereco.cep,"12228-900");
    }
    system("cls");
    moldura(0);
    {//t�tulo da tela.
        gotoxy(29,12);
        printf("Tela de Cadastro");
    }
    {//exibi�ao de itens preenchimento imediata.
        gotoxy(13,14);
        printf("Nome completo:");
        gotoxy(13,15);
        printf("RG:");
        gotoxy(13,16);
        grafia();
        printf("Fun��o:");
        desgrafia();
        gotoxy(15,17);
        printf("a.Analista");
        gotoxy(15,18);
        printf("b.Gerente");
        gotoxy(15,19);
        printf("c.Arquiteto");
        gotoxy(15,20);
        printf("d.Programador");
        gotoxy(15,21);
        printf("e.Testador");
        gotoxy(15,22);
        printf("f.Suporte");
        gotoxy(13,23);
        grafia();
        printf("Sal�rio:");
        desgrafia();
        gotoxy(13,24);
        printf("Data de Nascimento(DDMMAA):");
        gotoxy(13,25);
        grafia();
        printf("Voc� deseja utilizar o endere�o padr�o(s/n)?");
        desgrafia();
    }
    {//exibi��o dos dados de endere�o.
        gotoxy(13,26);
        grafia();
        printf("Endere�o:");
        desgrafia();
        gotoxy(15,27);
        printf("a.Rua:");
        gotoxy(15,28);
        grafia();
        printf("b.N�mero:");
        desgrafia();
        gotoxy(15,29);
        printf("c.Cidade:");
        gotoxy(15,30);
        printf("d.CEP:");
    }
    perguntafinal(13,32);
    {//exibi��o do padr�o do endere�o.
        gotoxy(21,27);
        grafia();
        printf("H8,Pc.Mar.Edu.Gomes");
        desgrafia();
        gotoxy(24,28);
        printf("50");
        gotoxy(24,29);
        grafia();
        printf("Sao Jose dos Campos");
        desgrafia();
        gotoxy(21,30);
        printf("12228-900");
    }
    {//cursor para o preenchimento de dados at� a pergunta sobre o endere�o padr�o ou n�o.
        gotoxy(27,14);
        fflush(stdin);
        gets(pessoa.nomecompleto);
        gotoxy(16,15);
        fflush(stdin);
        gets(pessoa.rg);
        gotoxy(20,16);
        fflush(stdin);
        gets(pessoa.cargo);
        gotoxy(21,23);
        fflush(stdin);
        scanf("%f",&pessoa.salario);
        gotoxy(40,24);
        fflush(stdin);
        gets(pessoa.natalidade);
        gotoxy(25,25);
        verificaresposta(57,25);
    }
    if(resposta=='n'||resposta=='N')
    {//cadastro n�o padr�o pelo usu�rio
        {//limpando os campos do endere�o padr�o para o preenchimento pelo usu�rio
            gotoxy(21,27);
            apagar(21,52,27);
            gotoxy(24,28);
            apagar(24,26,28);
            gotoxy(24,29);
            apagar(24,43,29);
            gotoxy(21,30);
            apagar(21,30,30);
        }
        {//cursor para o cadastro de endere�o pelo pr�prio usu�rio
            gotoxy(21,27);
            fflush(stdin);
            gets(pessoa.endereco.rua);
            gotoxy(24,28);
            fflush(stdin);
            scanf("%d",&pessoa.endereco.numero);
            gotoxy(24,29);
            fflush(stdin);
            gets(pessoa.endereco.cidade);
            gotoxy(21,30);
            fflush(stdin);
            gets(pessoa.endereco.cep);
        }
    }
    {//confirma��o dos dados cadastrais pelo usu�rio
        gotoxy(13,31);
        grafia();
        printf("Voc� confirma as informa��es digitadas acima (s/n)?");
        desgrafia();
        verificaresposta(64,31);
    }
    if(resposta=='s'||resposta=='S')
    {//armazenamento dos dados
        fprintf(arqRegistro,"*************************************************\n");
        fprintf(arqRegistro,"1.Nome Completo: %s\n",pessoa.nomecompleto);
        fprintf(arqRegistro,"2.RG: %s\n",pessoa.rg);
        fprintf(arqRegistro,"3.Fun��o: %s\n",pessoa.cargo);
        fprintf(arqRegistro,"4.Sal�rio: %f\n",pessoa.salario);
        fprintf(arqRegistro,"5.Data de Nascimento: %s\n",pessoa.natalidade);
        fprintf(arqRegistro,"6.Endere�o: \na.rua: %s\n",pessoa.endereco.rua);
        fprintf(arqRegistro,"b.N�mero: %d\n",pessoa.endereco.numero);
        fprintf(arqRegistro,"c.Cidade: %s\n",pessoa.endereco.cidade);
        fprintf(arqRegistro,"d.CEP: %s\n",pessoa.endereco.cep);
        fprintf(arqRegistro,"*************************************************\n");
    }
    {//resposta do usu�rio se gostaria de sair
        verificarespostaexit(52,32);
    }
    fclose(arqRegistro);//encerrando o arquivo para que as atribui��es persistam no arquivo.
}
void resultsimples1()//tela de resultados para a op��o 1 de consulta simpes
{
    FILE *arquivoLeitura,*arquivoConsultas;
    arquivoLeitura=fopen("minisgbd.txt","r");
    arquivoConsultas=fopen("consultas.txt","a");
    int tamanho=0;
    system("cls");
    moldura(0);
    {//imprimindo o t�tulo da tela
        gotoxy(23,12);
        printf("Resultados para a Consulta Simples");
    }
    {//imprimindo o requerimento da tela
        gotoxy(15,14);
        printf("Nome:");
        fflush(stdin);
        gets(busca);
    }
    fprintf(arquivoConsultas,"***********************************************\n");
    fprintf(arquivoConsultas,"Consulta Simples,op��o 1, Nome: %s\n",busca);//registrando no arquivo consultas
    tamanho=strlen(busca);//tamanho da string DIGITADA PELO USU�RIO (o \n n�o foi capturado no final, e sim substitu�do por '\0')
    int i=0,j=15,k=21;
    while(feof(arquivoLeitura)==0&&i<100)
    {
        fscanf(arquivoLeitura,"%s",buffer);
        if(strcmp(buffer,"1.Nome")==0)//capture o excerto inicial,quando ele corresponder � ep�grafe da busca
        {
            fscanf(arquivoLeitura,"%s",buffer);//capture o segundo excerto
            fgets(buffer,22,arquivoLeitura);//finalmente , capture o nome para o buffer considerando os espa�os(o BUFFER CAPTUROU UM ESPA�AMENTO INICIAL INCONVENIENTE)
            organizarbuffer();
            strcpy(aux,buffer);
            aux[tamanho]='\0';//corte a string na posi��o adequada para compar�-la com a busca
            if(strcmpi(busca,aux)==0)//compara��o indiferenciando mai�sculas de min�sculas
            {
                gotoxy(15,j);
                printf("%s\n",buffer);//printe na tela
                fprintf(arquivoConsultas,"%s",buffer);//registre no arquivo consultas
                j++;//incremento por resultado encontrado
            }
            i++;
            if((i+4)>k)//se a quantidade de nomes for grande
            {//apague a moldura e estenda-a reconstruindo-a
                deletemoldura((k-21));
                moldura((k-20));
                k++;
            }
        }
    }
    if(j==15)
    {//armazenar e imprimir que n�o h� registros
        gotoxy(15,15);
        printf("N�o h� registros");
        fprintf(arquivoConsultas,"N�o h� registros\n");
    }
    fprintf(arquivoConsultas,"***********************************************\n");
    fclose(arquivoLeitura);
    fclose(arquivoConsultas);
    perguntafinal(15,j+2);
    verificarespostaexit(54,j+2);
}
void resultsimples2()//tela de resultados para a op�ao 2 de consulta simples
{
    FILE *arquivoLeitura,*arquivoConsultas;
        arquivoLeitura=fopen("minisgbd.txt","r");
        arquivoConsultas=fopen("consultas.txt","a");
        int tamanho=0;
        system("cls");
        moldura(0);
        {//imprimindo o t�tulo da tela
            gotoxy(23,12);
            printf("Resultados para a Consulta Simples");
        }
        {//imprimindo o requerimento da tela
            gotoxy(15,14);
            printf("RG:");
            fflush(stdin);
            gets(busca);
        }
        fprintf(arquivoConsultas,"***********************************************\n");
        fprintf(arquivoConsultas,"Consulta Simples,op��o 2, RG: %s\n",busca);//registrando no arquivo consultas
        tamanho=strlen(busca);//tamanho da string DIGITADA PELO USU�RIO (o \n n�o foi capturado no final, e sim substitu�do por '\0')
        int i=0,j=15,k=21;
        while(feof(arquivoLeitura)==0&&i<100)
        {
            fscanf(arquivoLeitura,"%s",buffer);
            if(strcmp(buffer,"2.RG:")==0)//capture o excerto inicial,quando ele corresponder � ep�grafe da busca
            {
                fgets(buffer,12,arquivoLeitura);//finalmente , capture o RG para o buffer considerando os espa�os(o BUFFER CAPTUROU UM ESPA�AMENTO INICIAL INCONVENIENTE)
                organizarbuffer();
                strcpy(aux,buffer);
                aux[tamanho]='\0';//corte a string na posi��o adequada para compar�-la com a busca
                if(strcmp(busca,aux)==0)//compara��o indiferenciando mai�sculas de min�sculas
                {
                    gotoxy(15,j);
                    printf("%s\n",buffer);//printe na tela
                    fprintf(arquivoConsultas,"%s\n",buffer);//registre no arquivo consultas
                    j++;
                }
                i++;
                if((i+4)>k)//se a quantidade de nomes for grande
                {//apague a moldura e estenda-a reconstruindo-a
                    deletemoldura((k-21));
                    moldura((k-20));
                    k++;
                }
            }
        }
        if(j==15)
        {
            gotoxy(15,15);
            printf("N�o h� registros");
            fprintf(arquivoConsultas,"N�o h� registros\n");
        }
    fprintf(arquivoConsultas,"***********************************************\n");
    fclose(arquivoLeitura);
    fclose(arquivoConsultas);
    perguntafinal(15,j+2);
    verificarespostaexit(54,j+2);
}
void resultsimples3()//tela de resultados para a op�ao 3 de consulta simples
{
    FILE *arquivoLeitura,*arquivoConsultas;
        arquivoLeitura=fopen("minisgbd.txt","r");
        arquivoConsultas=fopen("consultas.txt","a");
        int tamanho=0;
        system("cls");
        moldura(0);
        {//imprimindo o t�tulo da tela
            gotoxy(23,12);
            printf("Resultados para a Consulta Simples");
        }
        {//imprimindo o requerimento da tela
            gotoxy(15,14);
            grafia();
            printf("Fun��o:");
            desgrafia();
            fflush(stdin);
            gets(busca);
        }
        fprintf(arquivoConsultas,"***********************************************\n");
        fprintf(arquivoConsultas,"Consulta Simples,op��o 3, Fun��o: %s\n",busca);//registrando no arquivo consultas
        tamanho=strlen(busca);//tamanho da string DIGITADA PELO USU�RIO (o \n n�o foi capturado no final, e sim substitu�do por '\0')
        int i=0,j=15,k=21;
        while(feof(arquivoLeitura)==0&&i<100)
        {
            fscanf(arquivoLeitura,"%s",buffer);//fscanf despreza \n's e espa�os
            if(strcmp(buffer,"3.Fun��o:")==0)//capture o excerto inicial,quando ele corresponder � ep�grafe da busca
            {
                fscanf(arquivoLeitura,"%s",buffer);//capture logo a fun��o desprezando os espa�os
                strcpy(aux,buffer);
                aux[tamanho]='\0';//corte a string na posi��o adequada para compar�-la com a busca
                if(strcmp(busca,aux)==0)//compara��o indiferenciando mai�sculas de min�sculas
                {
                    gotoxy(15,j);
                    printf("%s\n",buffer);//printe na tela
                    fprintf(arquivoConsultas,"%s\n",buffer);//registre no arquivo consultas
                    j++;
                }
                i++;
                if((i+4)>k)//se a quantidade de nomes for grande
                {//apague a moldura e estenda-a reconstruindo-a
                    deletemoldura((k-21));
                    moldura((k-20));
                    k++;
                }
            }
        }
        if(j==15)
        {//armazenar e imprimir que n�o h� registros
            gotoxy(15,15);
            grafia();
            printf("N�o h� registros\n");
            desgrafia();
            fprintf(arquivoConsultas,"N�o h� registros");
        }
    fprintf(arquivoConsultas,"***********************************************\n");
    fclose(arquivoLeitura);
    fclose(arquivoConsultas);
    perguntafinal(15,j+2);
    verificarespostaexit(54,j+2);
}
void teladeconsultasimples()//processo na tela de consulta simples;tela 2;(3� tela)
{
    int i=0;
    do
    {//la�o perdurado enquanto o usu�rio digita incorretamente
        //lembre-se de que o margeamento � [11,67;10,35]
        system("cls");
        moldura(0);
        if((option<1||option>5)&&i!=0)
        {//informar invalidez
            gotoxy(15,14);
            grafia();
            printf("Voc� digitou uma op��o inv�lida! digite novamente.");
            desgrafia();
        }
        {//imprimindo o t�tulo da tela
            gotoxy(29,12);
            printf("Consulta Simples");
        }
        {//descri��o das op��es, bem como do t�tulo de op��es
            grafia();
            gotoxy(15,16);
            printf("Escolha sua Op��o:");
            gotoxy(15,18);
            printf("1-Nome");
            gotoxy(15,20);
            printf("2-RG");
            gotoxy(15,22);
            grafia();
            printf("3-Fun��o");
            desgrafia();
            gotoxy(15,24);
            printf("4-Sair");
            desgrafia();
            gotoxy(15,26);
            grafia();
            printf("5-Retornar � tela inicial");
            desgrafia();
        }
        {//capturando a op��o
            gotoxy(33,16);
            fflush(stdin);
            scanf("%d",&option);
        }
        i++;
    }while(option<1||option>5);
    switch(option)
    {
        case 1:resultsimples1();break;
        case 2:resultsimples2();break;
        case 3:resultsimples3();break;
        case 4:egress=1;break;
        case 5:screen=0;break;
    }

}
void resultadvanced1()//tela de resultados para a op��o 1 de consuta avan�ada
{
    FILE *arquivoLeitura,*arquivoConsultas;
    arquivoLeitura=fopen("minisgbd.txt","r");
    arquivoConsultas=fopen("consultas.txt","a");
    system("cls");
    moldura(0);
    tostruct();
    {//imprimindo o t�tulo da tela
        gotoxy(18,12);
        grafia();
        printf("Resultado para a Consulta Avan�ada Op��o 1");
        desgrafia();
    }
    int ano1,ano2,mes1,mes2,dia1,dia2;
    for(int x=0,trocou=1;x<99&&trocou==1;x++)//bubbleSort para Structs;
    {
        for(int y=0;y<99;y++)
        {
            trocou=0;
            ano1=(employee[y].natalidade[6]-48)+(employee[y].natalidade[5]-48)*10;
            ano2=(employee[y+1].natalidade[6]-48)+(employee[y+1].natalidade[5]-48)*10;
            mes1=(employee[y].natalidade[4]-48)+(employee[y].natalidade[3]-48)*10;
            mes2=(employee[y+1].natalidade[4]-48)+(employee[y+1].natalidade[3]-48)*10;
            dia1=(employee[y].natalidade[2]-48)+(employee[y].natalidade[1]-48)*10;
            dia2=(employee[y+1].natalidade[2]-48)+(employee[y+1].natalidade[1]-48)*10;
            if((ano1>20&&ano2>20)||(ano1<20&&ano2<20))// Ambos nasceram no mesmo S�C.
            {
                if(ano1>ano2)
                {/*y+1 � mais velho*/
                    restruct(y);
                    trocou=1;
                }
                if(ano1==ano2)
                {/*desempate nos meses*/
                    if(mes1>mes2)
                    {
                        restruct(y);
                        trocou=1;
                    }
                    if(mes1==mes2)
                    {/*desempate nos dias*/
                        if(dia1>dia2)
                        {/*se o y+1 � mais velho que o y*/
                            restruct(y);
                            trocou=1;
                        }
                    }
                }
            }
            else/*nasceram em S�C.s diferentes*/
            {
                if(ano2>ano1)
                {//y+1 � mais velho
                    restruct(y);
                    trocou=1;
                }
            }
        }
    }
    fprintf(arquivoConsultas,"***********************************************\n");
    fprintf(arquivoConsultas,"Consulta Avan�ada,op��o 1\n");
    int k=21,j=15;
    for(int i=0;i<=max;i++)
    {
        fprintf(arquivoConsultas,"%s\n",employee[i].nomecompleto);
        gotoxy(15,j);
        printf("%s",employee[i].nomecompleto);
        if((i+4)>k)//se a quantidade de nomes for grande
        {//apague a moldura e estenda-a reconstruindo-a
            deletemoldura((k-21));
            moldura((k-20));
            k++;
        }
        j++;
    }
        if(j==15)
    {//armazenar e imprimir que n�o h� registros
        gotoxy(15,15);
        grafia();
        printf("N�o h� registros");
        desgrafia();
        fprintf(arquivoConsultas,"N�o h� registros\n");
    }
    fprintf(arquivoConsultas,"***********************************************\n");
    fclose(arquivoLeitura);
    fclose(arquivoConsultas);
    perguntafinal(15,j+2);
    verificarespostaexit(54,j+2);
}
void resultadvanced2()//tela de resultados para a op��o 2 de consulta avan�ada
{
    FILE *arquivoLeitura,*arquivoConsultas;
    arquivoLeitura=fopen("minisgbd.txt","r");
    arquivoConsultas=fopen("consultas.txt","a");
    system("cls");
    moldura(0);
    tostruct();
    {//imprimindo o t�tulo da tela
        gotoxy(18,12);
        grafia();
        printf("Resultados para a Consulta Avan�ada Op��o 2");
        desgrafia();
    }
    float gastos=0;
    for(int i=0;i<=max;i++)
        gastos+=employee[i].salario;
    gotoxy(14,14);
    grafia();
    printf("O gasto total da empresa com os funcion�rios � :");
    desgrafia();
    gotoxy(14,15);
    printf("%f",gastos);
    fprintf(arquivoConsultas,"***********************************************\n");
    fprintf(arquivoConsultas,"Consulta Avan�ada,Op��o 2\n");
    if(max==0)
        fprintf(arquivoConsultas,"O total de gastos mensal com\nos funcion�rios �:%f\n",0.0);
    else
        fprintf(arquivoConsultas,"O total de gastos mensal com\nos funcion�rios �:%f\n",gastos);
    fprintf(arquivoConsultas,"***********************************************\n");
    fclose(arquivoConsultas);
    fclose(arquivoLeitura);
    perguntafinal(15,18);
    verificarespostaexit(54,18);

}
void resultadvanced3()//tela de resultados para a op��o 3 de consulta avan�ada
{
    FILE *arquivoConsultas=fopen("consultas.txt","a");
    system("cls");
    moldura(0);
    tostruct();
    {//imprimindo o t�tulo da tela
        gotoxy(18,12);
        grafia();
        printf("Resultados para a Consulta Avan�ada Op��o 3");
        desgrafia();
    }
    deletemoldura(0);
    int y1=15,y2=15,y3=15,y4=15,y5=15,y6=15;
    {//esqueleto para a tabela
        gotoxy(5,14);
        printf("Analista");
        gotoxy(15,14);
        printf("|");
        gotoxy(17,14);
        printf("Gerente");
        gotoxy(27,14);
        printf("|");
        gotoxy(29,14);
        printf("Arquiteto");
        gotoxy(39,14);
        printf("|");
        gotoxy(41,14);
        printf("Programador");
        gotoxy(53,14);
        printf("|");
        gotoxy(55,14);
        printf("Testador");
        gotoxy(63,14);
        printf("|");
        gotoxy(65,14);
        printf("Suporte");
    }
    for(int i=0;i<=max;i++)
    {/*imprimir na tela a tabela na tela*/
        if(strcmpi(employee[i].cargo,"Analista")==0)
        {//imprimir os nomes correspondentes ao emprego analista
            gotoxy(2,y1);
            for(int j=0;j<10;j++)
            {
                printf("%c",employee[i].nomecompleto[j]);
            }
            gotoxy(2,y1+1);
            for(int j=10;j<16;j++)
            {
                printf("%c",employee[i].nomecompleto[j]);
            }
        }
        if(strcmpi(employee[i].cargo,"Gerente")==0)
        {//imprimir os nomes correspondentes ao emprego gerente
            gotoxy(17,y2);
            for(int j=0;j<10;j++)
            {
                printf("%c",employee[i].nomecompleto[j]);
            }
            gotoxy(17,y2+1);
            for(int j=10;j<16;j++)
            {
                printf("%c",employee[i].nomecompleto[j]);
            }
            y2+=3;
        }
        if(strcmpi(employee[i].cargo,"Arquiteto")==0)
        {//imprimir os nomes correspondentes ao emprego arquiteto
            gotoxy(29,y3);
            for(int j=0;j<10;j++)
            {
                printf("%c",employee[i].nomecompleto[j]);
            }
            gotoxy(29,y3+1);
            for(int j=10;j<16;j++)
            {
                printf("%c",employee[i].nomecompleto[j]);
            }
            y3+=3;
        }
        if(strcmpi(employee[i].cargo,"Programador")==0)
        {//imprimir os nomes correspondentes ao emprego programador
            gotoxy(41,y4);
            for(int j=0;j<10;j++)
            {
                printf("%c",employee[i].nomecompleto[j]);
            }
            gotoxy(41,y4+1);
            for(int j=10;j<16;j++)
            {
                printf("%c",employee[i].nomecompleto[j]);
            }
            y4+=3;
        }
        if(strcmpi(employee[i].cargo,"Testador")==0)
        {//imprimir os nomes correspondentes ao emprego testador
            gotoxy(55,y5);
            for(int j=0;j<10;j++)
            {
                printf("%c",employee[i].nomecompleto[j]);
            }
            gotoxy(55,y5+1);
            for(int j=10;j<16;j++)
            {
                printf("%c",employee[i].nomecompleto[j]);
            }
            y5+=3;
        }
        if(strcmpi(employee[i].cargo,"Suporte")==0)
        {//imprimir os nomes correspondentes ao emprego suporte
            gotoxy(65,y6);
            for(int j=0;j<10;j++)
            {
                printf("%c",employee[i].nomecompleto[j]);
            }
            gotoxy(65,y6+1);
            for(int j=10;j<16;j++)
            {
                printf("%c",employee[i].nomecompleto[j]);
            }
            y6+=3;
        }
    }
    {//observando o maior inteiro dos y's
        y1=maior(y1,y2);
        y1=maior(y1,y3);
        y1=maior(y1,y4);
        y1=maior(y1,y5);
        y1=maior(y1,y6);
    }
    {/*registrando no arquivo Consultas.txt*/
        fprintf(arquivoConsultas,"***********************************************\n");
        fprintf(arquivoConsultas,"Consulta Avan�ada,Op��o 3\n");
        fprintf(arquivoConsultas,"      |Analista|      \n");
        for(int i=0;i<=max;i++)
        {
            if(strcmpi(employee[i].cargo,"Analista")==0)
                fprintf(arquivoConsultas,"%s\n",employee[i].nomecompleto);
        }
        fprintf(arquivoConsultas,"      |Gerente|        \n");
        for(int i=0;i<=max;i++)
        {
            if(strcmpi(employee[i].cargo,"Gerente")==0)
                fprintf(arquivoConsultas,"%s\n",employee[i].nomecompleto);
        }
        fprintf(arquivoConsultas,"     |Arquiteto|      \n");
        for(int i=0;i<=max;i++)
        {
            if(strcmpi(employee[i].cargo,"Arquiteto")==0)
                fprintf(arquivoConsultas,"%s\n",employee[i].nomecompleto);
        }
        fprintf(arquivoConsultas,"     |Programador|    \n");
        for(int i=0;i<=max;i++)
        {
            if(strcmpi(employee[i].cargo,"Programador")==0)
                fprintf(arquivoConsultas,"%s\n",employee[i].nomecompleto);
        }
        fprintf(arquivoConsultas,"     |Testador|      \n");
        for(int i=0;i<=max;i++)
        {
            if(strcmpi(employee[i].cargo,"Testador")==0)
                fprintf(arquivoConsultas,"%s\n",employee[i].nomecompleto);
        }
        fprintf(arquivoConsultas,"     |Suporte|        \n");
        for(int i=0;i<=max;i++)
        {
            if(strcmpi(employee[i].cargo,"Suporte")==0)
                fprintf(arquivoConsultas,"%s\n",employee[i].nomecompleto);
        }
        fprintf(arquivoConsultas,"***********************************************\n");
    }
    fclose(arquivoConsultas);
    /*abaixo,declarou-se o final de tela e a pergunta se deseja voltar ou sair*/
    if (y1>18)
    {
        moldura(y1-18);
        perguntafinal(15,y1);
        verificarespostaexit(54,y1);
    }
    else
    {
        moldura(0);
        perguntafinal(15,18);
        verificarespostaexit(54,18);
    }
}
void resultadvanced4()//tela de resultados para a op��o 4 de consulta avan�ada
{
    FILE *arquivoConsultas=fopen("Consultas.txt","a");
    fprintf(arquivoConsultas,"*************************************************\n");
    fprintf(arquivoConsultas,"Consulta Avan�ada,Op��o 4\n");
    system("cls");
    tostruct();
    moldura(0);
    {//imprimindo o t�tulo da tela
        gotoxy(18,12);
        grafia();
        printf("Resultados para a Consulta Avan�ada Op��o 4");
        desgrafia();
    }
    {//exibi��o dos dados de endere�o.
        gotoxy(13,19);
        grafia();
        printf("Endere�o:");
        desgrafia();
        gotoxy(15,20);
        printf("a.Rua:");
        gotoxy(15,21);
        grafia();
        printf("b.N�mero:");
        desgrafia();
        gotoxy(15,22);
        printf("c.Cidade:");
        gotoxy(15,23);
        printf("d.CEP:");
    }
    perguntafinal(13,25);
    {//cursor para a busca por endere�o pelo pr�prio usu�rio
        gotoxy(21,20);
        fflush(stdin);
        gets(teclado[0]);
        gotoxy(24,21);
        fflush(stdin);
        scanf("%d",&NUM);
        gotoxy(24,22);
        fflush(stdin);
        gets(teclado[1]);
        gotoxy(21,23);
        fflush(stdin);
        gets(teclado[2]);
        fprintf(arquivoConsultas,"Endere�o:%s\n a.Rua:%s\n b.N�mero:%d\n c.Cidade:%s\n d.CEP:%s\n\n",teclado[0],teclado[1],NUM,teclado[2],teclado[3]);
    }
    {/*abaixo, deletou-se a pergunta final*/
        gotoxy(13,25);
        printf("                                       ");
        gotoxy(13,26);
        printf("                             ");
    }
    int z=0;
    for(int i=0;i<=max;i++)
    {
        if(strcmp(employee[i].endereco.rua,teclado[0])==0)
        {
            if(employee[i].endereco.numero==NUM)
            {
                if(strcmp(employee[i].endereco.cidade,teclado[1])==0)
                {
                    if(strcmp(employee[i].endereco.cep,teclado[2])==0)
                    {
                        gotoxy(15,25+z);
                        printf("%s",employee[i].nomecompleto);
                        fprintf(arquivoConsultas,"%s\n",employee[i].nomecompleto);
                        z++;
                        if(z>2)
                        {
                            deletemoldura(z-2);
                            moldura(z-1);
                        }
                    }
                }
            }
        }
    }
    if(z==0)
    {
        gotoxy(15,25);
        grafia();
        printf("N�o h� funcion�rio com o endere�o fornecido");
        desgrafia();
        fprintf(arquivoConsultas,"N�o h� funcion�rio com o endere�o fornecido\n");
    }
    fprintf(arquivoConsultas,"***********************************************\n");
    fclose(arquivoConsultas);
    perguntafinal(15,31+z);
    {//resposta do usu�rio se gostaria de sair
        verificarespostaexit(54,31+z);
    }
}
void telaadvancedconsulation()//processo na tela de consulta avan�ada;tela3;(4� tela)
{
    int i=0;
    do
    {//la�o perdurado enquanto o usu�rio digita incorretamente
        //lembre-se de que o margeamento � [11,67;10,35]
        system("cls");
        moldura(0);
        if((option<1||option>6)&&i!=0)
        {//informar invalidez
            gotoxy(15,14);
            grafia();
            printf("Voc� digitou uma op��o inv�lida! digite novamente.");
            desgrafia();
        }
        {//imprimindo o t�tulo da tela
            gotoxy(29,12);
            grafia();
            printf("Consulta Avan�ada");
            desgrafia();
        }
        {//descri��o das op��es, bem como do t�tulo de op��es
            grafia();
            gotoxy(15,16);
            printf("Escolha sua Op��o:");
            desgrafia();
            gotoxy(15,18);
            grafia();
            printf("1-Apresentar nome dos funcion�rios do mais velho");
            desgrafia();
            gotoxy(15,19);
            printf("para o mais novo,de cima para baixo,respectivamente.");
            gotoxy(15,21);
            grafia();
            printf("2-Apresentar o total de gastos mensal");
            desgrafia();
            gotoxy(15,22);
            grafia();
            printf("pela empresa de software com seus funcion�rios");
            desgrafia();
            gotoxy(15,24);
            grafia();
            printf("3-Imprimir uma tabela com as fun��es");
            desgrafia();
            gotoxy(15,25);
            grafia();
            printf("em ordem por coluna e os respectivos funcion�rios");
            desgrafia();
            gotoxy(15,26);
            printf("abaixo de cada coluna na ordem como foram");
            gotoxy(15,27);
            printf("efetivados os registros");
            gotoxy(15,29);
            grafia();
            printf("4-Imprimir funcion�rios por endere�o");
            desgrafia();
            gotoxy(15,31);
            printf("5-Sair");
            gotoxy(15,33);
            grafia();
            printf("6-Voltar � tela inicial");
            desgrafia();
        }
        {//capturando a op��o
            gotoxy(33,16);
            fflush(stdin);
            scanf("%d",&option);
        }
        i++;
    }while(option<1||option>6);
    switch(option)
    {
        case 1:resultadvanced1();break;
        case 2:resultadvanced2();break;
        case 3:resultadvanced3();break;
        case 4:resultadvanced4();break;
        case 5:egress=1;break;
        case 6:screen=0;break;
    }
}
void programa()//princ�pio do Aut�mato Finito
{
    do
    {//looping com fim definido pelo usu�rio
        switch(screen)
        {//estados(telas)
            case 0: telainicial();break;
            case 1: teladecadastro();break;
            case 2: teladeconsultasimples();break;
            case 3: telaadvancedconsulation();break;
            case 4: egress=1;break;
        }
    }while(egress!=1);//enquanto o par�metro de fim n�o for true,prossiga.
}

int main()
{
    programa();
    space(0);
    return 0;
}
