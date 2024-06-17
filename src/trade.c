#include "trade.h"

//                         1 = source, -1 = sink, and 0 = neither.
TradeGood tradeGoods[NUM_TRADE_GOODS] = {
	// trade good         ag  as  de  fl  he  hi  ic  in  lo  na  ni  po  ri  va  wa
	{ "consumables",    {  1, -1,  0, -1, -1,  0,  0,  0,  1, -1,  0,  1,  0, -1,  1}},
    { "data",           {  0, -1,  0,  0,  0,  1,  1, -1,  0,  0,  0,  0,  1,  0,  0}},
    { "entertainments", {  1,  0,  1, -1, -1,  1, -1,  0, -1,  0,  0, -1, -1,  0,  1}},
    { "high-tech",      {  0, -1,  0, -1, -1,  1, -1,  1,  0,  0,  0,  0,  0, -1, -1}},
    { "manufactureds",  { -1,  1,  1,  0,  1,  1,  0,  1, -1,  0, -1,  0, -1,  0,  0}},
    { "novelties",      {  0,  0,  0,  1,  0,  1,  0,  1,  0,  0,  0,  0, -1,  0,  0}},
    { "pharma",         {  1,  0,  1,  0,  0, -1,  0,  1,  0, -1, -1, -1, -1,  0,  1}},
    { "raw materials",  {  0,  1,  1,  1,  0,  0,  1, -1,  1,  1,  1,  1,  0,  1,  0}},
    { "samples",        {  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  1,  1}},
    { "scrap",          { -1,  1,  0,  0,  0,  1,  0, -1,  1,  0,  0,  1,  0,  0,  0}}	
};
