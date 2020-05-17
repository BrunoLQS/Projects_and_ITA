#include <stdio.h>
#include <conio.h>
#include "conio2.h"
int main () {
	int i, n;
	printf ("TESTE DO LIMITE DE LINHAS DO GOTOXY");
	printf ("\n\n\tDigite o numero de linhas: ");
	scanf ("%d", &n);
	printf ("\nMaximize a tela e digite algo!");
	getche (); clrscr ();
	for (i=1; i<=n; i++) {
		gotoxy ((i-1)%80+1, i); printf ("%d", i%10);
	}
 	printf ("\nDigite algo para encerrar: ");
	getch ();
	return 0;
}
