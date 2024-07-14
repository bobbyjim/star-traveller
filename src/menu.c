#include <conio.h>
#include <string.h>

#include "common.h"
#include "menu.h"

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
	cputcxy(x + 2, y, ' ');
	cputsxy(x + 3, y, title);
	cputcxy(x + 3 + strlen(title), y, ' ');
}