#include <cbm.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "trade.h"

#define TO_MAIN_RAM     0
#define DEVICE_SDCARD   8

CargoLot cargo[MAX_CARGO_LOTS];
uint16_t freight_tonnage;

// WorldState* worlds = ((WorldState*)(0xa000));

// void saveWorldStates()
// {
// 	RAM_BANK = 4; // world bank
//     cbm_save( "world.dat", DEVICE_SDCARD, (void*)0xa000, sizeof(WorldState)*NUM_WORLDS); // 7024 bytes
// }

// void loadWorldStates()
// {
//     RAM_BANK = 4; // world bank
//     cbm_load( "world.dat", DEVICE_SDCARD, (void*)0xa000);
// }

void determineSpeculativeGood()
{
    int i = rand() % NUM_TRADE_GOODS;
}