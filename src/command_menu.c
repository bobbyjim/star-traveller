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
      textcolor(COLOR_GRAY3);
      puts("\n\ncommand menu\n");
      puts(" 1    - trade");
      puts(" 2    - map");
      puts(" 3    - upgrade");
      puts(" 4    - end turn");
      puts(" xxxx - jump to hex");

      printf("\nyou have %d turns left\n", player.turns_left);

      textcolor(COLOR_YELLOW);
      printf("enter your choice: ");
      scanf("%d", &choice);
      textcolor(COLOR_GRAY3);
      
      switch(choice) {
         case 1: player.turns_left -= starport_trade();   break;
         case 2: astrogation_map(); break;
         case 3: player.turns_left -= shipyard_upgrade(); break;
         case 4: player.turns_left -= missions_view();    break;
         case 5: command_endTurn();  break;
         default:
            if (choice > 100) // a hex code
            {
               printf("\njump to hex %04d? ", choice);
               if (cgetc() == 'y')
               {
                  if (astrogation_attempt_jump_to(choice))
                     player.turns_left--;
               }
            }
       }
       player_save();
	}
}
