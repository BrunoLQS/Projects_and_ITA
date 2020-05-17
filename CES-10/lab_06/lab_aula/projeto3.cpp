#include <stdio.h>
#include <conio.h>
#include <conio2.h>
int main () {
	int i, j, demora = 20000000;
	printf ("Maximize a tela e digite algo: ");
	getche (); clrscr ();
	for (i = 10; i <= 60; i++) {
		gotoxy (i, 5); printf (" *");
		for (j = 1; j <= demora; j++);}
	for (i = 6; i <= 40; i++) {
		gotoxy (61, i-1); printf (" ");
		gotoxy (61, i); printf ("*");
		for (j = 1; j <= demora; j++);
	}
 	printf ("\n\nDigite algo para encerrar: ");
	getch (); return 0;
}


