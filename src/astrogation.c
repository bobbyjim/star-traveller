#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "astrogation.h"
#include "menu.h"
#include "ship.h"
#include "map.h"
#include "player.h"

extern Player player;

int astrogation_fetch( MAP1* world, int col, int row )
{
   int i, r, c;

   RAM_BANK = 1;
   for(i=0; i<512; ++i)
   {
      c = *((unsigned char*)(0xa000 + i * 16));
      r = *((unsigned char*)(0xa000 + i * 16 + 1));
	  if (c == col && r == row) {
	     MAP1* found = ((MAP1*)(0xa000 + i * 16));
	     *world = *found; // copy please!
		 return i;
	  }
   }
   return -1;
}

void astrogation_fetch2( MAP2* world2, int offset )
{
	RAM_BANK = 2;
	*world2 = *((MAP2*)(0xa000 + offset * 16)); // make a copy
}

//
//  e.g. 24,17 to 24,19:
//  aa = 17 + 12 = 29
//  ab = 19 + 12 = 31
//  da = 2
//  db = 0
//  d  = 29 - 31 - 24 + 24 = 2
//
int distance( int col1, int row1,      
              int col2, int row2 )
{
   int aa = row1 + (col1/2);
   int ab = row2 + (col2/2);
   int da = abs(aa-ab);
   int db = abs(col1-col2);
   int d  = abs(aa - ab - col1 + col2);

//   printf("  %02d%02d -> %02d%02d : aa(%d) ab(%d) da(%d) db(%d) d(%d)\n", col1, row1, col2, row2, aa, ab, da, db, d);

   if ((da >= db) && (da >= d)) d = da;
   if ((db >= da) && (db >= d)) d = db;

//   if (d > maximumValue1 || d > maximumValue2) return -1;

   return d;
}

//	Wild => 0,  	Vi   => 1,  	Na   => 2,  	Sw   => 3,  	
//	Pa   => 4,  	Rr   => 5,  	Cs   => 6,  	Du   => 7,
char* allegiance[8] = {
	"wilds",
	"vilis",
	"none",
	"gram",
	"pavabid",
	"regina",
	"client",
	"mora"
};

char* zone[4] = {
	"",
	"amber",
	"red",
	""
};

int astrogation_print_world(int col, int row)
{
	MAP1 current;
	MAP2 current2;
	unsigned char color;

	char bases[3] = { 0, 0, 0 };
	char belt     = ' ';
	char gg       = ' ';

	int offset = astrogation_fetch( &current, col, row );
	if (offset > -1)
    {
	   astrogation_fetch2( &current2, offset );
	   bases[0] = current.hasNavalBase? 'n' : ' ';
	   bases[1] = current.hasScoutBase? 's' : ' ';
	   belt     = current.hasBelt?      'y' : ' ';
	   gg       = current.hasGG?        'y' : ' ';

       if (player.row == row && player.col == col )
	      color = COLOR_LIGHTGREEN;
	   else if (current.zone == 1)
	   {
	      color = COLOR_YELLOW;
	   }
	   else if (current.zone == 2)
	   {
	      color = COLOR_LIGHTRED;
	   }
	   else
	   {
	      color = COLOR_LIGHTBLUE;
	   }

       textcolor(color);
	   printf(" %02d%02d  %-15s %9s  %2s     %c     %c       %-5s  %-8s  ",
		   col,
		   row,
		   current.name,
		   current2.uwp,
		   bases,
		   belt,
		   gg,
		   zone[ current.zone ],
  		   allegiance[ current.allegiance ]
	   );
	   return 1;
	}
	else
	   return 0;
}

int astrogation_map()
{
	int i,j;
	int d;
	int pos;
	unsigned char color = COLOR_LIGHTRED;

    clrscr();
    textcolor(COLOR_GREEN);
    revers(1);
	cputs(" hex   world name      uwp        bases  belt  jovian  zone   alleg  distance  \r\n");
	revers(0);
    textcolor(color);

    pos = 0;
    for(i=player.col - player.ship.j; i<=player.col + player.ship.j; ++i)
	   for(j=player.row - player.ship.j; j<=player.row + player.ship.j; ++j)
	   {
		  d=distance(i,j,player.col,player.row); 
		  
		  if (d > -1) {
			  //if (pos < 20) {
				  if (astrogation_print_world(i,j))
				  {
				     printf("%d\n", d);
				     ++pos;
				  }
			  //}
			  //else 
			    // puts("...and more");
		   }
	   }
    textcolor(COLOR_GRAY3);
}

int astrogation_attempt_jump_to(int hex)
{
   int i = hex / 100;
   int j = hex % 100;
   int d = distance(i,j,player.col,player.row);

   if (d == 0 || d > player.ship.j ) { 
      printf("\n  (%02d%02d) invalid destination!\n\n", i, j );
   }
   else {
      // move player and ship
      player.col = i;
      player.row = j;
   }
   return d;
}
