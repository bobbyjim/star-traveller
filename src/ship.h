#ifndef _SHIP_H_
#define _SHIP_H_

#include <stdint.h>

void ship_displayTurretSummary( int emplacementNumber );

typedef struct {

	int emplacement :3;	// Empty,  T1,     T2,    T3, B1, B2, Bay, LBay
	int deviceType  :2;	// None,   Weapon, Screen
	int device      :3;	//			Weapons: Laser, Missile, PA
						//			Screens: Sand,  Damper,  Black Globe
} Turret; // 1 byte

/*
  There are 24 Hull Types:

  #		Code	Name				Tonnage		Config	Hardpoints
  - 	-   	----------- 		----------- ------	----------
  0		S		Scout				100			L		1
  1		J		Sloop				100			L		1
  2		A		Trader				200			U 		2
  3		K		Safari				200			L		1
  4		U		Packet				300			S		2
  5		E		Escort				300			B		3
  6		R		Merchant			400			A		3
  7		L		Lab					400			C		2
  8		Y		Donosev				400			U		2
  9		T		Patrol 				400			A		4
  10	P		Corsair				400			U		4
  11	V		Corvette			500			A		5
  12	M		Liner				600			B		3
  13	W		Shivva				600			B		6
  14	N		Speculator			700			S		3
  15	C		Broadsword			800			S		8
  16	H		Long Liner			1000		U		3
  17	Q		Research			1000		C		3
  18	B		Kinunir				1200		A		8
  19	X		Transport			1400		U		2
  20	G		Frigate				1600		U		8
  20	D		Leviathan			1800		B		4
  22	Y		Cargoliner			2000		C		2
  23	Z		Interdictor			2200		U		8
  24	F		Freighter			2400		B		3
 
*/
typedef struct {

	char qsp[7];					// quick-ship profile + null
	int  tl 				:8;		// tech level
	char name[14];					// ship name + null

	int  cost   			:8;		// cost in 10 MCr units
	char builder;					// builder code

	int  spare1     		:1;
	int  hardpoints 		:3;		// 1-8
	int  status     		:4;		// status (in starport, in shipyard, at GG, at belt, etc)
	int  m 					:4;		// maneuver rating
	int  j 					:4;		// jump rating

	int  ar     			:8;		// armor rating
	int  passenger_blocks 	:8;		// passenger capacity (1 block = 4 tons)

	int  cargo_blocks 		:8;		// cargo capacity (1 block = 4 tons)
	int  lowberth_blocks 	:8;		// low berths (1 block = 4 tons)

	int  col    			:8;		// hex map col
	int  row    			:8;		// hex map row

	Turret turret[8]; 

} Ship; // 40 bytes

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
