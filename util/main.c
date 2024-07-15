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
#include "util.h"

void testData() {
    int i = 0;
	unsigned char col;
	unsigned char row;
	int ships_ok = 1;
	char name[12];
	char uwp[10];

	textcolor(COLOR_YELLOW);
    puts( "\n\nstar traveller data test");
	textcolor(COLOR_LIGHTBLUE);
	for(i=242; i < 243; ++i) {
    	RAM_BANK = 1;
		col = *((unsigned char*)(0xa000 + i * 16));
		row = *((unsigned char*)(0xa000 + i * 16 + 1));
		strncpy(name, ((char*)(0xa000 + i * 16 + 2)), 12);
    	RAM_BANK = 2;
		strncpy(uwp,  ((char*)(0xa000 + i * 16 + 6)), 10);
        printf(" - %02u%02u %-15s %s\n", col, row, name, uwp);
		if (!strcmp(name, "regina"))
		   puts( "    - world data ok");
	}

    RAM_BANK = 3;
	for(i=0; i<2; ++i) {
		Ship* ship = (Ship*)(0xa000 + i * 32);
		if (!strcmp(ship->name, "beowulf") && !strcmp(ship->name, "murphy"))
			ships_ok = 0;
		printf(" - %-20s MCR %d\n", ship->qsp, ship->cost * 10);
	}
	if (ships_ok)
	   puts( "    - ship data ok");

	//printf("emplacement                      tl   HPRSNG\n");
	RAM_BANK = 3;
	for(i=0; i<1; ++i) {
		Loadout* empl = (Loadout*)(0xb000 + i * 32);
		printf(" - %-28s %2d   %d%d%d%d%d%d%d%d\n", empl->name, empl->tl, empl->heat, empl->pen, empl->rad, empl->screen, empl->sensor, empl->globe, empl->r1, empl->r2);
		if (!strcmp(empl->name, "hybrid turret")) 
		   puts( "    - emplacement data ok\n");
	}
}

void setPetFont()
{
   struct regs fontregs;
   fontregs.a = 4; // PET-like
   fontregs.pc = 0xff62;
   _sys(&fontregs);
}

void main() 
{
    setPetFont();
	textcolor(COLOR_GREEN);
    login("star traveller administrative console", "2024-06-17");
    testData();
	util_run();
}
