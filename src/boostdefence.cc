#include "boostdefence.h"
  
//see .h for documentation
  BoostDefence::BoostDefence() {
  setType("BD");
  }

//see .h for documentation
  int BoostDefence::getDef(){
     if (getDrow())
         return p->getDef() + 5*1.5;
     else
         return p->getDef()+5;
  }

