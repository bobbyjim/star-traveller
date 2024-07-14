#include <stdio.h>

#include "shipyard.h"
#include "player.h"
#include "ship.h"

// extern Player;

int shipyard_upgrade() {

	puts( "\n\nupgrade ship menu\n"
	      " m - change maneuver rating\n"
	      " j - change jump rating\n"
		  " r - rebalance cargo, passengers, and low berths\n"
	      " 1 - change turret 1\n"
	      " 2 - change turret 2\n"
	);
	ship_displayTurretSummary( 0 );
	ship_displayTurretSummary( 1 );

	return 0;
}