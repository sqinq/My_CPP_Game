#ifndef __BOOSTATTACK_H__
#define __BOOSTATTACK_H__
#include "potion.h"
#include <string>
  
  class BoostAttack: public Potion {
  public:
    //constructor, sets the Hp, Atk, and Def value to their default values
    BoostAttack();
    
    //getAtl(): returns the attack of the character it decorates and add 5 to the original value
    //Void -> Int
    int getAtk();
  };


#endif

