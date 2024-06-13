#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "player.h"

#define	MAX_PLAYERS		255

typedef struct {

    char playerNames[MAX_PLAYERS][15];
	unsigned char currentTurn;
	unsigned char historyTop;

} GameState;

void gamestate_nextTurn();
void gamestate_save();
void gamestate_load();

#endif
