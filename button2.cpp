// button2.cpp -- Inline member functions

#include <iostream>
using namespace std;

#include "action.h"

class button {
   private:
      int isUp;
   public:
      void push(int upDown) { isUp = upDown; }
      int state(void) { return isUp; }
	  void toggle(void) {  isUp = ( isUp ? 0 : 1 ); }
};

#ifdef __TEST_BUTTON

int main()
{
   button myButton;
   action Act;

   while( Act.continues2() ) {
	    // myButton.push(1);
		// cout << "\nButton state = " << myButton.state();
		// myButton.push(0);
		// cout << "\nButton state = " << myButton.state();
		//	 for( int i = 0 ; i < 4 ; ++i ) {
		myButton.toggle();
		cout << "\nButton state = " << myButton.state();
		// }
   }
   Act.results();
}


// Copyright (c) 1990 by Tom Swan. All rights reserved
// Revision 1.00    Date: 09/19/1990   Time: 07:40 am

#endif