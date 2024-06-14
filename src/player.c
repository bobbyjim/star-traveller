#include <stdio.h>

#include "player.h"

#define		PLAYER_ACTIVE_FILENAME		"active.p"

void player_loadActive(Player* player)
{
	char activeFilename[16];
	FILE* fp = fopen(PLAYER_ACTIVE_FILENAME, "r");
	fscanf(fp, "%s", &activeFilename);
	fclose(fp);

	fp = fopen(activeFilename, "rb");
	fread(player, sizeof(Player), 1, fp);
	fclose(fp);
}
