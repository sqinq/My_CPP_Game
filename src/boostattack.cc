#include "boostattack.h"
  
//see .h for documentation
  BoostAttack::BoostAttack() {
  setType("BA");
 }

//see .h for documentation
  int BoostAttack::getAtk() {
     if (getDrow())
         return p->getAtk() + 5*1.5;
     else
         return p->getAtk() + 5;
  }

