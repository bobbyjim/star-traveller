#include <conio.h>
#include <stdio.h>
#include <string.h>

#include "player.h"
#include "ship.h"

void playerLogin();
void playerDump();
void newPlayerRegister();

void util_run() 
{
   textcolor(COLOR_YELLOW);
   while(1) {
	  
	  puts("\n\nmenu");
	  puts( "--------------------------");
	  puts( "(d) dump player data");
	  puts( "(l) log player in" );
	  puts( "(r) register new player");
	  puts( "(q) quit util\n");
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

void setShip( Ship* ship, char* qsp, char* name, int tl, char builder, int hardpoints, int m, int j, int cargo, int pax, int low, int cost, int col, int row) 
{
	int i;

	strcpy(ship->qsp,  qsp);
	ship->tl = tl;
	strcpy(ship->name, name);

	ship->cost  = cost;
	ship->builder = builder;

	ship->hardpoints = hardpoints;
	ship->status     = 1;
	ship->m = m;
	ship->j = j;

	ship->ar = tl;
	ship->passenger_blocks = pax;
	ship->cargo_blocks = cargo / 4;
	ship->lowberth_blocks   = low / 8;

	ship->col   = col;
	ship->row   = row;

	for(i=0; i<8; ++i) {
	   ship->turret[i].emplacement = 0;
	   ship->turret[i].deviceType = 0;
	   ship->turret[i].device = 0;
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

	puts(	"\n  select ship type:\n\n"
			"    (s) scout\n"
//			"    (j) sloop\n"
			"    (a) free trader\n"
//			"    (k) safari\n"
			"    (u) packet\n"
			// "    (e) escort\n"
			// "    (r) merchant\n"
			// "    (l) lab\n"
			// "    (y) donosev\n"
			// "    (t) patrol\n"
			// "    (p) corsair\n"
			// "    (v) corvette\n"
			// "    (m) liner\n"
			// "    (w) shivva\n"
			// "    (n) exploratory trader\n"
			// "    (c) cruiser\n"
			// "    (h) long liner\n"
			// "    (b) kinunir\n"
			// "    (g) frigate\n"
			// "    (d) leviathan\n"
			// "    (y) cargoliner\n"
			// "    (z) interdictor\n"
			// "    (f) freighter\n"
	);
	while(shipchoice == 0) {
		switch( shipchoice = cgetc() ) {
			case 'a':
	            player.turns_left = 60;
			   	setShip(&player.ship, "abu11", "beowulf", 10, 'b', 2, 1, 1, 82, 8, 10, 50, player.col, player.row);
				break;
			case 'u':
			    player.turns_left = 80;
				setShip(&player.ship, "ucs13", "ishillik", 10, 'b', 2, 1, 3, 80, 8, 10, 70, player.col, player.row);
				break;
			case 's':
				player.col = 24;
				player.row = 17;
				player.turns_left = 120;
			   	setShip(&player.ship, "saa22", "murphy",  11, 'b', 1, 2, 2,  4, 4,  4, 50, player.col, player.row);
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
	int i;

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
	fprintf(fp, "ship-tl: %d\n", player.ship.tl);
	fprintf(fp, "ship-name: %s\n", player.ship.name);
	fprintf(fp, "ship-cost: %d\n", player.ship.cost);
	fprintf(fp, "ship-builder: %c\n", player.ship.builder);
	fprintf(fp, "ship-hardpoints: %d\n", player.ship.hardpoints);
	fprintf(fp, "ship-status: %d\n", player.ship.status);
	fprintf(fp, "ship-m: %d\n", player.ship.m);
	fprintf(fp, "ship-j: %d\n", player.ship.j);
	fprintf(fp, "ship-ar: %d\n", player.ship.ar);
	fprintf(fp, "ship-passenger-blocks: %d\n", player.ship.passenger_blocks);
	fprintf(fp, "ship-cargo-blocks: %d\n", player.ship.cargo_blocks);
	fprintf(fp, "ship-lowberth-blocks: %d\n", player.ship.lowberth_blocks);
	fprintf(fp, "ship-col: %d\n", player.ship.col);
	fprintf(fp, "ship-row: %d\n", player.ship.row);

	for(i=0; i<8; ++i) {
	   fprintf(fp, "turret-%d: e=%u t=%u d=%u\n", 
	    i,
	   	player.ship.turret[i].emplacement,
	   	player.ship.turret[i].deviceType,
	   	player.ship.turret[i].device);
	}

	fclose(fp);
}

