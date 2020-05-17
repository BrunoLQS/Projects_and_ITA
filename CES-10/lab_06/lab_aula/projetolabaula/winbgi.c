/* Adaptador de funcoes graficas da Borland para Windows
 *
 * Autor: Carlos Henrique Q. Forster
 * Instituto Tecnologico de Aeronautica
 * Curso de CES-10 Introducao a Computacao
 */

#include <windows.h>
#include "winbgi.h"
#include <stdio.h>
#include <math.h>

/*  Make the class name into a global variable  */
char szClassName[ ] = "WinBGI";

HWND hwnd;               /* This is the handle for our window */
MSG messages;            /* Here messages to the application are saved */
WNDCLASSEX wincl;        /* Data structure for the windowclass */

HDC hdc;
DWORD ThreadID;

int ready=0;

HINSTANCE hThisInstance=0;

DWORD WINAPI ThreadFunc( LPVOID v)
{
    void start_window();
    start_window();
    ready=1;
    message_loop();
    return 0L;
}

    int winwidth, winheight;

void start_graphics()
{
    printf ("ABERTURA DO MODO GRAFICO\n\nLargura e altura da tela: ");
    scanf ("%d%d", &winwidth, &winheight);
    CreateThread(0,0,&ThreadFunc,0,0,&ThreadID);
    while(!ready) Sleep(100);
}

void message_loop()
{
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
        //printf(".");
    }
}

void start_window()
{
    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Windows App",       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           winwidth,                 /* The programs width */
           winheight,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, SW_SHOW);

    hdc=GetDC(hwnd); //GetWindowDC(hwnd);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    /* The program return-value is 0 - The value that PostQuitMessage() gave */
//    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK
WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

COLORREF bkcolor=DARKBROWN;
COLORREF color=WHITE;
int pen_style=PS_SOLID;
int pen_width=NORM_WIDTH;
int brush_style=BS_SOLID;
COLORREF brush_color=WHITE;
HFONT hfont=0L;

void setbkcolor(COLORREF cor)
{
  bkcolor=cor;
}

void cleardevice()
{
  HBRUSH hbrush=CreateSolidBrush(bkcolor);
  HPEN hpen=CreatePen(PS_NULL,0,0);
  SelectObject(hdc,hpen);
  SelectObject(hdc,hbrush);
  Rectangle(hdc,0,0,winwidth,winheight);
}

void setcolor(COLORREF cor)
{
  color=cor;
}

void rectangle(int x0, int y0, int x1, int y1)
{
  LOGBRUSH logbrush;
  HBRUSH hbrush;
  HPEN hpen;

  logbrush.lbStyle=BS_HOLLOW;
  hbrush=CreateBrushIndirect(&logbrush);
  hpen=CreatePen(pen_style,pen_width,color);
  SelectObject(hdc,hpen);
  SelectObject(hdc,hbrush);
  Rectangle(hdc,x0,y0,x1,y1);
}

void setlinestyle(int style,int whatever,int width)
{
  pen_style=style;
  pen_width=width;
}

void line(int x0, int y0, int x1, int y1)
{
  LOGBRUSH logbrush;
  HBRUSH hbrush;
  HPEN hpen;

  logbrush.lbStyle=BS_HOLLOW;
  hbrush=CreateBrushIndirect(&logbrush);
  hpen=CreatePen(pen_style,pen_width,color);
  SelectObject(hdc,hpen);
  SelectObject(hdc,hbrush);
  MoveToEx(hdc,x0,y0,NULL);
  LineTo(hdc,x1,y1);
}

void closegraph()
{
  DestroyWindow(hwnd);
  system("PAUSE");
}

void settextstyle(char *face,int angle,int size)
{
  hfont=CreateFont(8*size,0,angle,angle,0,  0,0,0,
    DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS,
    DEFAULT_QUALITY, DEFAULT_PITCH, face);
  SelectObject(hdc,hfont);
}

