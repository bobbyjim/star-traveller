#include <stdio.h>
#include <conio.h>

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

void command_endTurn() {
	gamestate_nextTurn();
	gamestate_save();
	printf("turn ended. next player, please log in.\n");
}

void command_menu() {
    unsigned char choice;
    unsigned char turns = 60;

    while(turns>0) {

      clrscr();
      gotoxy(2,2);
      menu_draw( 22, 12, "command menu" );

      cputsxy( 4,4, "1 - trade         " );
      cputsxy( 4,6, "2 - astrogate     " );
      cputsxy( 4,8, "3 - upgrade       " );
      cputsxy( 4,10,"4 - view missions " );
      cputsxy( 4,12,"5 - end turn      " );
      
      gotoxy(0,17);
      astrogation_print_current();
      printf("\n\n    you have %d turns left", turns);
      printf("\n\n    enter your choice: ");

      choice = cgetc();
      switch(choice) {
         case '1': turns -= starport_trade();   break;
         case '2': turns -= ship_travel();      break;
         case '3': turns -= shipyard_upgrade(); break;
         case '4': turns -= missions_view();    break;
         case '5': command_endTurn();  break;
       }
	}
}
