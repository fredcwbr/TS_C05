// building.cpp -- Building class module

// #include <conio.h>
// #include <disp.h>
#include <stdio.h>

extern int kbhit(); 

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "building.h"

#include "disp.h"
extern simWindow wndSim;

/* -- Return true if building simulation should continue. Adds
test for <Esc> keypress to action::continues(). */

int building::continues(void)
{
   if (kbhit())                  // If there is a keypress,
      if (getchar() == ESCKEY)     // And if it's the ESC key,
         setTime(0);             //  set time remaining to 0
   return action::continues();   // Return ancestor fn result
}

/* -- Perform the building's actions, that is, moving people in
elevators between floors. Each call to this function represents the
passage of one second (not necessarily in real time). */

void building::perform(void)
{
   thePersons.action();
   theElevators.action(theFloors, thePersons);
   reduceTime(1);          // One second passes
   totalTime++;            // Count seconds for time display
   // disp_move(24, 64);      // Display time remaining
   // disp_printf("%05d", getTime());
  
}

/* -- Updte the display, showing current status of floors and
elevators, plus the people waiting on floors or traveling in
elevators. Also show current simulation statistics and the elapsed
time on the bottom row. */

void building::display(void)
{
   long t;
   unsigned hours = 0;
   unsigned minutes = 0;
   unsigned seconds = 0;

   theFloors.showFloors(thePersons);
   theElevators.showElevators();
   avgWait = theFloors.avgWaiting();
   avgRide = theElevators.avgRiding();
   
   wndSim.disp_move(24, 1);
   wndSim.disp_printf(
    "%05u    %05u    %05u    %04u    %04u    %05u%5d%5d",
    totalPeople, inBuilding, leftBuilding, avgWait, 
    avgRide, tookStair, MAXELEVS, MAXFLOORS);
   wndSim.disp_move(24, 71);
   
   t = totalTime;
   if (t >= 3600) {
      hours = t / 3600;
      t -= (hours * 3600);
   }
   if (t >= 60) {
      minutes = t / 60;
      t -= (minutes * 60);
   }
   seconds = t;
   wndSim.disp_printf("%02d:%02d:%02d", hours, minutes, seconds);
}


// Copyright (c) 1990 by Tom Swan. All rights reserved
// Revision 1.00   Date: 09/18/1990   Time: 08:59 am
