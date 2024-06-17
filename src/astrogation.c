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
		 return 1;
	  }
   }
   return 0;
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
              int col2, int row2, 
              int maximumValue1, int maximumValue2 )
{
   int aa = row1 + (col1/2);
   int ab = row2 + (col2/2);
   int da = abs(aa-ab);
   int db = abs(col1-col2);
   int d  = abs(aa - ab - col1 + col2);

//   printf("  %02d%02d -> %02d%02d : aa(%d) ab(%d) da(%d) db(%d) d(%d)\n", col1, row1, col2, row2, aa, ab, da, db, d);

   if ((da >= db) && (da >= d)) d = da;
   if ((db >= da) && (db >= d)) d = db;

   if (d > maximumValue1 || d > maximumValue2) return 0;

   return d;
}

void astrogation_print_current()
{
	MAP1 current;
    astrogation_fetch( &current, player.col, player.row);
	printf("current world: (%02d%02d) %s", player.col, player.row, current.name );
}

// void astrogation_show_range()
// {
//    int i,j;
//    MAP1 world;

//    int k=0;

//    for(i=player.ship.col - player.ship.j; i<=player.ship.col + player.ship.j; ++i)
//       for(j=player.ship.row - player.ship.j; j<=player.ship.row + player.ship.j; ++j)
//       {
//          int d=distance(i,j,player.ship.col,player.ship.row,player.ship.j,player.ship.j);
//          if (d > 0)
// 			if (astrogation_fetch(&world, i, j)) 
// 			{
// 			   printf("%02d%02d ", world.col, world.row);
// 			   if (k % 10 == 9) printf("\n    ");
// 			   ++k;
// 			}
// 	  }
// }

int astrogation_menu()
{
	int i,j;
	int hex;
	int d;
	int pos;

	clrscr();
	gotoxy(1,1);
	menu_draw( 74, 21, "astrogation" );
	gotoxy(2,4);

    pos = 0;
    for(i=player.ship.col - player.ship.j; i<=player.ship.col + player.ship.j; ++i)
	   for(j=player.ship.row - player.ship.j; j<=player.ship.row + player.ship.j; ++j)
	   {
		  d=distance(i,j,player.ship.col,player.ship.row,player.ship.j,player.ship.j); // used to care about jump_fuel_carried but no longer
		  
		  if (d > 0) { 
			  if (pos < 20) {
		          MAP1 world;
				  if (astrogation_fetch(&world, i, j)) {
					 gotoxy(4 + (pos/7)*24, 4 + (pos%7)*2);
					 cprintf(" %02u%02u ", i, j);
					 textcolor(COLOR_LIGHTGREEN);
					 cprintf("(%d)", d);
					 textcolor(COLOR_WHITE);
					 cprintf(" %-15s", world.name);
					 ++pos;
				  }
			  }
			  else 
			     cputsxy(48,20,"...and more");
		  }
	   }

    gotoxy(2,25);
    astrogation_print_current();

	d=0;
	while(d==0) {
	   printf( "\n\n  enter destination hex: ");
	   scanf("%d", &hex);
	   if (hex == 0) return 0;
	   d = astrogation_attempt_jump_to(hex);
	}
}

int astrogation_attempt_jump_to(int hex)
{
   int i = hex / 100;
   int j = hex % 100;
   int d = distance(i,j,player.ship.col,player.ship.row,player.ship.j,player.ship.j);

   if (d == 0) { // used to care about jump_fuel_carried but no longer
      printf("\n  (%02d%02d) invalid destination!\n\n", i, j );
   }
   else {
      // move player and ship
      player.col = i;
      player.row = j;
      player.ship.col = i;
      player.ship.row = j;
    //player.ship.jump_fuel_carried -= d;  don't care
   }
   return d;
}
