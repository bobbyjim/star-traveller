#include <stdio.h>

#include "gamestate.h"

GameState gameState;

GameState* getGameState() { return &gameState; }

void gamestate_nextTurn() {
	gameState.currentTurn++;
	gameState.currentTurn %= MAX_PLAYERS;
}

void gamestate_save(const char* filename) {
    FILE* file = fopen(filename, "wb");
    fwrite(&gameState, sizeof(GameState), 1, file);
    fclose(file);
}

void gamestate_load(const char* filename) {
    FILE* file = fopen(filename, "rb");
    fread(&gameState, sizeof(GameState), 1, file);
    fclose(file);
}
