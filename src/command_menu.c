#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "command_menu.h"
#include "menu.h"
#include "gamestate.h"
#include "starport.h"
#include "ship.h"
#include "shipyard.h"
#include "missions.h"
#include "astrogation.h"
#include "player.h"

#define		CORNER1		213
#define		CORNER2		201
#define		CORNER3		202
#define		CORNER4		203
#define		HORIZ		192
#define		VERT		221

extern Player player;

void command_endTurn() 
{
	gamestate_nextTurn();
	gamestate_save();
	printf("turn ended. next player, please log in.\n");
}

void command_menu() {
    int choice;

    while(player.turns_left>0) {

      clrscr();

      textcolor(COLOR_GRAY3);
      gotoxy(67, 59);
      printf("%u k free", _heapmemavail());

      //gotoxy(4, 20);
      //textcolor(COLOR_LIGHTBLUE);
      //printf("hexes in range:\n\n    ");
      //astrogation_show_range();

      gotoxy(2,2);
      textcolor(COLOR_WHITE);
      menu_draw( 35, 14, "command menu" );
      cputsxy( 4,4, "1    - trade         " );
      cputsxy( 4,6, "2    - astrogate     " );
      cputsxy( 4,8, "3    - upgrade       " );
      cputsxy( 4,10,"4    - view missions " );
      cputsxy( 4,12,"5    - end turn      " );
      cputsxy( 4,14,"xxxx - jump to hex   " );
      
      gotoxy(42,3);
      astrogation_print_current();
      gotoxy(42,5);
      printf("you have %d turns left", player.turns_left);
      gotoxy(42,12);
      printf("enter your choice: ");
      scanf("%d", &choice);
      
      switch(choice) {
         case 1: player.turns_left -= starport_trade();   break;
         case 2: player.turns_left -= ship_travel();      break;
         case 3: player.turns_left -= shipyard_upgrade(); break;
         case 4: player.turns_left -= missions_view();    break;
         case 5: command_endTurn();  break;
         default:
            if (choice > 100) // a hex code
            {
               printf("\n");
               gotox(45);
               printf("jump to hex %04d? ", choice);
               if (cgetc() == 'y')
               {
                  astrogation_attempt_jump_to(choice);
               }
            }
       }
       player_save();
	}
}
