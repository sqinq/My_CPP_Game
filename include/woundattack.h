#ifndef __WOUNDATTACK_H__
#define __WOUNDATTACK_H__
#include "potion.h"
#include <string>

class WoundAttack: public Potion {
    public: 
    //constructor
    WoundAttack();

    //getAtk(): returns the atk of p and minus 5
   //Void -> Int
   int getAtk();
};


#endif

