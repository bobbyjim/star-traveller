#include <conio.h>
#include "menu.h"

#define		CORNER1		213
#define		CORNER2		201
#define		CORNER3		202
#define		CORNER4		203
#define		HORIZ		192
#define		VERT		221

void menu_draw(unsigned char width, unsigned char height, char* title)
{
	int i, j;
	int x = wherex();
	int y = wherey();

    for(i=x; i<x+width; ++i)
	{
		cputcxy(i,y,HORIZ);
		cputcxy(i,y+height,HORIZ);
	}

    for(j=y; j<y+height; ++j)
	{
		cputcxy(x,j,VERT);
		cputcxy(x+width,j,VERT);
	}
	cputcxy(x, y, CORNER1);
	cputcxy(x + width, y, CORNER2);
	cputcxy(x, y + height, CORNER3);
	cputcxy(x + width, y + height, CORNER4);
	cputsxy(x + 2, y, title);
}