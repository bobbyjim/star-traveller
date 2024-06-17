#include <stdio.h>

#include "player.h"

#define		PLAYER_ACTIVE_FILENAME		"active.p"

extern Player player;

char activeFilename[16];

void player_loadActive()
{
	FILE* fp = fopen(PLAYER_ACTIVE_FILENAME, "r");
	fscanf(fp, "%s", &activeFilename);
	fclose(fp);

	fp = fopen(activeFilename, "rb");
	fread(&player, sizeof(Player), 1, fp);
	fclose(fp);
}

void player_save()
{
	FILE* fp = fopen(activeFilename, "wb");
	fwrite(&player, sizeof(Player), 1, fp);
	fclose(fp);
}
