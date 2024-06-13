#include <stdio.h>
#include <string.h>
#include <cx16.h>

#include "ship.h"
#include "emplacement.h"

void testMap() {
    int i = 0;
	unsigned char col;
	unsigned char row;
	char name[12];
	char uwp[10];

	printf("\nreading the map...\n\n");
	for(i=0; i < 10; ++i) {
    	RAM_BANK = 1;
		col = *((unsigned char*)(0xa000 + i * 16));
		row = *((unsigned char*)(0xa000 + i * 16 + 1));
		strncpy(name, ((char*)(0xa000 + i * 16 + 2)), 12);
    	RAM_BANK = 2;
		strncpy(uwp,  ((char*)(0xa000 + i * 16 + 6)), 10);
		printf("%02u%02u %-15s %s\n", col, row, name, uwp);
	}

	printf("\nreading ships...\n\n");
    RAM_BANK = 3;
	for(i=0; i<9; ++i) {
		Ship* ship = (Ship*)(0xa000 + i * 32);
		printf("%-20s TL %d MCR %d\n", ship->qsp, ship->tl, ship->cost * 10);
	}

	printf("\nreading emplacements...\n\n");
	RAM_BANK = 3;
	    printf("name                         tl   HPRSNG\n");
	for(i=0; i<10; ++i) {
		Loadout* empl = (Loadout*)(0xb000 + i * 32);
		printf("%-28s %2d   %d%d%d%d%d%d%d%d\n", empl->name, empl->tl, empl->heat, empl->pen, empl->rad, empl->screen, empl->sensor, empl->globe, empl->r1, empl->r2);
	}

}

void main() {

	printf("star-traveller utils\n\n");

    testMap();

}