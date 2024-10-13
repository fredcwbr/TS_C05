// person.cpp -- Person class module

#include <stdlib.h>
#include "person.h"

/* -- The person class constructor. Runs when a person object comes
into being. Assigns defauts values to person data fields. */

person::person()
{
   floorNowOn = -1;     // Not in the building
   waitingForElev = 0;  // Not waiting for an elevator
   destination = -1;    // No destination assigned
   maxWaitTime = 0;     // Not waiting until next action
   takingStairs = 0;    // Not walking the stairs
   elevNowIn = -1;      // Not in any elevator
}

/* -- Perform an action for this person. Called once for every tick
of the simulation's clock. */

void person::action(void)
{
   
/* -- Decide whether a person outside should enter building. */
 
   if (floorNowOn < 0) {               // If not in bldg
      if (WANTS_TO_ENTER) {            // Decide to enter
         destination = ENTER_DEST;     // Select destination
         floorNowOn = 0;               // Enter on ground floor 
         maxWaitTime = MAX_WAIT;       // Set aggravation level
         waitingForElev = 1;           // Person is waiting
         takingStairs = 0;             // Not taking stairs
         elevNowIn = -1;               // Not inside an elevator
         totalPeople++;                // Count people handled
         inBuilding++;                 // Count people in bldg
      }

/* -- If person is inside and waiting for an elevator, depending on
the person's aggravation level, decide whether to take the stairs and
walk to the destination floor. */

   } else {                            // If in bldg
      if (waitingForElev) {            // If inside and waiting
         if ((maxWaitTime--) <= 0) {   // Mark time waiting
            waitingForElev = 0;        // Tired of waiting
            takingStairs = 1;          // Take stairs instead
            maxWaitTime =              // 30 secs per floor
               30 * abs(destination - floorNowOn);
            tookStair++;               // Count people who walk
         }
      }

/* -- If person is inside and is walking up or down the stairs, check
if that person has arrived. If so, set the amount of time the person
will spend on this floor. */

      else if (takingStairs) {
         if ((maxWaitTime--) <= 0) {   // Mark time walking
            floorNowOn = destination;  // Reached destination
            takingStairs = 0;          // Not walking on stairs
            maxWaitTime = BUSINESS;    // Time on this floor
         }
      }

/* -- If a person is not inside an elevator, that person must be on a
floor taking care of business. Check whether the person is done and
select another destination. Most people will decide to leave the
building, but some will travel to another floor. */

      else if (elevNowIn < 0) {        // If not inside an elevator
         if ((maxWaitTime--) <= 0) {   // Mark time on floor
            if (LEAVING)               // Most people will want
             destination = 0;          //  to leave on floor 0
            else                       // Some will travel to
             destination = ENTER_DEST; //  another floor
            if (destination == floorNowOn) // Don't let people
               destination = 0;            // travel to same floor
            maxWaitTime = MAX_WAIT;    // Set aggravation level
            waitingForElev = 1;        // Person is waiting
         }
      }

/* -- Check for any person who is in the building, has arrived at the
ground floor, and is ready to leave the building. */

      if ((floorNowOn == 0) && (destination == 0)) {
         floorNowOn = -1;              // Send person outside
         leftBuilding++;               // Count people leaving
         inBuilding--;                 //  and no longer in bldg
      }
   }
}

/* -- Return true if this person is now waiting for an up elevator at
the specified floor number. */

int person::upwaiting(int floorNumber)
{
   return ((waitingForElev           ) && 
           (floorNowOn == floorNumber) &&
           (destination > floorNowOn ));
}

/* -- Return true if this person is now waiting for a down elevator
at the specified floor number. */

int person::dnwaiting(int floorNumber)
{
   return ((waitingForElev           ) && 
           (floorNowOn == floorNumber) &&
           (destination < floorNowOn ));
}

/* -- Have person enter elevator if waiting for an elevator on this
floor regardless of direction. (Elevator is empty and the person will
determine its direction.) Return the person's destination in pdest to
simulate that person pressing one of the elevator's floor buttons. */

