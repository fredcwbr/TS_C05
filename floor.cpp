// floor.cpp -- Floor class module

// #include "disp.h"
#include "floor.h"

#include "disp.h"

extern simWindow wndSim;

/* -- The floor class constructor. This function initializes an
object (variable) of the floor class. Note: The collection of floors
is expected to assign a floor number to each floor in a building.
Until that happens, the floorNumber field is uninitialized. */

floor::floor()
{
   up = down = np = 0;    // Reset up and down buttons
}

/* -- Display a representation of this floor, showing its number and
the state of its up and down buttons. */

void floor::showFloor(persCollection &thePersons)
{
   int col = 0;
   int row = 20 - (floorNumber * 2);
   char uc = '-';
   char dc = '-';
   int nup, ndn;     // Number of persons going up and down
   
/* -- Get number of persons waiting on floor going up or down. */

   thePersons.numWaiting(floorNumber, nup, ndn);
   np = nup + ndn;
   if (nup > 0) setUpButton();      // Sense up button push
   if (ndn > 0) setDownButton();    // Sense down button push
   if (up) uc = 'U';                // Init up and down symbols
   if (down) dc = 'D';              //  for the display

/* -- Display information for this floor. */

   wndSim.disp_move(row , col);	
   wndSim.disp_printf("%02d:%c%c%03d", floorNumber, uc, dc, np );
	
}

/* -- Turn on the floor's up button, signaling that someone is 
waiting for an elevator to travel to a higher floor. The up button on
the top floor is permanently off. */

void floor::setUpButton(void)
{
   if (floorNumber < MAXFLOORS - 1)
      up = 1;
}

/* -- Turn on the floor's down button, signaling that someone is 
waiting for an elevator to travel to a lower floor. The down button
on the ground floor is permanently off. */

void floor::setDownButton(void)
{
   if (floorNumber > 0)
      down = 1;
}

/* -- The constructor for a floorCollection object. This function
initializes all floor objects in a collection--in other words, all of
the floors in the building. */

floorCollection::floorCollection()
{
   for (int i = 0; i < MAXFLOORS; i++)
      fa[i].setFloorNumber(i);   // Assign floor numbers
}

/* -- Call showFloor() function for every floor. This function
updates the display for all floors in the building. */

void floorCollection::showFloors(persCollection &thePersons)
{
   for (int i = 0; i < MAXFLOORS; i++)
      fa[i].showFloor(thePersons);
}

/* -- Reset the up or down button for this floor */

void floorCollection::resetButton(int direction, int floorNumber)
{
   if (direction == UP)
      fa[floorNumber].resetUpButton();
   else if (direction == DOWN)
      fa[floorNumber].resetDownButton();
}

/* -- Return true if there are any floors above the specified floor
signaling for an elevator in any direction. */

int floorCollection::signalUp(int floorNumber)
{
   for (int i = MAXFLOORS - 1; i > floorNumber; i--) 
      if (fa[i].upButton() || fa[i].downButton())
         return TRUE;
   return FALSE;
}

/* -- Return true if there are any floors below the specified floor
signaling for an elevator in any direction. */

int floorCollection::signalDown(int floorNumber)
{
   for (int i = 0; i < floorNumber; i++) 
      if (fa[i].upButton() || fa[i].downButton())
         return TRUE;
   return FALSE;
}

/* -- Return true if a button in the specified direction (up or down)
is pressed on this floor. Elevators use this function to help decide
whether to stop at a floor. Returns false if no buttons are pressed
or if direction is not set. */

int floorCollection::signalSameDir(int direction, int floorNumber)
{
   if (direction == UP)
      return fa[floorNumber].upButton();
   else if (direction == DOWN)
      return fa[floorNumber].downButton();
   else
      return FALSE;
}

/* -- Return average number of people now waiting on all floors for
an elevator in any direction. */

int floorCollection::avgWaiting(void)
{
   int total = 0;

   for (int i = 0; i < MAXFLOORS; i++)
      total += fa[i].getNumWaiting();
   return (total / MAXFLOORS);
}


// Copyright (c) 1990 by Tom Swan. All rights reserved
// Revision 1.00    Date: 09/18/1990   Time: 09:40 am
