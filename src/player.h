#ifndef _PLAYERS_H_
#define _PLAYERS_H_

#include "ship.h"
#include "player.h"

typedef struct {
	char          name[15]; // 14 chars max name
	unsigned long kilocredits;
	int           col: 8;
	int           row: 8;
	int			  turns_left: 8;

	// additional player-specific attribs
	Ship 		  ship;
} Player;

void player_loadActive(Player* player);

#endif
