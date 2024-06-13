#include <6502.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <cx16.h>

#include "ship.h"
#include "emplacement.h"
#include "menu.h"

void testData() {
    int i = 0;
	unsigned char col;
	unsigned char row;
	int ships_ok = 1;
	char name[12];
	char uwp[10];

    menu_draw( 30, 10, "star traveller data test");
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

void runUtils() 
{
   menu_draw( 30, 7, "star traveller utils");
   cputsxy( 2, 18, " " );
}

void main() 
{
    setPetFont();
	textcolor(COLOR_GREEN);
    gotoxy(2,3);
    testData();
	gotoxy( 2, 16 );
	runUtils();
}