#ifndef _TRADE_H_
#define _TRADE_H_

#define NUM_TRADE_GOODS 10
#define NUM_TRADE_CODES 15

typedef struct {
	char name[15];
	int tradeCodeRelation[NUM_TRADE_CODES];
} TradeGood;

#endif