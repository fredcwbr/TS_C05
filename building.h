// building.h -- Header file for building.cpp

#ifndef __BUILDING_H
#define __BUILDING_H    1     // Prevent multiple #includes

#include "action.h"
#include "person.h"
#include "floor.h"
#include "elevator.h"

class building : public action {
   private:
      persCollection thePersons;    // People in the system
      floorCollection theFloors;    // Floors in the building
      elevCollection theElevators;  // Elevators in the building
   public:
	  
      int continues(void);
      void perform(void);
      void display(void);
};

#endif   // __BUILDING_H


// Copyright (c) 1990 by Tom Swan. All rights reserved
// Revision 1.00   Date: 09/18/1990   Time: 08:59 am
