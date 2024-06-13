#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "astrogation.h"
#include "menu.h"
#include "ship.h"
#include "map.h"

extern Ship playerShip;

MAP1* astrogation_fetch( col, row )
{
   int i, r, c;

   RAM_BANK = 1;
   for(i=0; i<512; ++i)
   {
      c = *((unsigned char*)(0xa000 + i * 16));
      r = *((unsigned char*)(0xa000 + i * 16 + 1));
	  if (c == col && r == row)
	     return ((MAP1*)(0xa000 + i * 16));
   }
   return 0;
}

int distance( int col1, int row1,
              int col2, int row2,
              int maximumValue1, int maximumValue2 )
{
   int aa = row1 + (col1/2);
   int ab = row2 + (col2/2);
   int da = abs(aa-ab);
   int db = abs(col1-col2);
   int d  = abs(aa - ab - col1 + col2);

   if ((da >= db) && (da >= d)) d = da;
   if ((db >= da) && (db >= d)) d = db;

   if (d > maximumValue1 || d > maximumValue2) return 0;

   return d;
}


int astrogation_menu()
{
	int i,j;
	int hex;
	int x,y;
	int d;

	clrscr();
	gotoxy(1,1);
	menu_draw( 74, 21, "astrogation" );
	gotoxy(2,4);

    x = 4;
    y = 4;
    for(i=playerShip.col - playerShip.j; i<playerShip.col + playerShip.j; ++i)
	   for(j=playerShip.row - playerShip.j; j<playerShip.row + playerShip.j; ++j)
	   {
		  if ((d=distance(i,j,playerShip.col,playerShip.row,playerShip.j,playerShip.jump_fuel_carried)) > 0) {
			  if (x < 49) {
		          MAP1* world = astrogation_fetch(i,j);
				  if (world) {
					 gotoxy(x,y);
					 cprintf(" %02u%02u ", i, j);
					 textcolor(COLOR_LIGHTGREEN);
					 cprintf("(%d)", d);
					 textcolor(COLOR_WHITE);
					 cprintf(" %-15s", world->name);
					 y += 2;
					 if (y > 18) {
						y = 4;
						x += 22;
					 }
				  }
			  }
			  else 
			     cputsxy(48,20,"...and more");
		  }
	   }

    gotoxy(0,25);
	d=0;
	while(d==0) {
	   printf( "  enter destination hex: ");
	   scanf("%d", &hex);

	   if (hex == 0) return 0;

	   i = hex / 100;
	   j = hex % 100;
	   if ( (d=distance(i,j,playerShip.col,playerShip.row,playerShip.j,playerShip.jump_fuel_carried)) == 0) {
		   printf("\n  (%02d%02d) invalid destination!\n\n", i, j );
	   }
	   else {
          // move the ship
		  playerShip.col = i;
		  playerShip.row = i;
		  playerShip.jump_fuel_carried -= d;
	   }
	}

	return 1;
}