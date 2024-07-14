#ifndef _TRADE_H_
#define _TRADE_H_

#define MAX_CARGO_LOTS  24
#define NUM_TRADE_GOODS 21
#define NUM_WORLDS		439

typedef struct {
	int type    :5;
	int tonnage :7;
	int spare   :4;
	int cost    :16;
} CargoLot;

void determineSpeculativeGood();

#endif