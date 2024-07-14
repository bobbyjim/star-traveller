#ifndef _PLAYERS_H_
#define _PLAYERS_H_

#include "ship.h"
#include "player.h"

typedef struct {

	uint8_t type;
	uint8_t quantity;
	uint16_t value;

} CargoItem;

#define MAX_CARGO_ITEMS 10

typedef struct {
	char          name[15]; // 14 chars max name
	unsigned long kilocredits;
	int           col: 5;
	int           row: 6;
	int			  turns_left: 8;

	// additional player-specific attribs
	Ship 		  ship;
	CargoItem cargoManifest[MAX_CARGO_ITEMS];

} Player;

int player_loadActive();
void player_save();

#endif
