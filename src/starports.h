#ifndef _STARPORTS_H_
#define _STARPORTS_H_

typedef struct {
	char class;
	int warehouseCapacity   : 4;
	int defenseLevel        : 3;
	int hasBlackMarket      : 1;

	int hasLuxuryGoodsMarket: 1;
	int hasExoticGoodsMarket: 1;
} Starport;

#endif