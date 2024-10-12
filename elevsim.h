// elevsim.h -- General header file for elevator simulation

#ifndef __ELEVSIM_H
#define __ELEVSIM_H     1     // Prevent multiple #includes

/* -- Various constants. Don't change these. */

#define FALSE 0         // Value meaning false
#define TRUE 1          // Value meaning true
#define UP 1            // Value for direction == up
#define DOWN -1         // Value for direction == down
#define NODIRECTION 0   // Value for direction == none
#define ESCKEY 27       // ASCII value for <Esc> key

/* -- Other constants. Okay to change with care. MAXPERSONS is
limited by available memory--you may not be able to increase this
value much beyond 1000 or so. Also, be sure to keep MAXELEVS and
MAXFLOORS within the ranges stated in the comments below. Values
outside of these ranges may work, but too many floors or elevators 
will turn the simulation's display to mush. */

#define MAXELEVS 10     // Number of elevators (1 to 10 only)
#define MAXFLOORS 10    // Number of floors (2 to 10 only)
#define MAXPERSONS 750  // Maximum people in building
#define ELEVWAIT 15     // Min. seconds to wait at floors
#define CAPACITY 24     // Maximum people in an elevator
#define TRAVELTIME 5    // Seconds to travel between floors

/* -- Formulas using rand() function to make various decisions.  Feel
free adjust these values to alter the simulation. WANTS_TO_ENTER
controls how frequently people enter the building. ENTER_DEST selects
the destination floor which must be within 1 to MAXFLOORS - 1.
MAX_WAIT determines how many seconds a person will wait for an
elevator before getting fed up and taking the stairs. BUSINESS
controls how many seconds people spend at their destination floors
before going elsewhere or leaving the building. LEAVING controls
whether a person will leave or go to another floor--it's currently
set to force people to decide to leave about 2/3 the time. */

#define WANTS_TO_ENTER  rand() < RAND_MAX/3
#define ENTER_DEST      1 + (rand() % (MAXFLOORS - 1))
#define MAX_WAIT        60 + (rand() % 120)
#define BUSINESS        40 + (rand() % 60)
#define LEAVING         (rand() < 2*(RAND_MAX/3))

/* -- Global variable declarations. These variables are defined in
elevsim.cpp and are the only global variables in the program except
for the building object (see elevsim.cpp). The program uses these
values to display the simulation statistics on the bottom line. All
other program variables are class variables or are local to class
functions. */

extern unsigned totalPeople;     // Number of people handled
extern unsigned inBuilding;      // People in building now
extern unsigned leftBuilding;    // People who left building
extern unsigned avgWait;         // Average no. people waiting
extern unsigned avgRide;         // Average no. people in elevators
extern unsigned tookStair;       // Number people who walked
extern unsigned totalTime;       // Seconds simulation has run

#endif   // __ELEVSIM_H


// Copyright (c) 1990 by Tom Swan. All rights reserved
// Revision 1.00   Date: 09/18/1990   Time: 09:20 am
