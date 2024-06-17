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
	FILE* file;
    strcat(name, ".p");
	file = fopen(name, "wb");
	fwrite(player, sizeof(Player), 1, file);
	fclose(file);
}

void loadPlayer(char* name, Player* player)
{
	FILE* file;
    strcat(name, ".p");
	file = fopen(name, "rb");
	fread(player, sizeof(Player), 1, file);
	fclose(file);
}

void setShip( Ship* ship, char* qsp, char* name, int tl, char builder, int m, int j, int cargo, int pax, int low, int cost, int col, int row) 
{
	int i;

	strcpy(ship->qsp,  qsp);
	strcpy(ship->name, name);
	ship->tl = tl;
	ship->ar = tl;
	ship->builder = builder;
	ship->m = m;
	ship->j = j;
	ship->jump_fuel_capacity = j;
	ship->jump_fuel_carried  = j;
	ship->cargo_hold = cargo;
	ship->passengers   = pax;
	ship->low_berths   = low;
	ship->cost  = cost;
	ship->col   = col;
	ship->row   = row;

	for(i=0; i<10; ++i) {
	   ship->cargo[i].type = 0;
	   ship->cargo[i].quantity = 0;
	   ship->cargo[i].value = 0;
	}
}

void newPlayerRegister() 
{
	char name[16];
	Player player;
	int shipchoice = 0;

	printf("\n\n  enter player name: ");
	scanf("%s", name);

	strcpy(player.name, name);
	player.kilocredits = 100;
	player.col = 19;
	player.row = 10;
	player.turns_left = 60;

	printf("\n  select ship type:\n");
	printf("\n  1 - free trader\n");
	printf("\n  2 - scout\n");
	while(shipchoice == 0) {
		switch( shipchoice = cgetc() ) {
			case '1':
	            player.turns_left = 60;
			   	setShip(&player.ship, "abu11", "beowulf", 10, 'b', 1, 1, 82, 8, 10, 50, player.col, player.row);
				break;
			case '2':
				player.col = 24;
				player.row = 17;
				player.turns_left = 120;
			   	setShip(&player.ship, "saa22", "murphy",  11, 'b', 2, 2,  4, 4,  4, 50, player.col, player.row);
				break;
			default:
			    shipchoice = 0;
				break;
		}
	}

	printf("\ncreating player %s\n", name );

	savePlayer(name, &player);
}

void playerLogin()
{
	char name[16];
    FILE* file = fopen("active.p", "wb");

	printf("\n\n  enter player name: ");
	scanf("%s", name);
	strcat(name, ".p");

	fwrite(name, strlen(name), 1, file);
	fclose(file);
	printf("\n  %s is set active\n", name);
}

void playerDump()
{
	char name[16];
	char filenameDump[16];
	FILE* fp;
	Player player;

	printf("\n\n\n\n  enter player name: ");
	scanf("%s", name);
	sprintf(filenameDump, "%s.txt", name);

    loadPlayer(name, &player);
	printf("\n  dumping to %s\n", filenameDump);

    fp = fopen(filenameDump, "w");
	fprintf(fp, "name: %s\n", player.name);
	fprintf(fp, "kcr: %lu\n", player.kilocredits);
	fprintf(fp, "col: %d\n", player.col);
	fprintf(fp, "row: %d\n", player.row);
	fprintf(fp, "turns-left: %d\n", player.turns_left);
	fprintf(fp, "ship-qsp: %s\n", player.ship.qsp);
	fprintf(fp, "ship-name: %s\n", player.ship.name);
	fprintf(fp, "ship-tl: %d\n", player.ship.tl);
	fprintf(fp, "ship-builder: %c\n", player.ship.builder);
	fprintf(fp, "ship-m: %d\n", player.ship.m);
	fprintf(fp, "ship-j: %d\n", player.ship.j);
	fprintf(fp, "ship-j-fuel-capacity: %d\n", player.ship.jump_fuel_capacity);
	fprintf(fp, "ship-j-fuel-carried: %d\n", player.ship.jump_fuel_carried);
	fprintf(fp, "ship-cargo-hold: %d\n", player.ship.cargo_hold);
	fprintf(fp, "ship-pax: %d\n", player.ship.passengers);
	fprintf(fp, "ship-low: %d\n", player.ship.low_berths);
	fprintf(fp, "ship-ar: %d\n", player.ship.ar);
	fprintf(fp, "ship-cost: %d\n", player.ship.cost);
	fprintf(fp, "ship-status: %d\n", player.ship.status);
	fprintf(fp, "ship-col: %d\n", player.ship.col);
	fprintf(fp, "ship-row: %d\n", player.ship.row);
	fclose(fp);
}

void runUtils() 
{
   while(1) {
	  printf("\n\n\n\n\n\n     press a key\n");
	  cgetc();

	  clrscr();
      gotoxy( 2, 2 );
      menu_draw( 74, 6, "star traveller utils");
      cputsxy( 4, 5, "(r) register (l) login (d) dump (q) quit" );
      gotoxy( 2, 9 );
      switch(cgetc()) {
		case 'r': 
		   newPlayerRegister();
		   break;
		case 'l':
		   playerLogin();
		   break; 
		case 'd':
		   playerDump();
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
    login("star traveller administrative console", "2024-06-17");
	clrscr();
    testData();
	runUtils();
}
