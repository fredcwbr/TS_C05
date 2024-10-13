// person.h -- Header file for person.cpp

#ifndef __PERSON_H
#define __PERSON_H      1     // Prevent multiple #includes

#include "elevsim.h"

class person {
   private:
      int floorNowOn;      // Floor (-1 if outside)
      int destination;     // Destination floor number
      int maxWaitTime;     // Aggravation level
      int waitingForElev;  // True (1) if waiting
      int takingStairs;    // True (1) if walking
      int elevNowIn;       // Elevator number (-1 if none)
   public:
      person();
      void action(void);
      int upwaiting(int floorNumber);
      int dnwaiting(int floorNumber);
      int loadIfWaiting(int elevNumber, 
         int floorNumber, int &pdest);
      int loadIfGoing(int elevNumber, 
         int floorNumber, int direction, int &pdest);
      int discharge(int elevNumber, int floorNumber);
};

class persCollection {
   private:
      person *pa;  // Array of person objects
   public:
	  persCollection();
	  ~persCollection();
      void action(void);
      void numWaiting(int floorNumber, int &nup, int &ndn);
      int loadAny(int elevNumber, 
         int floorNumber, int &pdest);
      int loadOne(int elevNumber, 
         int floorNumber, int direction, int &pdest);
      int discharge(int elevNumber, int floorNumber);
};

#endif   // __PERSON_H


// Copyright (c) 1990 by Tom Swan. All rights reserved
// Revision 1.00    Date: 09/18/1990   Time: 09:47 am
