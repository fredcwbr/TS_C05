// action.cpp -- Action class module


#include <iostream>
// #include <conio>

using namespace std;
#include "action.h"


/* -- The action's "constructor." Runs when an action object (in
other words, a variable of type action) comes into being. */

action::action()
{
   timeAtStart = 6000;           // Seconds to run simulation
   timeRemaining = timeAtStart;  // Time remaining to end
}

/* -- Return TRUE if time remaining is greater than 0. The
program's main loop continues the action until this function
returns FALSE. */

int action::continues(void)
{
   return timeRemaining > 0;
}


int action::continues2(void)
{
   display();
   --timeRemaining;
   return timeRemaining > 0;
}

/* -- Set time counters to this many seconds. */

void action::setTime(int secs)
{
   timeAtStart = secs;
   timeRemaining = timeAtStart;
}

/* -- Return time remaining for simulation. */

int action::getTime(void)
{
   return timeRemaining;
}

void action::reduceTime(void)
{
   --timeRemaining;
}

/* -- Reduce time remaining for simulation. Minimum resolution,
or "granularity," is one second. Can't reduce time to < 0. */

void action::reduceTime(int secs)
{
   if (secs > timeRemaining)
      timeRemaining = 0;
   else
      timeRemaining -= secs;
}

/* -- Perform the action. In this case, the function is just a shell.
Later, we'll add programming to simulate a real action. */

void action::perform(void)
{
   cout << "\n\nAction! (Press <Space> to continue...";
   // while (getch() != ' ') ;   // Pause for <Space> keypress
   reduceTime(900);           // Decrease time remaining 900 secs
}

/* -- Display the current action status. Calling display() is the
only way a statement outside of the action object can access the
timeRemaining value. */

void action::display(void)
{
   cout << "\n\nTime remaining: " << timeRemaining << " sec.";
}

/* -- Display final results. As in action::display(), calling
results() is the only way a statement outside of the action object
can access the private data fields in the action class. */

void action::results(void)
{
   cout << "\n\nSimulation results";
   cout << "\n==================";
   cout << "\nTime at start .. : " << timeAtStart << " sec.";
   cout << "\nTime at end .... : " << timeRemaining << " sec.\n";
}


// Copyright (c) 1990 by Tom Swan. All rights reserved
// Revision 1.00    Date: 09/18/1990   Time: 08:54 am
