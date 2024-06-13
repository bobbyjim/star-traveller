#ifndef _EMPLACEMENT_H_
#define _EMPLACEMENT_H_

typedef struct {

	int heat   :1;
	int pen    :1;
	int rad    :1;
	int screen :1;
	int sensor :1;
	int globe  :1;
	int r1     :1;
	int r2     :1;
	char name[29];
	unsigned char tl;
	unsigned char mcr;

} Loadout;

#endif