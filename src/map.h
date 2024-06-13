#ifndef _MAP_H_
#define _MAP_H_


typedef struct {

	int col 	     :8;
	int row 	     :8;

	char name[12];
	
	int starport     :3;
	int              :1;
	int hasNavalBase :1;
	int hasScoutBase :1;
	int isAmberZone  :1;
	int isRedZone    :1;

	int allegiance   :3;
	int              :3;
	int hasBelt      :1;
	int hasGG        :1;

} MAP1;

typedef struct {

	int col		:8;
	int row 	:8;

	int isAg	:1;
	int isAs	:1;
	int isDe 	:1;
	int isFl 	:1;
	int isHe 	:1;
	int isHi 	:1;
	int isIc 	:1;
	int isIn 	:1;
	int isLo 	:1;
	int isNa 	:1;
	int isNi 	:1;
	int isPo 	:1;
	int isRi 	:1;
	int isVa 	:1;
	int isWa 	:1;
	int			:1;

	int         :8;
	int			:8;

	char uwp[10];

} MAP2;

#endif