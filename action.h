// action.h -- Action header file

#ifndef __ACTION_H
#define __ACTION_H      1     // Prevent multiple #includes

class action {
   private:
      long timeAtStart;       // Seconds for simulation
      long timeRemaining;     // Seconds remaining to end
   public:
      action();               // The "constructor"
      int continues(void);
	  int continues2(void);
      void setTime(int secs);
      int getTime(void);
	  void reduceTime(void);
      void reduceTime(int secs);
      void perform(void);
      void display(void);
      void results(void);
};

#endif   // __ACTION_H


// Copyright (c) 1990 by Tom Swan. All rights reserved
// Revision 1.00    Date: 09/18/1990   Time: 08:57 am
