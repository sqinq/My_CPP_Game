#include "wounddefence.h"

//see .h for documentation
WoundDefence::WoundDefence() {
    setType("WD");
}

//see .h for documentation
int WoundDefence::getDef(){
     if (getDrow())
         return p->getDef() - 5*1.5;
     else
          return p->getDef()-5;
}

