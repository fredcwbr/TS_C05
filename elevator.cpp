// elevator.cpp -- Elevator class module

// #include <disp.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "elevator.h"
#include "disp.h"

extern simWindow wndSim;

/* -- The elevator class constructor. This function runs for each
elevator variable as it comes into being. It initializes the
elevator's location, number of people on board, etc. */

elevator::elevator()
{
   elevNumber = -1;           // Elevator number not assigned
   timeToAction = ELEVWAIT;   // Time elevator waits at floor
   floorNumber = 0;           // Current floor number
   stopped = 1;               // Elevator is stopped at floor
   direction = NODIRECTION;   // Elevator direction not set
   passengers = 0;            // No passengers on board
   
/* -- Reset all floor buttons inside elevator. */

   for (int i = 0; i < MAXFLOORS; i++)
      buttons[i] = 0;
}

/* -- Assign number to this elevator. The first elevator must be
number 0, the next 1, and so on. These numbers are not displayed. */

void elevator::setelevNumber(int n)
{
   elevNumber = n;
}

/* -- Return true if there are any buttons inside the elevator
pressed for floors above the current floor. Elevators use this
function to determine whether there are passengers traveling to
higher floors. */

int elevator::buttonUp(void)
{
   for (int i = floorNumber + 1; i < MAXFLOORS; i++)
      if (buttons[i]) return TRUE;
   return FALSE;
}

/* -- Return true if there are any buttons inside the elevator
pressed for floors below the current floor. Elevators use this
function to determine whether there are passengers traveling to
lower floors. */

int elevator::buttonDown(void)
{
   for (int i = 0; i < floorNumber; i++)
      if (buttons[i]) return TRUE;
   return FALSE;
}

/* -- Display this elevator, showing its direction, the number of
people travelling up and down, and the elevator cable. */

void elevator::showElevator(void)
{
   int row = 20 - (floorNumber * 2);   // Display row 
   int col = 10 + (elevNumber * 7);    // Display column

	
   if (floorNumber < MAXFLOORS - 2) {
	  // ** Converter para ncurses
      wndSim.disp_move(row - 3, col);
      wndSim.disp_puts("  :  ");              // Display elevator cable
   }
   if (floorNumber < MAXFLOORS - 1) {
      wndSim.disp_move(row - 2, col);
      wndSim.disp_puts("  :  ");              // Display more cable
      wndSim.disp_move(row - 1, col);
      wndSim.disp_puts("__:__");              // Display elevator roof
   }
   wndSim.disp_startstand();                  // Start reversed video
   wndSim.disp_move(0, col + 2);
   wndSim.disp_printf("%d", floorNumber);     // Floor # at top of screen
   // printf( "Piso %d: Elev %d", floorNumber, elevNumber );

   // disp_move(row, col);
   if (direction == UP) {                // Display direction
      wndSim.disp_puts("Up ");
      // printf(" Up " );
   } else if (direction == DOWN) {
      wndSim.disp_puts("Dn ");
	  //  printf(" Dn ");
   } else {
      wndSim.disp_puts("-- ");
	  // printf(" -- ");
   }
   wndSim.disp_move(row , col + 1);	
   wndSim.disp_printf("%02d", passengers);    // Number of passengers
   // printf("%02d\n" , passengers );
   wndSim.disp_endstand();                    // End reversed video
   if (floorNumber > 0) {
      wndSim.disp_move(row + 2, col);         // Erase old elevator so
      wndSim.disp_puts("     ");              //  it appears to move
      wndSim.disp_move(row + 1, col);
      wndSim.disp_puts("     ");
   }

}

/* -- Decide on the direction the elevator should travel next. */

void elevator::setDirection(floorCollection &theFloors)
{
   if (buttonUp()) direction = UP;
   else if (buttonDown()) direction = DOWN;
   else if (theFloors.signalUp(floorNumber)) direction = UP;
   else if (theFloors.signalDown(floorNumber)) direction = DOWN;
   else direction = NODIRECTION;
}

/* -- Decide whether elevator should stop at the current floor. */

int elevator::elevStopping(floorCollection &theFloors)
{
   if (buttons[floorNumber]) 
      return TRUE;            // Passengers getting off
   else if (theFloors.signalSameDir(direction, floorNumber))
      return TRUE;            // Persons waiting for elevator
   else if (floorNumber == 0)
      return TRUE;            // Stop at ground floor
   else if (floorNumber == MAXFLOORS - 1)
      return TRUE;            // Stop at highest floor
   else if (direction == NODIRECTION)
      return TRUE;            // No signals above or below
   else
      return FALSE;           // Keep moving
}

