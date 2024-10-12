// floor.h -- Header file for floor.cpp

#ifndef __FLOOR_H
#define __FLOOR_H       1     // Prevent multiple #includes

#include "person.h"

class floor {
   private:
      int floorNumber;  // Lobby is floor 0
      int up, down;     // 1 = up or down buttons pressed
      int np;           // Number of people waiting for elev
   public:
      floor();
      void setFloorNumber(int n) { floorNumber = n; }
      int downButton(void) { return down; }
      int upButton(void) { return up; }
      void resetUpButton(void) { up = 0; }
      void resetDownButton(void) { down = 0; }
      int getNumWaiting(void) { return np; }
      void setUpButton(void);
      void setDownButton(void);
      void showFloor(persCollection &thePersons);
};

class floorCollection {
   private:
      floor fa[MAXFLOORS];    // Array of floor objects
   public:
      floorCollection();
      void showFloors(persCollection &thePersons);
      void resetButton(int direction, int floorNumber);
      int signalUp(int floorNumber);
      int signalDown(int floorNumber);
      int signalSameDir(int direction, int floorNumber);
      int avgWaiting(void);
};

#endif   // __FLOOR_H


// Copyright (c) 1990 by Tom Swan. All rights reserved
// Revision 1.00    Date: 09/18/1990   Time: 09:41 am
