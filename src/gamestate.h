#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "player.h"

#define	MAX_PLAYERS		16

typedef struct {

    int date        : 16;
	int historyTop  : 7;
	int junk        : 9;
    char playerNames[MAX_PLAYERS][15];

} GameState;

void gamestate_nextTurn();
void gamestate_save();
void gamestate_load();

#endif
