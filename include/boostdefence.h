#ifndef __BOOSTDEFENCE_H__
#define __BOOSTDEFENCE_H__
#include "potion.h"
#include <string>
  
  class BoostDefence: public Potion {
  public:
    //constructor, sets the Hp, Atk, and Def value to their default values
    BoostDefence();
    //getAtl(): returns the defence of the character it decorates and add 5 to the original value
    //Void -> Int
    int getDef();
  };


#endif