/* -- Perform all required actions for this elevator. This function
runs once for every tick of the simulation's clock. */

void elevator::action(floorCollection &theFloors, 
   persCollection &thePersons)
{
   int pdest;           // A person's destination
   int newdirection;    // New direction for elevator

/* -- Take care of actions for an elevator stopped at a floor. The
"else" clause to this statement handles actions for elevators
currently moving between floors. If elevator is stopped, the first job
is to discharge any passengers travelling to this floor. */

   if (stopped) {
      passengers -= thePersons.discharge(elevNumber, floorNumber);

/* -- If the direction is not set (nobody on board), load one person
and set the direction to that person's destination. In other words,
if the elevator doesn't know where it's going, the first person to
get on board decides the elevator's direction. */

      if ((direction == NODIRECTION) && (passengers < CAPACITY)) {
         if (thePersons.loadAny(elevNumber, floorNumber, pdest)) {
            passengers++;              // Count passenger
            timeToAction++;            // Takes time to get in
            buttons[pdest] = 1;        // Press destination button
            if (pdest > floorNumber)   // First person on board
               direction = UP;         //  sets elevator's direction
            else
               direction = DOWN;
         }
      }

/* -- If the direction is set (there's at least one person on board,)
pick up additional passengers waiting to go in that same direction.
Stop doing this when elevator becomes full. It takes some time to
load one person, so add 1 second to elapsed time. */

      if ((direction != NODIRECTION) && (passengers < CAPACITY)) {
         if (thePersons.loadOne(elevNumber, 
         floorNumber, direction, pdest))  // Then if another person
         {                                //  climbs on board...
            passengers++;                 // Count the newcomer
            timeToAction++;               // Takes time to get in
            buttons[pdest] = 1;           // Press dest. button
            if (passengers >= CAPACITY)   // Leave immediately if
               timeToAction = 0;          //  elevator is full
         }
      }

/* -- If ready to start moving (elapsed time is 0 or less), perform
final actions before leaving for the next floor. For instance, If the
direction is still not set, then there are no passengers on board. In
that case, look for signals from other floors. If there are no
signals, head down unless on ground floor. If a new direction is
selected, reset the floor's up or down button and start moving. */

      if (timeToAction-- <= 0) {
         if (direction == NODIRECTION)
            setDirection(theFloors);
         if ((direction == NODIRECTION) && (floorNumber > 0))
            direction = DOWN;
         if (direction == NODIRECTION)
            timeToAction = ELEVWAIT;      // Stay at floor 0
         else {                           // Ready to start moving
            theFloors.                    // Reset floor up or
               resetButton(direction,     //  down button
               floorNumber);
            stopped = 0;                  // Tell elevator to move
            timeToAction = TRAVELTIME;    // Set time to next floor
         }
      }
   }
   else if (timeToAction-- <= 0) {     // If moved to next floor
      if (direction == UP)             // Change floor number
         floorNumber++;                //  to go up,
      else
         floorNumber--;                //  or down.
      setDirection(theFloors);         // Decide direction
      if (elevStopping(theFloors)) {   // If elevator should stop
         theFloors.                    // Reset floor up or
            resetButton(direction,     //  down button.
            floorNumber);
         stopped = 1;                  // Stop the elevator
         timeToAction = ELEVWAIT;      // Set wait time
         buttons[floorNumber] = 0;     // Reset button in elevator
      } else
         timeToAction = TRAVELTIME;    // Else keep moving
   }
}

/* -- Elevator collection constructor. Runs when a variable of type
elevCollection comes into being. */

elevCollection::elevCollection()
{
   for (int i = 0; i < MAXELEVS; i++)
      ea[i].setelevNumber(i);          // Assign elevator numbers
}

/* -- Display all elevators in the building. Calls showElevator
function for every elevator object. */

void elevCollection::showElevators(void)
{
   for (int i = 0; i < MAXELEVS; i++)
      ea[i].showElevator();
}

/* -- Call action() function for every elevator. This function runs
for every tick of the simulation's clock. */

void elevCollection::action(floorCollection &theFloors, 
   persCollection &thePersons)
{
   for (int i = 0; i < MAXELEVS; i++)
      ea[i].action(theFloors, thePersons);
}

/* -- Return average number of passengers riding in all elevators. */

int elevCollection::avgRiding(void)
{
   int total = 0;

   for (int i = 0; i < MAXELEVS; i++)
      total += ea[i].getPassengers();
   return (total / MAXELEVS);
}


// Copyright (c) 1990 by Tom Swan. All rights reserved
// Revision 1.00    Date: 09/18/1990   Time: 09:09 am
