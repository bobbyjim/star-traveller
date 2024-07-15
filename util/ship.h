#ifndef _SHIP_H_
#define _SHIP_H_

#include <stdint.h>

//int ship_travel();
//void ship_displayTurretSummary( 1 );

typedef struct {

	int emplacement :3;	// Empty,  T1,     T2,    T3, B1, B2, Bay, LBay
	int deviceType  :2;	// None,   Weapon, Screen
	int device      :3;	//			Weapons: Laser, Missile, PA
						//			Screens: Sand,  Damper,  Black Globe

} Turret; // 1 byte

/*
  There are 32 ship types.
*/
typedef struct {

	char name[16];					// ship name + null
	int  m                  :4;
	int  j                  :4;

	int  bridge             :2;
	int  globe              :1;
	int  stealth            :1;
	int  advancedSensors    :1;
	int  feature3           :1;
	int  feature4           :1;
	int  feature5           :1;

    int  av                 :8;
	char qsp[7];					// quick-ship profile + null
	char builder; 

	int  cargo              :8;
	int  passengers         :8;
	int  lowBerths          :8;
    char allegiance[3];				// two chars plus null

	int  cost   			:8;		// cost in 10 MCr units

	char status;
    char spare[5];

	Turret turret[8]; 

} Ship;  // 48 bytes

/*
typedef struct {

	int shipType    	:5; // 24 types
	int col    			:5;	// hex map col
	int row    			:6;	// hex map row

	int status			:3;	// status (in starport, in shipyard, at GG, at belt, etc)
	int j 				:3; 
	int m          		:3; 
	int ar     			:5;	// armor rating
	int spare1			:2;

	int cargoBlocks		:8; // 0-1020 tons  (4 ton blocks = 4 tons cargo)	
	int passengerBlocks	:6; // 0-252 pax    (4 ton blocks = 1 passenger)
	int spare2			:2;

	int lowberthBlocks 	:5; // 0-248 berths (4 ton blocks = 8 low berths)
	int spare3			:11;

	Turret turrets[8]; 

	// CargoManifest[] goes in Player struct!

} CompressedShip; // 16 bytes
*/

typedef struct {

	int shipType 		:5;		// references Ship
	int col      		:5;
	int row      		:6;

	int status   		:3;
	int turretLoadout 	:2; 	// from predetermined turret loadouts
	int spare			:11;

} NPCShip;	// 4 bytes -> 2000 NPC ships fit into an NPC Ship Bank.

#endif
