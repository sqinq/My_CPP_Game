#ifndef __WOUNDDEFENCE_H__
#define __WOUNDDEFENCE_H__
#include "potion.h"
#include <string>

class WoundDefence: public Potion {
    public:
    //constructor
    WoundDefence();

   //getDef(): returns the def of p and minus 5
   //Void -> Int
   int getDef();
};


#endif