void setfillstyle(int style,COLORREF cor)
{
  brush_style=style;
  brush_color=cor;
}

void bar(int x0, int y0, int x1, int y1)
{
  LOGBRUSH logbrush;
  HBRUSH hbrush;
  HPEN hpen;

  logbrush.lbStyle=brush_style;
  logbrush.lbHatch=HS_FDIAGONAL;
  logbrush.lbColor=brush_color;
  hbrush=CreateBrushIndirect(&logbrush);
  hpen=CreatePen(pen_style,pen_width,color);
  SelectObject(hdc,hpen);
  SelectObject(hdc,hbrush);
  Rectangle(hdc,x0,y0,x1,y1);
}

void outtextxy(int x, int y, char *texto)
{
  TextOut(hdc, x,y, texto, strlen(texto));
}

void sector(int xc,int yc,double angini,double angfin,int rx, int ry)
{
  LOGBRUSH logbrush;
  HBRUSH hbrush;
  HPEN hpen;

  logbrush.lbStyle=brush_style;
  logbrush.lbHatch=HS_FDIAGONAL;
  logbrush.lbColor=brush_color;
  hbrush=CreateBrushIndirect(&logbrush);
  hpen=CreatePen(pen_style,pen_width,color);
  SelectObject(hdc,hpen);
  SelectObject(hdc,hbrush);
  Pie(hdc,xc-rx,yc-ry,xc+rx,yc+ry
    ,rx*cos(angini*3.1416/180)+xc
    ,-ry*sin(angini*3.1416/180)+yc
    ,rx*cos(angfin*3.1416/180)+xc
    ,-ry*sin(angfin*3.1416/180)+yc
   );
}

int textheight(char *texto)
{
  SIZE size;
  GetTextExtentPoint32(
    hdc,
    texto,	// address of text string
    strlen(texto),	// number of characters in string
    &size 	// address of structure for string size
   );
  return size.cy;
}

int textwidth(char *texto)
{
  SIZE size;
  GetTextExtentPoint32(
    hdc,
    texto,	// address of text string
    strlen(texto),	// number of characters in string
    &size 	// address of structure for string size
   );
  return size.cx;
}

void circle (int x0, int y0, int raio) {
    int x, y11, y12, y21, y22;
    for (x = x0-raio; x < x0+raio; x++) {
        y11 = y0 + (int)sqrt (raio*raio-(x-x0)*(x-x0));
        y12 = y0 - (int)sqrt (raio*raio-(x-x0)*(x-x0));
        y21 = y0 + (int)sqrt (raio*raio-(x+1-x0)*(x+1-x0));
        y22 = y0 - (int)sqrt (raio*raio-(x+1-x0)*(x+1-x0));
        line (x, y11, x+1, y21);
        line (x, y12, x+1, y22);
    }
}

void elipse (int x0, int y0, int r1, int r2) {
    int x, y11, y12, y21, y22;
    for (x = x0-r1; x < x0+r1; x++) {
        y11 = y0 + (int)sqrt (r2*r2*(1-(x-x0)*(double)(x-x0)/(r1*r1)));
        y12 = y0 - (int)sqrt (r2*r2*(1-(x-x0)*(double)(x-x0)/(r1*r1)));
        y21 = y0 + (int)sqrt (r2*r2*(1-(x+1-x0)*(double)(x+1-x0)/(r1*r1)));
        y22 = y0 - (int)sqrt (r2*r2*(1-(x+1-x0)*(double)(x+1-x0)/(r1*r1)));
        line (x, y11, x+1, y21);
        line (x, y12, x+1, y22);
    }
}

void fillcircle (int xc, int yc, int raio) {
    sector (xc, yc, 0.0, 359.990, raio, raio);
}

void fillelipse (int xc, int yc, int r1, int r2) {
    sector (xc, yc, 0.0, 359.990, r1, r2);
}

void putpixel(int col, int lin, int cor) {
    SetPixel(hdc, col, lin, cor);
}


