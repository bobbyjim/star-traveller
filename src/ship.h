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

	char qsp[6];
	char name[14];
	int  tl :8;
	char builder;
	int  m :4;
	int  j :4;
	int  jump_fuel_capacity :4;
	int  jump_fuel_carried  :4;
	int  cargo_hold :8;
	int  passengers :8;
	int  low_berths :8;
	int  ar     :8;
	int  cost   :8;
	int  status :8;
	int  col    :8;
	int  row    :8;

	CargoItem cargo[MAX_CARGO_ITEMS];

} Ship;

int ship_travel();

#endif
