#ifndef _PLAYERS_H_
#define _PLAYERS_H_


typedef struct {
	char          name[15]; // 14 chars max name
	unsigned long kilocredits;
	int           row: 8;
	int           col: 8;
	// additional player-specific attribs
} Player;

void player_register();
unsigned char player_login();

#endif
