// button.cpp -- Creating a class

#include <iostream>

class button {
   private:
      int isUp;
   public:
      void push(int upDown);
      int state(void);
};

int  main()
{
   button myButton;

   myButton.push(1);
   std::cout << "\nButton state = " << myButton.state();
   myButton.push(0);
   std::cout << "\nButton state = " << myButton.state();
}

void button::push(int upDown)
{
   isUp = upDown;
}

int button::state(void)
{
   return isUp;
}


// Copyright (c) 1990 by Tom Swan. All rights reserved
// Revision 1.00    Date: 09/18/1990   Time: 04:20 pm


