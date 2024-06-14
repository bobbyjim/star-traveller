#ifndef _PLAYERS_H_
#define _PLAYERS_H_

#include "ship.h"

typedef struct {
	char          name[15]; // 14 chars max name
	unsigned long kilocredits;
	int           col: 8;
	int           row: 8;
	// additional player-specific attribs
	Ship 		  ship;
} Player;

void player_register();
unsigned char player_login();

#endif
