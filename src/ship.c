#include <stdio.h>

#include "player.h"
#include "ship.h"
#include "astrogation.h"

extern Player player;

void ship_displayTurretSummary( int emplacementNumber ) {
   printf( "\nemplacement %u:\n"
           " - emplacement type: %u\n"
		   " - device type: %u\n"
		   " - device id: %u\n"
		   , emplacementNumber+1
		   , player.ship.turret[emplacementNumber].emplacement
		   , player.ship.turret[emplacementNumber].deviceType
		   , player.ship.turret[emplacementNumber].device
   );
}