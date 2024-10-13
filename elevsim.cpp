// elevsim.cpp -- Elevator simulation in C++

#include <iostream>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "tsargs.h"


void initDisplay(void);

#include "disp.h"
#include "building.h"


int MAXELEVS = DFLT_MAXELEVS;     // Number of elevators (1 to 10 only)
int MAXFLOORS = DFLT_MAXFLOORS;    // Number of floors (2 to 10 only)
int MAXPERSONS = DFLT_MAXPERSONS;   // Maximum people in building
int ELEVWAIT = DFLT_ELEVWAIT;      // Min. seconds to wait at floors
int CAPACITY = DFLT_CAPACITY;      // Maximum people in an elevator
int TRAVELTIME = DFLT_TRAVELTIME;    // Seconds to travel between floors
int TICDELAY  = DFLT_TICDELAY;    // Simultation iteration delay (0.1s) ;
unsigned SIMTIME = 600;

/* -- Function prototype used only by main() */

simWindow wndSim;

/* -- Global variables. These are the only global variables used by
the simulation. Except for the main building object (theAction), the 
variables hold the statistics displayed on the bottom line. */

unsigned totalPeople;      // Number of people handled
unsigned inBuilding;       // People in building now
unsigned leftBuilding;     // People who left building
unsigned avgWait;          // Average no. people waiting
unsigned avgRide;          // Average no. people in elevators
unsigned tookStair;        // Number people who walked
unsigned totalTime;        // Seconds simulation has run

building theAction;        // Building simulation object

/* -- Note: Enable one of the optional sleep() or msleep() statements
below to slow the simulation on a fast system. */

int main(int argc, char **argv)
{
int ch; 
   if( TSargs::init(argc,argv) == -1 ) exit( -1 );
	
   theAction.setTime(  SIMTIME  );
   srand(time(NULL));   // Randomize random-number generator
   initDisplay();       // Initialize the display
   theAction.display(); // Display the elevators and labels

	
/* -- This while-loop handles the entire simulation. It cycles
while the building object (named theAction) returns true through
its `continues()' function. */

   while (theAction.continues()) {
	   if( TICDELAY > 0 ) 
		   usleep(TICDELAY * 100000 );
    // 1 real second == 1 simulated second
	//      msleep(250);       // 1/4 real second = 1 simulated second
	//      msleep(125);       // 1/8 real second = 1 simulated second
      theAction.perform(); // Perform all simulation actions
      theAction.display(); // Update the display
   }

/* -- Perform an orderly exit. */

   // disp_move(24, 0);    // Position cursor on last line
   // disp_showcursor();   // Make cursor visible
   // disp_close();        // Close display package
	
   return(0);             // Exit with no errors to report
}

/* -- Initialize the display, showing various labels that remain
unchanged throughout the simulation. Also initialize the Zortech
display package for fast screen writes. */

void initDisplay(void)
{
   int i;

   wndSim.disp_open();               // Initialize display package
   wndSim.disp_move(0, 0);           // Move to "home" position
   wndSim.disp_eeop();               // Clear the display
   wndSim.disp_hidecursor();         // Make cursor invisible
   wndSim.disp_move(21, 30);         // Display title line
   wndSim.disp_puts( "Elevator Simulation from Learning C++ by Tom Swan");
   wndSim.disp_startstand();         // Begin reversed-video display
   wndSim.disp_move(0, 0);
   wndSim.disp_puts("Floors    ");
   for (i = 0; i < 10; i++)   // Show reversed video floor
      wndSim.disp_puts("  0    ");   //  numbers at top of screen
	  
   wndSim.disp_move(22, 0);
   wndSim.disp_puts(" Total       In     Left  Avg #   Avg #      ");
   wndSim.disp_puts("Took  Num  Num   Seconds   Elapsed");
   wndSim.disp_move(23, 0);
   wndSim.disp_puts("People     Bldg     Bldg  Waiting Riding    ");
   wndSim.disp_puts("Stair  Elv  Flr      Left      Time");
   wndSim.disp_endstand();           // End reversed-video display
   wndSim.disp_move(1, 0);
   for (i = 0; i < 10; i++)   // Display horzontal divider line
      wndSim.disp_puts("--------");
	  ;

/* -- Display elevator cables. These are redrawn by the elevator
class as needed while elevators move. */

   for (int row = 2; row < 18; row++) {
      for (int col = 0; col < MAXELEVS; col++) {
         wndSim.disp_move(row, 12 + (col * 7));
         wndSim.disp_putc(':');
      }
   }
}


// Copyright (c) 1990 by Tom Swan. All rights reserved
// Revision 1.00    Date: 09/18/1990   Time: 09:16 am


