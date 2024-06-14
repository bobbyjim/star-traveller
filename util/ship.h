#ifndef _SHIP_H_
#define _SHIP_H_

#include <stdint.h>

typedef struct {

	uint8_t type;
	uint8_t quantity;
	uint16_t value;

} CargoItem;

#define MAX_CARGO_ITEMS 10

typedef struct {

	char qsp[6];					// 6b quick-ship profile
	char name[14];					// 13b ship name + null
	int  tl :8;						// 1b tech level
	char builder;					// 1c builder code
	int  m :4;						// 4 bits maneuver rating
	int  j :4;						// 4 bits jump rating
	int  jump_fuel_capacity :4;		// 4 bits jump fuel capacity
	int  jump_fuel_carried  :4;		// 4 bits actual fuel carried
	int  cargo_hold :8;				// 1b cargo capacity
	int  passengers :8;				// 1b passenger capacity
	int  low_berths :8;				// 1b low berths
	int  ar     :8;					// 1b armor rating
	int  cost   :8;					// 1b cost in 10 MCr units
	int  status :8;					// status (in starport, in shipyard, at GG, at belt, etc)
	int  col    :8;					// hex map col
	int  row    :8;					// hex map row
	
	CargoItem cargo[MAX_CARGO_ITEMS];

} Ship;

void ship_travel();

#endif
