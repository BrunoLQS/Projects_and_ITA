#include<stdio.h>
#include<stdlib.h>
int main() {
    /*declaração de variáveis*/
int aluno,numalunos,p1,p2,p3,p4;float n1,n2,n3,n4;
printf("NOTAS DE DIVERSOS ALUNOS EM 4 PROVAS:\n\n");
printf("Digite o numero de alunos:");
scanf("%d",&numalunos);printf("\n\n");aluno = 1;
printf("Digite o peso da prova 1:");
scanf("%d",&p1);printf("\n");
printf("Digite o peso da prova 2:");
scanf("%d",&p2);printf("\n");
printf("Digite o peso da prova 3:");
scanf("%d",&p3);printf("\n");
printf("Digite o peso da prova 4:");
scanf("%d",&p4);printf("\n\n\n");
while (aluno <= numalunos) {printf("Aluno %d:\n\n\tNota na prova 1:",aluno);
scanf("%f",&n1);
printf("\n\tNota na prova 2:");
scanf("%f",&n2);
printf("\n\tNota na prova 3:");
scanf("%f",&n3);
printf("\n\tNota na prova 4:");
scanf("%f",&n4);
printf("\n\n\tMedia: %g\n", ((p1*n1)+(p2*n2)+(p3*n3)+(p4*n4))/(p1+p2+p3+p4));
aluno= aluno+1; }
printf("\n\nDigite algo para encerrar :"); system ("PAUSE"); return 0;}
