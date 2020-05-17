#include <stdio.h>
#include <conio.h>
#include "conio2.h"

int main () {
	int col, lin; char c;
	printf ("Maximize a tela e digite algo: ");
	getche (); clrscr ();
 	printf ("Posicionar cursor? (s/n): ");
	c = getche();
	while (c == 's' || c == 'S') {
		printf ("\rDigite a coluna e a linha: ");
      	scanf ("%d%d", &col, &lin);
      	gotoxy (col, lin); getche ();
      	gotoxy (1, 1);
      	printf ("                                           ");
      	printf ("\rPosicionar cursor? (s/n): "); c = getche();
      	}
	return 0;
}

