#include <stdio.h>

#include "gamestate.h"

#define     GAMESTATE_FILENAME      "game.dat"

GameState gameState;

GameState* getGameState() { return &gameState; }

void gamestate_nextTurn() {
	gameState.currentTurn++;
//	gameState.currentTurn %= MAX_PLAYERS;  // no we won't do it this way
    gamestate_save();
}

void gamestate_save() {
    FILE* file = fopen(GAMESTATE_FILENAME, "wb");
    fwrite(&gameState, sizeof(GameState), 1, file);
    fclose(file);
}

void gamestate_load() {
    FILE* file = fopen(GAMESTATE_FILENAME, "rb");
    fread(&gameState, sizeof(GameState), 1, file);
    fclose(file);
}
