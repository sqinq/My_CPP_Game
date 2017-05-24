#include "woundattack.h"

//see .h for documentation
WoundAttack::WoundAttack() {
    setType("WA");
}

//see .h for documentation
int WoundAttack::getAtk(){
     if (getDrow())
         return p->getAtk() - 5*1.5;
     else
        return p->getAtk()-5;
}

