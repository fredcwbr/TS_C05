// simulate.cpp -- Sample C++ simulation

#include <stream.hpp>
#include "action.h"

action theAction;

main()
{
   theAction.display();
   while (theAction.continues()) {
      theAction.perform();
      theAction.display();
   }
   theAction.results();
}


// Copyright (c) 1990 by Tom Swan. All rights reserved
// Revision 1.00    Date: 09/18/1990   Time: 09:47 am


