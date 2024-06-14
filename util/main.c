#include <6502.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <cx16.h>

#include "splash.h"
#include "ship.h"
#include "emplacement.h"
#include "menu.h"
#include "player.h"

void testData() {
    int i = 0;
	unsigned char col;
	unsigned char row;
	int ships_ok = 1;
	char name[12];
	char uwp[10];

    gotoxy(2,4);
    menu_draw( 74, 10, "star traveller data test");
	for(i=242; i < 243; ++i) {
    	RAM_BANK = 1;
		col = *((unsigned char*)(0xa000 + i * 16));
		row = *((unsigned char*)(0xa000 + i * 16 + 1));
		strncpy(name, ((char*)(0xa000 + i * 16 + 2)), 12);
    	RAM_BANK = 2;
		strncpy(uwp,  ((char*)(0xa000 + i * 16 + 6)), 10);
		if (!strcmp(name, "regina"))
		   cputsxy( 4,6,"* world data ok");
		//printf("%02u%02u %-15s %s\n", col, row, name, uwp);
	}

    RAM_BANK = 3;
	for(i=0; i<2; ++i) {
		Ship* ship = (Ship*)(0xa000 + i * 32);
		if (!strcmp(ship->name, "beowulf") && !strcmp(ship->name, "murphy"))
			ships_ok = 0;
		//printf("%-20s TL %d MCR %d\n", ship->qsp, ship->tl, ship->cost * 10);
	}
	if (ships_ok)
	   cputsxy( 4,8,"* ship data ok\n");

	//printf("emplacement                      tl   HPRSNG\n");
	RAM_BANK = 3;
	for(i=0; i<1; ++i) {
		Loadout* empl = (Loadout*)(0xb000 + i * 32);
		if (!strcmp(empl->name, "hybrid turret")) 
		   cputsxy( 4,10, "* emplacement data ok\n");
		//printf("%-28s %2d   %d%d%d%d%d%d%d%d\n", empl->name, empl->tl, empl->heat, empl->pen, empl->rad, empl->screen, empl->sensor, empl->globe, empl->r1, empl->r2);
	}

	printf("\n\n\n\n    press a key to continue");
	cgetc();
}

void setPetFont()
{
   struct regs fontregs;
   fontregs.a = 4; // PET-like
   fontregs.pc = 0xff62;
   _sys(&fontregs);
}

void savePlayer(char* name, Player* player)
{
	FILE* file = fopen(name, "wb");
	fwrite(player, sizeof(Player), 1, file);
	fclose(file);
}

void loadPlayer(char* name, Player* player)
{
	FILE* file = fopen(name, "rb");
	fread(player, sizeof(Player), 1, file);
	fclose(file);
}

void newPlayerRegister() 
{
	int i;
	char name[15];
	Player player;

	clrscr();
	printf("\n  enter player name: ");
	scanf("%s", name);

	printf("\ncreating player %s\n", name );

	strcpy(player.name, name);
	player.kilocredits = 100;
	player.col = 19;
	player.row = 10;
	strcpy(player.ship.qsp,  "abu11");
    strcpy(player.ship.name, "beowulf");
    player.ship.tl = 10;
	player.ship.builder = 'B';
	player.ship.m = 1;
	player.ship.j = 1;
	player.ship.jump_fuel_capacity = 1;
	player.ship.jump_fuel_carried = 1;
	player.ship.cargo_hold = 82;
    player.ship.passengers = 8;
    player.ship.lowBerths = 10;
	player.ship.ar = 10;
	player.ship.cost = 50;
    player.ship.status = 0;
	player.ship.col = 19;
	player.ship.row = 10;
	for(i=0; i<10; ++i) {
	   player.ship.cargo[i].type = 0;
	   player.ship.cargo[i].quantity = 0;
	   player.ship.cargo[i].value = 0;
	}

	savePlayer(name, &player);
}

void playerLogin()
{
	char name[15];
    FILE* file = fopen("active", "wb");

	clrscr();
	printf("\n  enter player name: ");
	scanf("%s", name);
	fwrite(name, strlen(name), 1, file);
	fclose(file);
	printf("\n  %s is set active\n", name);
}

void runUtils() 
{
   while(1) {
	  clrscr();
      gotoxy( 2, 2 );
      menu_draw( 74, 6, "star traveller utils");
      cputsxy( 4, 5, "(r) register (l) login (q) quit" );
      gotoxy( 2, 9 );
      switch(cgetc()) {
		case 'r': 
		   newPlayerRegister();
		   break;
		case 'l':
		   playerLogin();
		   break; 
		case 'q': 
		   return;
	  }
   }
}

void main() 
{
    setPetFont();
	textcolor(COLOR_GREEN);
    login("star traveller", "2024-06-13");
	clrscr();
    testData();
	runUtils();
}
