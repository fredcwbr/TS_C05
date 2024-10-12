// animal.cpp -- Inheritance example

#include <stream.hpp>
#include <string.h>
#include <stdlib.h>

#define FALSE     0
#define TRUE      1

class animal {
   private:
      char name[30];    // The animal's name
   public:
      animal(const char *s);
      const char *getName(void) { return name; }
};

class mammal : public animal {
   private:
      int offspring;     // Number of offspring
   public:
      mammal(const char *s, int nc);
      int numOffspring(void) { return offspring; }
};

class bird : public animal {
   private:
      int eggs;         // Average number of eggs
      int nesting;      // True if builds nest
   public:
      bird(const char *s, int ne, int nests);
      int getEggs(void) { return eggs; }
      const char *buildsNest()
       { if (nesting) return "True"; else return "False"; }
};

void showMammal(mammal &m);
void showBird(bird &b);

main()
{
   mammal homoSapiens("Homo Sapiens", 1);
   mammal gopher("Gopher", 9);
   mammal armidillo("Armidillo", 4);
   mammal houseMouse("House Mouse", 12);

   bird woodDuck("Wood Duck", 15, FALSE);
   bird sandhillCrane("Sandhill Crane", 2, TRUE);
   bird loon("Loon", 3, TRUE);

   cout << "\n\nMammals:";
   showMammal(homoSapiens);
   showMammal(gopher);
   showMammal(armidillo);
   showMammal(houseMouse);

   cout << "\n\nBirds:";
   showBird(woodDuck);
   showBird(sandhillCrane);
   showBird(loon);

   exit(0);
}

/* -- Display functions */

void showMammal(mammal &m)
{
   cout << "\nName ............... " << (m.getName());
   cout << "\n Avg offspring ..... " << (m.numOffspring());
}

void showBird(bird &b)
{
   cout << "\nName ............... " << (b.getName());
   cout << "\n Avg no. eggs ...... " << (b.getEggs());
   cout << "\n Builds a nest ..... " << (b.buildsNest());
}

/* -- Class constructors */

animal::animal(const char *s)
{ 
   strncpy(name, s, 29);
}

mammal::mammal(const char *s, int nc) : (s)
{
   offspring = nc;
}

bird::bird(const char *s, int ne, int nests) : (s)
{
   eggs = ne;
   nesting = nests;
}


// Copyright (c) 1990 by Tom Swan. All rights reserved
// Revision 1.00    Date: 09/24/1990   Time: 10:04 am