int person::loadIfWaiting(int elevNumber, 
   int floorNumber, int &pdest)
{
   if (waitingForElev && (floorNowOn == floorNumber)) {
      waitingForElev = 0;     // Not waiting any longer
      elevNowIn = elevNumber; // Save elevator number
      pdest = destination;    // Pass person's destination back
      return TRUE;            // Person got on board
   }
   return FALSE;              // Person did not get on board
}

/* -- Load person if waiting for an elevator going in the specified
direction. Return the person's destination in pdest to simulate that
person pressing one of the elevator's floor buttons. Similar to 
loadIfWaiting(), but loads only people going up or down. */

int person::loadIfGoing(int elevNumber, 
   int floorNumber, int direction, int &pdest)
{
   int pdir;      // Person's direction, up or down

   if (destination > floorNumber)
      pdir = UP;
   else
      pdir = DOWN;
   if (waitingForElev && (floorNowOn == floorNumber) && 
      (direction == pdir)) {
      waitingForElev = 0;
      elevNowIn = elevNumber;
      pdest = destination;
      return TRUE;
   }
   return FALSE;
}

/* -- If this person is in the specified elevator and is headed for
the designated floor number, make that person get off the elevator.
Return true if the person gets off; otherwise, return false. Set the
person's wait time to the number of seconds this person will remain
on the floor unless that floor is 0 in which case the person will
exit the building immediately. */

int person::discharge(int elevNumber, int floorNumber)
{
   if ((elevNowIn == elevNumber) && (destination == floorNumber)) {
      elevNowIn = -1;            // Get out of elevator
      floorNowOn = destination;  // Set floor person is on
      if (floorNowOn != 0)
         maxWaitTime = BUSINESS; // Set time to spend on floor
      return TRUE;               // Person got off elevator
   } else
      return FALSE;              // Person did not exit
}



persCollection::persCollection(){
	pa =  new person[MAXPERSONS] ;
	
}

persCollection::~persCollection(){
	delete( pa );
	
}


/* -- Call action() function for every person. Runs once for every
tick of the simulation's clock. */

void persCollection::action(void)
{
   for (int i = 0; i < MAXPERSONS; i++)
      pa[i].action();
}

/* -- Count number of persons waiting on a floor. Returns nup (number
of persons going up) and ndn (number of persons going down) on the
specified floor. */

void persCollection::numWaiting(int floorNumber, 
   int &nup, int &ndn)
{
   nup = ndn = 0;
   for (int i = 0; i < MAXPERSONS; i++) {
      nup += pa[i].upwaiting(floorNumber);
      ndn += pa[i].dnwaiting(floorNumber);
   }
}

/* -- Load any person waiting for an elevator at this floor number.
Return the person's destination in pdest so the elevator can begin
traveling in the necessary direction. Return true if a person is
loaded, else return false. If false, pdest is undefined. */

int persCollection::loadAny(int elevNumber, 
   int floorNumber, int &pdest)
{
   for (int i = 0; i < MAXPERSONS; i++)
      if (pa[i].loadIfWaiting(elevNumber, floorNumber, pdest))
         return TRUE;   // Person got on board
   return FALSE;        // No person got into an elevator
}

/* -- Load one person waiting for an elevator at this floor number,
and headed in the specified direction. Return true if a person is 
loaded, else return false. Similar to loadAny, but loads only persons
traveling in a specified direction. */

int persCollection::loadOne(int elevNumber, 
   int floorNumber, int direction, int &pdest)
{
   for (int i = 0; i < MAXPERSONS; i++)
      if (pa[i].loadIfGoing(elevNumber, 
         floorNumber, direction, pdest))
         return TRUE;   // Person got on board
   return FALSE;        // No person got into an elevator
}

/* -- Discharge all persons in this elevator who are traveling to
the specified floor. Return number of people who got off elevator. */

int persCollection::discharge(int elevNumber, int floorNumber)
{
   int n = 0;     // Number of people who get off elevator

   for (int i = 0; i < MAXPERSONS; i++)
      n += pa[i].discharge(elevNumber, floorNumber);
   return n;
}


// Copyright (c) 1990 by Tom Swan. All rights reserved
// Revision 1.00    Date: 09/18/1990   Time: 09:46 am
