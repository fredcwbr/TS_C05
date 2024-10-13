// elevator.h -- Header file for elevator.cpp

#ifndef __ELEVATOR_H
#define __ELEVATOR_H    1     // Prevent multiple #includes

#include "elevsim.h"
#include "floor.h"
#include "person.h"

class elevator {
   private:
      int elevNumber;         // Elevator's number
      int timeToAction;       // Time in secs until next action
      int floorNumber;        // Current floor number
      int stopped;            // 1 == stopped at floor
      int direction;          // 1 == up, -1 == down, 0 == none
      int *buttons; // Flr buttons (0 == off, 1 == on)
      int passengers;         // Number of passengers on board
      int buttonUp(void);
      int buttonDown(void);
   public:
      elevator();
      int getPassengers(void) { return passengers; }
      void setelevNumber(int n);
      void showElevator(void);
      void setDirection(floorCollection &theFloors);
      int elevStopping(floorCollection &theFloors);
      void action(floorCollection &theFloors, 
         persCollection &thePersons);
};

class elevCollection {
   private:
      elevator *ea;  // Array of elevator objects
   public:
      elevCollection();
      void showElevators(void);
      void action(floorCollection &theFloors, 
         persCollection &thePersons);
      int avgRiding(void);
};

#endif   // __ELEVATOR_H


// Copyright (c) 1990 by Tom Swan. All rights reserved
// Revision 1.00    Date: 09/18/1990   Time: 09:11 am
