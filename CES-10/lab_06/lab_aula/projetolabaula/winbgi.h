#ifndef _WINBGI_H
#define _WINBGI_H

#include <windows.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

void start_graphics();
void message_loop();
void setbkcolor(COLORREF cor);
void cleardevice();
void setcolor(COLORREF cor);
void rectangle(int x0, int y0, int x1, int y1);
void setlinestyle(int style,int whatever,int width);
void line(int x0, int y0, int x1, int y1);
void settextstyle(char *face,int angle,int size);
void setfillstyle(int style,COLORREF cor);
void bar(int x0, int y0, int x1, int y1);
void outtextxy(int x, int y, char *texto);
void sector(int xc,int yc,double angini,double angfin,int rx, int ry);
void fillcircle(int, int, int);
void fillelipse (int, int, int, int);
void circle(int, int, int);
void elipse(int, int, int, int);
int textheight(char *texto);
int textwidth(char *texto);
void putpixel (int, int, int);

void closegraph();


#define SOLID_FILL BS_SOLID

#define DOTTED_LINE PS_DOT
#define SOLID_LINE PS_SOLID
#define NORM_WIDTH 0

#define TRIPLEX_FONT "Times New Roman"

#define HORIZ_DIR 0
#define VERT_DIR 900

#define DARKGRAY RGB(50,50,50)
#define RED RGB(250,0,0)
#define GREEN RGB(0,250,0)
#define BLUE RGB(0,0,250)
#define MAGENTA RGB(250,0,250)
#define YELLOW RGB(250,250,0)
#define CYAN RGB(0,250,250)
#define LIGHTGRAY RGB(200,200,200)
#define GRAY RGB(120,120,120)
#define BLACK RGB(0,0,0)
#define WHITE RGB(250,250,250)
#define LIGHTRED RGB(250,100,100)
#define LIGHTGREEN RGB(150,250,150)
#define LIGHTBLUE RGB(100,100,250)
#define LIGHTMAGENTA RGB(250,100,250)
#define LIGHTYELLOW RGB(250,250,100)
#define LIGHTCYAN RGB(100,250,250)
#define BROWN RGB(100,150,50)
#define LIGHTBROWN RGB(150,200,80)
#define DARKBROWN RGB(50,80,30)
#define ORANGE RGB(250,100,0)
#define LIGHTORANGE RGB(250,200,50)

#endif
