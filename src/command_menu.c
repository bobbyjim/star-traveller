#include <stdio.h>
#include <conio.h>

#include "command_menu.h"
#include "gamestate.h"
#include "starport.h"
#include "ship.h"
#include "shipyard.h"
#include "missions.h"

#define		CORNER1		213
#define		CORNER2		201
#define		CORNER3		202
#define		CORNER4		203
#define		HORIZ		192
#define		VERT		221

void command_endTurn() {
	gamestate_nextTurn();
	gamestate_save();
	printf("turn ended. next player, please log in.\n");
}

void command_menu() {
	unsigned char choice;
	unsigned char i;

    clrscr();
    printf("  %c", CORNER1);
	for(i=0; i<20; ++i) cputc( HORIZ );
	cputc(CORNER2);
	printf("\n");

	printf("  %c                    %c\r\n", VERT, VERT );
    printf("  %c 1 - trade          %c\r\n", VERT, VERT );
	printf("  %c 2 - travel         %c\r\n", VERT, VERT );
	printf("  %c 3 - upgrade        %c\r\n", VERT, VERT );
	printf("  %c 4 - view missions  %c\r\n", VERT, VERT );
	printf("  %c 5 - end turn       %c\r\n", VERT, VERT );
	printf("  %c                    %c\r\n", VERT, VERT );

    printf("  %c", CORNER3);
	for(i=0; i<20; ++i) cputc( HORIZ );
	cputc(CORNER4);
	printf("\n");


	printf("    enter your choice: ");
	while(1) {
		choice = cgetc();
	    switch(choice) {
		   case '1': starport_trade();   return;
		   case '2': ship_travel();      return;
		   case '3': shipyard_upgrade(); return;
		   case '4': missions_view();    return;
		   case '5': command_endTurn();  return;
	    }
	}
}
